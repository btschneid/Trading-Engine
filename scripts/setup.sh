#!/bin/bash

# Exit on error
set -e

# Function to print colored messages
print_message() {
    echo -e "\033[1;34m==>\033[0m $1"
}

print_error() {
    echo -e "\033[1;31mError:\033[0m $1"
}

print_success() {
    echo -e "\033[1;32mSuccess:\033[0m $1"
}

# Check if running as root
if [ "$EUID" -eq 0 ]; then
    print_error "Please do not run this script as root"
    exit 1
fi

# Install C++ dependencies
print_message "Installing C++ dependencies..."
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    libsqlite3-dev \
    python3-dev \
    python3-venv

# Create Python virtual environment
print_message "Creating Python virtual environment..."
python3 -m venv venv

# Activate virtual environment and install Python dependencies
print_message "Installing Python dependencies..."
source venv/bin/activate
pip install --upgrade pip
pip install -r config/python_requirements.txt

print_success "Setup completed successfully!"
print_message "To activate the virtual environment, run: source venv/bin/activate" 