/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/


#include "LibHandler.hpp"
#include "../Networking/ClientUdp.hpp"

Babel::Management::LibHandler::LibHandler() {
    _libAudio = std::make_shared<Babel::Audio::PortAudio>();
    _libCompressor = std::make_shared<Babel::Compression::Opus>();
}

Babel::Management::LibHandler::~LibHandler() {
}

std::shared_ptr<Babel::Audio::PortAudio> Babel::Management::LibHandler::get_lib_audio() const {
    return _libAudio;
}

std::shared_ptr<Babel::Compression::Opus> Babel::Management::LibHandler::get_lib_compressor() const {
    return _libCompressor;
}

void Babel::Management::LibHandler::start() {
    _libAudio->startRecording();
    _libAudio->startPlaying();
}

void Babel::Management::LibHandler::stop() {
    _libAudio->stopRecording();
    _libAudio->stopPlaying();
}