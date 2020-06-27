// SerializationTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "SerializableAsset.h"
#include "Serializer.h"
#include "AssetFactory.h"

int main()
{
    Serializer::LoadSerializers();
    AssetFactory::RegisterAsset<TestAsset>();

    TestAsset* asset = AssetFactory::CreateInstance<TestAsset>();
    const GUID& guid = asset->GetGUID();

    printf("Guid = {%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

    std::cout << std::endl;

    std::cout << asset->m_TestData1 << std::endl;
    std::cout << asset->m_TestData2 << std::endl;
    std::cout << asset->m_TestData3 << std::endl;
    std::cout << asset->m_TestData4 << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    std::ofstream output("test", std::ios::binary);
    asset->Serialize(output);
    output.close();

    std::cin.get();

    std::ifstream input("test", std::ios::binary);
    TestAsset* deserializedAsset = (TestAsset*)AssetFactory::DeserializeToAsset(input);
    input.close();

    const GUID& newGUID = deserializedAsset->GetGUID();

    printf("Deserialized Guid = {%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}",
        newGUID.Data1, newGUID.Data2, newGUID.Data3,
        newGUID.Data4[0], newGUID.Data4[1], newGUID.Data4[2], newGUID.Data4[3],
        newGUID.Data4[4], newGUID.Data4[5], newGUID.Data4[6], newGUID.Data4[7]);

    std::cout << std::endl;

    std::cout << deserializedAsset->m_TestData1 << std::endl;
    std::cout << deserializedAsset->m_TestData2 << std::endl;
    std::cout << deserializedAsset->m_TestData3 << std::endl;
    std::cout << deserializedAsset->m_TestData4 << std::endl;

    std::cin.get();

    delete asset;
}
