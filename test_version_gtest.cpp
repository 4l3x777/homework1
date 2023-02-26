#include "lib.h"
#include "gtest/gtest.h"

namespace {
    TEST(VersionTest, NotZero) 
    {  
        EXPECT_TRUE(version() > 0);
    }
}