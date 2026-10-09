# syntax=docker/dockerfile:1
#
# MoOS sur Ubuntu 24.04, en trois étapes :
#   build   : compile et installe dans /opt/moos
#   test    : tests unitaires + batterie d'intégration (l'image finale en dépend :
#             elle ne se construit que si les tests passent)
#   runtime : binaire + ressources + bibliothèques d'exécution, utilisateur non-root
#
#   docker compose up --build        (voir compose.yaml)
#   docker build -t moos .           (image seule)

ARG UBUNTU_VERSION=24.04

# ---------------------------------------------------------------------------- build
FROM ubuntu:${UBUNTU_VERSION} AS build

# Boost 1.83 : < 1.87 comme l'exige websocketpp 0.8 (boost::asio::io_service)
RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential cmake ninja-build pkg-config \
        libboost-thread-dev libboost-system-dev libboost-serialization-dev libboost-filesystem-dev \
        libgecode-dev liblo-dev libwebsocketpp-dev portaudio19-dev librtmidi-dev libpcap-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . .

RUN cmake -S . -B build -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/opt/moos \
 && cmake --build build \
 && cmake --install build --strip

# ---------------------------------------------------------------------------- test
FROM build AS test

# La batterie d'intégration demande Node >= 22 (WebSocket global) ; Ubuntu n'a que la 18
COPY --from=node:22-bookworm-slim /usr/local/bin/node /usr/local/bin/node

# Reconfigure pour que CMake trouve node et enregistre la batterie d'intégration
RUN cmake -S . -B build > /dev/null \
 && ctest --test-dir build --output-on-failure

# ---------------------------------------------------------------------------- runtime
FROM ubuntu:${UBUNTU_VERSION} AS runtime

RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        libboost-thread1.83.0 libboost-system1.83.0 libboost-serialization1.83.0 libboost-filesystem1.83.0 \
        libgecode49t64 liblo7 libportaudio2 librtmidi6 libpcap0.8t64 \
 && rm -rf /var/lib/apt/lists/* \
 && useradd --system --uid 10001 --home-dir /var/lib/moos --create-home moos

# Copié depuis l'étape test : l'image n'existe que si les tests sont verts
COPY --from=test /opt/moos /opt/moos

ENV MOOS_RESOURCE_DIR=/opt/moos/share/moos \
    PATH=/opt/moos/bin:$PATH

# Répertoire de travail inscriptible : MoOS y écrit ses sauvegardes XML
WORKDIR /var/lib/moos
USER moos

EXPOSE 8080 9002

HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD bash -c 'exec 3<>/dev/tcp/127.0.0.1/8080' || exit 1

# MoOS [httpPort] [bindAddress] [wsPort] : 0.0.0.0 est nécessaire pour publier les
# ports hors du conteneur. Restreindre l'exposition côté hôte (cf. compose.yaml).
ENTRYPOINT ["MoOS"]
CMD ["8080", "0.0.0.0", "9002"]
