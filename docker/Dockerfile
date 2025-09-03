FROM alpine:3.20

# Installer Clang, CMake, Make, Ninja et dépendances
RUN apk add --no-cache \
    clang \
    clang-extra-tools \
    cmake \
    make \
    ninja \
    git \
    bash \
    zsh \
    libc-dev \
    boost-dev \    
    fmt-dev \
    build-base

# Définir Clang comme compilateur par défaut
ENV CC=clang
ENV CXX=clang++

