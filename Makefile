# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Applications/CMake 2.8-12.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-12.app/Contents/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-12.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ludoviclaffineur/Documents/LibLoAndCap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ludoviclaffineur/Documents/LibLoAndCap

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	"/Applications/CMake 2.8-12.app/Contents/bin/ccmake" -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"/Applications/CMake 2.8-12.app/Contents/bin/cmake" -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/ludoviclaffineur/Documents/LibLoAndCap/CMakeFiles /Users/ludoviclaffineur/Documents/LibLoAndCap/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/ludoviclaffineur/Documents/LibLoAndCap/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named bin/MoOS

# Build rule for target.
bin/MoOS: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 bin/MoOS
.PHONY : bin/MoOS

# fast build rule for target.
bin/MoOS/fast:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/build
.PHONY : bin/MoOS/fast

Inputs/Input.o: Inputs/Input.cpp.o
.PHONY : Inputs/Input.o

# target to build an object file
Inputs/Input.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/Inputs/Input.cpp.o
.PHONY : Inputs/Input.cpp.o

Inputs/Input.i: Inputs/Input.cpp.i
.PHONY : Inputs/Input.i

# target to preprocess a source file
Inputs/Input.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/Inputs/Input.cpp.i
.PHONY : Inputs/Input.cpp.i

Inputs/Input.s: Inputs/Input.cpp.s
.PHONY : Inputs/Input.s

# target to generate assembly for a file
Inputs/Input.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/Inputs/Input.cpp.s
.PHONY : Inputs/Input.cpp.s

LibLoAndCap/main.o: LibLoAndCap/main.cpp.o
.PHONY : LibLoAndCap/main.o

# target to build an object file
LibLoAndCap/main.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/LibLoAndCap/main.cpp.o
.PHONY : LibLoAndCap/main.cpp.o

LibLoAndCap/main.i: LibLoAndCap/main.cpp.i
.PHONY : LibLoAndCap/main.i

# target to preprocess a source file
LibLoAndCap/main.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/LibLoAndCap/main.cpp.i
.PHONY : LibLoAndCap/main.cpp.i

LibLoAndCap/main.s: LibLoAndCap/main.cpp.s
.PHONY : LibLoAndCap/main.s

# target to generate assembly for a file
LibLoAndCap/main.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/LibLoAndCap/main.cpp.s
.PHONY : LibLoAndCap/main.cpp.s

capture/PcapHandler.o: capture/PcapHandler.cpp.o
.PHONY : capture/PcapHandler.o

# target to build an object file
capture/PcapHandler.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/capture/PcapHandler.cpp.o
.PHONY : capture/PcapHandler.cpp.o

capture/PcapHandler.i: capture/PcapHandler.cpp.i
.PHONY : capture/PcapHandler.i

# target to preprocess a source file
capture/PcapHandler.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/capture/PcapHandler.cpp.i
.PHONY : capture/PcapHandler.cpp.i

capture/PcapHandler.s: capture/PcapHandler.cpp.s
.PHONY : capture/PcapHandler.s

# target to generate assembly for a file
capture/PcapHandler.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/capture/PcapHandler.cpp.s
.PHONY : capture/PcapHandler.cpp.s

mapping/Cell.o: mapping/Cell.cpp.o
.PHONY : mapping/Cell.o

# target to build an object file
mapping/Cell.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/mapping/Cell.cpp.o
.PHONY : mapping/Cell.cpp.o

mapping/Cell.i: mapping/Cell.cpp.i
.PHONY : mapping/Cell.i

# target to preprocess a source file
mapping/Cell.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/mapping/Cell.cpp.i
.PHONY : mapping/Cell.cpp.i

mapping/Cell.s: mapping/Cell.cpp.s
.PHONY : mapping/Cell.s

# target to generate assembly for a file
mapping/Cell.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/mapping/Cell.cpp.s
.PHONY : mapping/Cell.cpp.s

mapping/Grid.o: mapping/Grid.cpp.o
.PHONY : mapping/Grid.o

# target to build an object file
mapping/Grid.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/mapping/Grid.cpp.o
.PHONY : mapping/Grid.cpp.o

mapping/Grid.i: mapping/Grid.cpp.i
.PHONY : mapping/Grid.i

