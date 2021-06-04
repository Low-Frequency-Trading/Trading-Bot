#include <gtest/gtest.h>
#include "option.hpp"

using option_type = Option<double, uint32_t>;

TEST(OptionTest, Constructor)
{
  option_type *test_obj = new option_type(100.0, 0.2, 0.01, 10, 100.0);
  EXPECT_EQ(test_obj->get_strike_price(), 100.0);
  EXPECT_EQ(test_obj->get_volatility(), 0.2);
  EXPECT_EQ(test_obj->get_interest_rate(), 0.01);
  EXPECT_EQ(test_obj->get_expire_date(), 10U);
  EXPECT_EQ(test_obj->get_underlying_asset(), 100.0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* vim: set et ts=4 sw=4: */
