#include "src/Parser/IPost.h"
#include "src/Parser/IGet.h"



int main()
{
    IPost add;

    add.addToDB("{\n"
                "  \"context\" :\n"
                "  {\n"
                "    \"deviceId\" : \"1\",\n"
                "    \"modelId\" : \"228\",\n"
                "    \"creationUtc\" : \"3\",\n"
                "    \"serialNumber\" : \"4\",\n"
                "    \"mountingUtc\" : \"5\",\n"
                "    \"tuningUtc\" : \"6\",\n"
                "    \"quailityCheckUtc\" : \"7\",\n"
                "    \"shipmentUtc\" : \"8\",\n"
                "    \"mountingPassed\" : \"1\",\n"
                "    \"tuningPassed\" : \"1\",\n"
                "    \"qualityCheckPassed\" : \"1\",\n"
                "    \"shipmentPassed\" : \"1\"\n"
                "  }\n"
                "}");

    IGet get;

    std::cout << get.getJsonProductByDeviceId(1) << std::endl;
}