# target to preprocess a source file
mapping/Grid.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/mapping/Grid.cpp.i
.PHONY : mapping/Grid.cpp.i

mapping/Grid.s: mapping/Grid.cpp.s
.PHONY : mapping/Grid.s

# target to generate assembly for a file
mapping/Grid.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/mapping/Grid.cpp.s
.PHONY : mapping/Grid.cpp.s

outputs/OscHandler.o: outputs/OscHandler.cpp.o
.PHONY : outputs/OscHandler.o

# target to build an object file
outputs/OscHandler.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/outputs/OscHandler.cpp.o
.PHONY : outputs/OscHandler.cpp.o

outputs/OscHandler.i: outputs/OscHandler.cpp.i
.PHONY : outputs/OscHandler.i

# target to preprocess a source file
outputs/OscHandler.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/outputs/OscHandler.cpp.i
.PHONY : outputs/OscHandler.cpp.i

outputs/OscHandler.s: outputs/OscHandler.cpp.s
.PHONY : outputs/OscHandler.s

# target to generate assembly for a file
outputs/OscHandler.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/outputs/OscHandler.cpp.s
.PHONY : outputs/OscHandler.cpp.s

outputs/OutputsHandler.o: outputs/OutputsHandler.cpp.o
.PHONY : outputs/OutputsHandler.o

# target to build an object file
outputs/OutputsHandler.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/outputs/OutputsHandler.cpp.o
.PHONY : outputs/OutputsHandler.cpp.o

outputs/OutputsHandler.i: outputs/OutputsHandler.cpp.i
.PHONY : outputs/OutputsHandler.i

# target to preprocess a source file
outputs/OutputsHandler.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/outputs/OutputsHandler.cpp.i
.PHONY : outputs/OutputsHandler.cpp.i

outputs/OutputsHandler.s: outputs/OutputsHandler.cpp.s
.PHONY : outputs/OutputsHandler.s

# target to generate assembly for a file
outputs/OutputsHandler.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/outputs/OutputsHandler.cpp.s
.PHONY : outputs/OutputsHandler.cpp.s

processings/PcapEthernetProcessing.o: processings/PcapEthernetProcessing.cpp.o
.PHONY : processings/PcapEthernetProcessing.o

# target to build an object file
processings/PcapEthernetProcessing.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/processings/PcapEthernetProcessing.cpp.o
.PHONY : processings/PcapEthernetProcessing.cpp.o

processings/PcapEthernetProcessing.i: processings/PcapEthernetProcessing.cpp.i
.PHONY : processings/PcapEthernetProcessing.i

# target to preprocess a source file
processings/PcapEthernetProcessing.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/processings/PcapEthernetProcessing.cpp.i
.PHONY : processings/PcapEthernetProcessing.cpp.i

processings/PcapEthernetProcessing.s: processings/PcapEthernetProcessing.cpp.s
.PHONY : processings/PcapEthernetProcessing.s

# target to generate assembly for a file
processings/PcapEthernetProcessing.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/processings/PcapEthernetProcessing.cpp.s
.PHONY : processings/PcapEthernetProcessing.cpp.s

processings/PcapIpProcessing.o: processings/PcapIpProcessing.cpp.o
.PHONY : processings/PcapIpProcessing.o

# target to build an object file
processings/PcapIpProcessing.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/processings/PcapIpProcessing.cpp.o
.PHONY : processings/PcapIpProcessing.cpp.o

processings/PcapIpProcessing.i: processings/PcapIpProcessing.cpp.i
.PHONY : processings/PcapIpProcessing.i

# target to preprocess a source file
processings/PcapIpProcessing.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/processings/PcapIpProcessing.cpp.i
.PHONY : processings/PcapIpProcessing.cpp.i

processings/PcapIpProcessing.s: processings/PcapIpProcessing.cpp.s
.PHONY : processings/PcapIpProcessing.s

# target to generate assembly for a file
processings/PcapIpProcessing.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/processings/PcapIpProcessing.cpp.s
.PHONY : processings/PcapIpProcessing.cpp.s

processings/PcapLocationProcessing.o: processings/PcapLocationProcessing.cpp.o
.PHONY : processings/PcapLocationProcessing.o

