#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"

// Тесты для Account
TEST(AccountTest, Constructor) {
    Account acc(42, 100);
    EXPECT_EQ(acc.id(), 42);
    EXPECT_EQ(acc.GetBalance(), 100);
}
TEST(AccountTest, ChangeBalance_Throws_IfNotLocked) {
    Account acc(1, 50);
    EXPECT_THROW(acc.ChangeBalance(10), std::runtime_error);
}
TEST(AccountTest, Lock_Success) {
    Account acc(1, 50);
    EXPECT_NO_THROW(acc.Lock());
    // Повторный lock должен бросить
    EXPECT_THROW(acc.Lock(), std::runtime_error);
}
TEST(AccountTest, Unlock_Success) {
    Account acc(1, 50);
    acc.Lock();
    EXPECT_NO_THROW(acc.Unlock());
    EXPECT_THROW(acc.Unlock(), std::runtime_error);
}
TEST(AccountTest, ChangeBalance_AfterLock) {
    Account acc(1, 100);
    acc.Lock();
    acc.ChangeBalance(25);
    EXPECT_EQ(acc.GetBalance(), 125);
    
    acc.ChangeBalance(-30);
    EXPECT_EQ(acc.GetBalance(), 95);
}
