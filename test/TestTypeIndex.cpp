#ifdef EIGHTREFL_STANDARD_ENABLE
#ifdef EIGHTREFL_RTTI_ENABLE

#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/typeindex.hpp>

TEST(TestBuiltin, TestTypeIndex)
{
    auto type = eightrefl::standard()->find("std::type_index");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::type_index");
    EXPECT("type-size", type->size == sizeof(std::type_index));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::type_index");

    EXPECT("factory-R(std::type_info const&)", reflection->factory.find("std::type_index(std::type_info const&)") != nullptr);

#if __cplusplus > 201703L
    EXPECT("function-operator<=>", reflection->function.find("operator<=>") != nullptr);
#else
    EXPECT("function-operator==", reflection->function.find("operator==") != nullptr);
    EXPECT("function-operator!=", reflection->function.find("operator!=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-operator<", reflection->function.find("operator<") != nullptr);
    EXPECT("function-operator<=", reflection->function.find("operator<=") != nullptr);
    EXPECT("function-operator>", reflection->function.find("operator>") != nullptr);
    EXPECT("function-operator>=", reflection->function.find("operator>=") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
#endif // if

    EXPECT("function-hash_code", reflection->function.find("hash_code") != nullptr);
    EXPECT("function-name", reflection->function.find("name") != nullptr);
}
#endif // EIGHTREFL_RTTI_ENABLE
#endif // EIGHTREFL_STANDARD_ENABLE
