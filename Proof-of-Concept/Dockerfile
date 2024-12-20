# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Set non-interactive mode to avoid prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install dependencies
RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
    python3-pip \
    python3-venv \
    python3-sphinx \
    python3-sphinx-rtd-theme \
    git \
    libglib2.0-dev \
    libfdt-dev \
    libpixman-1-dev \
    zlib1g-dev \
    ninja-build \
    build-essential \
    flex \
    bison \
    wget \
    curl \
    ca-certificates \
    && apt-get clean

# Install QEMU 8.2.5 directly from Git
RUN git clone --branch v8.2.5 https://gitlab.com/qemu-project/qemu.git /qemu && \
    cd /qemu && \
    ./configure && \
    make -j$(nproc) && \
    make install && \
    cd .. && \
    rm -rf /qemu

# Create the workspace directory
WORKDIR /workspace

# Set the default command to bash
CMD ["/bin/bash"]