#!/bin/bash

# precisa desta dependencia para compilar o projeto
# sudo apt install nlohmann-json3-dev


sudo modprobe vcan0
sudo ip link add dev vcan0 type vcan
sudo ip link set vcan0 mtu 16
sudo ip link set up vcan0


cd cpp
cmake . -DCMAKE_BUILD_TYPE=Release -DCPP_FETCH_DEPS=ON
cmake --build .

cd ..
cmake -S . -B build
cd build
make
cd ..
./build/parts

