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
include src/CMakeFiles/orb_matcher.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/orb_matcher.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/orb_matcher.dir/flags.make

src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o: src/CMakeFiles/orb_matcher.dir/flags.make
src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o: ../src/orb_matcher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kangdehua/Documents/RegistrationProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o -c /Users/kangdehua/Documents/RegistrationProject/src/orb_matcher.cpp

src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/orb_matcher.dir/orb_matcher.cpp.i"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kangdehua/Documents/RegistrationProject/src/orb_matcher.cpp > CMakeFiles/orb_matcher.dir/orb_matcher.cpp.i

src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/orb_matcher.dir/orb_matcher.cpp.s"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kangdehua/Documents/RegistrationProject/src/orb_matcher.cpp -o CMakeFiles/orb_matcher.dir/orb_matcher.cpp.s

src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o.requires:

.PHONY : src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o.requires

src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o.provides: src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/orb_matcher.dir/build.make src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o.provides.build
.PHONY : src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o.provides

src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o.provides.build: src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o


# Object files for target orb_matcher
orb_matcher_OBJECTS = \
"CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o"

# External object files for target orb_matcher
orb_matcher_EXTERNAL_OBJECTS =

../bin/orb_matcher: src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o
../bin/orb_matcher: src/CMakeFiles/orb_matcher.dir/build.make
../bin/orb_matcher: /opt/local/lib/libopencv_videostab.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_superres.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_stitching.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_shape.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_photo.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_objdetect.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_calib3d.3.1.0.dylib
../bin/orb_matcher: ../lib/libcvcommon.a
../bin/orb_matcher: /opt/local/lib/libopencv_features2d.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_ml.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_highgui.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_videoio.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_imgcodecs.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_flann.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_video.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_imgproc.3.1.0.dylib
../bin/orb_matcher: /opt/local/lib/libopencv_core.3.1.0.dylib
../bin/orb_matcher: src/CMakeFiles/orb_matcher.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kangdehua/Documents/RegistrationProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/orb_matcher"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/orb_matcher.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/orb_matcher.dir/build: ../bin/orb_matcher

.PHONY : src/CMakeFiles/orb_matcher.dir/build

src/CMakeFiles/orb_matcher.dir/requires: src/CMakeFiles/orb_matcher.dir/orb_matcher.cpp.o.requires

.PHONY : src/CMakeFiles/orb_matcher.dir/requires

src/CMakeFiles/orb_matcher.dir/clean:
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && $(CMAKE_COMMAND) -P CMakeFiles/orb_matcher.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/orb_matcher.dir/clean

src/CMakeFiles/orb_matcher.dir/depend:
	cd /Users/kangdehua/Documents/RegistrationProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kangdehua/Documents/RegistrationProject /Users/kangdehua/Documents/RegistrationProject/src /Users/kangdehua/Documents/RegistrationProject/build /Users/kangdehua/Documents/RegistrationProject/build/src /Users/kangdehua/Documents/RegistrationProject/build/src/CMakeFiles/orb_matcher.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/orb_matcher.dir/depend

