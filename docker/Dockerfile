# Image de base légère
FROM debian:bullseye-slim

# Eviter les interactions pendant les installs
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8

# Installer les outils de compilation et Boost.Test
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        clang \
        cmake \
        make \
        g++ \
        libboost-test-dev \
        libboost-dev \
        build-essential \
        ca-certificates \
        curl \
        git \
        zsh \
        libfmt-dev \
    && apt-get clean && \
    rm -rf /var/lib/apt/lists/*

