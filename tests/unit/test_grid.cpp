//
//  test_grid.cpp
//  Grid : recherches, création des cellules, compute(), accès concurrents
//

#define BOOST_TEST_MODULE GridTests
#include <boost/test/included/unit_test.hpp>

#include "Grid.h"
#include "Converter.h"
#include "TestHelpers.h"

static void addInputs(Grid& g, int n) {
    for (int i = 0; i < n; i++) {
        std::string name = "in" + std::to_string(i);
        g.addInput(name.c_str(), 0, 1, -1, 0, Converter::LINEAR);
    }
}

BOOST_AUTO_TEST_CASE(lookups_return_null_when_missing) {
    Grid g;
    addInputs(g, 2);
    g.addOutput(new RecordingOutput("out"));
    BOOST_TEST(g.getInputWithName("nope") == (Input*)NULL);
    BOOST_TEST(g.getOutputWithName("nope") == (OutputsHandler*)NULL);
    BOOST_TEST(g.getOutputWithId(999) == (OutputsHandler*)NULL);
    BOOST_TEST(g.getCellWithName("nope", "out") == (Cell*)NULL);
    BOOST_TEST(g.getCellWithName("in0", "nope") == (Cell*)NULL);
    BOOST_TEST(g.getCellWithName("in1", "out") != (Cell*)NULL);
}

BOOST_AUTO_TEST_CASE(add_output_creates_one_cell_per_existing_input) {
    Grid g;
    addInputs(g, 3);
    g.addOutput(new RecordingOutput("a"));
    g.addOutput(new RecordingOutput("b"));
    BOOST_TEST(g.getNbrInputs() == 3u);
    BOOST_TEST(g.getNbrOutputs() == 2u);
    BOOST_TEST(g.getCells()->size() == 6u);
    // Les ids sont attribués dans l'ordre d'ajout
    BOOST_TEST(g.getOutputWithId(0)->compareName("a"));
    BOOST_TEST(g.getOutputWithId(1)->compareName("b"));
}

BOOST_AUTO_TEST_CASE(remove_output_removes_its_cells) {
    Grid g;
    addInputs(g, 2);
    g.addOutput(new RecordingOutput("a"));
    g.addOutput(new RecordingOutput("b"));
    g.removeOutput(0);
    BOOST_TEST(g.getNbrOutputs() == 1u);
    BOOST_TEST(g.getCells()->size() == 2u);
    BOOST_TEST(g.getCellWithName("in0", "a") == (Cell*)NULL);
}

BOOST_AUTO_TEST_CASE(compute_does_nothing_while_inactive) {
    Grid g;
    addInputs(g, 1);
    RecordingOutput* out = new RecordingOutput("out");
    g.addOutput(out);
    g.compute();
    BOOST_TEST(out->mSent.load() == 0);
}

BOOST_AUTO_TEST_CASE(compute_sends_weighted_sum_when_active) {
    Grid g;
    addInputs(g, 2);
    RecordingOutput* out = new RecordingOutput("out");
    g.addOutput(out);
    g.getCellWithName("in0", "out")->setCoeff(0.5);
    g.getCellWithName("in1", "out")->setCoeff(0.25);
    g.getInputWithName("in0")->setValue(1.0);
    g.getInputWithName("in1")->setValue(1.0);
    g.switchActive();
    g.compute();
    BOOST_TEST(out->mSent.load() == 1);
    BOOST_TEST(out->mLast.load() == 0.75f, boost::test_tools::tolerance(0.01f));
}

BOOST_AUTO_TEST_CASE(cell_coefficients_are_clamped_to_unit_range) {
    Grid g;
    addInputs(g, 1);
    g.addOutput(new RecordingOutput("out"));
    Cell* c = g.getCellWithName("in0", "out");
    c->setCoeff(0.3);
    c->setCoeff(5.0);   // hors [-1, 1] : ignoré
    BOOST_TEST(c->getCoeff() == 0.3f, boost::test_tools::tolerance(1e-6f));
}

BOOST_AUTO_TEST_CASE(mutex_is_recursive) {
    Grid g;
    std::lock_guard<std::recursive_mutex> outer(g.getMutex());
    // Les méthodes de Grid reprennent le verrou : ne doit pas bloquer
    g.addOutput(new RecordingOutput("out"));
    BOOST_TEST(g.getNbrOutputs() == 1u);
}

// Régression : un thread de capture appelle compute() pendant que les serveurs
// ajoutent/retirent des sorties. Sans verrou, la réallocation des vecteurs
// pendant l'itération provoquait des use-after-free.
BOOST_AUTO_TEST_CASE(compute_is_safe_against_concurrent_mutation) {
    Grid g;
    addInputs(g, 64);
    g.switchActive();
    std::atomic<bool> stop{false};
    std::atomic<long> computes{0};
    std::thread capture([&] {
        while (!stop) { g.compute(); computes++; }
    });
    for (int i = 0; i < 300; i++) {
        std::string name = "o" + std::to_string(i);
        g.addOutput(new RecordingOutput(name.c_str()));
        if (i % 3 == 0) g.removeOutput(i);
    }
    stop = true;
    capture.join();
    BOOST_TEST(computes.load() > 0);
    BOOST_TEST(g.getNbrOutputs() == 200u);
    BOOST_TEST(g.getCells()->size() == 200u * 64u);
}
