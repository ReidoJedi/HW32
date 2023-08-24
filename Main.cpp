#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "mysql.h"
#include "Back.h"
using namespace std;


TEST(PainterTest, test1)
{
    MockTesting mDBconnector;

    EXPECT_CALL(mDBconnector, openConnection).Times(::testing::AtLeast(1));
    EXPECT_CALL(mDBconnector, useConnection).Times(::testing::AtLeast(1));
    EXPECT_CALL(mDBconnector, closeonnection).Times(::testing::AtLeast(2));
    
}

int main()
{
    ::testing::InitGoogleTest(); 
    return RUN_ALL_TESTS();
}

