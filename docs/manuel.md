## En bref

MoOS transforme des flux de données vivants en contrôles sonores : le son d'un fichier, le trafic d'un réseau ou un capteur pilote des synthés via OSC, MIDI ou un synthé granulaire intégré. Entre les deux, une grille de poids décide quelle donnée fait bouger quel paramètre, et on la règle depuis un navigateur.

État au 9 octobre 2026 : le projet de 2013–2015 a été relancé. Il compile, tourne dans Docker sous Ubuntu et passe une suite de tests (unitaires et intégration). La partie la plus faible est la configuration web : c'est le prochain chantier (voir « Et après »).

Selon ce que tu cherches :

- **Faire du son** : Démarrage, Le zoo des inputs, Les outputs, Recettes.
- **Comprendre le moteur** : Comment ça marche, La grille et le mapping.
- **Coder dessus** : Les interfaces, Développer, Sécurité et limites.

## La petite histoire

MoOS est né le 30 octobre 2013 sous le nom LibPcapAndLiblo : capturer des paquets réseau et les envoyer en OSC. En 18 mois, il a grandi jusqu'à une dizaine d'inputs et trois familles d'outputs, au service d'installations artistiques, de concerts et de travaux de recherche. Son nom dit son projet : Modular Open Sonification Framework. Il a dormi de 2016 à 2026, puis a été relancé.

| Date | Jalon |
| --- | --- |
| Oct. 2026 | Docker Ubuntu, suite de tests, CI Linux |
| Oct. 2026 | Résurrection : build CMake moderne, correctifs de plantages |
| Oct. 2016 | Dernier commit : MIDI |
| Mars 2015 | « Modifications for JL » |
| Fév. 2015 | Interface web v2 en WebSocket, OpenCV, synthé granulaire pilotable |
| Janv. 2015 | Outputs MIDI, input base de données (ODBC) |
| Déc. 2014 | Synthé granulaire (PortAudio), FFT et lecteur WAV |
| Nov. 2014 | Leap Motion |
| Oct. 2014 | Branches KIKK et KISS |
| Sept. 2014 | Premier CMake, build pour Raspberry Pi, solveur de contraintes |
| Mai 2014 | Requêtes DNS, support Kyma (Pacarana) |
| Mars–avr. 2014 | Couche Processings, algorithme génétique, input série (Arduino) |
| Mars 2014 | Géolocalisation des adresses IP |
| Fév. 2014 | Ajout/suppression d'outputs depuis le web, sauvegardes |
| Nov.–déc. 2013 | Grille, cellules et inputs ; mini serveur web |
| Oct. 2013 | Capture pcap → messages OSC |

À compléter par toi : les œuvres, concerts et lieux où MoOS a joué et ce qu'étaient KIKK, KISS et « JL ».

## Démarrage en 2 minutes

MoOS se lance toujours avec Docker : une commande construit l'image, exécute les tests et démarre le serveur. Seul prérequis : Docker (Docker Desktop sur Mac ou Windows).

1. Récupérer le code et lancer : `git clone https://github.com/ludoviclaffineur/MoOS.git && cd MoOS && docker compose up --build -d`. Le premier build prend quelques minutes ; si un test échoue, l'image n'est pas créée.
2. Ouvrir l'interface : http://localhost:8080/v2/index.html.
3. Choisir l'input « ReadWave Handler » : MoOS lit `data/sound15.wav` en boucle (5,9 s) et l'analyse en 512 bandes de fréquence.
4. Choisir l'output « OSC » : deux sorties, `TEST` et `TEST2`, envoient un float sur `/osc` et `/osc1`.
5. Monter quelques poids dans la grille, puis écouter l'OSC sur ta machine, port UDP 20000, avec n'importe quel logiciel qui reçoit de l'OSC (TouchDesigner, SuperCollider, VCV Rack, Processing, Max for Live…). Par exemple :
    - Pure Data : `[netreceive -u -b 20000]` → `[oscparse]`
    - Max : `[udpreceive 20000]`
    - Terminal : `oscdump 20000` (paquet liblo-tools)

