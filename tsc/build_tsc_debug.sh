#!/bin/sh
cd ../__build/tsc-ninja
cmake --build . --config Debug -j 8
bash -f ../../scripts/separate_debug_info.sh ./bin/tsc
