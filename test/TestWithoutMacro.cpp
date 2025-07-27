#include <EightreflTestingBase.hpp>

TEST_SPACE()
{

struct TestWithoutMacroBaseStruct {};

struct TestWithoutMacroStruct : TestWithoutMacroBaseStruct
{
    void Function() {}

    int Property = 0;
};

struct TestWithoutMacroInjection : eightrefl::injectable_t {};

} // TEST_SPACE

// need only for default injections
// template <>
// struct xxeightrefl_traits<1>
// {
//     using R = TestWithoutMacroInjection;
// };

template <>
struct xxeightrefl_traits<TestWithoutMacroInjection>
{
    using R = TestWithoutMacroInjection; // not required by library
    static auto name() { return "TestWithoutMacroInjection"; }
};

template <>
struct xxeightrefl_traits<TestWithoutMacroBaseStruct>
{
    static auto registry() { return eightrefl::global(); }
    static auto name() { return "TestWithoutMacroBaseStruct"; }
};

template <>
struct xxeightrefl<TestWithoutMacroBaseStruct>
{
    template <typename InjectionType>
    void evaluate(InjectionType& injection)
    {
        eightrefl::find_or_add_type<TestWithoutMacroBaseStruct>();
    }
};

template <>
struct xxeightrefl_traits<TestWithoutMacroStruct>
{
    static auto registry() { return eightrefl::global(); }
    static auto name() { return "TestWithoutMacroStruct"; }
};

template <>
struct xxeightrefl<TestWithoutMacroStruct>
{
    using R = TestWithoutMacroStruct; // not required by library

    template <typename InjectionType>
    static void evaluate(InjectionType&& injection)
    {
        auto type = eightrefl::find_or_add_type<R>();
        eightrefl::find_or_add_parent<R, TestWithoutMacroBaseStruct>(type);
        eightrefl::find_or_add_factory<R()>(type);
        eightrefl::find_or_add_function(type, "Function", &R::Function);
        eightrefl::find_or_add_property(type, "Property", &R::Property, &R::Property);
        eightrefl::find_or_add_deleter<void(R*)>(type);
        eightrefl::find_or_add_meta(type->meta, "Meta", 123);
        eightrefl::find_or_add_injection<R, TestWithoutMacroInjection>(type);
    }
};

// need only for reflectable using
// struct TestWithoutMacroStructAlias : TestWithoutMacroStruct {};

// template <>
// struct xxeightrefl_alias<TestWithoutMacroStructAlias>
// {
//     using R = TestWithoutMacroStruct;
// };

TEST(TestLibrary, TestWithoutMacro)
{
    eightrefl::reflectable<TestWithoutMacroStruct>();

    auto type = eightrefl::global()->find("TestWithoutMacroStruct");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "TestWithoutMacroStruct");

    EXPECT("parent", type->parent.find("TestWithoutMacroBaseStruct") != nullptr);
    EXPECT("factory", type->factory.find("TestWithoutMacroStruct()") != nullptr);
    EXPECT("function", type->function.find("Function") != nullptr);
    EXPECT("property", type->property.find("Property") != nullptr);
    EXPECT("deleter", type->deleter.find("void(TestWithoutMacroStruct*)") != nullptr);
    EXPECT("meta", type->meta.find("Meta") != nullptr);
    EXPECT("injection", type->injection.find("TestWithoutMacroInjection") != nullptr);
}
