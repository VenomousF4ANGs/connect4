# Install script for directory: /Users/abhisekh.nag/code/axmol/extensions

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/GUI/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/assets-manager/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/Particle3D/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/physics-nodes/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/spine/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/DragonBones/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/fairygui/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/ImGui/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/Inspector/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/SDFGen/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/cocostudio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/scripting/lua-bindings/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/JSONDefault/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/abhisekh.nag/code/connect4/proj.android/app/.cxx/Debug/6t3o4y22/arm64-v8a/engine/extensions/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()