# target to build an object file
processings/PcapLocationProcessing.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/processings/PcapLocationProcessing.cpp.o
.PHONY : processings/PcapLocationProcessing.cpp.o

processings/PcapLocationProcessing.i: processings/PcapLocationProcessing.cpp.i
.PHONY : processings/PcapLocationProcessing.i

# target to preprocess a source file
processings/PcapLocationProcessing.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/processings/PcapLocationProcessing.cpp.i
.PHONY : processings/PcapLocationProcessing.cpp.i

processings/PcapLocationProcessing.s: processings/PcapLocationProcessing.cpp.s
.PHONY : processings/PcapLocationProcessing.s

# target to generate assembly for a file
processings/PcapLocationProcessing.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/processings/PcapLocationProcessing.cpp.s
.PHONY : processings/PcapLocationProcessing.cpp.s

save/SaveXml.o: save/SaveXml.cpp.o
.PHONY : save/SaveXml.o

# target to build an object file
save/SaveXml.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/save/SaveXml.cpp.o
.PHONY : save/SaveXml.cpp.o

save/SaveXml.i: save/SaveXml.cpp.i
.PHONY : save/SaveXml.i

# target to preprocess a source file
save/SaveXml.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/save/SaveXml.cpp.i
.PHONY : save/SaveXml.cpp.i

save/SaveXml.s: save/SaveXml.cpp.s
.PHONY : save/SaveXml.s

# target to generate assembly for a file
save/SaveXml.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/save/SaveXml.cpp.s
.PHONY : save/SaveXml.cpp.s

utils/Converter.o: utils/Converter.cpp.o
.PHONY : utils/Converter.o

# target to build an object file
utils/Converter.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/utils/Converter.cpp.o
.PHONY : utils/Converter.cpp.o

utils/Converter.i: utils/Converter.cpp.i
.PHONY : utils/Converter.i

# target to preprocess a source file
utils/Converter.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/utils/Converter.cpp.i
.PHONY : utils/Converter.cpp.i

utils/Converter.s: utils/Converter.cpp.s
.PHONY : utils/Converter.s

# target to generate assembly for a file
utils/Converter.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/utils/Converter.cpp.s
.PHONY : utils/Converter.cpp.s

utils/CsvImporter.o: utils/CsvImporter.cpp.o
.PHONY : utils/CsvImporter.o

# target to build an object file
utils/CsvImporter.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/utils/CsvImporter.cpp.o
.PHONY : utils/CsvImporter.cpp.o

utils/CsvImporter.i: utils/CsvImporter.cpp.i
.PHONY : utils/CsvImporter.i

# target to preprocess a source file
utils/CsvImporter.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/utils/CsvImporter.cpp.i
.PHONY : utils/CsvImporter.cpp.i

utils/CsvImporter.s: utils/CsvImporter.cpp.s
.PHONY : utils/CsvImporter.s

# target to generate assembly for a file
utils/CsvImporter.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/utils/CsvImporter.cpp.s
.PHONY : utils/CsvImporter.cpp.s

utils/LocationIp.o: utils/LocationIp.cpp.o
.PHONY : utils/LocationIp.o

# target to build an object file
utils/LocationIp.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/utils/LocationIp.cpp.o
.PHONY : utils/LocationIp.cpp.o

utils/LocationIp.i: utils/LocationIp.cpp.i
.PHONY : utils/LocationIp.i

# target to preprocess a source file
utils/LocationIp.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/utils/LocationIp.cpp.i
.PHONY : utils/LocationIp.cpp.i

utils/LocationIp.s: utils/LocationIp.cpp.s
.PHONY : utils/LocationIp.s

# target to generate assembly for a file
utils/LocationIp.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/utils/LocationIp.cpp.s
.PHONY : utils/LocationIp.cpp.s

view/server/SnfHandler.o: view/server/SnfHandler.cpp.o
.PHONY : view/server/SnfHandler.o

# target to build an object file
view/server/SnfHandler.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/SnfHandler.cpp.o
.PHONY : view/server/SnfHandler.cpp.o

view/server/SnfHandler.i: view/server/SnfHandler.cpp.i
.PHONY : view/server/SnfHandler.i

