#!/bin/sh

#  linkLibScript.sh
#  LibLoAndCap
#
#  Created by Ludovic Laffineur on 4/03/14.
#  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.

install_name_tool -change /usr/local/lib/liblo.7.dylib @executable_path/liblo.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./LibLoAndCap