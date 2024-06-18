// fifoQueue_test.cpp
#include <gtest/gtest.h>
#include "../lib/queue.h"
#include <fstream> //uesd in custom setup

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
    ASSERT_EQ(q->queue(8), 0);
    ASSERT_EQ(q->queue(9), 0);
    ASSERT_EQ(q->queue(10), -1);
}

TEST_F(fifoQueueTest, HandlesSizeDecrease)
{
    Node *deqNode = q->dequeue();
    ASSERT_NE(deqNode, nullptr);
    ASSERT_EQ(deqNode->val, 0);
    delete deqNode;

    deqNode = q->dequeue();
    ASSERT_NE(deqNode, nullptr);
    ASSERT_EQ(deqNode->val, 1);
    delete deqNode;

    ASSERT_EQ(q->get_size(), 6);
}

TEST_F(fifoQueueTest, EmptyQueue)
{
    for (int i = 0; i < 8; i++)
    {
        Node *deqNode = q->dequeue();
        ASSERT_NE(deqNode, nullptr);
        ASSERT_EQ(deqNode->val, i);
        delete deqNode;
    }
    ASSERT_EQ(q->dequeue(), nullptr);
    ASSERT_EQ(q->get_size(), 0);
}

TEST_F(fifoQueueTest, CopyAssignmentOperatiorWorks)
{
    Queue *tempQueue = new Queue(5);
    for (int i = 0; i < 5; i++)
    {
        tempQueue->queue(i);
    }
    // use copy assignment operator to change the tempQueue
    *tempQueue = *q;
    // Validate the copied queue
    for (int i = 0; i < 8; i++)
    {
        Node *deqNode = tempQueue->dequeue();
        ASSERT_NE(deqNode, nullptr);
        ASSERT_EQ(deqNode->val, i);
        delete deqNode;
    }
    ASSERT_EQ(tempQueue->dequeue(), nullptr);
    ASSERT_EQ(tempQueue->get_size(), 0);
    // clean up
    delete tempQueue;
}

// // TODO
// TEST_F(fifoQueueTest, MoveAssignmentOperatorWorks)
// {
// }

void CustomSetup()
{
    std::cout << "Custom setup: Initializing logging system." << std::endl;
    std::ofstream logFile("est_log.txt");
    logFile << "Starting test log" << std::endl;
    logFile.close();
}

void CustomTeardown()
{
    std::cout << "Custom setup: Cleaning up logging system." << std::endl;
    std::ofstream logFile("est_log.txt", std::ios_base::app);
    logFile << "Ending test log" << std::endl;
    logFile.close();
}

// 1. If you need to perform any special setup or teardown before or after running all the tests, you would include your own main function. This allows you to call custom code before
// 2. If GTest::gtest is speficifed in the target_link_libraries, the main function is needed
// 3. if GTest::gtest_main is specified, the custom main will be executed when it is available (it overrides the default main function from google Test). If custom main is not available, then the default main function from GTest::gtest_main will be executed.
int main(int argc, char **argv)
{
    std::cout << "custom main function is executed." << std::endl;
    ::testing::InitGoogleTest(&argc, argv);

    // Perform custom setup before running tests
    CustomSetup();

    int result = RUN_ALL_TESTS();

    // Perform custom teardown after running tests
    CustomTeardown();

    return result;
}