cmake_minimum_required(VERSION 3.10)
project(CarmenSandiego VERSION 1.0.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

# Include directories
include_directories(
    ${GTKMM_INCLUDE_DIRS}       # gtkmm include directories
    ${SQLITE3_INCLUDE_DIRS}      # sqlite3 include directories
    "${CMAKE_SOURCE_DIR}/include" # Header files directory in the project
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/ui    # Añadir la ruta a la carpeta 'ui'
    ${CMAKE_SOURCE_DIR}/Multimedia
)

# Link directories for libraries
link_directories(
    ${GTKMM_LIBRARY_DIRS}        # gtkmm library directories
    ${SQLITE3_LIBRARY_DIRS}       # sqlite3 library directories
)

# Add source files to the executable
add_executable(CarmenSandiego
    src/CarmenSandiegoApp.cpp
    src/game_logic.cpp
    src/DatabaseHandler.cpp
    src/main.cpp
    core/PistaDAO.cpp
    core/SecuazDAO.cpp
    Multimedia/MultimediaHandler.cpp
        src/app/main.cpp
        src/app/WelcomeWindow.cpp  # Multimedia handler
)

# Link libraries to the executable
target_link_libraries(CarmenSandiego
    ${GTKMM_LIBRARIES}
    ${SQLITE3_LIBRARIES}
)

# Add extra compiler flags if necessary (optional optimization)
target_compile_options(CarmenSandiego PRIVATE -Wall -Wextra -pedantic)

# Optional packaging configuration
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "CarmenSandiego")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Juego de Carmen Sandiego")
set(CPACK_PACKAGE_VENDOR "TuNombre")
set(CPACK_PACKAGE_CONTACT "correo@tudominio.com")
set(CPACK_SYSTEM_NAME "x64")
set(CPACK_PACKAGE_EXECUTABLES "CarmenSandiego" "CarmenSandiego Game")
set(CPACK_GENERATOR "ZIP;TGZ")
include(CPack)

# Ensuring paths for mingw64
include_directories("H:/TALLER UNO I/T1/mingw64/include")
link_directories("H:/TALLER UNO I/T1/mingw64/lib")
