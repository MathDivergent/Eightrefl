#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/map.hpp>

TEST(TestStandard, TestMap)
{
    eightrefl::reflectable<std::map<int, float>>();

    auto type = eightrefl::standard()->find("std::map<int, float>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::map<int, float>");
    EXPECT("type-size", type->size == sizeof(std::map<int, float>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::map<int, float>()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(key_compare const&, allocator_type const&)", type->factory.find("std::map<int, float>(std::less<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("factory-R(key_compare const&)", type->factory.find("std::map<int, float>(std::less<int> const&)") != nullptr);
    EXPECT("factory-R(allocator_type const&)", type->factory.find("std::map<int, float>(std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, key_compare const&, allocator_type const&)", type->factory.find("std::map<int, float>(std::map<int, float>::const_iterator, std::map<int, float>::const_iterator, std::less<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, allocator_type const&)", type->factory.find("std::map<int, float>(std::map<int, float>::const_iterator, std::map<int, float>::const_iterator, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(R const&)", type->factory.find("std::map<int, float>(std::map<int, float> const&)") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(R const&, allocator_type const&)", type->factory.find("std::map<int, float>(std::map<int, float> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>, key_compare const&, allocator_type const&)", type->factory.find("std::map<int, float>(std::initializer_list<std::pair<int const, float>>, std::less<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>)", type->factory.find("std::map<int, float>(std::initializer_list<std::pair<int const, float>>)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-get_allocator", type->function.find("get_allocator") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-at", type->function.find("at") != nullptr);
    EXPECT("function-operator[]", type->function.find("operator[]") != nullptr);

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
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-clear", type->function.find("clear") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-insert", type->function.find("insert") != nullptr);
    EXPECT("function-erase", type->function.find("erase") != nullptr);
    EXPECT("function-swap", type->function.find("swap") != nullptr);
//  EXPECT("function-extract", type->function.find("extract") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-merge", type->function.find("merge") != nullptr);
    EXPECT("function-count", type->function.find("count") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-find", type->function.find("find") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

#if __cplusplus >= 202002L
    EXPECT("function-contains", type->function.find("contains") != nullptr);
#endif // if

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-equal_range", type->function.find("equal_range") != nullptr);
    EXPECT("function-lower_bound", type->function.find("lower_bound") != nullptr);
    EXPECT("function-upper_bound", type->function.find("upper_bound") != nullptr);
    EXPECT("function-key_comp", type->function.find("key_comp") != nullptr);
//  EXPECT("function-value_comp", type->function.find("value_comp") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
