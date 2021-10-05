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

Babel::Audio::PortAudio::PortAudio(void (*sender)(std::queue<std::vector<float>>)) {
    PaError err = Pa_Initialize();

    if (sender)
        _sender = sender;
    else {
        exit(84);
        //TODO: throw error
    }
    if (err != paNoError) {
        std::cerr << "PortAudio initialisation failed." << std::endl;
        exit(84);
        //TODO: throw error
    }
    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice) {
        std::cerr << "No default input device." << std::endl;
        exit(84);
        //TODO: throw error
    }
    _inputParameters.channelCount = STEREO;
    _inputParameters.sampleFormat = paFloat32;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = nullptr;

    _outputParameters.device = Pa_GetDefaultOutputDevice();
    if (_outputParameters.device == paNoDevice) {
        std::cerr << "No default output device." << std::endl;
        exit(84);
        //TODO: throw error
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
    if (!_is_initialized) {
        exit(84);
        //TODO: throw error
    }
    PaError err = Pa_OpenStream(&_stream, &_inputParameters, nullptr, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, PortAudio::recordCallback, this);
    if (err != paNoError) {
        exit(84);
       //TODO: throw error
    }
    err = Pa_StartStream(_stream);
    if (err != paNoError) {
        exit(84);
        //TODO: throw error
    }
    _recording = true;
}

void Babel::Audio::PortAudio::stopRecording() {
    if (!_is_initialized || !_recording) {
        exit(84);
        //TODO: throw error
    }
    PaError err = Pa_StopStream(_stream);
    if (err != paNoError) {
        exit(84);
        //TODO: throw error
    }
}

void Babel::Audio::PortAudio::startPlaying() {
    PaError err = Pa_OpenStream(&_stream, nullptr, &_outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, playCallback, this);
    if (err != paNoError) {
        exit(84);
        //TODO: throw error
    }
    err = Pa_StartStream(_stream);
    if (err != paNoError) {
        exit(84);
        //TODO: throw error
    }
}

void Babel::Audio::PortAudio::stopPlaying() {
    PaError err = Pa_CloseStream(_stream);
    if (err != paNoError) {
        exit(84);
        //TODO: throw error
    }
}

int Babel::Audio::PortAudio::recordCallback(const void *inputBuffer, void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags , void *userData) {
    auto *audioHandler = (PortAudio *)userData;
    std::vector<float> newAudio = std::vector<float>();

    newAudio.assign((float *)inputBuffer, (float *)inputBuffer + framesPerBuffer * STEREO);
    audioHandler->_input_sample.push(newAudio);
    audioHandler->send_audio(audioHandler->get_audio_input());
    return 0;
}

int Babel::Audio::PortAudio::playCallback(const void *, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags , void *userData) {
    auto *audioHandler = (PortAudio *)userData;
    auto *output = (float *)outputBuffer;

    if (audioHandler->_output_sample.empty())
        return 1;
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

void Babel::Audio::PortAudio::send_audio(std::queue<std::vector<float>> samples) {
    _sender(std::move(samples));
}