# target to preprocess a source file
view/server/SnfHandler.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/SnfHandler.cpp.i
.PHONY : view/server/SnfHandler.cpp.i

view/server/SnfHandler.s: view/server/SnfHandler.cpp.s
.PHONY : view/server/SnfHandler.s

# target to generate assembly for a file
view/server/SnfHandler.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/SnfHandler.cpp.s
.PHONY : view/server/SnfHandler.cpp.s

view/server/connection.o: view/server/connection.cpp.o
.PHONY : view/server/connection.o

# target to build an object file
view/server/connection.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/connection.cpp.o
.PHONY : view/server/connection.cpp.o

view/server/connection.i: view/server/connection.cpp.i
.PHONY : view/server/connection.i

# target to preprocess a source file
view/server/connection.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/connection.cpp.i
.PHONY : view/server/connection.cpp.i

view/server/connection.s: view/server/connection.cpp.s
.PHONY : view/server/connection.s

# target to generate assembly for a file
view/server/connection.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/connection.cpp.s
.PHONY : view/server/connection.cpp.s

view/server/connection_manager.o: view/server/connection_manager.cpp.o
.PHONY : view/server/connection_manager.o

# target to build an object file
view/server/connection_manager.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/connection_manager.cpp.o
.PHONY : view/server/connection_manager.cpp.o

view/server/connection_manager.i: view/server/connection_manager.cpp.i
.PHONY : view/server/connection_manager.i

# target to preprocess a source file
view/server/connection_manager.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/connection_manager.cpp.i
.PHONY : view/server/connection_manager.cpp.i

view/server/connection_manager.s: view/server/connection_manager.cpp.s
.PHONY : view/server/connection_manager.s

# target to generate assembly for a file
view/server/connection_manager.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/connection_manager.cpp.s
.PHONY : view/server/connection_manager.cpp.s

view/server/mime_types.o: view/server/mime_types.cpp.o
.PHONY : view/server/mime_types.o

# target to build an object file
view/server/mime_types.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/mime_types.cpp.o
.PHONY : view/server/mime_types.cpp.o

view/server/mime_types.i: view/server/mime_types.cpp.i
.PHONY : view/server/mime_types.i

# target to preprocess a source file
view/server/mime_types.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/mime_types.cpp.i
.PHONY : view/server/mime_types.cpp.i

view/server/mime_types.s: view/server/mime_types.cpp.s
.PHONY : view/server/mime_types.s

# target to generate assembly for a file
view/server/mime_types.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/mime_types.cpp.s
.PHONY : view/server/mime_types.cpp.s

view/server/reply.o: view/server/reply.cpp.o
.PHONY : view/server/reply.o

# target to build an object file
view/server/reply.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/reply.cpp.o
.PHONY : view/server/reply.cpp.o

view/server/reply.i: view/server/reply.cpp.i
.PHONY : view/server/reply.i

# target to preprocess a source file
view/server/reply.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/reply.cpp.i
.PHONY : view/server/reply.cpp.i

view/server/reply.s: view/server/reply.cpp.s
.PHONY : view/server/reply.s

# target to generate assembly for a file
view/server/reply.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/reply.cpp.s
.PHONY : view/server/reply.cpp.s

view/server/request_handler.o: view/server/request_handler.cpp.o
.PHONY : view/server/request_handler.o

# target to build an object file
view/server/request_handler.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/request_handler.cpp.o
.PHONY : view/server/request_handler.cpp.o

view/server/request_handler.i: view/server/request_handler.cpp.i
.PHONY : view/server/request_handler.i

# target to preprocess a source file
view/server/request_handler.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/request_handler.cpp.i
.PHONY : view/server/request_handler.cpp.i

view/server/request_handler.s: view/server/request_handler.cpp.s
.PHONY : view/server/request_handler.s

# target to generate assembly for a file
view/server/request_handler.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/request_handler.cpp.s
.PHONY : view/server/request_handler.cpp.s

view/server/request_parser.o: view/server/request_parser.cpp.o
.PHONY : view/server/request_parser.o

# target to build an object file
view/server/request_parser.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/request_parser.cpp.o
.PHONY : view/server/request_parser.cpp.o

view/server/request_parser.i: view/server/request_parser.cpp.i
.PHONY : view/server/request_parser.i

