/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#ifndef BABEL_PORTAUDIO_HPP
#define BABEL_PORTAUDIO_HPP

#include <queue>
#include "portaudio.h"

#define STEREO              2
#define SAMPLE_RATE         24000
#define FRAMES_PER_BUFFER   480

class PortAudio {
public:
    PortAudio();
    ~PortAudio();
    void startRecording();
    void stopRecording();
    void startPlaying();
    void stopPlaying();
    std::queue<std::vector<float>> get_audio_samples();
    void set_audio_samples(std::queue<std::vector<float>> samples);
private:
    PaStreamParameters  _inputParameters;
    PaStreamParameters  _outputParameters;
    PaStream *          _stream;
    bool                _is_initialized = false;
    bool                _recording = false;
    std::queue<std::vector<float>> _audio_samples;
    static int recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
    static int playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

};

#endif //BABEL_PORTAUDIO_HPP
