# Install script for directory: /Users/abhisekh.nag/code/axmol/3rdparty/fmt

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Users/abhisekh.nag/Library/Android/sdk/ndk/23.2.8568313/toolchains/llvm/prebuilt/darwin-x86_64/bin/llvm-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6o6m6h1c/arm64-v8a/lib/libfmtd.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/fmt" TYPE FILE FILES
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/args.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/base.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/chrono.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/color.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/compile.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/core.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/format.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/format-inl.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/os.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/ostream.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/printf.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/ranges.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/std.h"
    "/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include/fmt/xchar.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt" TYPE FILE FILES
    "/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6o6m6h1c/arm64-v8a/engine/3rdparty/fmt/fmt-config.cmake"
    "/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6o6m6h1c/arm64-v8a/engine/3rdparty/fmt/fmt-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets.cmake"
         "/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6o6m6h1c/arm64-v8a/engine/3rdparty/fmt/CMakeFiles/Export/b834597d9b1628ff12ae4314c3a2e4b8/fmt-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt" TYPE FILE FILES "/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6o6m6h1c/arm64-v8a/engine/3rdparty/fmt/CMakeFiles/Export/b834597d9b1628ff12ae4314c3a2e4b8/fmt-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt" TYPE FILE FILES "/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6o6m6h1c/arm64-v8a/engine/3rdparty/fmt/CMakeFiles/Export/b834597d9b1628ff12ae4314c3a2e4b8/fmt-targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6o6m6h1c/arm64-v8a/engine/3rdparty/fmt/fmt.pc")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6o6m6h1c/arm64-v8a/engine/3rdparty/fmt/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
