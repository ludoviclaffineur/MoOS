//
//  test_constrain.cpp
//  ConstrainGenetic : garde sur le nombre d'inputs, matrice singulière (plus d'exit()),
//  boucle bornée, remise à zéro des contraintes après chaque calcul.
//

#define BOOST_TEST_MODULE ConstrainGeneticTests
#include <boost/test/included/unit_test.hpp>

#include <chrono>
#include <future>

#include "ConstrainGenetic.h"
#include "Grid.h"
#include "TestHelpers.h"

// Grille de 3 inputs et 1 output. computeGrid résout les coefficients des 2
// derniers inputs (matrice 2x2 = leurs valeurs dans les 2 instantanés).
struct Fixture {
    Grid g;
    RecordingOutput* out;
    ConstrainGenetic algo{&g};
    Fixture() {
        for (int i = 0; i < 3; i++) {
            std::string name = "in" + std::to_string(i);
            g.addInput(name.c_str(), 0, 1, -1, 0, Converter::LINEAR);
        }
        out = new RecordingOutput("out");
        g.addOutput(out);
    }
    void snapshot(float a, float b, float c, float output) {
        g.getInputWithName("in0")->setValue(a);
        g.getInputWithName("in1")->setValue(b);
        g.getInputWithName("in2")->setValue(c);
        out->setValue(output);
        algo.setConstrain();
    }
    float coeff(const char* input) {
        return g.getCellWithName(input, "out")->getCoeff();
    }
    // Exécute f avec un délai maximum : une régression de type boucle infinie fait échouer le test
    template <class F> bool runWithin(F f, int seconds) {
        auto fut = std::async(std::launch::async, f);
        return fut.wait_for(std::chrono::seconds(seconds)) == std::future_status::ready;
    }
};

BOOST_AUTO_TEST_CASE(set_constrain_needs_two_inputs) {
    Grid g;
    g.addInput("only", 0, 1, -1, 0, Converter::LINEAR);
    g.addOutput(new RecordingOutput("out"));
    ConstrainGenetic algo(&g);
    // Avant le correctif : soustraction size_t qui déborde -> std::out_of_range
    BOOST_CHECK_NO_THROW(algo.setConstrain());
    BOOST_CHECK_NO_THROW(algo.setConstrain());
}

BOOST_AUTO_TEST_CASE(set_constrain_without_outputs_is_ignored) {
    Grid g;
    g.addInput("a", 0, 1, -1, 0, Converter::LINEAR);
    g.addInput("b", 0, 1, -1, 0, Converter::LINEAR);
    ConstrainGenetic algo(&g);
    BOOST_CHECK_NO_THROW(algo.setConstrain());
    BOOST_CHECK_NO_THROW(algo.setConstrain());
}

BOOST_FIXTURE_TEST_CASE(solvable_constraints_set_the_coefficients, Fixture) {
    // in1 seul dans le 1er instantané, in2 seul dans le 2e : solution exacte 0.5 / 0.3
    BOOST_TEST(runWithin([&] { snapshot(0, 1, 0, 0.5f); snapshot(0, 0, 1, 0.3f); }, 10));
    BOOST_TEST(coeff("in1") == 0.5f, boost::test_tools::tolerance(0.02f));
    BOOST_TEST(coeff("in2") == 0.3f, boost::test_tools::tolerance(0.02f));
}

// Régression : gauss() appelait exit(EXIT_FAILURE) et tuait toute l'application
BOOST_FIXTURE_TEST_CASE(singular_matrix_leaves_grid_unchanged, Fixture) {
    BOOST_TEST(runWithin([&] { snapshot(0, 1, 1, 0.5f); snapshot(0, 1, 1, 0.5f); }, 10));
    BOOST_TEST(coeff("in0") == 0.0f);
    BOOST_TEST(coeff("in1") == 0.0f);
    BOOST_TEST(coeff("in2") == 0.0f);
}

// Régression : do/while sans borne qui bloquait le thread HTTP à 100 % CPU
BOOST_FIXTURE_TEST_CASE(unreachable_constraints_terminate, Fixture) {
    // Il faudrait des coefficients de 900 : aucune solution dans [-1, 1]
    BOOST_TEST(runWithin([&] { snapshot(0, 0.001f, 0, 0.9f); snapshot(0, 0, 0.001f, 0.9f); }, 20));
    BOOST_TEST(coeff("in1") == 0.0f);
    BOOST_TEST(coeff("in2") == 0.0f);
}

// Régression : la liste n'était jamais vidée, donc plus aucun calcul après la 2e contrainte
BOOST_FIXTURE_TEST_CASE(constraints_are_reset_after_each_computation, Fixture) {
    BOOST_TEST(runWithin([&] {
        snapshot(0, 1, 1, 0.5f); snapshot(0, 1, 1, 0.5f);   // 1re paire : singulière
        snapshot(0, 1, 0, 0.4f); snapshot(0, 0, 1, 0.2f);   // 2e paire : doit être calculée
    }, 10));
    BOOST_TEST(coeff("in1") == 0.4f, boost::test_tools::tolerance(0.02f));
    BOOST_TEST(coeff("in2") == 0.2f, boost::test_tools::tolerance(0.02f));
}
