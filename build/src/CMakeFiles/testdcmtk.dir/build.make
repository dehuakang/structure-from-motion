# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.8.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.8.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kangdehua/Documents/RegistrationProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kangdehua/Documents/RegistrationProject/build

# Include any dependencies generated for this target.
include src/CMakeFiles/testdcmtk.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/testdcmtk.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/testdcmtk.dir/flags.make

src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o: src/CMakeFiles/testdcmtk.dir/flags.make
src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o: ../src/testdcmtk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kangdehua/Documents/RegistrationProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o -c /Users/kangdehua/Documents/RegistrationProject/src/testdcmtk.cpp

src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testdcmtk.dir/testdcmtk.cpp.i"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kangdehua/Documents/RegistrationProject/src/testdcmtk.cpp > CMakeFiles/testdcmtk.dir/testdcmtk.cpp.i

src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testdcmtk.dir/testdcmtk.cpp.s"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kangdehua/Documents/RegistrationProject/src/testdcmtk.cpp -o CMakeFiles/testdcmtk.dir/testdcmtk.cpp.s

src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o.requires:

.PHONY : src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o.requires

src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o.provides: src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/testdcmtk.dir/build.make src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o.provides.build
.PHONY : src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o.provides

src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o.provides.build: src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o


# Object files for target testdcmtk
testdcmtk_OBJECTS = \
"CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o"

# External object files for target testdcmtk
testdcmtk_EXTERNAL_OBJECTS =

../bin/testdcmtk: src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o
../bin/testdcmtk: src/CMakeFiles/testdcmtk.dir/build.make
../bin/testdcmtk: /usr/local/lib/libofstd.a
../bin/testdcmtk: /usr/local/lib/liboflog.a
../bin/testdcmtk: /usr/local/lib/libdcmdata.a
../bin/testdcmtk: /usr/local/lib/libi2d.a
../bin/testdcmtk: /usr/local/lib/libdcmimgle.a
../bin/testdcmtk: /usr/local/lib/libdcmimage.a
../bin/testdcmtk: /usr/local/lib/libdcmjpeg.a
../bin/testdcmtk: /usr/local/lib/libijg8.a
../bin/testdcmtk: /usr/local/lib/libijg12.a
../bin/testdcmtk: /usr/local/lib/libijg16.a
../bin/testdcmtk: /usr/local/lib/libdcmjpls.a
../bin/testdcmtk: /usr/local/lib/libcharls.a
../bin/testdcmtk: /usr/local/lib/libdcmtls.a
../bin/testdcmtk: /usr/local/lib/libdcmnet.a
../bin/testdcmtk: /usr/local/lib/libdcmsr.a
../bin/testdcmtk: /usr/local/lib/libcmr.a
../bin/testdcmtk: /usr/local/lib/libdcmdsig.a
../bin/testdcmtk: /usr/local/lib/libdcmwlm.a
../bin/testdcmtk: /usr/local/lib/libdcmqrdb.a
../bin/testdcmtk: /usr/local/lib/libdcmpstat.a
../bin/testdcmtk: /usr/local/lib/libdcmrt.a
../bin/testdcmtk: /usr/local/lib/libdcmiod.a
../bin/testdcmtk: /usr/local/lib/libdcmfg.a
../bin/testdcmtk: /usr/local/lib/libdcmseg.a
../bin/testdcmtk: /usr/local/lib/libdcmtract.a
../bin/testdcmtk: /usr/local/lib/libdcmpmap.a
../bin/testdcmtk: ../lib/libdcmtkcommon.a
../bin/testdcmtk: /usr/local/lib/libdcmtls.a
../bin/testdcmtk: /usr/local/lib/libdcmsr.a
../bin/testdcmtk: /usr/local/lib/libdcmimage.a
../bin/testdcmtk: /usr/local/lib/libtiff.dylib
../bin/testdcmtk: /usr/local/lib/libjpeg.dylib
../bin/testdcmtk: /usr/local/lib/libpng.dylib
../bin/testdcmtk: /usr/lib/libxml2.dylib
../bin/testdcmtk: /usr/local/lib/libdcmdsig.a
../bin/testdcmtk: /usr/local/opt/openssl/lib/libssl.dylib
../bin/testdcmtk: /usr/local/opt/openssl/lib/libcrypto.dylib
../bin/testdcmtk: /usr/local/lib/libdcmqrdb.a
../bin/testdcmtk: /usr/local/lib/libdcmnet.a
../bin/testdcmtk: /usr/local/lib/libdcmimgle.a
../bin/testdcmtk: /usr/local/lib/libdcmfg.a
../bin/testdcmtk: /usr/local/lib/libdcmiod.a
../bin/testdcmtk: /usr/local/lib/libdcmdata.a
../bin/testdcmtk: /usr/local/lib/liboflog.a
../bin/testdcmtk: /usr/local/lib/libofstd.a
../bin/testdcmtk: /usr/lib/libiconv.dylib
../bin/testdcmtk: /usr/lib/libcharset.dylib
../bin/testdcmtk: /usr/lib/libz.dylib
../bin/testdcmtk: src/CMakeFiles/testdcmtk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kangdehua/Documents/RegistrationProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/testdcmtk"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testdcmtk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/testdcmtk.dir/build: ../bin/testdcmtk

.PHONY : src/CMakeFiles/testdcmtk.dir/build

src/CMakeFiles/testdcmtk.dir/requires: src/CMakeFiles/testdcmtk.dir/testdcmtk.cpp.o.requires

.PHONY : src/CMakeFiles/testdcmtk.dir/requires

src/CMakeFiles/testdcmtk.dir/clean:
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && $(CMAKE_COMMAND) -P CMakeFiles/testdcmtk.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/testdcmtk.dir/clean

src/CMakeFiles/testdcmtk.dir/depend:
	cd /Users/kangdehua/Documents/RegistrationProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kangdehua/Documents/RegistrationProject /Users/kangdehua/Documents/RegistrationProject/src /Users/kangdehua/Documents/RegistrationProject/build /Users/kangdehua/Documents/RegistrationProject/build/src /Users/kangdehua/Documents/RegistrationProject/build/src/CMakeFiles/testdcmtk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/testdcmtk.dir/depend