| Port | Sens | Rôle |
| --- | --- | --- |
| 8080/tcp | entrant | Interfaces web et API HTTP `.snf` |
| 9002/tcp | entrant | WebSocket de l'interface v2 |
| 20000/udp | sortant, vers ta machine | Messages OSC des sorties par défaut |

Les ports ne sont ouverts que sur `127.0.0.1` de ta machine : MoOS n'a aucune authentification. L'input ne se choisit qu'une fois par lancement ; pour repartir de zéro : `docker compose restart moos`. Logs : `docker compose logs -f moos`. Pour envoyer l'OSC ailleurs que sur ta machine, change `MOOS_OSC_HOST` dans `compose.yaml`.

## Comment ça marche

Les données vont toujours dans le même sens : source, capture, inputs, grille, outputs. Les interfaces web ne transportent aucune donnée : elles règlent le circuit.

<!-- diagram:pipeline -->

Chaque trame de la source traverse la chaîne de gauche à droite, environ 86 fois par seconde avec un WAV ; la grille, en couleur, est le seul endroit où l'on décide quoi pilote quoi. Le code suit le même découpage : `capture/`, `processings/`, `mapping/`, `outputs/`, `view/`.

## Le zoo des inputs

Six sources de données existent ; seul le lecteur WAV fonctionne tel quel dans Docker aujourd'hui. Chaque source crée ses inputs dans la grille, et chaque input est une valeur qui bouge, ramenée entre 0 et 1.

| Input (id) | Ce qu'il capte | Inputs créés | État dans Docker |
| --- | --- | --- | --- |
| ReadWave Handler (3) | Un fichier WAV 16 bits lu en boucle, analysé par FFT (fenêtre de 1024) | 512 bandes, nommées par leur fréquence en Hz : `0`, `43`, `86`… | Fonctionne (`data/sound15.wav`) |
| Pcap Handler (0) | Les paquets du réseau | `TypeOfService`, `TTL`, `Protocol`, `PacketLength` ; latitude/longitude source et destination ; requêtes DHCP | Docker Desktop (Mac) : voit la VM Linux, pas le wifi du Mac. Docker sur Linux (ex. Raspberry Pi) : possible avec le réseau de l'hôte et les droits de capture |
| Serial Handler (1) | Un Arduino sur port série (115200 bauds), trames de 8 octets | Une valeur 0–1024 par canal | Port `/dev/tty.usbmodem1411` codé en dur ; pas d'USB dans Docker Desktop sur Mac |
| LeapMotion Handler (2) | Les deux mains : chaque doigt, chaque os, sur 3 axes | Une valeur −300…300 par main × doigt × os × axe | Désactivé : SDK Leap v2 plus distribué |
| ODBC Handler (4) | Les lignes d'une requête SQL, une ligne à la fois (`trig`, `setRow`) | Une valeur par colonne | Désactivé (option `MOOS_WITH_ODBC`) |
| VideoOpenCv Handler (5) | La webcam | Aucun : le code lit l'image mais ne nourrit pas encore la grille | Désactivé (option `MOOS_WITH_OPENCV`) |

La capture réseau écoute tout ce qui passe par la carte réseau. Sur un réseau moderne (switch, wifi), c'est le trafic de la machine plus ce qui est diffusé à tous (ARP, DHCP, mDNS) ; pour entendre tout un réseau, MoOS doit tourner là où tout passe : le routeur, un point d'accès ou un port miroir du switch.

Elle a aussi des modules en sommeil : géolocalisation par une base IP→GPS de 50 Mo, détection de mots de passe en clair, récupération des images HTTP. Ils sont désactivés et contiennent des bugs connus (voir Sécurité et limites).

## Les outputs

MoOS sait sortir de l'OSC, du MIDI et de l'audio, mais depuis Docker seul l'OSC sort aujourd'hui. L'OSC voyage par le réseau et traverse le conteneur ; le MIDI et l'audio ont besoin d'un périphérique que Docker Desktop sur Mac ne donne pas au conteneur.

