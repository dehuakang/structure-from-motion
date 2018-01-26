# VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
# DCMTK
find_package(DCMTK REQUIRED)
include_directories(${DCMTK_INCLUDE_DIRS})
include_directories(${DCMTK_LIBS})

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# PCL
find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_library(cvcommon cvcommon.cpp)
add_library(common common.cpp)
add_library(vtkcommon vtkcommon.cpp)
add_library(vtkpolydatadelta vtkpolydatadelta.cpp)
add_library(dcmtkcommon dcmtkcommon.cpp)
#vtk
add_executable(readdicommc readdicommc.cpp)
add_executable(raycastingexample raycastingexample.cpp)
add_executable(icpregistration icpregistration.cpp)
add_executable(interactorwidget interactorwidget.cpp)
add_executable(polydatadeltaexample polydatadeltaexample.cpp)
add_executable(kdtreetimingdemo kdtreetimingdemo.cpp)
add_executable(cal_phantom cal_phantom.cpp)
add_executable(octreetimingdemo octreetimingdemo.cpp)
add_executable(testcbctorigin testcbctorigin.cpp)
add_executable(testdcmtk testdcmtk.cpp)
add_executable(testdcmtkreadrtdose testdcmtkreadrtdose.cpp)



target_link_libraries(readdicommc ${VTK_LIBRARIES} vtkcommon)
target_link_libraries(raycastingexample ${VTK_LIBRARIES} vtkcommon)
target_link_libraries(icpregistration ${VTK_LIBRARIES} vtkcommon)
target_link_libraries(interactorwidget ${VTK_LIBRARIES} vtkcommon)
target_link_libraries(polydatadeltaexample ${VTK_LIBRARIES} vtkpolydatadelta)
target_link_libraries(kdtreetimingdemo ${VTK_LIBRARIES} vtkcommon)
target_link_libraries(cal_phantom ${VTK_LIBRARIES} vtkcommon)
target_link_libraries(octreetimingdemo ${VTK_LIBRARIES} vtkcommon)
target_link_libraries(testcbctorigin ${VTK_LIBRARIES} common)
target_link_libraries(testdcmtk ${DCMTK_LIBRARIES} dcmtkcommon)
target_link_libraries(testdcmtkreadrtdose ${DCMTK_LIBRARIES} dcmtkcommon ${VTK_LIBRARIES})
#pcl
add_executable(normal_distributions_transform normal_distributions_transform.cpp)
add_executable(don_segmentation don_segmentation.cpp)
target_link_libraries(normal_distributions_transform ${PCL_LIBRARIES})
target_link_libraries(don_segmentation ${PCL_LIBRARIES})


#opencv
add_executable(cv_test cv_test.cpp)
target_link_libraries(cv_test ${OpenCV_LIBS} cvcommon)
add_executable(pnp_vtkcamera pnp_vtkcamera.cpp)
target_link_libraries(pnp_vtkcamera ${OpenCV_LIBS} ${VTK_LIBRARIES})
add_executable(orb_matcher orb_matcher.cpp)
target_link_libraries(orb_matcher ${OpenCV_LIBS} cvcommon)
add_executable(twoviewreconstruction twoviewreconstruction.cpp)
target_link_libraries(twoviewreconstruction ${OpenCV_LIBS} cvcommon ${PCL_LIBRARIES})
