#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/list.hpp>

TEST(TestStandard, TestList)
{
    eightrefl::reflectable<std::list<int>>();

    auto type = eightrefl::standard()->find("std::list<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::list<int>");
    EXPECT("type-size", type->size == sizeof(std::list<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::list<int>()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(allocator_type const&)", type->factory.find("std::list<int>(std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference, allocator_type const&)", type->factory.find("std::list<int>(unsigned long, int const&, std::allocator<int> const&)") != nullptr || type->factory.find("std::list<int>(unsigned long long, int const&, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference)", type->factory.find("std::list<int>(unsigned long, int const&)") != nullptr || type->factory.find("std::list<int>(unsigned long long, int const&)") != nullptr);
    EXPECT("factory-R(size_type, allocator_type const&)", type->factory.find("std::list<int>(unsigned long, std::allocator<int> const&)") != nullptr || type->factory.find("std::list<int>(unsigned long long, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(size_type)", type->factory.find("std::list<int>(unsigned long)") != nullptr || type->factory.find("std::list<int>(unsigned long long)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, allocator_type const&)", type->factory.find("std::list<int>(std::list<int>::const_iterator, std::list<int>::const_iterator, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator)", type->factory.find("std::list<int>(std::list<int>::const_iterator, std::list<int>::const_iterator)") != nullptr);
    EXPECT("factory-R(R const&, allocator_type const&)", type->factory.find("std::list<int>(std::list<int> const&, std::allocator<int> const&)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(R const&)", type->factory.find("std::list<int>(std::list<int> const&)") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(std::initializer_list<value_type>, allocator_type const&)", type->factory.find("std::list<int>(std::initializer_list<int>, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>)", type->factory.find("std::list<int>(std::initializer_list<int>)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-assign", type->function.find("assign") != nullptr);
    EXPECT("function-get_allocator", type->function.find("get_allocator") != nullptr);
    EXPECT("function-front", type->function.find("front") != nullptr);
    EXPECT("function-back", type->function.find("back") != nullptr);
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
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-push_back", type->function.find("push_back") != nullptr);
    EXPECT("function-push_front", type->function.find("push_front") != nullptr);
    EXPECT("function-pop_back", type->function.find("pop_back") != nullptr);
    EXPECT("function-pop_front", type->function.find("pop_front") != nullptr);
    EXPECT("function-resize", type->function.find("resize") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-merge", type->function.find("merge") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-splice", type->function.find("splice") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-remove", type->function.find("remove") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-remove_if", type->function.find("remove_if") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-reverse", type->function.find("reverse") != nullptr);
    EXPECT("function-sort", type->function.find("sort") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
