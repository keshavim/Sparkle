#!/bin/bash
cmake -S . -B build -G Ninja
cmake --build build
./build/bin/Engine
