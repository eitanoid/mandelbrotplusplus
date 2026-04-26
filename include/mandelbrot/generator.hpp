#include <complex>
#include <cstdint>

namespace mandelbrot {

template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template <FloatingPoint T>
uint32_t escape_time(std::complex<T> c, uint32_t max_iterations) {
  std::complex<T> z(0, 0);
  for (uint32_t i = 0; i < max_iterations; i++) {
    if (std::norm(z) > 4.0)
      return i;
    z = z * z + c;
  }
  return max_iterations;
};

} // namespace mandelbrot
