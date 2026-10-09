//
//  TestHelpers.h
//  Outils partagés par les tests unitaires MoOS
//

#ifndef MoOS_TestHelpers_h
#define MoOS_TestHelpers_h

#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>

#include "OutputsHandler.h"

// Sortie qui ne fait qu'enregistrer ce que Grid::compute() lui envoie
class RecordingOutput : public OutputsHandler {
public:
    explicit RecordingOutput(const char* n) : OutputsHandler(n, 0, 1) {}
    bool sendData() override {
        mSent++;
        mLast = mValueBeforeSending;
        return true;
    }
    void setParameters(std::vector<std::string>) override {}
    std::atomic<int> mSent{0};
    std::atomic<float> mLast{0.0f};
};

// Répertoire temporaire propre au process de test
inline std::string tempPath(const std::string& name) {
    const char* tmp = getenv("TMPDIR");
    std::string dir = tmp ? tmp : "/tmp";
    if (!dir.empty() && dir.back() != '/') dir += '/';
    return dir + "moos_test_" + std::to_string(getpid()) + "_" + name;
}

template <class T> void writeLE(std::ofstream& f, T v) {
    f.write(reinterpret_cast<const char*>(&v), sizeof(T));
}

// Écrit un WAV PCM à en-tête canonique (44 octets) contenant une sinusoïde
inline std::string writeWav(const std::string& name, int numSamples, uint16_t bitsPerSample = 16,
                            uint16_t channels = 1, uint32_t rate = 44100, double freq = 440.0) {
    std::string path = tempPath(name);
    std::ofstream f(path, std::ios::binary);
    uint32_t bytesPerSample = bitsPerSample / 8;
    uint32_t dataSize = numSamples * bytesPerSample * channels;
    f.write("RIFF", 4); writeLE<uint32_t>(f, 36 + dataSize); f.write("WAVE", 4);
    f.write("fmt ", 4); writeLE<uint32_t>(f, 16); writeLE<uint16_t>(f, 1); writeLE<uint16_t>(f, channels);
    writeLE<uint32_t>(f, rate); writeLE<uint32_t>(f, rate * bytesPerSample * channels);
    writeLE<uint16_t>(f, bytesPerSample * channels); writeLE<uint16_t>(f, bitsPerSample);
    f.write("data", 4); writeLE<uint32_t>(f, dataSize);
    for (int i = 0; i < numSamples; i++) {
        double s = 0.8 * std::sin(2 * M_PI * freq * i / rate);
        for (int c = 0; c < channels; c++) {
            if (bitsPerSample == 16) writeLE<int16_t>(f, (int16_t)(s * 32767));
            else writeLE<uint8_t>(f, (uint8_t)(128 + s * 127));
        }
    }
    return path;
}

// Attend qu'une condition devienne vraie (polling), au plus timeoutMs
template <class F> bool waitFor(F cond, int timeoutMs) {
    auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeoutMs);
    while (std::chrono::steady_clock::now() < end) {
        if (cond()) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return cond();
}

#endif
