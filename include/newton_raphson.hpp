#ifndef NEWTON_RAPHSON_HPP_
#define NEWTON_RAPHSON_HPP_

#include <algorithm>
#include <cmath>
#include <exception>

#define ITER_MAX 1e3

class NewtonRaphson {
public:
  using value_type = double;
  using function_type = std::function<value_type (value_type)>;

  explicit NewtonRaphson(function_type g, function_type g_prime, value_type err)
            : g_(g), g_prime_(g_prime), tolerance_(err) {}
  NewtonRaphson(NewtonRaphson &other) = delete;
  NewtonRaphson& operator() (NewtonRaphson &other) = delete;

  ~NewtonRaphson() = default;

  value_type solve(value_type init_value, value_type target_value) {
    value_type y = this->g_(init_value);
    value_type root = init_value;
    uint32_t iter = 0U;
    value_type dx = 0.0;

    try {
      while ((fabs(y - target_value) > this->tolerance_) && (iter <= ITER_MAX)) {
        dx = this->g_prime_(root);
        if (dx == 0.0) {
          throw std::runtime_error("g_prime equal to zero !!\n");
        }
        root += (target_value - y) / this->g_prime_(root);
        y = this->g_(root);
        iter++;
      }
      if (iter > ITER_MAX) throw std::runtime_error("Iteration number maxium exceed !!\n");
    } catch (std::runtime_error &e) {
      std::cout << e.what() << std::endl;
      std::exit(-1);
    }

    return root;
  }

private:
  function_type g_;
  function_type g_prime_;
  value_type tolerance_;
};

#endif // NEWTON_RAPHSON_HPP_
