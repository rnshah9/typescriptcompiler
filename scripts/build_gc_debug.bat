pushd
mkdir __build\gc
cd __build\gc
cmake ../../3rdParty/gc-8.0.4 -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug -Wno-dev -DCMAKE_INSTALL_PREFIX=../../3rdParty/gc/debug -Denable_threads=ON -Denable_cplusplus=OFF
cmake --build . --config Debug -j 8
popd