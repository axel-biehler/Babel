/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#include "LibHandler.hpp"
#include "../Audio/Portaudio.hpp"
#include "../Networking/ClientUdp.hpp"

Babel::Management::LibHandler::LibHandler() {
    _libAudio = std::make_shared<Babel::Audio::PortAudio>();
    _libCompressor = std::make_shared<Babel::Compression::Opus>();
    _libNetwork = std::make_shared<Babel::Networking::ClientUDP>(this);
}

Babel::Management::LibHandler::~LibHandler() {
}

void Babel::Management::LibHandler::send(std::queue<std::vector<float>> &samples) {
    //std::cout << "sending..." << std::endl;
}

std::shared_ptr<Babel::Audio::IAudio> Babel::Management::LibHandler::get_lib_audio() const {
    return _libAudio;
}

std::shared_ptr<Babel::Compression::Opus> Babel::Management::LibHandler::get_lib_compressor() const {
    return _libCompressor;
}

std::shared_ptr<Babel::Networking::IClient> Babel::Management::LibHandler::get_lib_network() const {
    return _libNetwork;
}
