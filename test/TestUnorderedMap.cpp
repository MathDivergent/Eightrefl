#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/unordered_map.hpp>

TEST(TestStandard, TestUnorderedMap)
{
    eightrefl::reflectable<std::unordered_map<int, float>>();

    auto type = eightrefl::standard()->find("std::unordered_map<int, float>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::unordered_map<int, float>");
    EXPECT("type-size", type->size == sizeof(std::unordered_map<int, float>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::unordered_map<int, float>()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("R(size_type, hasher const&, key_equal const&, allocator_type const&)", type->factory.find("std::unordered_map<int, float>(unsigned long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(unsigned long long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(size_type, hasher const&, key_equal const&)", type->factory.find("std::unordered_map<int, float>(unsigned long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(unsigned long long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr);
    EXPECT("R(size_type, hasher const&)", type->factory.find("std::unordered_map<int, float>(unsigned long, std::hash<int> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(unsigned long long, std::hash<int> const&)") != nullptr);
    EXPECT("R(size_type)", type->factory.find("std::unordered_map<int, float>(unsigned long)") != nullptr || type->factory.find("std::unordered_map<int, float>(unsigned long long)") != nullptr);
    EXPECT("R(size_type, allocator_type const&)", type->factory.find("std::unordered_map<int, float>(unsigned long, std::allocator<std::pair<int const, float>> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(unsigned long long, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(size_type, hasher const&, typename R::allocator_type const&)", type->factory.find("std::unordered_map<int, float>(unsigned long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(unsigned long long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, hasher const&, key_equal const&, allocator_type const&)", type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, hasher const&, key_equal const&)", type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, hasher const&)", type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::hash<int> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::hash<int> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type)", type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, allocator_type const&)", type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::allocator<std::pair<int const, float>> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, hasher const&, allocator_type const&)", type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type, hasher const&, key_equal const&, allocator_type const&)", type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type, hasher const&, key_equal const&)", type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type, hasher const&)", type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long, std::hash<int> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long, std::hash<int> const&)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type)", type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type, hasher const&, allocator_type const&)", type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || type->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(R const&)", type->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float> const&)") != nullptr);
    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-get_allocator", type->function.find("get_allocator") != nullptr);
    EXPECT("function-begin", type->function.find("begin") != nullptr);
    EXPECT("function-cbegin", type->function.find("cbegin") != nullptr);
    EXPECT("function-end", type->function.find("end") != nullptr);
    EXPECT("function-cend", type->function.find("cend") != nullptr);
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
    EXPECT("function-at", type->function.find("at") != nullptr);
    EXPECT("function-operator[]", type->function.find("operator[]") != nullptr);
    EXPECT("function-count", type->function.find("count") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-find", type->function.find("find") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

#if __cplusplus >= 202002L
    EXPECT("function-contains", type->function.find("contains") != nullptr);
#endif // if

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-equal_range", type->function.find("equal_range") != nullptr);
    EXPECT("function-bucket_count", type->function.find("bucket_count") != nullptr);
    EXPECT("function-max_bucket_count", type->function.find("max_bucket_count") != nullptr);
    EXPECT("function-bucket_size", type->function.find("bucket_size") != nullptr);
    EXPECT("function-bucket", type->function.find("bucket") != nullptr);
    EXPECT("function-load_factor", type->function.find("load_factor") != nullptr);
    EXPECT("function-max_load_factor", type->function.find("max_load_factor") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-rehash", type->function.find("rehash") != nullptr);
    EXPECT("function-reserve", type->function.find("reserve") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-hash_function", type->function.find("hash_function") != nullptr);
    EXPECT("function-key_eq", type->function.find("key_eq") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
