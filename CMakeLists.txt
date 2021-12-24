# CMakeList.txt : CMake project for gSolB, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("gSolB")


option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB mainS ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB mainH ${PROJECT_SOURCE_DIR}/*.h)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(gSol gSolB.cpp ${sources} ${headers} "include/UPrimaryGeneratorAction.h" "include/UMaterials.h" "src/UDetectorConstruction.cpp"  "src/UPhysicsList.cpp" "src/UDetector.cpp" "include/URunAction.h" "src/URunAction.cpp" )
target_link_libraries(gSol ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------

set(gSOL_SCRIPTS
  gSolJet.in
  gSolJet.out
  cll.mac
  vis.mac
  single_action.mac
  )

foreach(_script ${gSOL_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(Solution DEPENDS gSol)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS gSol DESTINATION bin)
