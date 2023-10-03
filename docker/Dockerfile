# Base image
FROM ubuntu:latest

# Run setup: install packages (auto yes) and remove lists to reduce image size
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set/create working directory
WORKDIR /app

# Copy root into image
COPY ../ .

# Run CMake and build
RUN mkdir -p build && cd build && cmake -S ../ -B . && make

# Command when run
CMD ["/bin/bash"]
