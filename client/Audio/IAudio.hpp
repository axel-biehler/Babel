/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#ifndef BABEL_IAUDIO_HPP
#define BABEL_IAUDIO_HPP

namespace Babel::Management {
    class LibHandler;
}

namespace Babel::Networking {
    class ClientUDP;
}

namespace Babel::Audio {
    class IAudio {
    public:
        virtual void startRecording() = 0;
        virtual void stopRecording() = 0;
        virtual void startPlaying() = 0;
        virtual void stopPlaying() = 0;
        virtual void send_audio() = 0;
        virtual void add_sample(std::vector<float> &sample) = 0;
        virtual void set_sender(Babel::Networking::ClientUDP *sender) = 0;
    };
}

#endif //BABEL_IAUDIO_HPP
