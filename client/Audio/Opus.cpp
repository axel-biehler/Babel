/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#include <QtEndian>
#include "Opus.hpp"

#define STEREO              2
#define SAMPLE_RATE         48000
#define FRAMES_PER_BUFFER   480

Babel::Compression::Opus::Opus() {
    int error;

    _encoder = opus_encoder_create(SAMPLE_RATE, STEREO, OPUS_APPLICATION_VOIP, &error);
    if (error) {
        exit(84);
        //TODO: throw error
    }
    _decoder = opus_decoder_create(SAMPLE_RATE, STEREO, &error);
    if (error) {
        exit(84);
        //TODO: throw error
    }
}

Babel::Compression::Opus::~Opus() {
    opus_encoder_destroy(_encoder);
    opus_decoder_destroy(_decoder);
}

std::vector<unsigned char> Babel::Compression::Opus::encode(std::vector<float> audio_input) {
    std::vector<unsigned char> encoded_buff;

    if (audio_input.empty()) {
        encoded_buff.resize(0);
        return encoded_buff;
    }
    encoded_buff.resize(audio_input.size() * 2);
    opus_int32 nb_encoded = opus_encode_float(_encoder, audio_input.data(), FRAMES_PER_BUFFER, encoded_buff.data(), static_cast<int>(audio_input.size()) * 2);
    if (nb_encoded)
        encoded_buff.resize(nb_encoded);
    return encoded_buff;
}

std::vector<float> Babel::Compression::Opus::decode(std::vector<unsigned char> encoded) {
    std::vector<float> decoded_buff;

    if (encoded.empty()) {
        decoded_buff.resize(0);
        return decoded_buff;
    }
    decoded_buff.resize(FRAMES_PER_BUFFER * STEREO);
    opus_int32 nb_decoded = opus_decode_float(_decoder, encoded.data(), static_cast<int>(encoded.size()), decoded_buff.data(), 480, 0) * 2;
    decoded_buff.resize(nb_decoded);
    return decoded_buff;
}