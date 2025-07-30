#ifdef EIGHTREFL_STANDARD_ENABLE
#ifdef EIGHTREFL_RTTI_ENABLE

#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/typeindex.hpp>

TEST(TestStandard, TestTypeIndex)
{
    auto type = eightrefl::standard()->find("std::type_index");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::type_index");
    EXPECT("type-size", type->size == sizeof(std::type_index));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R(std::type_info const&)", type->factory.find("std::type_index(std::type_info const&)") != nullptr);

#if __cplusplus > 201703L
    EXPECT("function-operator<=>", type->function.find("operator<=>") != nullptr);
#else
    EXPECT("function-operator==", type->function.find("operator==") != nullptr);
    EXPECT("function-operator!=", type->function.find("operator!=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-operator<", type->function.find("operator<") != nullptr);
    EXPECT("function-operator<=", type->function.find("operator<=") != nullptr);
    EXPECT("function-operator>", type->function.find("operator>") != nullptr);
    EXPECT("function-operator>=", type->function.find("operator>=") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
#endif // if

    EXPECT("function-hash_code", type->function.find("hash_code") != nullptr);
    EXPECT("function-name", type->function.find("name") != nullptr);
}
#endif // EIGHTREFL_RTTI_ENABLE
#endif // EIGHTREFL_STANDARD_ENABLE
