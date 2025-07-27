#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/vector.hpp>

TEST(TestBuiltin, TestVectorBool)
{
    eightrefl::reflectable<std::vector<bool>>();

    auto type = eightrefl::standard()->find("std::vector<bool>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::vector<bool>");
    EXPECT("type-size", type->size == sizeof(std::vector<bool>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::vector<bool>()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(allocator_type const&)", type->factory.find("std::vector<bool>(std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference, allocator_type const&)", type->factory.find("std::vector<bool>(unsigned long, std::vector<bool>::const_reference, std::allocator<bool> const&)") != nullptr || type->factory.find("std::vector<bool>(unsigned long long, std::vector<bool>::const_reference, std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference)", type->factory.find("std::vector<bool>(unsigned long, std::vector<bool>::const_reference)") != nullptr || type->factory.find("std::vector<bool>(unsigned long long, std::vector<bool>::const_reference)") != nullptr);
    EXPECT("factory-R(size_type, allocator_type const&)", type->factory.find("std::vector<bool>(unsigned long, std::allocator<bool> const&)") != nullptr || type->factory.find("std::vector<bool>(unsigned long long, std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(size_type)", type->factory.find("std::vector<bool>(unsigned long)") != nullptr || type->factory.find("std::vector<bool>(unsigned long long)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, allocator_type const&)", type->factory.find("std::vector<bool>(std::vector<bool>::const_iterator, std::vector<bool>::const_iterator, std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator)", type->factory.find("std::vector<bool>(std::vector<bool>::const_iterator, std::vector<bool>::const_iterator)") != nullptr);
    EXPECT("factory-R(R const&, allocator_type const&)", type->factory.find("std::vector<bool>(std::vector<bool> const&, std::allocator<bool> const&)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(R const&)", type->factory.find("std::vector<bool>(std::vector<bool> const&)") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(std::initializer_list<value_type>, allocator_type const&)", type->factory.find("std::vector<bool>(std::initializer_list<bool>, std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>)", type->factory.find("std::vector<bool>(std::initializer_list<bool>)") != nullptr);
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

//  EXPECT("function-push_back", type->function.find("push_back") != nullptr);
    EXPECT("function-pop_back", type->function.find("pop_back") != nullptr);
//  EXPECT("function-resize", type->function.find("resize") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    EXPECT("function-flip", type->function.find("flip") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
