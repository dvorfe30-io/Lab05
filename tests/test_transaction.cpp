#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"
#include "Account.h"

class MockTransaction : public Transaction {
public:
    MOCK_METHOD(void, SaveToDataBase, (Account&, Account&, int), (override));
};

TEST(TransactionTest, DefaultFee) {
    Transaction t;
    EXPECT_EQ(t.fee(), 1);
}
TEST(TransactionTest, SetFee) {
    Transaction t;
    t.set_fee(5);
    EXPECT_EQ(t.fee(), 5);
}
TEST(TransactionTest, Make_Throws_SameAccount) {
    Transaction t;
    Account acc(1, 100);
    EXPECT_THROW(t.Make(acc, acc, 200), std::logic_error);
}
TEST(TransactionTest, Make_Throws_NegativeSum) {
    Transaction t;
    Account from(1, 200), to(2, 100);
    EXPECT_THROW(t.Make(from, to, -50), std::invalid_argument);
}
TEST(TransactionTest, Make_Throws_TooSmall) {
    Transaction t;
    Account from(1, 200), to(2, 100);
    EXPECT_THROW(t.Make(from, to, 50), std::logic_error); // < 100
}
TEST(TransactionTest, Make_ReturnsFalse_IfFeeTooHigh) {
    Transaction t;
    t.set_fee(60); // fee*2 = 120 > sum=100
    Account from(1, 500), to(2, 100);
    from.Lock(); to.Lock(); // нужно для ChangeBalance
    EXPECT_FALSE(t.Make(from, to, 100));
}
TEST(TransactionTest, Make_Success_WithMock) {
    MockTransaction t;
    t.set_fee(10);
    Account from(1, 200), to(2, 50);
    EXPECT_CALL(t, SaveToDataBase(::testing::_, ::testing::_, ::testing::_))
        .Times(1);
    EXPECT_TRUE(t.Make(from, to, 150));
    EXPECT_EQ(from.GetBalance(), 40);
    EXPECT_EQ(to.GetBalance(), 200);
}
