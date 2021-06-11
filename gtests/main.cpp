#include <gtest/gtest.h>
#include "call_option.hpp"
#include "put_option.hpp"

TEST(OptionTest, CopyConstructor) {
  Option *test_obj = new Option(1.0, 100.0, 0.2, 0.01, 10.0, 100.0);
  Option copy_obj(*test_obj);

  EXPECT_NE(&copy_obj, test_obj);
  EXPECT_EQ(test_obj->premium_, copy_obj.premium_);
  EXPECT_EQ(test_obj->K_, copy_obj.K_);
  EXPECT_EQ(test_obj->Vol_, copy_obj.Vol_);
  EXPECT_EQ(test_obj->r_, copy_obj.r_);
  EXPECT_EQ(test_obj->T_, copy_obj.T_);
  EXPECT_EQ(test_obj->underlying_asset_, copy_obj.underlying_asset_);
}

TEST(OptionTest, Call_Greek) {
  Option *opt = new Option(0.0, 597.5, 0.5392, 0.0156, 14.0, 599.05);

  CallDelta Delta(opt);
  CallGamma Gamma(opt);
  CallVega Vega(opt);
  CallRho Rho(opt);
  CallPrice Price(opt);
  CallTheta Theta(opt);

  EXPECT_FALSE(std::signbit(Price(opt->underlying_asset_)));
  EXPECT_FALSE(std::signbit(Delta(opt->underlying_asset_)));
  EXPECT_FALSE(std::signbit(Gamma(opt->underlying_asset_)));
  EXPECT_FALSE(std::signbit(Vega(opt->underlying_asset_)));
  EXPECT_TRUE(std::signbit(Theta(opt->underlying_asset_)));
  EXPECT_FALSE(std::signbit(Rho(opt->underlying_asset_)));
}

TEST(OptionTest, Put_Greek) {
  Option *opt = new Option(0.0, 597.5, 0.5392, 0.0156, 14.0, 599.05);

  PutDelta Delta(opt);
  PutGamma Gamma(opt);
  PutVega Vega(opt);
  PutRho Rho(opt);
  PutPrice Price(opt);
  PutTheta Theta(opt);

  EXPECT_FALSE(std::signbit(Price(opt->underlying_asset_)));
  EXPECT_TRUE(std::signbit(Delta(opt->underlying_asset_)));
  EXPECT_FALSE(std::signbit(Gamma(opt->underlying_asset_)));
  EXPECT_FALSE(std::signbit(Vega(opt->underlying_asset_)));
  EXPECT_TRUE(std::signbit(Theta(opt->underlying_asset_)));
  EXPECT_TRUE(std::signbit(Rho(opt->underlying_asset_)));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* vim: set et ts=4 sw=4: */
