/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#ifndef BABEL_OPUS_HPP
#define BABEL_OPUS_HPP

#include <cstdlib>
#include "opus.h"

namespace Babel::Compression {
    class Opus {
    public:
        Opus();
        ~Opus();
        std::vector<unsigned char> encode(std::vector<float> audio_input);
        std::vector<float> decode(std::vector<unsigned char> audio_input);
    private:
        OpusEncoder *_encoder;
        OpusDecoder *_decoder;
    };
}

#endif //BABEL_OPUS_HPP
