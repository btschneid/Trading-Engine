#!/bin/bash

# Exit on error
set -e

# Function to print colored messages
print_message() {
    echo -e "\033[1;34m$1\033[0m"
}

print_error() {
    echo -e "\033[1;31m$1\033[0m"
}

print_success() {
    echo -e "\033[1;32m$1\033[0m"
}

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    print_error "CMake is not installed. Please install CMake first."
    exit 1
fi

# Check CMake version
CMAKE_VERSION=$(cmake --version | head -n1 | cut -d" " -f3)
CMAKE_MAJOR=$(echo $CMAKE_VERSION | cut -d. -f1)
CMAKE_MINOR=$(echo $CMAKE_VERSION | cut -d. -f2)

if [ "$CMAKE_MAJOR" -lt 3 ] || ([ "$CMAKE_MAJOR" -eq 3 ] && [ "$CMAKE_MINOR" -lt 14 ]); then
    print_error "CMake version 3.14 or higher is required. Current version: $CMAKE_VERSION"
    exit 1
fi

# Create build directory if it doesn't exist
mkdir -p build

# Navigate to build directory
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build . --config Release

# Return to original directory
cd ..

echo "Build completed. Executable is in build/bin/TradingEngine" 