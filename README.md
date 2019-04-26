Compile and run (debug)
1. `mkdir cmake-build-debug && cd cmake-build-debug`
2. `cmake ..`
3. `make -j4`
4. `./src/Main`

Compile and run (release)
1. `mkdir cmake-build-release && cd cmake-build-release`
2. `cmake -DCMAKE_BUILD_TYPE=Release ..`
3. `make -j4`
4. `./src/Main`
