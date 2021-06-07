#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <cmath>
#include "boost/math/constants/constants.hpp"
#include "boost/math/distributions/normal.hpp"
#include "boost/math/distributions.hpp"
// Normal variates etc.
double Pdf(const double x) {
  boost::math::normal_distribution<> myNormal(0.0, 1.0);
  return boost::math::pdf(myNormal, x);
}
// C++11 supports the error function
double Cdf(const double x) { // The approximation to the cumulative normal distribution
  boost::math::normal_distribution<> myNormal(0.0, 1.0);
  return boost::math::cdf(myNormal, x);
}

double N(double x) {
    // aka CdfN(x)
    return Cdf(x);
}

double N_prime(double x) {
    // aka pdf(x)
    return Pdf(x);
}

#endif // UTILITY_HPP_
