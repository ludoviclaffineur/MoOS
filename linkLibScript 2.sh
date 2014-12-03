#!/bin/sh

#  linkLibScript.sh
#  LibLoAndCap
#
#  Created by Ludovic Laffineur on 4/03/14.
#  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.

install_name_tool -change /usr/local/lib/liblo.7.dylib @executable_path/liblo.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libgecodedriver.35.dylib @executable_path/libgecodedriver.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libgecodeminimodel.35.dylib @executable_path/libgecodeminimodel.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libgecodeint.35.dylib @executable_path/libgecodeint.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libgecodesupport.35.dylib @executable_path/libgecodesupport.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libgecodekernel.35.dylib @executable_path/libgecodekernel.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libgecodesearch.35.dylib @executable_path/libgecodesearch.dylib ./LibLoAndCap
install_name_tool -change /opt/local/lib/libgecodefloat.35.dylib @executable_path/libgecodesearch.dylib ./LibLoAndCap


install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./libboost_thread-mt.dylib
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./libboost_thread-mt.dylib



install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./libgecodedriver.dylib
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./libgecodedriver.dylib
install_name_tool -change /opt/local/lib/libgecodedriver.35.dylib @executable_path/libgecodedriver.dylib ./libgecodedriver.dylib
install_name_tool -change /opt/local/lib/libgecodeminimodel.35.dylib @executable_path/libgecodeminimodel.dylib ./libgecodedriver.dylib
install_name_tool -change /opt/local/lib/libgecodeint.35.dylib @executable_path/libgecodeint.dylib ./libgecodedriver.dylib
install_name_tool -change /opt/local/lib/libgecodesupport.35.dylib @executable_path/libgecodesupport.dylib ./libgecodedriver.dylib
install_name_tool -change /opt/local/lib/libgecodekernel.35.dylib @executable_path/libgecodekernel.dylib ./libgecodedriver.dylib
install_name_tool -change /opt/local/lib/libgecodesearch.35.dylib @executable_path/libgecodesearch.dylib ./libgecodedriver.dylib
install_name_tool -change /opt/local/lib/libgecodefloat.35.dylib @executable_path/libgecodesearch.dylib ./libgecodedriver.dylib


install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./libgecodefloat.dylib
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./libgecodefloat.dylib
install_name_tool -change /opt/local/lib/libgecodedriver.35.dylib @executable_path/libgecodedriver.dylib ./libgecodefloat.dylib
install_name_tool -change /opt/local/lib/libgecodeminimodel.35.dylib @executable_path/libgecodeminimodel.dylib ./libgecodefloat.dylib
install_name_tool -change /opt/local/lib/libgecodeint.35.dylib @executable_path/libgecodeint.dylib ./libgecodefloat.dylib
install_name_tool -change /opt/local/lib/libgecodesupport.35.dylib @executable_path/libgecodesupport.dylib ./libgecodefloat.dylib
install_name_tool -change /opt/local/lib/libgecodekernel.35.dylib @executable_path/libgecodekernel.dylib ./libgecodefloat.dylib
install_name_tool -change /opt/local/lib/libgecodesearch.35.dylib @executable_path/libgecodesearch.dylib ./libgecodefloat.dylib
install_name_tool -change /opt/local/lib/libgecodefloat.35.dylib @executable_path/libgecodesearch.dylib ./libgecodefloat.dylib

install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./libgecodeminimodel.dylib
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./libgecodeminimodel.dylib
install_name_tool -change /opt/local/lib/libgecodedriver.35.dylib @executable_path/libgecodedriver.dylib ./libgecodeminimodel.dylib
install_name_tool -change /opt/local/lib/libgecodeminimodel.35.dylib @executable_path/libgecodeminimodel.dylib ./libgecodeminimodel.dylib
install_name_tool -change /opt/local/lib/libgecodeint.35.dylib @executable_path/libgecodeint.dylib ./libgecodeminimodel.dylib
install_name_tool -change /opt/local/lib/libgecodesupport.35.dylib @executable_path/libgecodesupport.dylib ./libgecodeminimodel.dylib
install_name_tool -change /opt/local/lib/libgecodekernel.35.dylib @executable_path/libgecodekernel.dylib ./libgecodeminimodel.dylib
install_name_tool -change /opt/local/lib/libgecodesearch.35.dylib @executable_path/libgecodesearch.dylib ./libgecodeminimodel.dylib
install_name_tool -change /opt/local/lib/libgecodefloat.35.dylib @executable_path/libgecodesearch.dylib ./libgecodeminimodel.dylib
install_name_tool -change /opt/local/lib/libgecodeset.35.dylib @executable_path/libgecodeset.35.0.dylib ./libgecodeminimodel.dylib

install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./libgecodeint.dylib
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./libgecodeint.dylib
install_name_tool -change /opt/local/lib/libgecodedriver.35.dylib @executable_path/libgecodedriver.dylib ./libgecodeint.dylib
install_name_tool -change /opt/local/lib/libgecodeminimodel.35.dylib @executable_path/libgecodeminimodel.dylib ./libgecodeint.dylib
install_name_tool -change /opt/local/lib/libgecodeint.35.dylib @executable_path/libgecodeint.dylib ./libgecodeint.dylib
install_name_tool -change /opt/local/lib/libgecodesupport.35.dylib @executable_path/libgecodesupport.dylib ./libgecodeint.dylib
install_name_tool -change /opt/local/lib/libgecodekernel.35.dylib @executable_path/libgecodekernel.dylib ./libgecodeint.dylib
install_name_tool -change /opt/local/lib/libgecodesearch.35.dylib @executable_path/libgecodesearch.dylib ./libgecodeint.dylib
install_name_tool -change /opt/local/lib/libgecodefloat.35.dylib @executable_path/libgecodesearch.dylib ./libgecodeint.dylib

