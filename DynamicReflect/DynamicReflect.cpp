
#include "TypeRegist/TypeInfoRegistry.hpp"
#include <iostream>

using namespace NekiraReflect;

enum class TestEnum
{
    ValueOne,
    ValueTwo,
    ValueThree
};

int main()
{
    EnumVector Enums = {
        {std::string("ValueOne"), static_cast<size_t>(TestEnum::ValueOne)},
        {std::string("ValueTwo"), static_cast<size_t>(TestEnum::ValueTwo)},
        {std::string("ValueThree"), static_cast<size_t>(TestEnum::ValueThree)}};

    auto EnumInfo = RegistEnumTypeInfo("TestEnum", std::move(Enums));

    std::cout << "Enum Name: " << EnumInfo->GetName() << std::endl;
    std::cout << "Enum Count: " << EnumInfo->GetEnumCount() << std::endl;

    std::cout << "Enum Values:" << std::endl;
    for (size_t i = 0; i < EnumInfo->GetEnumCount(); ++i)
    {
        std::cout << EnumInfo->GetEnumNameByValue(i) << " = " << i << std::endl;
    }

    return 0;
}