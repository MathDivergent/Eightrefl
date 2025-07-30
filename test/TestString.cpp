#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/string.hpp>

TEST(TestStandard, TestString)
{
    auto type = eightrefl::standard()->find("std::string");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::string");
    EXPECT("type-size", type->size == sizeof(std::string));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::string()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(allocator_type const&)", type->factory.find("std::string(std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(size_type, value_type, allocator_type const&)", type->factory.find("std::string(unsigned long, char, std::allocator<char> const&)") != nullptr || type->factory.find("std::string(unsigned long long, char, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(size_type, value_type)", type->factory.find("std::string(unsigned long, char)") != nullptr || type->factory.find("std::string(unsigned long long, char)") != nullptr);
    EXPECT("factory-R(R const&, size_type, size_type, allocator_type const&)", type->factory.find("std::string(std::string const&, unsigned long, unsigned long, std::allocator<char> const&)") != nullptr || type->factory.find("std::string(std::string const&, unsigned long long, unsigned long long, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(R const&, size_type, size_type)", type->factory.find("std::string(std::string const&, unsigned long, unsigned long)") != nullptr || type->factory.find("std::string(std::string const&, unsigned long long, unsigned long long)") != nullptr);
    EXPECT("factory-R(value_type const*, size_type, allocator_type const&)", type->factory.find("std::string(char const*, unsigned long, std::allocator<char> const&)") != nullptr || type->factory.find("std::string(char const*, unsigned long long, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(value_type const*, size_type)", type->factory.find("std::string(char const*, unsigned long)") != nullptr || type->factory.find("std::string(char const*, unsigned long long)") != nullptr);
    EXPECT("factory-R(value_type const*, allocator_type const&)", type->factory.find("std::string(char const*, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(value_type const*)", type->factory.find("std::string(char const*)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, allocator_type const&)", type->factory.find("std::string(std::string::const_iterator, std::string::const_iterator, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator)", type->factory.find("std::string(std::string::const_iterator, std::string::const_iterator)") != nullptr);
    EXPECT("factory-R(R const&, allocator_type const&)", type->factory.find("std::string(std::string const&, std::allocator<char> const&)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(R const&)", type->factory.find("std::string(std::string const&)") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(std::initializer_list<value_type>, allocator_type const&)", type->factory.find("std::string(std::initializer_list<char>, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>)", type->factory.find("std::string(std::initializer_list<char>)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-assign", type->function.find("assign") != nullptr);
    EXPECT("function-get_allocator", type->function.find("get_allocator") != nullptr);
    EXPECT("function-at", type->function.find("at") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator[]", type->function.find("operator[]") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-front", type->function.find("front") != nullptr);
    EXPECT("function-back", type->function.find("back") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-data", type->function.find("data") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-c_str", type->function.find("c_str") != nullptr);
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
    EXPECT("function-length", type->function.find("length") != nullptr);
    EXPECT("function-max_size", type->function.find("max_size") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-capacity", type->function.find("capacity") != nullptr);
    EXPECT("function-reserve", type->function.find("reserve") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-shrink_to_fit", type->function.find("shrink_to_fit") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-clear", type->function.find("clear") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-insert", type->function.find("insert") != nullptr);
    EXPECT("function-erase", type->function.find("erase") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-push_back", type->function.find("push_back") != nullptr);
    EXPECT("function-pop_back", type->function.find("pop_back") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-append", type->function.find("append") != nullptr);
    EXPECT("function-operator+=", type->function.find("operator+=") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-replace", type->function.find("replace") != nullptr);
    EXPECT("function-resize", type->function.find("resize") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    EXPECT("function-find", type->function.find("find") != nullptr);
    EXPECT("function-rfind", type->function.find("rfind") != nullptr);
    EXPECT("function-find_first_of", type->function.find("find_first_of") != nullptr);
    EXPECT("function-find_first_not_of", type->function.find("find_first_not_of") != nullptr);
    EXPECT("function-find_last_of", type->function.find("find_last_of") != nullptr);
    EXPECT("function-find_last_not_of", type->function.find("find_last_not_of") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-compare", type->function.find("compare") != nullptr);

#if __cplusplus >= 202002L
    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-starts_with", type->function.find("starts_with") != nullptr);
    EXPECT("function-ends_with", type->function.find("ends_with") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
#endif // if

    EXPECT("function-substr", type->function.find("substr") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
