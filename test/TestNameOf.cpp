#include <EightreflTestingBase.hpp>

// TODO: add nameof member pointer
TEST_SPACE()
{

struct TestNameOfStruct;
struct TestCustomNameOfStruct;

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestNameOfStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(TestCustomNameOfStruct)
    REFLECTABLE_NAME("Test_CustomNameOf_Struct")
REFLECTABLE_DECLARATION_INIT()

// TODO: add member - function point
TEST(TestLibrary, TestNameOf)
{
    EXPECT("const-type", eightrefl::name_of<const int>() == "int const");
    EXPECT("pointer-type", eightrefl::name_of<int*>() == "int*");
    EXPECT("const_pointer-type", eightrefl::name_of<int* const>() == "int* const");
    EXPECT("reference-type", eightrefl::name_of<int&>() == "int&");
    EXPECT("function-type", eightrefl::name_of<void(int, float)>() == "void(int, float)");
    EXPECT("function-const-type",  eightrefl::name_of<void(double const)>() == "void(double)"); // pass const qualifier - standard behavior
    EXPECT("function-pointer-type", eightrefl::name_of<void(*)(int, float)>() == "std::type_identity_t<void(int, float)>*");
    EXPECT("function-reference-type", eightrefl::name_of<void(&)(int, float)>() == "std::type_identity_t<void(int, float)>&");
    EXPECT("const-qualified_function-type", eightrefl::name_of<void(int, float) const>() == "void(int, float) const");
    EXPECT("reference-qualified_function-type", eightrefl::name_of<void(int, float)&>() == "void(int, float)&");
    EXPECT("const-reference_qualified_function-type", eightrefl::name_of<void(int, float) const&>() == "void(int, float) const&");
    EXPECT("array-type", eightrefl::name_of<int[8]>() == "int[8]");
    EXPECT("array-pointer-type", eightrefl::name_of<int(*)[8]>() == "std::type_identity_t<int[8]>*");
    EXPECT("array-reference-type", eightrefl::name_of<int(&)[8]>() == "std::type_identity_t<int[8]>&");
    EXPECT("mixed-type0", eightrefl::name_of<float(*[8])(void)>() == "std::type_identity_t<float()>*[8]");
    EXPECT("mixed-type1", eightrefl::name_of<char(*(* const*&)[8])(void)>() == "std::type_identity_t<std::type_identity_t<char()>*[8]>* const*&");
    EXPECT("mixed-type2", eightrefl::name_of<bool*(** const* (* const&)(void*, long))[3]>() == "std::type_identity_t<std::type_identity_t<bool*[3]>** const*(void*, long)>* const&");

    EXPECT("type", eightrefl::name_of<TestNameOfStruct>() == "TestNameOfStruct");
    EXPECT("custom-type", eightrefl::name_of<TestCustomNameOfStruct>() == "Test_CustomNameOf_Struct");

    #ifdef EIGHTREFL_MEMBER_ENABLE
    EXPECT("data-member-type", eightrefl::name_of<int TestNameOfStruct::*>() == "int TestNameOfStruct::*");
    EXPECT("data-member-mixed-type0", eightrefl::name_of<int(TestNameOfStruct::*)[2]>() == "std::type_identity_t<int[2]> TestNameOfStruct::*");
    EXPECT("data-member-mixed-type1", eightrefl::name_of<int(*(TestNameOfStruct::*))(char)>() == "std::type_identity_t<int(char)>* TestNameOfStruct::*");
    EXPECT("member-function-type", eightrefl::name_of<char const(TestCustomNameOfStruct::*)(void*)>() == "std::type_identity_t<char const(void*)> Test_CustomNameOf_Struct::*");
    EXPECT("member-function-mixed-type0", eightrefl::name_of<bool*(& (TestCustomNameOfStruct::* const&)(float const*))[4]>() == "std::type_identity_t<std::type_identity_t<bool*[4]>&(float const*)> Test_CustomNameOf_Struct::* const&");
    EXPECT("member-function-mixed-type1", eightrefl::name_of<char(*(TestNameOfStruct::*)() const&)[3]>() == "std::type_identity_t<std::type_identity_t<char[3]>*() const&> TestNameOfStruct::*");
    #endif // EIGHTREFL_MEMBER_ENABLE
}

// Patterns:
// array<T, N> ~ T[N]
// array<T, N>& ~ T(&)[N]
// array<T, N> const& ~ T( const&)[N]
// array<T, N>* ~ T(*)[N]
// array<T, N> const* ~ T( const*)[N]
// array<T, N>* const ~ T(* const)[N]
// array<T, N> const* const ~ T( const* const)[N]

// function<R(Args...)>& ~ R(&)(Args...)
// function<R(Args...)> const& ~ R( const&)(Args...)
// function<R(Args...) ~ R(Args...)
// function<R(Args...)>* ~ R(*)(Args...)
// function<R(Args...)> const* ~ R( const*)(Args...)
// function<R(Args...)>* const ~ R(* const)(Args...)
// function<R(Args...)> const* const ~ R( const* const)(Args...)

// Pointers/References as T/R:
// if T is type pointer/reference of function or array,
// we should wrapp Pattern to '(' and ')' braces, examples:
// array<array<T, InnerN>*, N>* ~ T(*(*)[N])[InnerN]
// array<function<R(Args...)>*, N>* ~ R(*(*)[N])(Args...)

// if R is type pointer/reference of function or array,
// we should wrapp Pattern to '(' and ')' braces, examples:
// function<function<R(InnerArgs...)>*(Args...)>* ~ InnerR(*(*)(Args...))(InnerArgs...)
// function<array<T, N>*(Args...)>* ~ T(*(*)(Args...))[N]
