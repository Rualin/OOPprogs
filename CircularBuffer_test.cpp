#include <gtest/gtest.h>
#include "CircularBuffer.hpp"
#include <iostream>

typedef char value_type;

class CircularBufferTest : public ::testing::Test {
protected:
    CircularBuffer cb;

    void SetUp() override {
        cb = CircularBuffer(5); // создаем буфер с ёмкостью 5
    }
};

TEST_F(CircularBufferTest, ConstructorWithElement) {
    CircularBuffer cb(5, 'A');
    EXPECT_EQ(cb.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(cb[i], 'A');
    }
}

TEST_F(CircularBufferTest, CopyConstructor) {
    cb.push_back('A');
    cb.push_back('B');
    CircularBuffer cb2(cb);
    EXPECT_EQ(cb2.size(), 2);
    EXPECT_EQ(cb2[0], 'A');
    EXPECT_EQ(cb2[1], 'B');
}

TEST_F(CircularBufferTest, PushBack) {
    cb.push_back('A');
    cb.push_back('B');
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.back(), 'B');
}

TEST_F(CircularBufferTest, PushFront) {
    cb.push_back('A');
    cb.push_back('B');
    cb.push_front('C');
    EXPECT_EQ(cb.front(), 'C');
}

TEST_F(CircularBufferTest, PopBack) {
    cb.push_back('A');
    cb.push_back('B');
    cb.pop_back();
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.back(), 'A');
}

TEST_F(CircularBufferTest, PopFront) {
    cb.push_back('A');
    cb.push_back('B');
    cb.pop_front();
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.front(), 'B');
}

TEST_F(CircularBufferTest, AtMethod) {
    cb.push_back('A');
    cb.push_back('B');
    EXPECT_EQ(cb.at(1), 'B');
}

TEST_F(CircularBufferTest, AtMethodOutOfRange) {
    EXPECT_THROW(cb.at(0), std::out_of_range);
}

TEST_F(CircularBufferTest, Linearize) {
    cb.push_back('A');
    cb.push_back('B');
    value_type* linearized = cb.linearize();
    EXPECT_EQ(linearized[0], 'A');
}

TEST_F(CircularBufferTest, IsLinearized) {
    EXPECT_TRUE(cb.is_linearized());
}

TEST_F(CircularBufferTest, Rotate) {
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    cb.rotate(1);
    EXPECT_EQ(cb.front(), 'B');
}

TEST_F(CircularBufferTest, Resize) {
    cb.resize(10, 'X');
    EXPECT_EQ(cb.capacity(), 10);
}

TEST_F(CircularBufferTest, ResizeSmallerThanCurrentSize) {
    cb.push_back('A');
    cb.push_back('B');
    EXPECT_THROW(cb.resize(1), std::length_error);
}

TEST_F(CircularBufferTest, Clear) {
    cb.push_back('A');
    cb.clear();
    EXPECT_TRUE(cb.empty());
}

TEST_F(CircularBufferTest, Insert) {
    cb.push_back('A');
    cb.insert(0, 'B'); // insert B at position 0
    EXPECT_EQ(cb.front(), 'B');
}

TEST_F(CircularBufferTest, Erase) {
    cb.push_back('A');
    cb.push_back('B');
    cb.erase(0, 1); // erase from index 0 to 1
    EXPECT_EQ(cb.size(), 1);
}

TEST_F(CircularBufferTest, Swap) {
    CircularBuffer cb2(5, 'X');
    cb.push_back('A');
    
    cb.swap(cb2);
    
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb2.size(), 1);
}

TEST_F(CircularBufferTest, AssignmentOperator) {
    cb.push_back('A');
    
    CircularBuffer cb2;
    cb2 = cb;
    
    EXPECT_EQ(cb2.size(), 1);
    EXPECT_EQ(cb2.front(), 'A');
}

TEST_F(CircularBufferTest, EqualityOperator) {
    CircularBuffer cb2(5, 'A');
    
    EXPECT_TRUE(cb == cb2);
    
    cb2.push_back('B'); 
    EXPECT_FALSE(cb == cb2);
}

TEST_F(CircularBufferTest, InequalityOperator) {
    CircularBuffer cb2(5, 'A');

    EXPECT_FALSE(cb != cb2);

    cb2.push_back('B'); 
    EXPECT_TRUE(cb != cb2);
}

TEST_F(CircularBufferTest, SetCapacity) {
    cb.push_back('A');
    cb.push_back('B');
    cb.set_capacity(10);
    EXPECT_EQ(cb.capacity(), 10);
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.front(), 'A');
    EXPECT_EQ(cb.back(), 'B');
}

TEST_F(CircularBufferTest, ResizeSmaller) {
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    cb.resize(2);
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.front(), 'A');
    EXPECT_EQ(cb.back(), 'B');
}


TEST_F(CircularBufferTest, InsertMiddle) {
    cb.push_back('A');
    cb.push_back('C');
    cb.insert(1, 'B'); // insert B at position 1
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 'A');
    EXPECT_EQ(cb[1], 'B');
    EXPECT_EQ(cb[2], 'C');
}

TEST_F(CircularBufferTest, InsertEnd) {
    cb.push_back('A');
    cb.push_back('B');
    cb.insert(2, 'C'); // insert C at the end
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 'A');
    EXPECT_EQ(cb[1], 'B');
    EXPECT_EQ(cb[2], 'C');
}

TEST_F(CircularBufferTest, EraseMiddle) {
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    cb.erase(1, 2); // erase from index 1 to 2
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 'A');
    EXPECT_EQ(cb[1], 'C');
}

TEST_F(CircularBufferTest, EraseEnd) {
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    cb.erase(1, 3); // erase from index 1 to the end
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb[0], 'A');
}


TEST_F(CircularBufferTest, SwapDifferentCapacity) {
    CircularBuffer cb2(10, 'X');
    cb.push_back('A');
    cb.push_back('B');

    cb.swap(cb2);

    EXPECT_EQ(cb.capacity(), 10);
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 'A');
    EXPECT_EQ(cb[1], 'B');

    EXPECT_EQ(cb2.capacity(), 5);
    EXPECT_EQ(cb2.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(cb2[i], 'X');
    }
}


TEST_F(CircularBufferTest, AssignmentOperatorMultipleElements) {
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');

    CircularBuffer cb2;
    cb2 = cb;

    EXPECT_EQ(cb2.size(), 3);
    EXPECT_EQ(cb2.front(), 'A');
    EXPECT_EQ(cb2.back(), 'C');
}


