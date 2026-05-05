#include <EightreflTestingBase.hpp>
#include <Eightrefl/Utility.hpp>

TEST(TestLibrary, TestBackward)
{
    {
        int glvalue = 8;

        std::any as_any = eightrefl::backward(glvalue);
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("glvalue", as_value == &glvalue);
    }
    {
        int glvalue = 8;

        std::any as_any = eightrefl::backward(std::move(glvalue));

        EXPECT("xvalue", std::any_cast<int>(as_any) == glvalue);
    }
    {
        std::any as_any = eightrefl::backward(8);

        EXPECT("prvalue", std::any_cast<int>(as_any) == 8);
    }

    {
        int glvalue = 8;
        int* glvalue_pointer = &glvalue;

        std::any as_any = eightrefl::backward(glvalue_pointer);
        int** as_value = std::any_cast<int**>(as_any);

        EXPECT("glvalue-pointer", as_value == &glvalue_pointer);
    }
    {
        int glvalue = 8;
        int* glvalue_pointer = &glvalue;

        std::any as_any = eightrefl::backward(std::move(glvalue_pointer));
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("xvalue-pointer", as_value == &glvalue);
    }
    {
        int glvalue = 8;

        std::any as_any = eightrefl::backward(&glvalue);
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("prvalue-pointer", as_value == &glvalue);
    }

    {
        int const const_glvalue = 8;
        int const* const_glvalue_pointer = &const_glvalue;

        std::any as_any = eightrefl::backward(const_glvalue_pointer);
        int const** as_value = std::any_cast<int const**>(as_any);

        EXPECT("const-glvalue-pointer", as_value == &const_glvalue_pointer);
    }
    {
        int const const_glvalue = 8;
        int const* const_glvalue_pointer = &const_glvalue;

        std::any as_any = eightrefl::backward(std::move(const_glvalue_pointer));
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("const-xvalue-pointer", as_value == &const_glvalue);
    }
    {
        int const const_glvalue = 8;

        std::any as_any = eightrefl::backward(static_cast<int const*>(&const_glvalue));
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("const-prvalue-pointer", as_value == &const_glvalue);
    }

    {
        int glvalue = 8;
        int& glvalue_reference = glvalue;

        std::any as_any = eightrefl::backward(glvalue_reference);
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("glvalue-reference", as_value == &glvalue);
    }
    {
        int const const_glvalue = 8;
        int const& const_glvalue_reference = const_glvalue;

        std::any as_any = eightrefl::backward(const_glvalue_reference);
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("const-glvalue-reference", as_value == &const_glvalue);
    }

    {
        int glvalue = 8;
        int* glvalue_pointer = &glvalue;
        int*& glvalue_pointer_reference = glvalue_pointer;

        std::any as_any = eightrefl::backward(glvalue_pointer_reference);
        int** as_value = std::any_cast<int**>(as_any);

        EXPECT("glvalue-pointer-reference", as_value == &glvalue_pointer);
    }
    {
        int const const_glvalue = 8;
        int const* const_glvalue_pointer = &const_glvalue;
        int const*& const_glvalue_pointer_reference = const_glvalue_pointer;

        std::any as_any = eightrefl::backward(const_glvalue_pointer_reference);
        int const** as_value = std::any_cast<int const**>(as_any);

        EXPECT("const-glvalue-pointer-reference", as_value == &const_glvalue_pointer);
    }

    {
        int glvalue[4] = {8, 8, 8, 8};
        int (*glvalue_pointer)[4] = &glvalue;

        std::any as_any = eightrefl::backward(glvalue_pointer);
        int (**as_value)[4] = std::any_cast<int(**)[4]>(as_any);

        EXPECT("glvalue-array-glvalue-pointer", as_value == &glvalue_pointer);
    }
    {
        int glvalue[4] = {8, 8, 8, 8};
        int (*glvalue_pointer)[4] = &glvalue;

        std::any as_any = eightrefl::backward(std::move(glvalue_pointer));
        int (*as_value)[4] = std::any_cast<int(*)[4]>(as_any);

        EXPECT("glvalue-array-xvalue-pointer", as_value == &glvalue);
    }
    {
        int glvalue[4] = {8, 8, 8, 8};

        std::any as_any = eightrefl::backward(&glvalue);
        int (*as_value)[4] = std::any_cast<int(*)[4]>(as_any);

        EXPECT("glvalue-array-prvalue-pointer", as_value == &glvalue);
    }

    {
        int glvalue[4] = {8, 8, 8, 8};
        int (&glvalue_reference)[4] = glvalue;

        std::any as_any = eightrefl::backward(glvalue_reference);
        int (*as_value)[4] = std::any_cast<int(*)[4]>(as_any);

        EXPECT("glvalue-array-reference", as_value == &glvalue);
    }
    {
        int const glvalue[4] = {8, 8, 8, 8};
        int const (&glvalue_reference)[4] = glvalue;

        std::any as_any = eightrefl::backward(glvalue_reference);
        int (*as_value)[4] = std::any_cast<int(*)[4]>(as_any);

        EXPECT("const-glvalue-array-reference", as_value == &glvalue);
    }
}

