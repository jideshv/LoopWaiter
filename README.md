# LoopWaiter

A header only library to simplify waiting on MCUs without using a delay. This library is published as a Particle Library for use with the Particle Photon and Particle Electron platforms. For other platforms just copy the header file [LoopWaiter.h](src/LoopWaiter.h) to your project. 

The library has been tested using [Google Test](https://github.com/google/googletest) and [fff](https://github.com/meekrosoft/fff).

## Usage

See the [example](examples/usage/usage.ino) for a complete example.

You may clone this repository and run the tests by doing the following:

```
mkdir build
cd build
cmake ..
make
make test
```

## LICENSE

Copyright 2018 Jidesh Veeramachaneni  
Distributed under the MIT License
