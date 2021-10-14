/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/



#ifndef BABEL_PORTAUDIO_HPP
#define BABEL_PORTAUDIO_HPP

#include <queue>
#include <memory>
//#include <Networking/ClientUdp.hpp>
#include "portaudio.h"
#include "IAudio.hpp"

#define STEREO              2
#define SAMPLE_RATE         48000
#define FRAMES_PER_BUFFER   480

namespace Babel::Networking {
    class ClientUDP;
}

namespace Babel::Audio {
    class PortAudio : public IAudio {
    public:
        PortAudio();
        ~PortAudio();
        void startRecording() override;
        void stopRecording() override;
        void startPlaying() override;
        void stopPlaying() override;
        void add_sample(std::vector<float> &sample) override;
        void send_audio() override;
        std::queue<std::vector<float>> get_audio_input();
        std::queue<std::vector<float>> get_audio_output();
        void set_audio_input(std::queue<std::vector<float>> &samples);
        void set_audio_output(std::queue<std::vector<float>> &samples);
        void set_sender(Babel::Networking::ClientUDP *sender) override;
    private:
        Babel::Networking::ClientUDP *_sender;
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
