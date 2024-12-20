# Use Ubuntu 22.04.1 as the base image
FROM ubuntu:22.04.1

# Set non-interactive mode to avoid prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install dependencies
RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
    python3-pip \
    python3-venv \
    python-venv \
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

# Install QEMU 8.2.50
RUN wget https://download.qemu.org/qemu-8.2.50.tar.xz && \
    tar -xf qemu-8.2.50.tar.xz && \
    cd qemu-8.2.50 && \
    ./configure && \
    make -j$(nproc) && \
    sudo make install && \
    cd .. && \
    rm -rf qemu-8.2.50 qemu-8.2.50.tar.xz

# Create the workspace directory
WORKDIR /workspace

# Set the default command to bash
CMD ["/bin/bash"]