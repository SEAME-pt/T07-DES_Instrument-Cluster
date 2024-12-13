# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/olink_core-src"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/olink_core-build"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/olink_core-subbuild/olink_core-populate-prefix"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/olink_core-subbuild/olink_core-populate-prefix/tmp"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/olink_core-subbuild/olink_core-populate-prefix/src/olink_core-populate-stamp"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/olink_core-subbuild/olink_core-populate-prefix/src"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/olink_core-subbuild/olink_core-populate-prefix/src/olink_core-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/olink_core-subbuild/olink_core-populate-prefix/src/olink_core-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/olink_core-subbuild/olink_core-populate-prefix/src/olink_core-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
