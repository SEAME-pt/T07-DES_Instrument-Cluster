#!/bin/bash

# precisa desta dependencia para compilar o projeto
# sudo apt install nlohmann-json3-dev

#cd cpp
#cmake . -DCMAKE_BUILD_TYPE=Release -DCPP_FETCH_DEPS=ON
#cmake --build .

#cd ..

#!/bin/bash

# Function to check and install packages
install_package() {
    PACKAGE=$1
    dpkg -l | grep -qw $PACKAGE || sudo apt-get install -y $PACKAGE
}

echo "Checking dependencies..."

# Checking SDL2
echo "Checking SDL2..."
dpkg -l | grep -qw libsdl2-dev || install_package libsdl2-dev

# Checking Google Test
echo "Checking Google Test..."
dpkg -l | grep -qw libgtest-dev || install_package libgtest-dev

# Checking pigpio
echo "Checking pigpio..."
dpkg -l | grep -qw pigpio || install_package pigpio

echo "Check and installation complete!"


git submodule update --remote

cmake -S . -B build
cd build
make
cd ..
./build/MainCarServer

