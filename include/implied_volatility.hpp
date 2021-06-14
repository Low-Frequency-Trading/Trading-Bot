#ifndef IMPLIED_VOLATILITY_HPP_
#define IMPLIED_VOLATILITY_HPP_

#include <functional>
#include "newton_raphson.hpp"
#include "option.hpp"

class ImpVol {
public:
  explicit ImpVol(Option *ptr) : opt_ptr_(ptr), price_ptr_(nullptr),
                                vega_ptr_(nullptr), solver_(nullptr) {}
  ~ImpVol() = default;
  // Want to forbid copy constructor and assignment operator
  ImpVol(const ImpVol& c) = delete;
  ImpVol& operator = (const ImpVol& c) = delete;
  virtual double operator() (double S_Market) = 0;
protected:
  Option* opt_ptr_;
  OptionGreek *price_ptr_;
  OptionGreek *vega_ptr_;
  NewtonRaphson *solver_;
};

class CallImpVol : public ImpVol {
public:
  CallImpVol(Option *ptr) : ImpVol(ptr) {
    this->price_ptr_ = new CallPrice(ptr);
    this->vega_ptr_ = new CallVega(ptr);
    std::function<double (double)> f = std::bind(&CallImpVol::price_sig, this,
                                      std::placeholders::_1);
    std::function<double (double)> f_prime = std::bind(&CallImpVol::vega_sig, this,
                                      std::placeholders::_1);
    this->solver_ = new NewtonRaphson(f,
                                      f_prime,
                                      1e-4);
  }
  ~CallImpVol() {
    delete this->price_ptr_;
    delete this->vega_ptr_;
    delete this->solver_;
  }

  virtual double operator() (double S_Market) override {
    return this->solver_->solve(this->opt_ptr_->Vol_, S_Market);
  }
private:
  double price_sig(double sig) {
    this->opt_ptr_->Vol_ = sig;
    return this->price_ptr_->execute(this->opt_ptr_->underlying_asset_);
  }
  double vega_sig(double sig) {
    this->opt_ptr_->Vol_ = sig;
    return this->vega_ptr_->execute(this->opt_ptr_->underlying_asset_) * 100.0;
  }
};

#endif // IMPLIED_VOLATILITY_HPP_