TEST(TestLibrary, TestForward)
{
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int*>(&glvalue);
        int& as_value = eightrefl::forward<int&>(as_any);

        EXPECT("glvalue", &as_value == &glvalue);
    }
    {
        int glvalue = 8;

        // will not work, since reflectable reference storing as mutable
        // std::any as_any = std::make_any<int const*>(&glvalue);
        std::any as_any = std::make_any<int*>(&glvalue);
        int const& as_value = eightrefl::forward<int const&>(as_any);
    
        EXPECT("const-glvalue", &as_value == &glvalue);
    }
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int*>(&glvalue);
        int* as_value = eightrefl::forward<int*>(as_any);

        EXPECT("glvalue-pointer", as_value == &glvalue);
    }
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int*>(&glvalue);
        int const* as_value = eightrefl::forward<int const*>(as_any);

        EXPECT("const-glvalue-pointer", as_value == &glvalue);
    }
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int>(glvalue);
        int as_value = eightrefl::forward<int>(as_any);

        EXPECT("xlvalue", as_value == glvalue);
    }
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int>(glvalue);
        const int as_value = eightrefl::forward<int const>(as_any);

        EXPECT("const-xlvalue", as_value == glvalue);
    }

    // same as xvalue
    {
        std::any as_any = std::make_any<int>(8);
        int as_value = eightrefl::forward<int>(as_any);

        EXPECT("prvalue", as_value == 8);
    }
    {
        std::any as_any = std::make_any<int>(8);
        int as_value = eightrefl::forward<int const>(as_any);

        EXPECT("const-prvalue", as_value == 8);
    }
}

TEST(TestLibrary, TestBackwardForward)
{
    {
        int glvalue = 8;
        std::any as_any = eightrefl::backward(glvalue);
        int& as_value = eightrefl::forward<int&>(as_any);

        EXPECT("glvalue", &as_value == &glvalue);
    }
    {
        int glvalue = 8;
        std::any as_any = eightrefl::backward(std::move(glvalue));
        int as_value = eightrefl::forward<int>(as_any);

        EXPECT("xlvalue", as_value == glvalue);
    }
    {
        std::any as_any = eightrefl::backward(8);
        int as_value = eightrefl::forward<int>(as_any);

        EXPECT("prvalue", as_value == 8);
    }
}


TEST_SPACE()
{

struct TestForwardTypeStruct
{
    int Property = 8;
    static int StaticProperty;
    static int& StaticPropertyRef;

    int& IWithContext() { return Property; } void OWithContext(int& value) { Property = value; }
    int INoContext() { return Property; } void ONoContext(int value) { Property = value; }

    static int& IStaticWithContext() { return StaticProperty; } static void OStaticWithContext(int& value) { StaticProperty = value; }
    static int IStaticNoContext() { return StaticProperty; } static void OStaticNoContext(int value) { StaticProperty = value; }
};

int TestForwardTypeStruct::StaticProperty = 8;
int& TestForwardTypeStruct::StaticPropertyRef = TestForwardTypeStruct::StaticProperty;

int ExternalProperty = 8;
int& ExternalPropertyRef = ExternalProperty;

static int& IExternalWithContext() { return ExternalProperty; } void OExternalWithContext(int& value) { ExternalProperty = value; }
static int IExternalNoContext() { return ExternalProperty; } void OExternalNoContext(int value) { ExternalProperty = value; }

} // TEST_SPACE

