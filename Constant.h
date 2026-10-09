//
//  Constant.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 16/03/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef LibLoAndCap_Constant_h
#define LibLoAndCap_Constant_h
#include <cstdlib>
#include <string>
#include <sstream>
#ifndef MOOS_SOURCE_DIR
#define MOOS_SOURCE_DIR "."
#endif
// Racine des ressources (www/, data/) : la variable d'environnement MOOS_RESOURCE_DIR
// si elle est définie (version installée, image Docker), sinon la racine du repo
// injectée par CMake.
inline std::string moosResourceDir(){
    const char* dir = std::getenv("MOOS_RESOURCE_DIR");
    return (dir && *dir) ? dir : MOOS_SOURCE_DIR;
}
const std::string CURRENT_PATH = moosResourceDir();

// Hôte de destination des sorties OSC créées par défaut : MOOS_OSC_HOST si définie
// (ex. host.docker.internal depuis un conteneur), sinon 127.0.0.1.
inline std::string moosOscHost(){
    const char* host = std::getenv("MOOS_OSC_HOST");
    return (host && *host) ? host : "127.0.0.1";
}

#endif