# target to preprocess a source file
view/server/request_parser.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/request_parser.cpp.i
.PHONY : view/server/request_parser.cpp.i

view/server/request_parser.s: view/server/request_parser.cpp.s
.PHONY : view/server/request_parser.s

# target to generate assembly for a file
view/server/request_parser.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/request_parser.cpp.s
.PHONY : view/server/request_parser.cpp.s

view/server/server.o: view/server/server.cpp.o
.PHONY : view/server/server.o

# target to build an object file
view/server/server.cpp.o:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/server.cpp.o
.PHONY : view/server/server.cpp.o

view/server/server.i: view/server/server.cpp.i
.PHONY : view/server/server.i

# target to preprocess a source file
view/server/server.cpp.i:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/server.cpp.i
.PHONY : view/server/server.cpp.i

view/server/server.s: view/server/server.cpp.s
.PHONY : view/server/server.s

# target to generate assembly for a file
view/server/server.cpp.s:
	$(MAKE) -f CMakeFiles/bin/MoOS.dir/build.make CMakeFiles/bin/MoOS.dir/view/server/server.cpp.s
.PHONY : view/server/server.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... bin/MoOS"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Inputs/Input.o"
	@echo "... Inputs/Input.i"
	@echo "... Inputs/Input.s"
	@echo "... LibLoAndCap/main.o"
	@echo "... LibLoAndCap/main.i"
	@echo "... LibLoAndCap/main.s"
	@echo "... capture/PcapHandler.o"
	@echo "... capture/PcapHandler.i"
	@echo "... capture/PcapHandler.s"
	@echo "... mapping/Cell.o"
	@echo "... mapping/Cell.i"
	@echo "... mapping/Cell.s"
	@echo "... mapping/Grid.o"
	@echo "... mapping/Grid.i"
	@echo "... mapping/Grid.s"
	@echo "... outputs/OscHandler.o"
	@echo "... outputs/OscHandler.i"
	@echo "... outputs/OscHandler.s"
	@echo "... outputs/OutputsHandler.o"
	@echo "... outputs/OutputsHandler.i"
	@echo "... outputs/OutputsHandler.s"
	@echo "... processings/PcapEthernetProcessing.o"
	@echo "... processings/PcapEthernetProcessing.i"
	@echo "... processings/PcapEthernetProcessing.s"
	@echo "... processings/PcapIpProcessing.o"
	@echo "... processings/PcapIpProcessing.i"
	@echo "... processings/PcapIpProcessing.s"
	@echo "... processings/PcapLocationProcessing.o"
	@echo "... processings/PcapLocationProcessing.i"
	@echo "... processings/PcapLocationProcessing.s"
	@echo "... save/SaveXml.o"
	@echo "... save/SaveXml.i"
	@echo "... save/SaveXml.s"
	@echo "... utils/Converter.o"
	@echo "... utils/Converter.i"
	@echo "... utils/Converter.s"
	@echo "... utils/CsvImporter.o"
	@echo "... utils/CsvImporter.i"
	@echo "... utils/CsvImporter.s"
	@echo "... utils/LocationIp.o"
	@echo "... utils/LocationIp.i"
	@echo "... utils/LocationIp.s"
	@echo "... view/server/SnfHandler.o"
	@echo "... view/server/SnfHandler.i"
	@echo "... view/server/SnfHandler.s"
	@echo "... view/server/connection.o"
	@echo "... view/server/connection.i"
	@echo "... view/server/connection.s"
	@echo "... view/server/connection_manager.o"
	@echo "... view/server/connection_manager.i"
	@echo "... view/server/connection_manager.s"
	@echo "... view/server/mime_types.o"
	@echo "... view/server/mime_types.i"
	@echo "... view/server/mime_types.s"
	@echo "... view/server/reply.o"
	@echo "... view/server/reply.i"
	@echo "... view/server/reply.s"
	@echo "... view/server/request_handler.o"
	@echo "... view/server/request_handler.i"
	@echo "... view/server/request_handler.s"
	@echo "... view/server/request_parser.o"
	@echo "... view/server/request_parser.i"
	@echo "... view/server/request_parser.s"
	@echo "... view/server/server.o"
	@echo "... view/server/server.i"
	@echo "... view/server/server.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

