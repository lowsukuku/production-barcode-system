#include "gtest/gtest.h"

#include "../Scaner/Scaner.h"

TEST(get_set, 1)
{
    Scaner scaner;

    scaner.setAPI("qwe123ww1fj12");

    ASSERT_STREQ("qwe123ww1fj12", scaner.getAPI());

    delete user;
}