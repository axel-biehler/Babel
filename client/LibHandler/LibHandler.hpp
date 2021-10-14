/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#ifndef BABEL_LIBHANDLER_HPP
#define BABEL_LIBHANDLER_HPP

#include <queue>
#include <memory>
#include "Audio/Portaudio.hpp"
#include "Audio/Opus.hpp"

namespace Babel::Management {
    class LibHandler {
    public:
        LibHandler();
        ~LibHandler();
        void send(std::queue<std::vector<float>> &samples);
        void start();
        void stop();
        [[nodiscard]] std::shared_ptr<Babel::Audio::PortAudio> get_lib_audio() const;
        [[nodiscard]] std::shared_ptr<Babel::Compression::Opus> get_lib_compressor() const;
    private:
        std::shared_ptr<Babel::Audio::PortAudio>    _libAudio;
        std::shared_ptr<Babel::Compression::Opus>   _libCompressor;
    };
}

#endif //BABEL_LIBHANDLER_HPP
