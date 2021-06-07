#ifndef CALL_OPTION_HPP_
#define CALL_OPTION_HPP_

#include "option.hpp"

class CallDelta : public OptionGreek {
public:
  CallDelta() : OptionGreek() {};
  explicit CallDelta(Option *ptr) : OptionGreek(ptr) {}
  explicit CallDelta(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  CallDelta(const CallDelta& c) = delete;
  CallDelta& operator = (const CallDelta& c) = delete;
  virtual double execute(double S_t) override {
    double tmp = OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / tmp;
    return std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) * N(d1); // considering discount rate
  }
};

class CallGamma : public OptionGreek {
public:
  CallGamma() : OptionGreek() {};
  explicit CallGamma(Option *ptr) : OptionGreek(ptr) {}
  explicit CallGamma(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  CallGamma(const CallGamma& c) = delete;
  CallGamma& operator = (const CallGamma& c) = delete;
  virtual double execute(double S_t) override {
    double tmp = OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / tmp;
    return N_prime(d1) * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) / (S_t * tmp);
  }
};

class CallVega : public OptionGreek {
public:
  CallVega() : OptionGreek() {};
  explicit CallVega(Option *ptr) : OptionGreek(ptr) {}
  explicit CallVega(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  CallVega(const CallVega& c) = delete;
  CallVega& operator = (const CallVega& c) = delete;
  virtual double execute(double S_t) override {
    double tmp = OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / tmp;
    return (S_t * std::sqrt(OptPtr_->T_) * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) * N_prime(d1)) / 100.0;
  }
};

class CallTheta : public OptionGreek {
public:
  CallTheta() : OptionGreek() {};
  explicit CallTheta(Option *ptr) : OptionGreek(ptr) {}
  explicit CallTheta(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  CallTheta(const CallTheta& c) = delete;
  CallTheta& operator = (const CallTheta& c) = delete;
  virtual double execute(double S_t) override {
    double discount = std::exp(-OptPtr_->r_ * OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / (OptPtr_->Vol_ *
          std::sqrt(OptPtr_->T_));
    double d2 = d1 - OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    return (-((S_t * N_prime(d1) * OptPtr_->Vol_ * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_)) /
            (2. * std::sqrt(OptPtr_->T_))) - OptPtr_->r_
            * OptPtr_->K_ * std::exp(-OptPtr_->r_ * OptPtr_->T_) * N(d2) -
            (OptPtr_->b_ - OptPtr_->r_) * S_t * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_)
            * N(d1)) / 365.0;
  }
};

class CallRho : public OptionGreek {
public:
  CallRho() : OptionGreek() {};
  explicit CallRho(Option *ptr) : OptionGreek(ptr) {}
  explicit CallRho(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  CallRho(const CallRho& c) = delete;
  CallRho& operator = (const CallRho& c) = delete;
  virtual double execute(double S_t) override {
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / (OptPtr_->Vol_ *
          std::sqrt(OptPtr_->T_));
    double d2 = d1 - OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    return (OptPtr_->K_ * OptPtr_->T_ * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) * N(d2)) / 100.0;
  }
};

class CallPrice : public OptionGreek {
public:
  CallPrice() : OptionGreek() {};
  explicit CallPrice(Option *ptr) : OptionGreek(ptr) {}
  explicit CallPrice(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  CallPrice(const CallPrice& c) = delete;
  CallPrice& operator = (const CallPrice& c) = delete;
  virtual double execute(double S_t) override {
    double tmp = OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / tmp;
    double d2 = d1 - tmp;
    return N(d1) * S_t * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) - N(d2) *
            OptPtr_->K_ * std::exp(-OptPtr_->r_ * OptPtr_->T_);
  }
};

#endif // CALL_OPTION_HPP_
