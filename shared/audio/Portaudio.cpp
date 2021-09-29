/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "Portaudio.hpp"

PortAudio::PortAudio() {
    PaError err = Pa_Initialize();

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

PortAudio::~PortAudio() {
    Pa_Terminate();
}

void PortAudio::startRecording() {
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

void PortAudio::stopRecording() {
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

void PortAudio::startPlaying() {
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

void PortAudio::stopPlaying() {
    PaError err = Pa_CloseStream(_stream);
    if (err != paNoError) {
        exit(84);
        //TODO: throw error
    }
}

int PortAudio::recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    auto *audioHandler = (PortAudio *)userData;
    std::vector<float> newAudio = std::vector<float>();

    newAudio.assign((float *)inputBuffer, (float *)inputBuffer + framesPerBuffer * STEREO);
    audioHandler->_audio_samples.push(newAudio);
    return 0;
}

int PortAudio::playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    auto *audioHandler = (PortAudio *)userData;
    auto *output = (float *)outputBuffer;

    if (audioHandler->_audio_samples.empty())
        return 1;
    std::vector<float> playAudio = audioHandler->_audio_samples.front();
    auto it = playAudio.begin();
    audioHandler->_audio_samples.pop();
    for (int i = 0; i < framesPerBuffer * STEREO; i++) {
        if (it != playAudio.end())
            *(output++) = *(it++);
        else
            *(output++) = 0;
    }
    return 0;
}

std::queue<std::vector<float>> PortAudio::get_audio_samples() {
    return _audio_samples;
}

void PortAudio::set_audio_samples(std::queue<std::vector<float>> samples) {
    _audio_samples = samples;
}
