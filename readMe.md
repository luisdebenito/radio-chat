# Decentralized LoRa Messenger Project

This project compiles and runs a message radio transmitter\receiver program using technology from a LoRa USB Modem written in C++.

## Project Structure

- main.cpp — Entry point
- src/common/ — Common utilities (ID generator, message handling, CRC, package handling, config)
- src/transmission/ — Transmission logic (package builder, manager, queue, LoRa sender)
- include/ — Header files
- build/ — Output directory for binary and config

## Build and Run

### Requirements
- clang++ with C++20 support, linux only (X11)
`sudo apt install libx11-dev clang`

### Commands
- Build and run:
    `make all`

- Run without building:
    `make run`

- Clean build files:
    `make clean`

- Generate default config:
    `make config`


## Output
- Compiled binary: build/transmitter
- Config file: build/config.conf