| Output (id) | Ce qu'il envoie | Paramètres réglables | Depuis Docker |
| --- | --- | --- | --- |
| OSC (0) | Un float par sortie, à chaque calcul de la grille (~86 fois/s en WAV) | `IPAddress`, `Port`, `OscAddressPattern`, `Name` | Oui, vers ta machine (UDP 20000) |
| MIDI (2) | 7 Control Change (`Noise`, `Feedback`, `FreqEq`, `Resonnance`, `Insert`, `Modulation`, `EqualBoost`) + des notes (hauteur, vélocité, durée) | `cc`, `MinCCValue`, `MaxCCValue`, `MinKey`, `MaxKey`, `MinVelocity`, `MaxVelocity`, `MinDuration`, `MaxDuration` | Non : aucun port MIDI visible |
| Synthé granulaire (1) | Du son, via PortAudio, à partir d'un fichier source | 7 paramètres pilotés : durée des grains, recouvrement, silence, décroïssance et délai de réverb, coupure passe-bas, position de départ | Non : aucune carte son ; plante aussi en natif |
| Kyma (API HTTP) | OSC vers un Pacarana Kyma, dont MoOS récupère les widgets | Adresse IP du Pacarana | Non testé |

À savoir :

- Les noms MIDI (`Noise`, `Feedback`…) visaient un instrument précis ; `FreqEq` envoie des valeurs jusqu'à 131, hors de la norme MIDI (0–127).
- Le synthé granulaire cherche `data/bouceAllSounds.wav`, absent du repo, et son callback audio a des bugs connus : à éviter tant qu'ils ne sont pas corrigés.
- En build natif sur Mac, le MIDI devrait passer par CoreMIDI (non testé depuis la relance).

## La grille et le mapping

La grille est une matrice inputs × outputs : chaque cellule porte un poids entre −1 et 1, à 0 par défaut. Tant que tous les poids valent 0, les sorties envoient 0. À chaque calcul, chaque sortie reçoit la somme pondérée des inputs :

<p class="formula">sortie<sub>j</sub> = conv<sub>j</sub>( Σ<sub>i</sub> input<sub>i</sub> × w<sub>ij</sub> ), avec w<sub>ij</sub> ∈ [−1, 1]</p>

`conv` ramène la somme dans la plage de la sortie (0–127 pour un CC MIDI, par exemple). Trois façons de régler les poids :

| Méthode | Comment | Appel |
| --- | --- | --- |
| À la main | Un poids par cellule, depuis l'interface | WebSocket `sendWeight`, HTTP `updateCell.snf` |
| Algorithme génétique | Tu notes la grille que tu entends ; MoOS croise les meilleures grilles notées et applique l'enfant. Population de départ : 5 grilles aléatoires | HTTP `rateGrid.snf?rate=N` |
| Solveur de contraintes | Tu captures deux instants « ces inputs doivent donner ces valeurs de sortie » ; MoOS calcule des poids qui les respectent | HTTP `setConstain.snf`, deux fois |

Pièges à connaître :

- L'ordre compte : choisir l'input **avant** les outputs. Les cellules sont créées quand une sortie arrive ; un input ajouté après n'en a pas.
- Le solveur fixe les poids des 2 derniers inputs et tire les autres au hasard ; il abandonne après 10 000 essais si aucune solution ne tient dans \[−1, 1\]. Avec la FFT, ce sont les 2 bandes les plus aiguës, souvent proches de 0 : le résultat est rarement exploitable.
- La grille n'est calculée que si elle est active : l'output par défaut l'active au moment où on le choisit.

## Les interfaces et l'API

Deux interfaces web cohabitent, chacune avec son protocole, et toutes deux pilotent la même grille. Aucune n'est documentée côté serveur ailleurs qu'ici.

| Interface | Adresse | Protocole | Usage |
| --- | --- | --- | --- |
| v2 (2015) | `/v2/index.html` | WebSocket JSON, port 9002 | Parcours complet : input, outputs, grille de poids |
| Legacy (2014) | `/` | HTTP GET `*.snf`, réponses XML | Édition des cellules et des outputs, algorithmes, sauvegardes |

### WebSocket : messages du navigateur vers MoOS

