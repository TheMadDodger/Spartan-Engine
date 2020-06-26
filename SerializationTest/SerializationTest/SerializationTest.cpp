// SerializationTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "SerializableAsset.h"
#include "Serializer.h"
#include <string>


int main()
{
    Serializer::LoadSerializers();

    GUID newGuid;
    CoCreateGuid(&newGuid);
    TestAsset* asset = new TestAsset(newGuid);

    const GUID& guid = asset->GetGUID();

    printf("Guid = {%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

    std::cout << std::endl;
    std::cout << std::endl;

    std::ofstream output("test", std::ios::binary);
    asset->Serialize(output);
    output.close();


    //std::ifstream input("test", std::ios::binary);
    //asset->Deserialize(input);
    //std::cin.get();

    delete asset;
}
