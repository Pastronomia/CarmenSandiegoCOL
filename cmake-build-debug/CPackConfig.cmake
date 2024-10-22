# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "H:/TALLER UNO I/1a_PROYECT/PROYECT;H:/TALLER UNO I/1a_PROYECT/PROYECT/cmake-build-debug")
set(CPACK_CMAKE_GENERATOR "MinGW Makefiles")
set(CPACK_COMPONENTS_ALL "")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "D:/Clion/bin/cmake/win/x64/share/cmake-3.29/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "CarmenSandiego built using CMake")
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALL_CMAKE_PROJECTS "H:/TALLER UNO I/1a_PROYECT/PROYECT/cmake-build-debug;CarmenSandiego;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/CarmenSandiego")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "CarmenSandiego 1.0.0")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "CarmenSandiego 1.0.0")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "H:/TALLER UNO I/T1/mingw64/bin/objcopy.exe")
set(CPACK_OBJDUMP_EXECUTABLE "H:/TALLER UNO I/T1/mingw64/bin/objdump.exe")
set(CPACK_OUTPUT_CONFIG_FILE "H:/TALLER UNO I/1a_PROYECT/PROYECT/cmake-build-debug/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "correo@tudominio.com")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "D:/Clion/bin/cmake/win/x64/share/cmake-3.29/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Juego de Carmen Sandiego en Colonia")
set(CPACK_PACKAGE_EXECUTABLES "CarmenSandiego;CarmenSandiego Game")
set(CPACK_PACKAGE_FILE_NAME "CarmenSandiego-1.0.0-x64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CarmenSandiego 1.0.0")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "CarmenSandiego 1.0.0")
set(CPACK_PACKAGE_NAME "CarmenSandiego")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "TuNombre")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_READELF_EXECUTABLE "H:/TALLER UNO I/T1/mingw64/bin/readelf.exe")
set(CPACK_RESOURCE_FILE_LICENSE "D:/Clion/bin/cmake/win/x64/share/cmake-3.29/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "D:/Clion/bin/cmake/win/x64/share/cmake-3.29/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "D:/Clion/bin/cmake/win/x64/share/cmake-3.29/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "H:/TALLER UNO I/1a_PROYECT/PROYECT/cmake-build-debug/CPackSourceConfig.cmake")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_SYSTEM_NAME "x64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "x64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "H:/TALLER UNO I/1a_PROYECT/PROYECT/cmake-build-debug/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()