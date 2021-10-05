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
#define SAMPLE_RATE         48000
#define FRAMES_PER_BUFFER   480

namespace Babel::Audio {
    class PortAudio {
    public:
        PortAudio(void (*_sender)(std::queue<std::vector<float>>));
        ~PortAudio();
        void startRecording();
        void stopRecording();
        void startPlaying();
        void stopPlaying();
        void send_audio(std::queue<std::vector<float>> samples);
        std::queue<std::vector<float>> get_audio_input();
        std::queue<std::vector<float>> get_audio_output();
        void set_audio_input(std::queue<std::vector<float>> &samples);
        void set_audio_output(std::queue<std::vector<float>> &samples);
    private:
        void (*_sender)(std::queue<std::vector<float>>);
        PaStreamParameters  _inputParameters;
        PaStreamParameters  _outputParameters;
        PaStream *          _stream;
        bool                _is_initialized = false;
        bool                _recording = false;
        std::queue<std::vector<float>> _input_sample;
        std::queue<std::vector<float>> _output_sample;
        static int recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
        static int playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

    };
}

#endif //BABEL_PORTAUDIO_HPP
