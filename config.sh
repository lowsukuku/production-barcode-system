#!/bin/bash
mkdir -p build
cd build
cmake -DSTM32_CHIP=STM32F103 -DCMAKE_TOOLCHAIN_FILE=../stm32-cmake/cmake/gcc_stm32.cmake -DCMAKE_BUILD_TYPE=Release ../scanner
make BarcodeScanner.bin