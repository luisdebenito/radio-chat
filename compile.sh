#!/bin/bash

# Check if clang++ is installed
if ! command -v clang++ &> /dev/null; then
    echo "clang++ not found. You can install it with:"
    echo "sudo apt update && sudo apt install clang"
    exit 1
fi

SOURCES=(
    main.cpp
     
    src/common/idGenerator.cpp 
    src/common/message.cpp 
    src/common/crcGenerator.cpp
    src/common/package.cpp

    src/transmission/packageBuilder.cpp
    src/transmission/waveFormEncoder.cpp
    src/transmission/transmissionManager.cpp
    src/transmission/waveFormQueue.cpp

    src/reception/waveFormDecoder.cpp
)

OUTPUT="transmitter"

# Compile with Clang using C++20
clang++ -std=c++20 -Iinclude "${SOURCES[@]}" -o "$OUTPUT"

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running ./$OUTPUT"
    ./$OUTPUT
else
    echo "Compilation failed."
fi