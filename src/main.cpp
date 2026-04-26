#include "mandelbrot/generator.hpp"
#include "matplot/freestanding/axes_functions.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <execution>
#include <matplot/matplot.h>
#include <numeric>
#include <print>
#include <stdfloat>
#include <string>
#include <vector>

void visualize(const std::vector<uint32_t> &data, int width, int height) {
  using namespace matplot;

  uint32_t max_iter = *std::max_element(data.begin(), data.end());
  if (max_iter == 0) {
    max_iter = 1;
  }
  std::vector<std::vector<double>> matrix(height, std::vector<double>(width));
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      // use log scale to improve visualisation
      auto val = data[y * width + x];
      matrix[y][x] = val > 0 ? std::log(static_cast<double>(val)) : 0.0;
    }
  }
  auto f = figure(false);
  // matplot throws a lot of warnings for some reaosn
  // https://github.com/alandefreitas/matplotplusplus/issues/432
  f->backend()->run_command("unset warnings");
  f->ioff();
  f->size(1000, 1000);

  auto img = image(matrix);
  colormap(palette::magma());

  title("Mandelbrot Set");
  save("mandelbrot.png");
  std::cout << "Mandelbrot saved to mandelbrot.png" << std::endl;
}

int main(int argc, char *argv[]) {
  using Real = float_t;
  int width;
  int height;
  uint32_t max_iter;

  if (argc < 4) {
    std::cerr << "Incorrect usage: ./mandelbrot [width] [height] [max_iter]"
              << std::endl;
    return 1;
  }
  // validate input
  try {
    width = std::stoi(argv[1]);
    height = std::stoi(argv[2]);
    max_iter = std::stoi(argv[3]);
  } catch (...) {
    std::cerr << "Incorrect usage: ./mandelbrot [width] [height] [max_iter]"
              << std::endl;
    return 1;
  }

  if (width <= 0 || height <= 0 || max_iter == 0) {
    std::cerr << "Incorrect usage: all values must be positive." << std::endl;
    return 1;
  }

  // flat 2d array
  std::vector<uint32_t> image(width * height);

  std::vector<int> indices(height);
  std::iota(indices.begin(), indices.end(), 0);

  // iterate on each row in parallel
  std::for_each(std::execution::par, indices.begin(), indices.end(),
                [&](int y) {
                  for (int x = 0; x < width; ++x) {
                    Real scaled_x = -2.0 + (2.5 * x) / (width);
                    Real scaled_y = (-1.5 + (3.0 * y / height));

                    std::complex<Real> c(scaled_x, scaled_y);
                    image[y * width + x] = mandelbrot::escape_time(c, max_iter);
                  }
                });

  std::print("Finished generating Mandelbrot with {} pixels\n", image.size());
  visualize(image, width, height);
  return 0;
}
