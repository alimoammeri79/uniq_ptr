#include "ali_unique_ptr.h"
#include <cctype>
#include <gtest/gtest.h>

TEST(UniquePtrTest, DefaultConstructor) {
    ali::unique_ptr<int> u_ptr;
    EXPECT_EQ(u_ptr.get(), nullptr);
}

TEST(UniquePtrTest, NullConstructor) {
    ali::unique_ptr<int> u_ptr{nullptr};
    EXPECT_EQ(u_ptr.get(), nullptr);
}

TEST(UniquePtrTest, PointerConstructor) {
    ali::unique_ptr<int> u_ptr{new int};
    EXPECT_NE(u_ptr.get(), nullptr);
}

TEST(UniquePtrTest, MoveCostructor) {
    ali::unique_ptr<int> u_ptr1{new int};
    ali::unique_ptr<int> u_ptr2{std::move(u_ptr1)};
    EXPECT_EQ(u_ptr1.get(), nullptr);
    EXPECT_NE(u_ptr2.get(), nullptr);
}

TEST(UniquePtrTest, ReleaseTest) {
    ali::unique_ptr<int> u_ptr1{new int};
    ali::unique_ptr<int> u_ptr2{u_ptr1.release()};
    EXPECT_EQ(u_ptr1.get(), nullptr);
    EXPECT_NE(u_ptr2.get(), nullptr);
}

TEST(UniquePtrTest, ResetTest) {
    ali::unique_ptr<int> u_ptr{new int};
    u_ptr.reset(nullptr);
    EXPECT_EQ(u_ptr.get(), nullptr);
    u_ptr.reset(new int);
    EXPECT_NE(u_ptr.get(), nullptr);
}

TEST(UniquePtrTest, DereferenceTest) {
    constexpr int a {3};
    constexpr int b {5};
    ali::unique_ptr<int> u_ptr1{new int{a}};
    ali::unique_ptr<int> u_ptr2{new int{b}};
    EXPECT_EQ(*u_ptr1, a);
    EXPECT_EQ(*u_ptr2, b);
}

TEST(UniquePtrTest, SwapTest) {
    constexpr int a {3};
    constexpr int b {5};
    ali::unique_ptr<int> u_ptr1{new int{a}};
    ali::unique_ptr<int> u_ptr2{new int{b}};
    u_ptr1.swap(u_ptr2);
    EXPECT_EQ(*u_ptr1, b);
    EXPECT_EQ(*u_ptr2, a);
}

TEST(UniquePtrTest, EqualityOperator) {
    ali::unique_ptr<int> u_ptr1{new int};
    ali::unique_ptr<int> u_ptr2{new int};
    EXPECT_EQ(u_ptr1 == u_ptr2, 0);
    EXPECT_EQ(u_ptr1 == u_ptr1, 1);
}

TEST(UniquePtrTest, NEqualityOperator) {
    ali::unique_ptr<int> u_ptr1{new int};
    ali::unique_ptr<int> u_ptr2{new int};
    EXPECT_EQ(u_ptr1 != u_ptr2, true);
    EXPECT_EQ(u_ptr1 != u_ptr1, false);
}

TEST(UniquePtrTest, ComparisionOperatorsTest) {
    ali::unique_ptr<int> u_ptr1{new int};
    ali::unique_ptr<int> u_ptr2{new int};
    EXPECT_EQ(u_ptr1 < u_ptr2, false);
    EXPECT_EQ(u_ptr1 > u_ptr2, true);
}

TEST(UniquePtrTest, BoolCastTest) {
    ali::unique_ptr<int> u_ptr1;
    ali::unique_ptr<int> u_ptr2{new int};
    EXPECT_EQ(static_cast<bool>(u_ptr1), false);
    EXPECT_EQ(static_cast<bool>(u_ptr2), true);
}

TEST(UniquePtrForArrays, Constructor) {
    constexpr std::size_t n {5};
    ali::unique_ptr<int[]> u_ptr{new int[n]};
    EXPECT_NE(u_ptr.get(), nullptr);
}

TEST(UniquePtrForArrays, MoveCostructor) {
    constexpr std::size_t n{5};
    ali::unique_ptr<int[]> u_ptr1{new int[n]};
    EXPECT_NE(u_ptr1.get(), nullptr);
    ali::unique_ptr<int[]> u_ptr2(std::move(u_ptr1));
    EXPECT_EQ(u_ptr1.get(), nullptr);
    EXPECT_NE(u_ptr2.get(), nullptr);
}

TEST(UniquePtrForArrays, ReleaseTest) {
    constexpr std::size_t n{5};
    ali::unique_ptr<int[]> u_ptr{new int[n]};
    u_ptr.release();
    EXPECT_EQ(u_ptr.get(), nullptr);
}

TEST(UniquePtrForArrays, ResetTest) {
    constexpr std::size_t n{10};
    ali::unique_ptr<int[]> u_ptr{new int[n]};
    u_ptr.reset(nullptr);
    EXPECT_EQ(u_ptr.get(), nullptr);
    u_ptr.reset(new int[n]);
    EXPECT_NE(u_ptr.get(), nullptr);
}

TEST(UniquePtrForArrays, SwapTest) {
    constexpr std::size_t n{10};
    ali::unique_ptr<int[]> u_ptr1{new int[n]};
    ali::unique_ptr<int[]> u_ptr2;
    u_ptr1.swap(u_ptr2);
    EXPECT_EQ(u_ptr1.get(), nullptr);
    EXPECT_NE(u_ptr2.get(), nullptr);
}

TEST(UniquePtrForArrays, MoveAssigment) {
    constexpr std::size_t n{10};
    ali::unique_ptr<int[]> u_ptr1{new int[n]};
    ali::unique_ptr<int[]> u_ptr2{new int[n]};
    u_ptr2 = std::move(u_ptr1);
    EXPECT_EQ(u_ptr1.get(), nullptr);
    EXPECT_NE(u_ptr2.get(), nullptr);
}

TEST(UniquePtrForArrays, BoolCast) {
    constexpr std::size_t n{10};
    ali::unique_ptr<int[]> u_ptr1;
    ali::unique_ptr<int[]> u_ptr2{new int[n]};
    EXPECT_EQ(static_cast<bool>(u_ptr1), false);
    EXPECT_EQ(static_cast<bool>(u_ptr2), true);
}

TEST(UniquePtrForArrays, DereferenceTest) {
    constexpr std::size_t n{5};
    ali::unique_ptr<int[]> u_ptr(new int[n] {1, 2, 3, 4, 5});
    for (size_t i {0}; i < n; i++)
        EXPECT_EQ(u_ptr[i], i + 1);
}

TEST(UniquePtrForArrays, EqualityOperator) {
    constexpr std::size_t n{5};
    ali::unique_ptr<int[]> u_ptr1;
    ali::unique_ptr<int[]> u_ptr2{new int[n]};
    EXPECT_EQ(u_ptr1 == u_ptr1, true);
    EXPECT_EQ(u_ptr1 == u_ptr2, false);
}