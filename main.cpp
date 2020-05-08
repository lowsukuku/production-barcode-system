#include "Product/Product.h"
#include "Product/ProductMapper.h"

int main()
{
    Product A;
    A.setDeviceId(1234);
    A.setModelId(5678);
    A.setMountingPassed(1);

    ProductMapper PM;
    PM.addProduct(A);
}