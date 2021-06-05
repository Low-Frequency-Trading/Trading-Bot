#ifndef OPTION_HPP_
#define OPTION_HPP_

template<class asset, class date>
class Option {
public:
  Option() = default;
  explicit Option(double strike_price, double volatility, double interest_rate,
                  date expire_date, asset underlying_asset):
            strike_price_(strike_price), volatility_(volatility), interest_rate_(interest_rate),
            expire_date_(expire_date), underlying_asset_(underlying_asset) {}

  Option(const Option &other) : strike_price_(other.strike_price_), volatility_(other.volatility_),
            interest_rate_(other.interest_rate_), expire_date_(other.expire_date_),
            underlying_asset_(other.underlying_asset_) {}

  Option(Option &&other) noexcept : strike_price_(other.strike_price_), volatility_(other.volatility_),
            interest_rate_(other.interest_rate_), expire_date_(std::move(other.expire_date_)),
            underlying_asset_(std::move(other.underlying_asset_)) {}

  ~Option() = default;

  Option& operator=(const Option &other) {
    if (this == &other) return *this;
    this->strike_price_ = other.strike_price_;
    this->volatility_ = other.volatility_;
    this->interest_rate_ = other.interest_rate_;
    // TODO: Careful if the implementation of date is change,
    // that the way of copy expire_date_ should be rewrite.
    this->expire_date_ = other.expire_date_;
    // TODO: ditto
    this->underlying_asset_ = other.underlying_asset_;

    return *this;
  }

  Option& operator=(Option &&other) noexcept {
    if (this == &other) return *this;
    this->strike_price_ = other.strike_price_;
    this->volatility_ = other.volatility_;
    this->interest_rate_ = other.interest_rate_;
    // TODO: Careful if the implementation of date is change,
    // that the way of copy expire_date_ should be rewrite.
    this->expire_date_ = std::move(other.expire_date_);
    // TODO: ditto
    this->underlying_asset_ = std::move(other.underlying_asset_);

    return *this;
  }

  double get_strike_price(void) { return this->strike_price_; }
  double get_volatility(void) { return this->volatility_; }
  double get_interest_rate(void) { return this->interest_rate_; }
  date get_expire_date(void) { return this->expire_date_; }
  asset get_underlying_asset(void) { return this->underlying_asset_; }

protected:
  double strike_price_;
  double volatility_;
  double interest_rate_;
  date expire_date_;
  asset underlying_asset_;
};

#endif // OPTION_HPP_

