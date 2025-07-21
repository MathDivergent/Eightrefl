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
        eightrefl::find_or_add_parent<R, TestWithoutMacroBaseStruct>(type->reflection);
        eightrefl::find_or_add_factory<R()>(type->reflection);
        eightrefl::find_or_add_function(type->reflection, "Function", &R::Function);
        eightrefl::find_or_add_property(type->reflection, "Property", &R::Property, &R::Property);
        eightrefl::find_or_add_deleter<void(R*)>(type->reflection);
        eightrefl::find_or_add_meta(type->reflection->meta, "Meta", 123);
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

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "TestWithoutMacroStruct");

    EXPECT("parent", reflection->parent.find("TestWithoutMacroBaseStruct") != nullptr);
    EXPECT("factory", reflection->factory.find("TestWithoutMacroStruct()") != nullptr);
    EXPECT("function", reflection->function.find("Function") != nullptr);
    EXPECT("property", reflection->property.find("Property") != nullptr);
    EXPECT("deleter", reflection->deleter.find("void(TestWithoutMacroStruct*)") != nullptr);
    EXPECT("meta", reflection->meta.find("Meta") != nullptr);
    EXPECT("injection", type->injection.find("TestWithoutMacroInjection") != nullptr);
}
