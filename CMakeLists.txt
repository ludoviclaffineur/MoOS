cmake_minimum_required(VERSION 3.20)

project(MoOS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Composants optionnels (dépendances lourdes ou plus disponibles)
option(MOOS_WITH_OPENCV "Capture vidéo via OpenCV" OFF)
option(MOOS_WITH_LEAP   "Capture Leap Motion (SDK Leap v2, obsolète)" OFF)
option(MOOS_WITH_ODBC   "Capture base de données via SOCI/ODBC" OFF)

# Homebrew : websocketpp 0.8 et le serveur HTTP utilisent boost::asio::io_service,
# supprimé dans Boost 1.87 -> on cible boost@1.85 si présent.
if(APPLE AND NOT Boost_DIR AND EXISTS "/opt/homebrew/opt/boost@1.85")
    list(PREPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/boost@1.85")
endif()

find_package(Boost 1.66 REQUIRED COMPONENTS thread system serialization filesystem)
if(Boost_VERSION VERSION_GREATER_EQUAL 1.87)
    message(FATAL_ERROR "Boost ${Boost_VERSION} trop récent (io_service supprimé). Installez boost@1.85.")
endif()

find_package(Gecode REQUIRED)
find_package(websocketpp REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBLO     REQUIRED IMPORTED_TARGET liblo)
pkg_check_modules(PORTAUDIO REQUIRED IMPORTED_TARGET portaudio-2.0)
pkg_check_modules(RTMIDI    REQUIRED IMPORTED_TARGET rtmidi)
find_library(PCAP_LIBRARY NAMES pcap REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE MOOS_SOURCES CONFIGURE_DEPENDS
    LibLoAndCap/*.cpp
    capture/*.cpp
    Inputs/*.cpp
    mapping/*.cpp
    outputs/*.cpp
    processings/*.cpp
    save/*.cpp
    utils/*.cpp
    view/*.cpp
)

if(NOT MOOS_WITH_OPENCV)
    list(FILTER MOOS_SOURCES EXCLUDE REGEX "/capture/VideoOpenCvHandler\\.cpp$")
endif()
if(NOT MOOS_WITH_LEAP)
    list(FILTER MOOS_SOURCES EXCLUDE REGEX "/(capture/LeapMotionHandler|processings/LeapHandsProcessing)\\.cpp$")
endif()
if(NOT MOOS_WITH_ODBC)
    list(FILTER MOOS_SOURCES EXCLUDE REGEX "/capture/OdbcHandler\\.cpp$")
endif()

# Tout sauf main.cpp va dans une lib statique, partagée par l'exécutable et les tests
list(FILTER MOOS_SOURCES EXCLUDE REGEX "/LibLoAndCap/main\\.cpp$")
add_library(moos_core STATIC ${MOOS_SOURCES})

target_include_directories(moos_core PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/capture
    ${PROJECT_SOURCE_DIR}/Inputs
    ${PROJECT_SOURCE_DIR}/mapping
    ${PROJECT_SOURCE_DIR}/outputs
    ${PROJECT_SOURCE_DIR}/outputs/GranularSynth
    ${PROJECT_SOURCE_DIR}/outputs/Midi
    ${PROJECT_SOURCE_DIR}/processings
    ${PROJECT_SOURCE_DIR}/save
    ${PROJECT_SOURCE_DIR}/utils
    ${PROJECT_SOURCE_DIR}/view/server
    ${PROJECT_SOURCE_DIR}/view/websocket
)

target_compile_definitions(moos_core PUBLIC
    MOOS_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
    _WEBSOCKETPP_CPP11_STL_
)

target_link_libraries(moos_core PUBLIC
    Boost::thread Boost::system Boost::serialization Boost::filesystem
    Gecode::gecodedriver Gecode::gecodeminimodel Gecode::gecodefloat
    Gecode::gecodeint Gecode::gecodeset Gecode::gecodesearch
    Gecode::gecodekernel Gecode::gecodesupport
    websocketpp::websocketpp
    PkgConfig::LIBLO PkgConfig::PORTAUDIO PkgConfig::RTMIDI
    ${PCAP_LIBRARY}
    Threads::Threads
)

if(MOOS_WITH_OPENCV)
    find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui videoio)
    target_link_libraries(moos_core PUBLIC ${OpenCV_LIBS})
    target_compile_definitions(moos_core PUBLIC MOOS_HAS_OPENCV)
endif()

if(MOOS_WITH_LEAP)
    find_path(LEAP_INCLUDE_DIR leap/Leap.h REQUIRED)
    find_library(LEAP_LIBRARY Leap REQUIRED)
    target_include_directories(moos_core PUBLIC ${LEAP_INCLUDE_DIR})
    target_link_libraries(moos_core PUBLIC ${LEAP_LIBRARY})
    target_compile_definitions(moos_core PUBLIC MOOS_HAS_LEAP)
endif()

if(MOOS_WITH_ODBC)
    find_package(SOCI REQUIRED)
    target_link_libraries(moos_core PUBLIC SOCI::soci_core SOCI::soci_odbc)
    target_compile_definitions(moos_core PUBLIC MOOS_HAS_ODBC)
endif()

add_executable(MoOS LibLoAndCap/main.cpp)
target_link_libraries(MoOS PRIVATE moos_core)

# Installation : le binaire + les ressources lues via CURRENT_PATH (www/, data/).
# Au lancement d'une version installée, MOOS_RESOURCE_DIR doit pointer sur share/moos.
include(GNUInstallDirs)
install(TARGETS MoOS RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY www data DESTINATION ${CMAKE_INSTALL_DATADIR}/moos)

option(MOOS_BUILD_TESTS "Tests unitaires (Boost.Test) et batterie d'integration (Node)" ON)
if(MOOS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