TEST(TestLibrary, TestForwardType)
{
    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::Property)>;

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        static_assert(std::is_same_v<property_traits::forward_type, int&>, "data-member-pointer-forward_type");
        #else
        static_assert(std::is_same_v<property_traits::forward_type, int>, "data-member-pointer-forward_type");
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        TestForwardTypeStruct object;
        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        std::any as_any = eightrefl::backward(object.Property);
        #else
        std::any as_any = object.Property;
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int& as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("data-member-pointer", &as_value == &object.Property);
        #else
        int as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("data-member-copy", as_value == object.Property);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::StaticProperty)>;

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        static_assert(std::is_same_v<property_traits::forward_type, int&>, "static-data-member-pointer-forward_type");
        #else
        static_assert(std::is_same_v<property_traits::forward_type, int>, "static-data-member-pointer-forward_type");
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        std::any as_any = eightrefl::backward(TestForwardTypeStruct::StaticProperty);
        #else
        std::any as_any = TestForwardTypeStruct::StaticProperty;
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int& as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("static-data-member-pointer", &as_value == &TestForwardTypeStruct::StaticProperty);
        #else
        int as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("static-data-member-copy", as_value == TestForwardTypeStruct::StaticProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&ExternalPropertyRef)>;

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        static_assert(std::is_same_v<property_traits::forward_type, int&>, "external-data-pointer-reference-forward_type");
        #else
        static_assert(std::is_same_v<property_traits::forward_type, int>, "external-data-pointer-reference-forward_type");
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        std::any as_any = eightrefl::backward(ExternalPropertyRef);
        #else
        std::any as_any = ExternalPropertyRef;
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int& as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("external-data-pointer-reference", &as_value == &ExternalPropertyRef);
        #else
        int as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("external-data-copy", as_value == ExternalPropertyRef);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&ExternalProperty)>;

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        static_assert(std::is_same_v<property_traits::forward_type, int&>, "external-data-pointer-forward_type");
        #else
        static_assert(std::is_same_v<property_traits::forward_type, int>, "external-data-pointer-forward_type");
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        std::any as_any = eightrefl::backward(ExternalProperty);
        #else
        std::any as_any = ExternalProperty;
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int& as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("external-data-pointer", &as_value == &ExternalProperty);
        #else
        int as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("external-data-copy", as_value == ExternalProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::StaticPropertyRef)>;

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        static_assert(std::is_same_v<property_traits::forward_type, int&>, "static-data-pointer-reference-forward_type");
        #else
        static_assert(std::is_same_v<property_traits::forward_type, int>, "static-data-pointer-reference-forward_type");
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        std::any as_any = eightrefl::backward(TestForwardTypeStruct::StaticPropertyRef);
        #else
        std::any as_any = TestForwardTypeStruct::StaticPropertyRef;
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int& as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("static-data-pointer-reference", &as_value == &TestForwardTypeStruct::StaticPropertyRef);
        #else
        int as_value = eightrefl::forward<property_traits::forward_type>(as_any);
        EXPECT("static-data-copy", as_value == TestForwardTypeStruct::StaticPropertyRef);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    }

    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::IWithContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int&>, "imember-with-context-function-pointer-forward_type");

        TestForwardTypeStruct object;
        std::any as_any = eightrefl::backward(object.IWithContext());
        int& as_value = eightrefl::forward<property_traits::forward_type>(as_any);

        EXPECT("imember-with-context-function-pointer", &as_value == &object.IWithContext());
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::OWithContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int&>, "omember-with-context-function-pointer-forward_type");

        TestForwardTypeStruct object;
        int glvalue = 8888;
        std::any as_any = eightrefl::backward(glvalue);
        object.OWithContext(eightrefl::forward<property_traits::forward_type>(as_any));

        EXPECT("omember-with-context-function-pointer", object.IWithContext() == glvalue);
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::IStaticWithContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int&>, "istatic-member-with-context-function-pointer-forward_type");

        std::any as_any = eightrefl::backward(TestForwardTypeStruct::IStaticWithContext());
        int& as_value = eightrefl::forward<property_traits::forward_type>(as_any);

        EXPECT("istatic-member-with-context-function-pointer", &as_value == &TestForwardTypeStruct::IStaticWithContext());
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::OStaticWithContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int&>, "ostatic-member-with-context-function-pointer-forward_type");

        int glvalue = 8888;
        std::any as_any = eightrefl::backward(glvalue);
        TestForwardTypeStruct::OStaticWithContext(eightrefl::forward<property_traits::forward_type>(as_any));

        EXPECT("ostatic-member-with-context-function-pointer", TestForwardTypeStruct::IStaticWithContext() == glvalue);
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&IExternalWithContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int&>, "iexternal-with-context-function-pointer-forward_type");

        std::any as_any = eightrefl::backward(IExternalWithContext());
        int& as_value = eightrefl::forward<property_traits::forward_type>(as_any);

        EXPECT("iexternal-with-context-function-pointer", &as_value == &IExternalWithContext());
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&OExternalWithContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int&>, "oexternal-with-context-function-pointer-forward_type");

        int glvalue = 8888;
        std::any as_any = eightrefl::backward(glvalue);
        OExternalWithContext(eightrefl::forward<property_traits::forward_type>(as_any));

        EXPECT("oexternal-with-context-function-pointer", IExternalWithContext() == glvalue);
    }

    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::INoContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int>, "imember-no-context-function-pointer-forward_type");

        TestForwardTypeStruct object;
        std::any as_any = eightrefl::backward(object.INoContext());
        int as_value = eightrefl::forward<property_traits::forward_type>(as_any);

        EXPECT("imember-no-context-function-pointer", as_value == object.INoContext());
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::ONoContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int>, "omember-no-context-function-pointer-forward_type");

        TestForwardTypeStruct object;
        std::any as_any = eightrefl::backward(8888);
        object.ONoContext(eightrefl::forward<property_traits::forward_type>(as_any));

        EXPECT("omember-no-context-function-pointer", object.INoContext() == 8888);
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::IStaticNoContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int>, "istatic-member-no-context-function-pointer-forward_type");

        std::any as_any = eightrefl::backward(TestForwardTypeStruct::IStaticNoContext());
        int as_value = eightrefl::forward<property_traits::forward_type>(as_any);

        EXPECT("istatic-member-no-context-function-pointer", as_value == TestForwardTypeStruct::IStaticNoContext());
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&TestForwardTypeStruct::OStaticNoContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int>, "ostatic-member-no-context-function-pointer-forward_type");

        std::any as_any = eightrefl::backward(8888);
        TestForwardTypeStruct::OStaticNoContext(eightrefl::forward<property_traits::forward_type>(as_any));

        EXPECT("ostatic-member-no-context-function-pointer", TestForwardTypeStruct::IStaticNoContext() == 8888);
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&IExternalNoContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int>, "iexternal-no-context-function-pointer-forward_type");

        std::any as_any = eightrefl::backward(IExternalNoContext());
        int as_value = eightrefl::forward<property_traits::forward_type>(as_any);

        EXPECT("iexternal-no-context-function-pointer", as_value == IExternalNoContext());
    }
    {
        using property_traits = xxeightrefl_property_traits<decltype(&OExternalNoContext)>;

        static_assert(std::is_same_v<property_traits::forward_type, int>, "oexternal-no-context-function-pointer-forward_type");

        std::any as_any = eightrefl::backward(8888);
        OExternalNoContext(eightrefl::forward<property_traits::forward_type>(as_any));

        EXPECT("oexternal-no-context-function-pointer", IExternalNoContext() == 8888);
    }
}
