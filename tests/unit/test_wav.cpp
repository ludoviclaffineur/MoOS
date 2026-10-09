//
//  test_wav.cpp
//  ReadWavFileHandler + FFTprocessing : chargement validé, fenêtre passée en float**,
//  lecture en boucle.
//
//  Les threads de lecture tournent indéfiniment (pas d'arrêt dans ReadWavFileHandler) :
//  les grilles sont donc volontairement jamais libérées.
//

#define BOOST_TEST_MODULE WavTests
#include <boost/test/included/unit_test.hpp>

#include "ReadWavFileHandler.h"
#include "Grid.h"
#include "TestHelpers.h"

static float sumOfInputs(Grid* g) {
    std::lock_guard<std::recursive_mutex> lock(g->getMutex());
    float sum = 0;
    for (Input* i : *g->getInputs()) sum += i->getValue();
    return sum;
}

BOOST_AUTO_TEST_CASE(fft_registers_one_input_per_bin) {
    Grid* g = new Grid();
    std::string path = writeWav("bins.wav", 44100);
    ReadWavFileHandler wav(g, path);
    BOOST_TEST(g->getNbrInputs() == 512u);           // fenêtre de 1024 -> 512 bins
    BOOST_TEST(g->getInputWithName("0") != (Input*)NULL);
    BOOST_TEST(g->getInputWithName("43") != (Input*)NULL);  // 1 * 44100/1024
    unlink(path.c_str());
}

// Régression : la fenêtre était passée en float* alors que FFTprocessing attend un
// float** -> les échantillons étaient lus comme une adresse (segfault)
BOOST_AUTO_TEST_CASE(valid_file_feeds_the_fft_inputs) {
    Grid* g = new Grid();
    std::string path = writeWav("valid.wav", 44100, 16, 1, 44100, 440.0);
    ReadWavFileHandler* wav = new ReadWavFileHandler(g, path);
    wav->init();
    BOOST_TEST(waitFor([&] { return sumOfInputs(g) > 0.0f; }, 3000));
    // Le bin le plus proche de 440 Hz (10 * 43.07 = 430 Hz) domine un bin lointain
    BOOST_TEST(waitFor([&] {
        return g->getInputWithName("430")->getValue() > g->getInputWithName("4306")->getValue();
    }, 3000));
}

BOOST_AUTO_TEST_CASE(stereo_file_is_accepted) {
    Grid* g = new Grid();
    std::string path = writeWav("stereo.wav", 44100, 16, 2);
    ReadWavFileHandler* wav = new ReadWavFileHandler(g, path);
    wav->init();
    BOOST_TEST(waitFor([&] { return sumOfInputs(g) > 0.0f; }, 3000));
}

// Régression : loadWave() échouait en silence et le thread lisait des données non initialisées
BOOST_AUTO_TEST_CASE(missing_file_does_not_start_playback) {
    Grid* g = new Grid();
    ReadWavFileHandler* wav = new ReadWavFileHandler(g, tempPath("does_not_exist.wav"));
    BOOST_TEST(g->getNbrInputs() == 512u);           // inputs créés avec 44100 Hz par défaut
    BOOST_CHECK_NO_THROW(wav->init());
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    BOOST_TEST(sumOfInputs(g) == 0.0f);
}

// Régression : un fichier de moins d'une fenêtre faisait récurser WavProcess() sans fin
BOOST_AUTO_TEST_CASE(too_short_file_is_rejected) {
    Grid* g = new Grid();
    std::string path = writeWav("short.wav", 500);
    ReadWavFileHandler* wav = new ReadWavFileHandler(g, path);
    wav->init();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    BOOST_TEST(sumOfInputs(g) == 0.0f);
    unlink(path.c_str());
}

BOOST_AUTO_TEST_CASE(unsupported_format_is_rejected) {
    Grid* g = new Grid();
    std::string path = writeWav("8bit.wav", 44100, 8);
    ReadWavFileHandler* wav = new ReadWavFileHandler(g, path);
    wav->init();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    BOOST_TEST(sumOfInputs(g) == 0.0f);
    unlink(path.c_str());
}

// Régression : la fin de fichier relançait WavProcess() par récursion (pile qui grossit).
// Un fichier de 1 fenêtre est relu ~43 fois/s : la lecture doit continuer sans planter.
BOOST_AUTO_TEST_CASE(playback_loops_over_the_file) {
    Grid* g = new Grid();
    std::string path = writeWav("loop.wav", 2048);
    RecordingOutput* out = new RecordingOutput("out");
    ReadWavFileHandler* wav = new ReadWavFileHandler(g, path);
    g->addOutput(out);
    g->switchActive();
    wav->init();
    // 2 fenêtres par passage, ~21 passages/s : > 40 compute() = au moins 20 relectures
    BOOST_TEST(waitFor([&] { return out->mSent.load() > 40; }, 4000));
}
