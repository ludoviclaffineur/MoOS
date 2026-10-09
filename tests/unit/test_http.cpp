//
//  test_http.cpp
//  request_handler + SnfHandler : robustesse des requêtes .snf sans configuration,
//  avec des identifiants inconnus ou des paramètres malformés.
//

#define BOOST_TEST_MODULE HttpTests
#include <boost/test/included/unit_test.hpp>

#include "request_handler.hpp"
#include "request.hpp"
#include "reply.hpp"
#include "Grid.h"
#include "Genetic.h"
#include "ConstrainGenetic.h"
#include "OscHandler.h"
#include "TestHelpers.h"

using http::server::reply;

struct HttpFixture {
    Grid grid;
    Genetic genetic{&grid, true, 0.5, 0.2, 0.5, 5};
    ConstrainGenetic constrain{&grid};
    // OdbcHandler* toujours NULL, comme dans main.cpp
    http::server::request_handler handler{std::string(MOOS_SOURCE_DIR) + "/www", &grid, &genetic, &constrain, NULL};

    reply get(const std::string& uri) {
        http::server::request req;
        req.method = "GET";
        req.uri = uri;
        req.http_version_major = 1;
        req.http_version_minor = 1;
        reply rep;
        handler.handle_request(req, rep);
        return rep;
    }
    bool contains(const reply& rep, const std::string& s) {
        return rep.content.find(s) != std::string::npos;
    }
};

BOOST_FIXTURE_TEST_CASE(serves_static_files, HttpFixture) {
    reply rep = get("/index.html");
    BOOST_TEST((rep.status == reply::ok));
    BOOST_TEST(!rep.content.empty());
    BOOST_TEST((get("/does-not-exist.html").status == reply::not_found));
}

BOOST_FIXTURE_TEST_CASE(rejects_path_traversal, HttpFixture) {
    BOOST_TEST((get("/../CMakeLists.txt").status == reply::bad_request));
    BOOST_TEST((get("/%2e%2e/CMakeLists.txt").status == reply::bad_request));
}

// Régression : mDatabase (toujours NULL) était déréférencé -> segfault
BOOST_FIXTURE_TEST_CASE(trig_without_database, HttpFixture) {
    BOOST_TEST((get("/trig.snf").status == reply::ok));
}

// Régression : getOutputWithId/WithName et getCellWithName renvoient NULL
BOOST_FIXTURE_TEST_CASE(unknown_ids_and_names_are_ignored, HttpFixture) {
    BOOST_TEST((get("/updateCell.snf?input=x&output=y&coeff=0.5").status == reply::ok));
    BOOST_TEST((get("/getOutput.snf?output=nope").status == reply::ok));
    BOOST_TEST((get("/updateOutput.snf?Identifier=999&").status == reply::ok));
    BOOST_TEST((get("/setOutputValue.snf?name=nope&value=0.5").status == reply::ok));
}

// Régression : underflow size_t dans ConstrainGenetic sans capture device
BOOST_FIXTURE_TEST_CASE(set_constrain_without_inputs, HttpFixture) {
    BOOST_TEST((get("/setConstain.snf").status == reply::ok));
    BOOST_TEST((get("/setConstain.snf").status == reply::ok));
}

// Régression : listParameters[1] lu sans contrôle de taille -> segfault
BOOST_FIXTURE_TEST_CASE(kyma_output_without_parameters, HttpFixture) {
    reply rep = get("/kymaOutput.snf?ip=1.2.3.4");
    BOOST_TEST((rep.status == reply::ok));
    BOOST_TEST(contains(rep, "ERROR"));
}

// Régression : une exception dans un handler remontait jusqu'à io_service::run()
BOOST_FIXTURE_TEST_CASE(handler_exception_becomes_500, HttpFixture) {
    grid.addOutput(new OscHandler("osc", "127.0.0.1", "20000", "/osc", "f"));
    // Nombre impair de paramètres : OscHandler::setParameters lit at(i+1) hors bornes
    reply rep = get("/updateOutput.snf?Identifier=0&x=Name&");
    BOOST_TEST((rep.status == reply::internal_server_error));
    // Le handler reste utilisable
    BOOST_TEST((get("/getOutputs.snf").status == reply::ok));
}

BOOST_FIXTURE_TEST_CASE(add_output_and_list_it, HttpFixture) {
    BOOST_TEST((get("/addOutput.snf").status == reply::ok));
    BOOST_TEST(grid.getNbrOutputs() == 1u);
    BOOST_TEST(contains(get("/getOutputs.snf"), "NewOsc0"));
}

BOOST_FIXTURE_TEST_CASE(update_cell_sets_the_coefficient, HttpFixture) {
    grid.addInput("440", 0, 1, -1, 0, Converter::LINEAR);
    grid.addOutput(new RecordingOutput("out"));
    get("/updateCell.snf?input=440&output=out&coeff=0.5");
    BOOST_TEST(grid.getCellWithName("440", "out")->getCoeff() == 0.5f, boost::test_tools::tolerance(1e-6f));
}
