#ifndef OPTION_HPP_
#define OPTION_HPP_

#include <utility>
#include "utility.hpp"

struct Option {
public:
  Option() = default;
  explicit Option(double premium, double strike_price, double volatility, double interest_rate,
                  uint32_t expire_date, double underlying_asset):
            premium_(premium), K_(strike_price), Vol_(volatility), r_(interest_rate),
            b_(interest_rate), T_(expire_date), underlying_asset_(underlying_asset) {
              this->T_ = this->T_ / 365.0;
            }

  Option(const Option &other) : premium_(other.premium_), K_(other.K_), Vol_(other.Vol_),
            r_(other.r_), b_(other.b_), T_(other.T_),
            underlying_asset_(other.underlying_asset_) {}

  Option(Option &&other) noexcept : premium_(other.premium_), K_(other.K_), Vol_(other.Vol_),
            r_(other.r_), b_(other.b_), T_(other.T_),
            underlying_asset_(other.underlying_asset_) {}

  ~Option() = default;

  Option& operator=(const Option &other) {
    if (this == &other) return *this;
    this->premium_= other.premium_;
    this->K_ = other.K_;
    this->Vol_ = other.Vol_;
    this->r_ = other.r_;
    this->b_ = other.b_;
    this->T_ = other.T_;
    this->underlying_asset_ = other.underlying_asset_;

    return *this;
  }

  Option& operator=(Option &&other) noexcept {
    if (this == &other) return *this;
    this->premium_= other.premium_;
    this->K_ = other.K_;
    this->Vol_ = other.Vol_;
    this->r_ = other.r_;
    this->b_ = other.b_;
    this->T_ = other.T_;
    this->underlying_asset_ = other.underlying_asset_;

    return *this;
  }

  double premium_; // Option's market value
  double K_;  // strike price
  double Vol_; // Volatility
  double r_; // Interest rate or Risk free rate
  double b_;
  double T_; // Day to expire date
  double underlying_asset_;
};

class OptionGreek {
public:
  OptionGreek() : OptPtr_(nullptr) {};
  explicit OptionGreek(Option *ptr) : OptPtr_(ptr) {}
  explicit OptionGreek(Option &obj) {
    this->OptPtr_ = new Option(obj);
  }

  // Want to forbid copy constructor and assignment operator
  OptionGreek(const OptionGreek& c) = delete;
  OptionGreek& operator = (const OptionGreek& c) = delete;
  // The abstract interface
  virtual double execute(double S) = 0;
  // Implement as function object; example of Template Method Pattern
  virtual double operator () (double S) {
    // Call derived class' execute()
    return execute(S);
  }

  virtual ~OptionGreek() {};

protected:
  Option *OptPtr_;
};

#endif // OPTION_HPP_

