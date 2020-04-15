#include "gtest/gtest.h"

#include "../Scaner/Scaner.h"

TEST(get_set, 1)
{
    Product product;

    product.setDeviceId(123);

    ASSERT_EQ(123, product.getDeviceId());

    delete user;
}

TEST(get_set, 2)
{
    Product product;

    product.setModelId(123);

    ASSERT_EQ(123, product.getModelId());

    delete user;
}

TEST(get_set, 3)
{
    Product product;

    product.setCreationUtc(123);

    ASSERT_EQ(123, product.getCreationUtc());

    delete user;
}

TEST(get_set, 4)
{
    Product product;

    product.setSerialNumber(123);

    ASSERT_EQ(123, product.getSerialNumber());

    delete user;
}

TEST(get_set, 5)
{
    Product product;

    product.setMountingUtc(123);

    ASSERT_EQ(123, product.getMountingUtc());

    delete user;
}

TEST(get_set, 6)
{
    Product product;

    product.setTuningUtc(123);

    ASSERT_EQ(123, product.getTuningUtc());

    delete user;
}

TEST(get_set, 7)
{
    Product product;

    product.setQuailityCheckUtc(123);

    ASSERT_EQ(123, product.getQuailityCheckUtc());

    delete user;
}

TEST(get_set, 8)
{
    Product product;

    product.setShipmentUtc(123);

    ASSERT_EQ(123, product.getShipmentUtc());

    delete user;
}

TEST(get_set, 9)
{
    Product product;

    product.setMountingPassed(123);

    ASSERT_EQ(123, product.getMountingPassed());

    delete user;
}

TEST(get_set, 10)
{
    Product product;

    product.setTuningPassed(123);

    ASSERT_EQ(123, product.getTuningPassed());

    delete user;
}

TEST(get_set, 11)
{
    Product product;

    product.setQualityCheckPassed(123);

    ASSERT_EQ(123, product.getQualityCheckPassed());

    delete user;
}

TEST(get_set, 12)
{
    Product product;

    product.setShipmentPassed(123);

    ASSERT_EQ(123, product.getShipmentPassed());

    delete user;
}
