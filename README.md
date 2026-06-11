# SIGINT Radar Signal Receiver

A lightweight, low-level Windows C++ console application designed to intercept and parse digitized radar telemetry data over UDP. This project serves as a foundational component for a broader Signal Intelligence (SIGINT) tracking system, simulating or interfacing with a network-based radar emitter.

## Tech Stack & Architecture
* **Language:** C++11 / C++14
* **API:** Windows Sockets 2 (Winsock2)
* **Protocol:** UDP (User Datagram Protocol) for connectionless, low-latency telemetry streaming
* **Target OS:** Windows (Migrated from a Linux `sys/socket.h` implementation)

## Features
* **Zero Overhead:** Written in native C++ using the Winsock2 API directly, avoiding the overhead of heavy managed runtimes (like C#/.NET).
* **Asynchronous-Ready Datagrams:** Binds to `INADDR_ANY` on port `5005` to capture incoming radar packets across all available network interfaces.
* **Custom Protocol Parsing:** Deserializes raw network bytes directly into a structured `RadarPacket` format for real-time console telemetry output.

## Project Structure
* `main.cpp` - Initializes the Winsock DLL, manages memory allocations for network structures, creates/binds the socket, and hosts the packet ingestion loop.
* `protocol.h` - Contains the shared network struct definition (e.g., `RadarPacket`) establishing the data contract between the emitter and this receiver.

## Getting Started

### Prerequisites
* Windows OS
* A C++ compiler (MSVC via Visual Studio is highly recommended)
* `ws2_32.lib` (Linked automatically via `#pragma comment` in the code)

### Building and Running
1. Open the project in Visual Studio or your preferred C++ IDE.
2. Ensure the build configuration targets **Windows**.
3. Compile and run the executable.

Upon launch, the terminal will initialize Winsock and begin listening:
```text
Receiver is listening on port 5005...
