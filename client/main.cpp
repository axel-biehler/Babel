#include <QApplication>
#include <QWindow>
#include <QLabel>
#include <iostream>
#include "audio/Portaudio.hpp"
#include "audio/Opus.hpp"

void test_function(std::queue<std::vector<float>> samples)
{
    (void)samples;
}

int main(int ac, char **av)
{
    QApplication app{ac, av};
    Babel::Audio::PortAudio audioHandler = Babel::Audio::PortAudio(test_function);
    Babel::Compression::Opus compressor = Babel::Compression::Opus();
    std::queue<std::vector<float>> samples;
    std::queue<std::vector<unsigned char>> compressed_samples;

    audioHandler.startRecording();
    Pa_Sleep(5000);
    audioHandler.stopRecording();
    std::cout << "compressing..." << std::endl;
    samples = audioHandler.get_audio_input();
    for (; !samples.empty();) {
        compressed_samples.push(compressor.encode(samples.front()));
        samples.pop();
    }
    std::cout << "decompressing..." << std::endl;
    for (; !compressed_samples.empty();) {
        samples.push(compressor.decode(compressed_samples.front()));
        compressed_samples.pop();
    }
    audioHandler.set_audio_output(samples);
    std::cout << "playing" << std::endl;
    audioHandler.startPlaying();
    Pa_Sleep(5000);
    audioHandler.stopPlaying();
    //QLabel label{};
    //label.setText("How are you?");
    //label.show();
    return 0;//app.exec();
}