Format : `{"action": "<nom>", "parameters": {…}}`.

| Action | Paramètres | Effet |
| --- | --- | --- |
| `init` | — | Renvoie la liste des inputs (`capture_device_list`) |
| `setCaptureDevice` | `id` (0–5, voir Le zoo des inputs) | Choisit l'input, une seule fois par lancement |
| `setConfigurationPcap` | `id` d'interface réseau | Lance la capture sur cette interface |
| `setDefaultOutput` | `id` : 0 OSC, 1 synthé granulaire, 2 MIDI | Crée les outputs par défaut et active la grille |
| `setMidiPort` | `id` de port MIDI | Ouvre le port et crée les 10 outputs MIDI |
| `sendWeight` | `inputName`, `outputName`, `weight` | Règle un poids |
| `setOutput` | `identifier` + les paramètres de l'output | Modifie un output (nom, IP, port…) |
| `trig`, `setRow` | — / numéro de ligne | Avance dans une base de données (ODBC) |
| `getSavedFiles` | — | Liste les sauvegardes (côté serveur seulement) |

### WebSocket : messages de MoOS vers le navigateur

| Action | Contenu |
| --- | --- |
| `capture_device_list` | Les 6 inputs disponibles |
| `setConfiguration` | Les interfaces réseau (pcap), ou le passage à l'étape outputs |
| `set_outputs_list` | Les 3 types d'outputs |
| `setOutputConfig` | Les ports MIDI disponibles |
| `setGrid` | Inputs, outputs, poids et description : l'état complet de la grille |
| `setDescription` | Description de la ligne courante (ODBC) |
| `stopConnection` | MoOS s'arrête |

### HTTP `.snf`

Chaque appel est un GET `/<méthode>.snf?clé=valeur&…`, avec une réponse XML `<response>…</response>`.

| Méthode | Paramètres | Effet |
| --- | --- | --- |
| `getInputs`, `getOutputs`, `getCells` | — | Liste les inputs, les outputs, les cellules et leurs poids |
| `getOutput` | `output` (nom) | Paramètres d'un output |
| `updateCell` | `input`, `output`, `coeff` | Règle un poids |
| `addOutput`, `deleteOutput` | — / `id` | Ajoute un output OSC, en supprime un |
| `updateOutput` | `Identifier` + paramètres, chaque paire terminée par `&` | Modifie un output |
| `setOutputValue` | `name`, `value` | Force la valeur d'un output et l'envoie |
| `setActiveGrid` | — | Active ou désactive la grille |
| `rateGrid` | `rate` | Note la grille (algorithme génétique) |
| `setConstain` | — | Capture une contrainte (solveur) |
| `save`, `load` | `filename` | Sauvegarde ou recharge la configuration en XML |
| `kymaOutput` | `ip` | Se connecte à un Pacarana Kyma |
| `trig` | — | Ligne suivante de la base de données |
| `getPictureToCheck`, `setPictureValided` | — / `OK` | Modération des images capturées (module pcap en sommeil) |

