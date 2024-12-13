# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/modules/vehicle_speed"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/vehicle_speed-build"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/vehicle_speed-subbuild/vehicle_speed-populate-prefix"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/vehicle_speed-subbuild/vehicle_speed-populate-prefix/tmp"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/vehicle_speed-subbuild/vehicle_speed-populate-prefix/src/vehicle_speed-populate-stamp"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/vehicle_speed-subbuild/vehicle_speed-populate-prefix/src"
  "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/vehicle_speed-subbuild/vehicle_speed-populate-prefix/src/vehicle_speed-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/vehicle_speed-subbuild/vehicle_speed-populate-prefix/src/vehicle_speed-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/hmaciel-/Dev/Seame/MainCar/MainCar/cpp/_deps/vehicle_speed-subbuild/vehicle_speed-populate-prefix/src/vehicle_speed-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
