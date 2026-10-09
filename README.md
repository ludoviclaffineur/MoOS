# MoOS

MoOS transforme des flux de données vivants en contrôles sonores : le son d'un fichier, le trafic d'un réseau ou un capteur pilote des synthés via OSC, MIDI ou un synthé granulaire intégré. Une grille de poids, réglable depuis un navigateur, décide quelle donnée fait bouger quel paramètre.

Projet de 2013–2015 (installations, concerts, recherche), relancé en 2026.

**Manuel complet** (fonctionnement, inputs, outputs, API, recettes, limites, feuille de route) :
https://ludoviclaffineur.github.io/MoOS/ — source dans [`docs/manuel.md`](docs/manuel.md).

## Démarrer

MoOS se lance toujours avec Docker (Ubuntu 24.04). Le build exécute toute la suite de tests ; si un test échoue, l'image n'est pas créée.

```sh
docker compose up --build -d
```

1. Ouvrir http://localhost:8080/v2/index.html
2. Choisir l'input « ReadWave Handler » (analyse FFT de `data/sound15.wav`, en boucle) puis l'output « OSC »
3. Monter quelques poids dans la grille
4. Écouter l'OSC sur ta machine, port UDP 20000 (`/osc`, `/osc1`), avec n'importe quel logiciel qui reçoit de l'OSC : Pure Data, Max, TouchDesigner, SuperCollider, `oscdump 20000`…

| Port | Rôle |
| --- | --- |
| 8080/tcp | Interfaces web et API HTTP `.snf` |
| 9002/tcp | WebSocket de l'interface v2 |
| 20000/udp | OSC sortant, vers ta machine |

Les ports ne sont publiés que sur `127.0.0.1` : MoOS n'a aucune authentification. L'input ne se choisit qu'une fois par lancement ; `docker compose restart moos` repart de zéro.

Depuis Docker, seul l'OSC sort : le MIDI et l'audio demandent un périphérique que Docker Desktop ne transmet pas au conteneur.

## Développer

```sh
docker build --target test .                 # compile + tests unitaires et d'intégration
cmake -S . -B build && cmake --build build   # build natif (macOS, dépendances Homebrew)
ctest --test-dir build --output-on-failure
```

La CI (GitHub Actions) construit et teste l'image Docker sur Ubuntu. Les conventions et pièges du code sont dans [CLAUDE.md](CLAUDE.md).