install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./libgecodesupport.dylib
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./libgecodesupport.dylib
install_name_tool -change /opt/local/lib/libgecodedriver.35.dylib @executable_path/libgecodedriver.dylib ./libgecodesupport.dylib
install_name_tool -change /opt/local/lib/libgecodeminimodel.35.dylib @executable_path/libgecodeminimodel.dylib ./libgecodesupport.dylib
install_name_tool -change /opt/local/lib/libgecodeint.35.dylib @executable_path/libgecodeint.dylib ./libgecodesupport.dylib
install_name_tool -change /opt/local/lib/libgecodesupport.35.dylib @executable_path/libgecodesupport.dylib ./libgecodesupport.dylib
install_name_tool -change /opt/local/lib/libgecodekernel.35.dylib @executable_path/libgecodekernel.dylib ./libgecodesupport.dylib
install_name_tool -change /opt/local/lib/libgecodesearch.35.dylib @executable_path/libgecodesearch.dylib ./libgecodesupport.dylib
install_name_tool -change /opt/local/lib/libgecodefloat.35.dylib @executable_path/libgecodesearch.dylib ./libgecodesupport.dylib


install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./libgecodekernel.dylib
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./libgecodekernel.dylib
install_name_tool -change /opt/local/lib/libgecodedriver.35.dylib @executable_path/libgecodedriver.dylib ./libgecodekernel.dylib
install_name_tool -change /opt/local/lib/libgecodeminimodel.35.dylib @executable_path/libgecodeminimodel.dylib ./libgecodekernel.dylib
install_name_tool -change /opt/local/lib/libgecodeint.35.dylib @executable_path/libgecodeint.dylib ./libgecodekernel.dylib
install_name_tool -change /opt/local/lib/libgecodesupport.35.dylib @executable_path/libgecodesupport.dylib ./libgecodekernel.dylib
install_name_tool -change /opt/local/lib/libgecodekernel.35.dylib @executable_path/libgecodekernel.dylib ./libgecodekernel.dylib
install_name_tool -change /opt/local/lib/libgecodesearch.35.dylib @executable_path/libgecodesearch.dylib ./libgecodekernel.dylib
install_name_tool -change /opt/local/lib/libgecodefloat.35.dylib @executable_path/libgecodesearch.dylib ./libgecodekernel.dylib

install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./libgecodesearch.dylib
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./libgecodesearch.dylib
install_name_tool -change /opt/local/lib/libgecodedriver.35.dylib @executable_path/libgecodedriver.dylib ./libgecodesearch.dylib
install_name_tool -change /opt/local/lib/libgecodeminimodel.35.dylib @executable_path/libgecodeminimodel.dylib ./libgecodesearch.dylib
install_name_tool -change /opt/local/lib/libgecodeint.35.dylib @executable_path/libgecodeint.dylib ./libgecodesearch.dylib
install_name_tool -change /opt/local/lib/libgecodesupport.35.dylib @executable_path/libgecodesupport.dylib ./libgecodesearch.dylib
install_name_tool -change /opt/local/lib/libgecodekernel.35.dylib @executable_path/libgecodekernel.dylib ./libgecodesearch.dylib
install_name_tool -change /opt/local/lib/libgecodesearch.35.dylib @executable_path/libgecodesearch.dylib ./libgecodesearch.dylib
install_name_tool -change /opt/local/lib/libgecodefloat.35.dylib @executable_path/libgecodesearch.dylib ./libgecodesearch.dylib

install_name_tool -change /opt/local/lib/libboost_thread-mt.dylib @executable_path/libboost_thread-mt.dylib ./libgecodeset.35.0.dylib
install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/libboost_system-mt.dylib ./libgecodeset.35.0.dylib
install_name_tool -change /opt/local/lib/libgecodedriver.35.dylib @executable_path/libgecodedriver.dylib ./libgecodeset.35.0.dylib
install_name_tool -change /opt/local/lib/libgecodeminimodel.35.dylib @executable_path/libgecodeminimodel.dylib ./libgecodeset.35.0.dylib
install_name_tool -change /opt/local/lib/libgecodeint.35.dylib @executable_path/libgecodeint.dylib ./libgecodeset.35.0.dylib
install_name_tool -change /opt/local/lib/libgecodesupport.35.dylib @executable_path/libgecodesupport.dylib ./libgecodeset.35.0.dylib
install_name_tool -change /opt/local/lib/libgecodekernel.35.dylib @executable_path/libgecodekernel.dylib ./libgecodeset.35.0.dylib
install_name_tool -change /opt/local/lib/libgecodesearch.35.dylib @executable_path/libgecodesearch.dylib ./libgecodeset.35.0.dylib
install_name_tool -change /opt/local/lib/libgecodefloat.35.dylib @executable_path/libgecodesearch.dylib ./libgecodeset.35.0.dylib