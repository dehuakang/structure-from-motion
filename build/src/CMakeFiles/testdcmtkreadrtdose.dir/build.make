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
include src/CMakeFiles/testdcmtkreadrtdose.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/testdcmtkreadrtdose.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/testdcmtkreadrtdose.dir/flags.make

src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o: src/CMakeFiles/testdcmtkreadrtdose.dir/flags.make
src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o: ../src/testdcmtkreadrtdose.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kangdehua/Documents/RegistrationProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o -c /Users/kangdehua/Documents/RegistrationProject/src/testdcmtkreadrtdose.cpp

src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.i"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kangdehua/Documents/RegistrationProject/src/testdcmtkreadrtdose.cpp > CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.i

src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.s"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kangdehua/Documents/RegistrationProject/src/testdcmtkreadrtdose.cpp -o CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.s

src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o.requires:

.PHONY : src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o.requires

src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o.provides: src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/testdcmtkreadrtdose.dir/build.make src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o.provides.build
.PHONY : src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o.provides

src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o.provides.build: src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o


# Object files for target testdcmtkreadrtdose
testdcmtkreadrtdose_OBJECTS = \
"CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o"

# External object files for target testdcmtkreadrtdose
testdcmtkreadrtdose_EXTERNAL_OBJECTS =

../bin/testdcmtkreadrtdose: src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o
../bin/testdcmtkreadrtdose: src/CMakeFiles/testdcmtkreadrtdose.dir/build.make
../bin/testdcmtkreadrtdose: /usr/local/lib/libofstd.a
../bin/testdcmtkreadrtdose: /usr/local/lib/liboflog.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmdata.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libi2d.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmimgle.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmimage.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmjpeg.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libijg8.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libijg12.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libijg16.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmjpls.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libcharls.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmtls.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmnet.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmsr.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libcmr.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmdsig.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmwlm.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmqrdb.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmpstat.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmrt.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmiod.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmfg.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmseg.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmtract.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmpmap.a
../bin/testdcmtkreadrtdose: ../lib/libdcmtkcommon.a
../bin/testdcmtkreadrtdose: /usr/lib/libz.dylib
../bin/testdcmtkreadrtdose: /usr/lib/libexpat.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkDomainsChemistryOpenGL2-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersFlowPaths-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersGeneric-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersHyperTree-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersParallelImaging-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersPoints-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersProgrammable-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersPython-8.0.1.dylib
../bin/testdcmtkreadrtdose: /System/Library/Frameworks/Python.framework/Versions/2.7/Python
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkWrappingPython27Core-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkWrappingTools-8.0.a
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersSMP-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersSelection-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersTexture-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersTopology-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersVerdict-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkverdict-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkGeovisCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libjpeg.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libpng.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libtiff.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkproj4-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOAMR-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libhdf5.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libsz.dylib
../bin/testdcmtkreadrtdose: /usr/lib/libdl.dylib
../bin/testdcmtkreadrtdose: /usr/lib/libm.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libhdf5_hl.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOEnSight-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOExodus-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libnetcdf.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOExportOpenGL2-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOImport-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOInfovis-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/lib/libxml2.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOLSDyna-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOMINC-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOMovie-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkoggtheora-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOPLY-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOParallel-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkjsoncpp-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOParallelXML-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOSQL-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtksqlite-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOTecplotTable-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOVideo-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingMorphological-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingStatistics-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingStencil-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkInfovisBoostGraphAlgorithms-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkInteractionImage-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingContextOpenGL2-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingFreeTypeFontConfig-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingImage-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingLOD-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingVolumeOpenGL2-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkViewsContext2D-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkViewsInfovis-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmtls.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmsr.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmimage.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmdsig.a
../bin/testdcmtkreadrtdose: /usr/local/opt/openssl/lib/libssl.dylib
../bin/testdcmtkreadrtdose: /usr/local/opt/openssl/lib/libcrypto.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmqrdb.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmnet.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmimgle.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmfg.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmiod.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libdcmdata.a
../bin/testdcmtkreadrtdose: /usr/local/lib/liboflog.a
../bin/testdcmtkreadrtdose: /usr/local/lib/libofstd.a
../bin/testdcmtkreadrtdose: /usr/lib/libiconv.dylib
../bin/testdcmtkreadrtdose: /usr/lib/libcharset.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libjpeg.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libpng.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libtiff.dylib
../bin/testdcmtkreadrtdose: /usr/lib/libxml2.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkDomainsChemistry-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersAMR-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOExport-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtklibharu-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingGL2PSOpenGL2-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkgl2ps-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersParallel-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkexoIIc-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOGeometry-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIONetCDF-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtknetcdf_c++.4.2.0.dylib
../bin/testdcmtkreadrtdose: /usr/local/lib/libnetcdf.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkParallelCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOLegacy-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingOpenGL2-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkglew-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingMath-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkChartsCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingContext2D-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersImaging-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkInfovisLayout-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkInfovisCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkViewsCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkInteractionWidgets-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersHybrid-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingGeneral-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingSources-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersModeling-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingHybrid-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOImage-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkDICOMParser-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkmetaio-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkInteractionStyle-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersExtraction-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersStatistics-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingFourier-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkalglib-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingAnnotation-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingColor-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingVolume-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkImagingCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOXML-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOXMLParser-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkIOCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtklz4-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingLabel-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingFreeType-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkRenderingCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkCommonColor-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersGeometry-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersSources-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersGeneral-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkCommonComputationalGeometry-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkFiltersCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkCommonExecutionModel-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkCommonDataModel-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkCommonTransforms-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkCommonMisc-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkCommonMath-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkCommonSystem-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkCommonCore-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtksys-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/local/Cellar/vtk/8.0.1/lib/libvtkfreetype-8.0.1.dylib
../bin/testdcmtkreadrtdose: /usr/lib/libz.dylib
../bin/testdcmtkreadrtdose: src/CMakeFiles/testdcmtkreadrtdose.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kangdehua/Documents/RegistrationProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/testdcmtkreadrtdose"
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testdcmtkreadrtdose.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/testdcmtkreadrtdose.dir/build: ../bin/testdcmtkreadrtdose

.PHONY : src/CMakeFiles/testdcmtkreadrtdose.dir/build

src/CMakeFiles/testdcmtkreadrtdose.dir/requires: src/CMakeFiles/testdcmtkreadrtdose.dir/testdcmtkreadrtdose.cpp.o.requires

.PHONY : src/CMakeFiles/testdcmtkreadrtdose.dir/requires

src/CMakeFiles/testdcmtkreadrtdose.dir/clean:
	cd /Users/kangdehua/Documents/RegistrationProject/build/src && $(CMAKE_COMMAND) -P CMakeFiles/testdcmtkreadrtdose.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/testdcmtkreadrtdose.dir/clean

src/CMakeFiles/testdcmtkreadrtdose.dir/depend:
	cd /Users/kangdehua/Documents/RegistrationProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kangdehua/Documents/RegistrationProject /Users/kangdehua/Documents/RegistrationProject/src /Users/kangdehua/Documents/RegistrationProject/build /Users/kangdehua/Documents/RegistrationProject/build/src /Users/kangdehua/Documents/RegistrationProject/build/src/CMakeFiles/testdcmtkreadrtdose.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/testdcmtkreadrtdose.dir/depend

