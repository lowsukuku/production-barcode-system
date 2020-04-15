#include "gtest/gtest.h"

#include "../User/User.h"

TEST(get_set, 1)
{
    User user;

    user.setName("Bob");

    ASSERT_STREQ("Bob", user.getName());

    delete user;
}

TEST(get_set, 2)
{
    User user;

    user.setSurname("Smith");

    ASSERT_STREQ("Smith", user.getSurname());

    delete user;
}

TEST(get_set, 3)
{
    User user;

    user.setLogin("Bob_1995");

    ASSERT_STREQ("Bob_1995", user.getLogin());

    delete user;
}

TEST(get_set, 4)
{
    User user;

    user.setPassword("QWERTY");

    ASSERT_STREQ("QWERTY", user.getPassword());

    delete user;
}