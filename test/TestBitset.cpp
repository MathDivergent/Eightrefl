#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/bitset.hpp>

TEST(TestStandard, TestBitset)
{
    eightrefl::reflectable<std::bitset<128>>();

    auto type = eightrefl::standard()->find("std::bitset<128>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::bitset<128>");
    EXPECT("type-size", type->size == sizeof(std::bitset<128>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::bitset<128>()") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::bitset<128>(std::bitset<128> const&)") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(unsigned long)", type->factory.find("std::bitset<128>(unsigned long)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(unsigned long long)", type->factory.find("std::bitset<128>(unsigned long long)") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(std::string const&, std::size_t)", type->factory.find("std::bitset<128>(std::string const&, std::size_t)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(std::string const&)", type->factory.find("std::bitset<128>(std::string const&)") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(char const*, std::size_t)", type->factory.find("std::bitset<128>(char const*, std::size_t)") != nullptr);
    EXPECT("factory-R(char const*)", type->factory.find("std::bitset<128>(char const*)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    ASSERT("function-operator=", type->function.find("operator=") != nullptr);
    ASSERT("function-operator==", type->function.find("operator==") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
//  ASSERT("function-operator[]", type->function.find("operator[]") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-test", type->function.find("test") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-all", type->function.find("all") != nullptr);
    EXPECT("function-any", type->function.find("any") != nullptr);
    EXPECT("function-none", type->function.find("none") != nullptr);
    EXPECT("function-count", type->function.find("count") != nullptr);
    EXPECT("function-size", type->function.find("size") != nullptr);
    EXPECT("function-operator&=", type->function.find("operator&=") != nullptr);
    EXPECT("function-operator|=", type->function.find("operator|=") != nullptr);
    EXPECT("function-operator^=", type->function.find("operator^=") != nullptr);
    EXPECT("function-operator~", type->function.find("operator~") != nullptr);
    EXPECT("function-operator<<", type->function.find("operator<<") != nullptr);
    EXPECT("function-operator<<=", type->function.find("operator<<=") != nullptr);
    EXPECT("function-operator>>", type->function.find("operator>>") != nullptr);
    EXPECT("function-operator>>=", type->function.find("operator>>=") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-set", type->function.find("set") != nullptr);
    EXPECT("function-reset", type->function.find("reset") != nullptr);
    EXPECT("function-flip", type->function.find("flip") != nullptr);
    EXPECT("function-to_string", type->function.find("to_string") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-to_ulong", type->function.find("to_ulong") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-to_ullong", type->function.find("to_ullong") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
