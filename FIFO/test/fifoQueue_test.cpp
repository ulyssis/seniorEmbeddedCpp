// fifoQueue_test.cpp
#include <gtest/gtest.h>
#include "../lib/queue.h"

// Test case for fifoQueue
class fifoQueueTest : public ::testing::Test
{
protected:
    Queue *q = new Queue(10);

    // You can do set-up work for each test here.
    void SetUp() override
    {
        for (int i = 0; i < 8; i++)
        {
            q->queue(i);
        }
    }

    // You can do clean-up work that doesn't throw exceptions here.
    void TearDown() override
    {
        // Clean up code if necessary
        delete q;
    }
};

// Tests that the fifoQueue can add elements.
TEST_F(fifoQueueTest, HandlesSizeIncrease)
{
    ASSERT_EQ(q->queue(1), 0);
    ASSERT_EQ(q->queue(1), 0);
    ASSERT_EQ(q->queue(1), -1);
}
