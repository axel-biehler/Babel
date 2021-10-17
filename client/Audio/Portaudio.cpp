/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#include <cstdlib>
#include <iostream>
#include <utility>
#include "Portaudio.hpp"
#include "Networking/Packets/PacketAudio.hpp"
#include "Networking/ClientUdp.hpp"

Babel::Audio::PortAudio::PortAudio(): IAudio() {
    PaError err = Pa_Initialize();

    _sender = nullptr;
    if (err != paNoError) {
        std::cerr << "PortAudio initialisation failed." << std::endl;
        exit(84);
    }
    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice) {
        std::cerr << "No default input device." << std::endl;
        exit(84);
    }
    _inputParameters.channelCount = STEREO;
    _inputParameters.sampleFormat = paFloat32;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = nullptr;

    _outputParameters.device = Pa_GetDefaultOutputDevice();
    if (_outputParameters.device == paNoDevice) {
        std::cerr << "No default output device." << std::endl;
        exit(84);
    }
    _outputParameters.channelCount = STEREO;
    _outputParameters.sampleFormat = paFloat32;
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo(_outputParameters.device)->defaultLowOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = nullptr;
    _is_initialized = true;
}

Babel::Audio::PortAudio::~PortAudio() {
    Pa_Terminate();
}

void Babel::Audio::PortAudio::startRecording() {
    if (!_is_initialized)
        exit(84);
    PaError err = Pa_OpenStream(&_stream, &_inputParameters, &_outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, PortAudio::recordCallback, this);
    if (err != paNoError)
        exit(84);
    err = Pa_StartStream(_stream);
    if (err != paNoError)
        exit(84);
    _recording = true;
}

void Babel::Audio::PortAudio::stopRecording() {
    if (!_is_initialized || !_recording) {
        exit(84);
    }
    PaError err = Pa_StopStream(_stream);
    _recording = false;
    if (err != paNoError)
        exit(84);
}

void Babel::Audio::PortAudio::startPlaying() {
    PaError err = Pa_OpenStream(&_stream, &_inputParameters, &_outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, PortAudio::playCallback, this);
    if (err != paNoError)
        exit(84);
    err = Pa_StartStream(_stream);
    if (err != paNoError)
        exit(84);
}

void Babel::Audio::PortAudio::stopPlaying() {
    PaError err = Pa_CloseStream(_stream);
    if (err != paNoError)
        exit(84);
}

void Babel::Audio::PortAudio::add_sample(std::vector<float> &sample) {
    _output_sample.push(sample);
}

int Babel::Audio::PortAudio::recordCallback(const void *inputBuffer, void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags , void *userData) {
    auto *audioHandler = (PortAudio *)userData;
    std::vector<float> newAudio = std::vector<float>();

    newAudio.assign((float *)inputBuffer, (float *)inputBuffer + framesPerBuffer * STEREO);
    audioHandler->_input_sample.push(newAudio);
    audioHandler->send_audio();
    return 0;
}

int Babel::Audio::PortAudio::playCallback(const void *, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags , void *userData) {
    auto *audioHandler = (PortAudio *)userData;
    auto *output = (float *)outputBuffer;

    if (audioHandler->_output_sample.empty())
        return 0;
    std::vector<float> playAudio = audioHandler->_output_sample.front();
    auto it = playAudio.begin();
    audioHandler->_output_sample.pop();
    for (int i = 0; i < framesPerBuffer * STEREO; i++) {
        if (it != playAudio.end())
            *(output++) = *(it++);
        else
            *(output++) = 0;
    }
    return 0;
}

std::queue<std::vector<float>> Babel::Audio::PortAudio::get_audio_input() {
    return _input_sample;
}

std::queue<std::vector<float>> Babel::Audio::PortAudio::get_audio_output() {
    return _output_sample;
}

void Babel::Audio::PortAudio::set_audio_input(std::queue<std::vector<float>> &samples) {
    _input_sample = samples;
}

void Babel::Audio::PortAudio::set_audio_output(std::queue<std::vector<float>> &samples) {
    _output_sample = samples;
}

void Babel::Audio::PortAudio::send_audio() {
    while (!_input_sample.empty()) {
        _sender->send(_input_sample.front());
        _input_sample.pop();
    }
}

void Babel::Audio::PortAudio::set_sender(Babel::Networking::ClientUDP *sender) {
    _sender = sender;
}