Limites du protocole actuel : actions toutes en GET (donc déclenchables par n'importe quelle page web ouverte), paramètres parsés par expressions régulières, coefficients négatifs ou à deux décimales mal lus par `updateCell`, et deux protocoles pour une même grille. C'est le point de départ de « Et après ».

## Recettes

Deux recettes marchent aujourd'hui dans Docker ; les autres demandent du matériel ou un build natif.

### Le son qui pilote le son (marche aujourd'hui)

1. Input « ReadWave Handler », output « OSC ».
2. Poids à 1 entre les bandes graves (`43` à `430` Hz) et `TEST`, entre les médiums (`473` à `1722` Hz) et `TEST2`.
3. Dans ton logiciel, `/osc` (l'énergie des graves) ouvre un filtre, `/osc1` (les médiums) module une réverb ou une vitesse de lecture.

Résultat mesuré lors des tests : `/osc` oscille entre 0,52 et 0,66 et `/osc1` entre 0,11 et 0,37, environ 80 messages par seconde.

### Ton propre morceau (marche aujourd'hui)

Remplace le son lu par MoOS sans reconstruire l'image, en le montant par-dessus `sound15.wav` dans `compose.yaml` :

```
    volumes:
      - moos-data:/var/lib/moos
      - ./mon-son.wav:/opt/moos/share/moos/data/sound15.wav:ro
```

Le fichier doit être un WAV PCM 16 bits, mono ou stéréo, d'au moins 1024 échantillons ; sinon MoOS refuse de le lire et le dit dans les logs.

### Laisser MoOS composer (à tester)

Partir de poids aléatoires, écouter, noter avec `rateGrid.snf?rate=N` : MoOS croise les grilles les mieux notées et applique la suivante. L'idée : converger vers une grille qui te plaît sans régler une cellule à la main. La note se donne depuis l'interface legacy (`/`), pas depuis la v2. Pas encore essayé sur une vraie grille depuis la relance.

### Le réseau qui chante (demande du matériel)

MoOS sur un Raspberry Pi qui sert de point d'accès wifi, en Docker avec le réseau de l'hôte : chaque paquet fait varier `TTL`, `PacketLength` et `Protocol`, donc le son suit l'activité du lieu. C'est l'usage d'origine du projet ; il reste à adapter `compose.yaml` (réseau hôte, droits de capture).

## Développer sur MoOS

La référence est Docker sous Ubuntu 24.04 : c'est ce que la CI construit et teste. Un build natif sur Mac reste possible pour itérer vite.

```
docker build --target test .                       # compile + toute la suite de tests
docker compose up --build -d                       # compile + tests + lance

# natif (Homebrew : cmake boost@1.85 gecode liblo websocketpp portaudio rtmidi pkgconf)
cmake -S . -B build && cmake --build build -j8
ctest --test-dir build --output-on-failure         # toute la suite
ctest --test-dir build -R unit.grid                # une suite
```

| Dossier | Rôle |
| --- | --- |
| `capture/` | Les inputs : un thread par source |
| `processings/` | Transforment les données brutes en inputs de la grille (FFT, champs IP, série…) |
| `mapping/` | La grille, les cellules, l'algorithme génétique et le solveur |
| `outputs/` | OSC, MIDI, synthé granulaire |
| `view/server/`, `view/websocket/` | Les deux serveurs de contrôle |
| `save/` | Sauvegarde et chargement XML |
| `www/` | Les deux interfaces web |
| `tests/` | Tests unitaires (Boost.Test) et batterie d'intégration (Node) |

Tests : 4 suites unitaires (grille, solveur, WAV, HTTP) et 27 tests d'intégration qui lancent le vrai binaire et le pilotent comme un navigateur (sécurité, requêtes malformées, chaîne WAV → OSC, arrêt propre). La CI GitHub Actions construit l'image Docker sur Ubuntu à chaque pull request ; jamais de runner macOS.

Pièges du code :

- Boost doit rester sous la 1.87 : websocketpp 0.8 et le serveur HTTP utilisent `io_service`, supprimé ensuite.
- La grille est partagée entre threads : tout code qui parcourt ses listes hors des serveurs doit prendre `getMutex()`.
- Les recherches par nom ou id (`getOutputWithName`…) renvoient NULL : toujours tester.
- Linux est sensible à la casse des noms de fichiers et plus strict sur les `#include` que macOS.
- Une exception dans une requête est rattrapée ; un segfault ne l'est pas.
- Le `CLAUDE.md` du repo tient à jour ces règles pour Claude Code.

## Sécurité et limites connues

Le parcours WAV → grille → OSC est solide et testé ; le reste contient encore des bugs connus, listés ici par gravité. Déjà corrigé lors de la relance : grille partagée et verrouillée, serveurs sur localhost, origine WebSocket vérifiée, exceptions rattrapées, lecture WAV, solveur sans `exit()`.

| Zone | Problème | Conséquence |
| --- | --- | --- |
| Sécurité | Aucune authentification ; actions HTTP en GET | Une page web ouverte dans ton navigateur peut piloter MoOS |
| Synthé granulaire | Fichier source absent, lecture hors limites dans le callback audio, membres non initialisés | Plante dès qu'on le choisit |
| Capture réseau | Longueurs lues dans les paquets sans vérification ; index d'interface non borné ; `PacketLength` sans conversion d'ordre réseau | Plantage possible provoqué par une machine du réseau ; valeur `PacketLength` fausse |
| Modules pcap en sommeil | Débordement dans l'import CSV, longueur non initialisée (mots de passe), pointeurs non initialisés (KISS) | Plantent dès qu'on les réactive : à corriger avant |
| Mots de passe | Le module recopie le trafic en clair dans les logs | À ne jamais réactiver tel quel |
| MIDI | Un thread par note, sur un port MIDI non thread-safe | Des centaines de threads sur un flux FFT |
| Chargement XML | Cellule absente non vérifiée | Plantage si la sauvegarde ne correspond pas à l'input choisi |
| Inputs désactivés | Choisir Leap, ODBC ou Vidéo installe une coquille vide | Plus d'autre input possible sans redémarrer |
| Interface | `updateCell` lit mal les poids négatifs et à deux décimales ; `FreqEq` sort de la plage MIDI | Réglages faux sans message d'erreur |
| Chemins | Plusieurs chemins `/Users/…/LibLoAndCap/…` encore codés en dur | Fonctions concernées inopérantes |

## Et après : une vraie API, puis une interface qu'on a envie d'ouvrir

Le prochain chantier est la configuration web : la remplacer par une API unique et documentée, puis construire dessus une interface vivante. Aujourd'hui, on configure à l'aveugle : on ne voit pas les valeurs bouger, on ne peut pas changer d'input sans redémarrer, et deux protocoles se partagent la même grille.

Ce qui ne va pas aujourd'hui :

- Deux interfaces, deux protocoles (GET `.snf` en XML et WebSocket JSON), aucune ne fait tout.
- Des actions qui modifient l'état en GET, des paramètres lus par expressions régulières.
- Un input choisi une fois pour toutes ; une adresse WebSocket codée en dur (`ws://127.0.0.1:9002`).
- Aucun retour en direct : ni niveau des inputs, ni valeur des outputs.

Proposition d'API, en JSON, toutes les modifications en POST/PUT/PATCH/DELETE :

| Ressource | Méthodes | Rôle |
| --- | --- | --- |
| `/api/devices` | GET | Inputs disponibles et leur état (compilé, matériel présent) |
| `/api/input` | GET, PUT | Input actif ; le changer sans redémarrer |
| `/api/outputs`, `/api/outputs/{id}` | GET, POST, PATCH, DELETE | Outputs et leurs paramètres (hôte OSC, port MIDI…) |
| `/api/grid` | GET, PATCH | Poids de la grille, en lot |
| `/api/presets`, `/api/presets/{nom}` | GET, POST, PUT | Sauvegarder et rappeler une configuration complète |
| `/api/genetic/rate`, `/api/constraints` | POST | Les deux algorithmes de mapping |
| `/api/live` | WebSocket | Flux des valeurs d'inputs et d'outputs, environ 30 images/s |

Avec : une spécification OpenAPI comme contrat, un jeton d'accès, les tests d'intégration réécrits sur l'API, et les anciennes interfaces retirées une fois la nouvelle prête.

Idées pour la nouvelle interface :

- Une matrice vivante : chaque input affiche son niveau, chaque output sa valeur, les poids se règlent en glissant.
- Des presets en un clic, un bouton « au hasard », et la note étoilée de l'algorithme génétique directement dans la grille.
- Le spectre FFT dessiné en temps réel au-dessus des 512 bandes.

Autres pistes : faire sortir le MIDI et l'audio de Docker sur un hôte Linux (accès à `/dev/snd`), corriger le synthé granulaire, sécuriser la capture réseau pour le Raspberry Pi.

Questions ouvertes :

- L'API dans le binaire C++ (Boost.Beast) ou dans un petit service à côté, qui pilote le moteur ?
- Quelle techno pour la nouvelle interface ?
- Faut-il garder les deux anciennes interfaces pendant la transition ?
