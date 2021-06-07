#ifndef PUT_OPTION_HPP_
#define PUT_OPTION_HPP_

class PutDelta : public OptionGreek {
public:
  PutDelta() : OptionGreek() {};
  explicit PutDelta(Option *ptr) : OptionGreek(ptr) {}
  explicit PutDelta(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  PutDelta(const PutDelta& c) = delete;
  PutDelta& operator = (const PutDelta& c) = delete;
  virtual double execute(double S_t) override {
    double tmp = OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / tmp;
    return -std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) * N(-d1); // considering discount rate
  }
};

class PutGamma : public OptionGreek {
public:
  PutGamma() : OptionGreek() {};
  explicit PutGamma(Option *ptr) : OptionGreek(ptr) {}
  explicit PutGamma(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  PutGamma(const PutGamma& c) = delete;
  PutGamma& operator = (const PutGamma& c) = delete;
  virtual double execute(double S_t) override {
    double tmp = OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / tmp;
    return N_prime(d1) * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) / (S_t * tmp);
  }
};

class PutVega : public OptionGreek {
public:
  PutVega() : OptionGreek() {};
  explicit PutVega(Option *ptr) : OptionGreek(ptr) {}
  explicit PutVega(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  PutVega(const PutVega& c) = delete;
  PutVega& operator = (const PutVega& c) = delete;
  virtual double execute(double S_t) override {
    double tmp = OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / tmp;
    return (S_t * std::sqrt(OptPtr_->T_) * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) * N_prime(d1)) / 100.0;
  }
};

class PutTheta : public OptionGreek {
public:
  PutTheta() : OptionGreek() {};
  explicit PutTheta(Option *ptr) : OptionGreek(ptr) {}
  explicit PutTheta(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  PutTheta(const PutTheta& c) = delete;
  PutTheta& operator = (const PutTheta& c) = delete;
  virtual double execute(double S_t) override {
    double discount = std::exp(-OptPtr_->r_ * OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / (OptPtr_->Vol_ *
          std::sqrt(OptPtr_->T_));
    double d2 = d1 - OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    return (-((S_t * N_prime(d1) * OptPtr_->Vol_ * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_)) /
            (2. * std::sqrt(OptPtr_->T_))) + OptPtr_->r_
            * OptPtr_->K_ * std::exp(-OptPtr_->r_ * OptPtr_->T_) * N(-d2) +
            (OptPtr_->b_ - OptPtr_->r_) * S_t * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_)
            * N(d1)) / 365.0;
  }
};

class PutRho : public OptionGreek {
public:
  PutRho() : OptionGreek() {};
  explicit PutRho(Option *ptr) : OptionGreek(ptr) {}
  explicit PutRho(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  PutRho(const PutRho& c) = delete;
  PutRho& operator = (const PutRho& c) = delete;
  virtual double execute(double S_t) override {
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / (OptPtr_->Vol_ *
          std::sqrt(OptPtr_->T_));
    double d2 = d1 - OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    return (-OptPtr_->K_ * OptPtr_->T_ * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) * N(-d2)) / 100.0;
  }
};

class PutPrice : public OptionGreek {
public:
  PutPrice() : OptionGreek() {};
  explicit PutPrice(Option *ptr) : OptionGreek(ptr) {}
  explicit PutPrice(Option &obj) : OptionGreek(obj) {}
  // Want to forbid copy constructor and assignment operator
  PutPrice(const PutPrice& c) = delete;
  PutPrice& operator = (const PutPrice& c) = delete;
  virtual double execute(double S_t) override {
    double tmp = OptPtr_->Vol_ * std::sqrt(OptPtr_->T_);
    double d1 = (std::log(S_t / OptPtr_->K_) + (OptPtr_->b_ +
          (OptPtr_->Vol_ * OptPtr_->Vol_) * 0.5) * OptPtr_->T_) / tmp;
    double d2 = d1 - tmp;
    return -N(-d1) * S_t * std::exp((OptPtr_->b_ - OptPtr_->r_) * OptPtr_->T_) + N(-d2) *
            OptPtr_->K_ * std::exp(-OptPtr_->r_ * OptPtr_->T_);
  }
};

#endif // PUT_OPTION_HPP_
