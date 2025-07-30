#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/array.hpp>

TEST(TestStandard, TestArray)
{
    eightrefl::reflectable<std::array<int, 8>>();

    auto type = eightrefl::standard()->find("std::array<int, 8>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::array<int, 8>");
    EXPECT("type-size", type->size == sizeof(std::array<int, 8>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::array<int, 8>()") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::array<int, 8>(std::array<int, 8> const&)") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    ASSERT("function-at", type->function.find("at") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator[]", type->function.find("operator[]") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-front", type->function.find("front") != nullptr);
    EXPECT("function-back", type->function.find("back") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-data", type->function.find("data") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-begin", type->function.find("begin") != nullptr);
    EXPECT("function-cbegin", type->function.find("cbegin") != nullptr);
    EXPECT("function-end", type->function.find("end") != nullptr);
    EXPECT("function-cend", type->function.find("cend") != nullptr);
    EXPECT("function-rbegin", type->function.find("rbegin") != nullptr);
    EXPECT("function-crbegin", type->function.find("crbegin") != nullptr);
    EXPECT("function-rend", type->function.find("rend") != nullptr);
    EXPECT("function-crend", type->function.find("crend") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-empty", type->function.find("empty") != nullptr);
    EXPECT("function-size", type->function.find("size") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-max_size", type->function.find("max_size") != nullptr);
    EXPECT("function-fill", type->function.find("fill") != nullptr);
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
