# Mandelbrot Set Generator

Mandelbrot set generator in C++ with the [matplot++](https://github.com/alandefreitas/matplotplusplus/tree/master) visualisation library.

# Usage

```bash
cmake -S . -B build
cmake --build build -j$(nproc)
./build/mandelbrot 1000 1000 10000 # [width] [height] [iterations]
```
