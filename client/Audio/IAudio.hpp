/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#ifndef BABEL_IAUDIO_HPP
#define BABEL_IAUDIO_HPP

namespace Babel::Audio {
    class IAudio {
    public:

        virtual void startRecording() = 0;
        virtual void stopRecording() = 0;
        virtual void startPlaying() = 0;
        virtual void stopPlaying() = 0;
        virtual void send_audio(std::queue<std::vector<float>> samples) = 0;
    };
}

#endif //BABEL_IAUDIO_HPP
