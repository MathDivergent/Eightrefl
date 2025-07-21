#ifdef EIGHTREFL_RTTI_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/typeinfo.hpp>

TEST(TestBuiltin, TestTypeInfo)
{
    auto type = eightrefl::standard()->find("std::type_info");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::type_info");
    EXPECT("type-size", type->size == sizeof(std::type_info));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::type_info");

    EXPECT("function-operator==", reflection->function.find("operator==") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-before", reflection->function.find("before") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-hash_code", reflection->function.find("hash_code") != nullptr);
    EXPECT("function-name", reflection->function.find("name") != nullptr);
}
#endif // EIGHTREFL_RTTI_ENABLE
