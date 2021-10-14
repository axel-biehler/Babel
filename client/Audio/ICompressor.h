/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#ifndef BABEL_ICOMPRESSOR_H
#define BABEL_ICOMPRESSOR_H

namespace Babel::Compression {
    class ICompressor {
    public:
        virtual std::vector<unsigned char> encode(std::vector<float> audio_input) = 0;
        virtual std::vector<float> decode(std::vector<unsigned char> audio_input) = 0;
    };
}

#endif //BABEL_ICOMPRESSOR_H