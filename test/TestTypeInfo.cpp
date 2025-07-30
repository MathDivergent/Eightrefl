#ifdef EIGHTREFL_STANDARD_ENABLE
#ifdef EIGHTREFL_RTTI_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/typeinfo.hpp>

TEST(TestStandard, TestTypeInfo)
{
    auto type = eightrefl::standard()->find("std::type_info");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::type_info");
    EXPECT("type-size", type->size == sizeof(std::type_info));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("function-operator==", type->function.find("operator==") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-before", type->function.find("before") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-hash_code", type->function.find("hash_code") != nullptr);
    EXPECT("function-name", type->function.find("name") != nullptr);
}
#endif // EIGHTREFL_RTTI_ENABLE
#endif // EIGHTREFL_STANDARD_ENABLE
