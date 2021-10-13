# Babel - VOIP software
## EPITECH Strasbourg - 2024

- Alexandre Sauner
- Axel Biehler
- Maxime Frechard
- Arthur Robine

## What is it?
Babel is a VOIP software project. The server and client are made in C++ using the following libraires:
- qt
- portaudio
- opus
- asio
- sqlite3

The implemented features are:
- Login/Register
- Friends management
- VOIP calls compressed with OPUS
- Messages

## Setup
- `mkdir build && cd build`
- `conan install ..`
- `cmake ..`
- `make`

## Usage
- Server: `./babel_server {port}`
- Client: `./babel_client`
