// TODO: provide tests for is_copy_assignable == false
#include <EightreflTestingBase.hpp>

TEST_SPACE()
{

struct TestPropertyReadonlyStruct
{
    TestPropertyReadonlyStruct& operator=(TestPropertyReadonlyStruct const&) = delete;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestPropertyReadonlyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestPropertyReadonlyStruct)
REFLECTABLE_INIT()


TEST_SPACE()
{

struct TestFieldPropertyStruct
{
    int Property = 0;
    int const Readonly = 0;
    TestPropertyReadonlyStruct ReadonlyStruct;
    int& Reference;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFieldPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFieldPropertyStruct)
    PROPERTY(Property)
    PROPERTY(Readonly)
    PROPERTY(ReadonlyStruct)
//  PROPERTY(Reference) // unsupported!
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestFieldProperty)
{
    auto type = eightrefl::global()->find("TestFieldPropertyStruct");

    ASSERT("type", type != nullptr);

    {
        auto property = type->property.find("Property");

        ASSERT("property", property != nullptr);
        EXPECT("property-get", property->get != nullptr);
        EXPECT("property-set", property->set != nullptr);
        EXPECT("property-context", property->context != nullptr);
    }
    {
        auto readonly = type->property.find("Readonly");

        ASSERT("property-readonly", readonly != nullptr);
        EXPECT("property-readonly-get", readonly->get != nullptr);
        EXPECT("property-readonly-set", readonly->set == nullptr);
        EXPECT("property-readonly-context", readonly->context != nullptr);
    }
    {
        auto readonly_struct = type->property.find("ReadonlyStruct");

        ASSERT("property-readonly_struct", readonly_struct != nullptr);
        EXPECT("property-readonly_struct-get", readonly_struct->get != nullptr);
        EXPECT("property-readonly_struct-set", readonly_struct->set == nullptr);
        EXPECT("property-readonly_struct-context", readonly_struct->context != nullptr);
    }
}


TEST_SPACE()
{

struct TestStaticFieldPropertyStruct
{
    static int Property;
    static int const Readonly;
    static TestPropertyReadonlyStruct ReadonlyStruct;

    template <typename T, typename... Args>
    static T Template;
};

int TestStaticFieldPropertyStruct::Property = 0;
int const TestStaticFieldPropertyStruct::Readonly = 0;
TestPropertyReadonlyStruct TestStaticFieldPropertyStruct::ReadonlyStruct;

template <typename T, typename... Args>
T TestStaticFieldPropertyStruct::Template = T();

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestStaticFieldPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestStaticFieldPropertyStruct)
    PROPERTY(Property)
    PROPERTY(Readonly)
    PROPERTY(ReadonlyStruct)
    PROPERTY(Template<int>)
    PROPERTY((Template<int, bool>))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestStaticFieldProperty)
{
    auto type = eightrefl::global()->find("TestStaticFieldPropertyStruct");

    ASSERT("type", type != nullptr);

    {
        auto property = type->property.find("Property");

        ASSERT("property", property != nullptr);
        EXPECT("property-get", property->get != nullptr);
        EXPECT("property-set", property->set != nullptr);
        EXPECT("property-context", property->context != nullptr);
    }
    {
        auto readonly = type->property.find("Readonly");

        ASSERT("property-readonly", readonly != nullptr);
        EXPECT("property-readonly-get", readonly->get != nullptr);
        EXPECT("property-readonly-set", readonly->set == nullptr);
        EXPECT("property-readonly-context", readonly->context != nullptr);
    }
    {
        auto readonly_struct = type->property.find("ReadonlyStruct");

        ASSERT("property-readonly_struct", readonly_struct != nullptr);
        EXPECT("property-readonly_struct-get", readonly_struct->get != nullptr);
        EXPECT("property-readonly_struct-set", readonly_struct->set == nullptr);
        EXPECT("property-readonly_struct-context", readonly_struct->context != nullptr);
    }
    {
        auto template_with_arg = type->property.find("Template<int>");

        ASSERT("property-template_with_arg", template_with_arg != nullptr);
        EXPECT("property-template_with_arg-get", template_with_arg->get != nullptr);
        EXPECT("property-template_with_arg-set", template_with_arg->set != nullptr);
        EXPECT("property-template_with_arg-context", template_with_arg->context != nullptr);
    }
    {
        auto template_with_args = type->property.find("Template<int, bool>");

        ASSERT("property-template_with_args", template_with_args != nullptr);
        EXPECT("property-template_with_args-get", template_with_args->get != nullptr);
        EXPECT("property-template_with_args-set", template_with_args->set != nullptr);
        EXPECT("property-template_with_args-context", template_with_args->context != nullptr);
    }
}


TEST_SPACE()
{

struct TestFreeFieldPropertyStruct {};

int Property = 0;
int const Readonly = 0;
TestPropertyReadonlyStruct ReadonlyStruct;
int& Reference = Property;

template <typename T, typename... Args>
T Template = T();

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFreeFieldPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFreeFieldPropertyStruct)
    FREE_PROPERTY(Property)
    FREE_PROPERTY(Readonly)
    FREE_PROPERTY(ReadonlyStruct)
    FREE_PROPERTY(Reference)
    FREE_PROPERTY(Template<int>)
    FREE_PROPERTY((Template<int, bool>))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestFreeFieldProperty)
{
    auto type = eightrefl::global()->find("TestFreeFieldPropertyStruct");

    ASSERT("type", type != nullptr);

    {
        auto property = type->property.find("Property");

        ASSERT("property", property != nullptr);
        EXPECT("property-get", property->get != nullptr);
        EXPECT("property-set", property->set != nullptr);
        EXPECT("property-context", property->context != nullptr);
    }
    {
        auto readonly = type->property.find("Readonly");

        ASSERT("property-readonly", readonly != nullptr);
        EXPECT("property-readonly-get", readonly->get != nullptr);
        EXPECT("property-readonly-set", readonly->set == nullptr);
        EXPECT("property-readonly-context", readonly->context != nullptr);
    }
    {
        auto readonly_struct = type->property.find("ReadonlyStruct");

        ASSERT("property-readonly_struct", readonly_struct != nullptr);
        EXPECT("property-readonly_struct-get", readonly_struct->get != nullptr);
        EXPECT("property-readonly_struct-set", readonly_struct->set == nullptr);
        EXPECT("property-readonly_struct-context", readonly_struct->context != nullptr);
    }
    {
        auto reference = type->property.find("Reference");

        ASSERT("property-reference", reference != nullptr);
        EXPECT("property-reference-get", reference->get != nullptr);
        EXPECT("property-reference-set", reference->set != nullptr);
        EXPECT("property-reference-context", reference->context != nullptr);
    }
    {
        auto template_with_arg = type->property.find("Template<int>");

        ASSERT("property-template_with_arg", template_with_arg != nullptr);
        EXPECT("property-template_with_arg-get", template_with_arg->get != nullptr);
        EXPECT("property-template_with_arg-set", template_with_arg->set != nullptr);
        EXPECT("property-template_with_arg-context", template_with_arg->context != nullptr);
    }
    {
        auto template_with_args = type->property.find("Template<int, bool>");

        ASSERT("property-template_with_args", template_with_args != nullptr);
        EXPECT("property-template_with_args-get", template_with_args->get != nullptr);
        EXPECT("property-template_with_args-set", template_with_args->set != nullptr);
        EXPECT("property-template_with_args-context", template_with_args->context != nullptr);
    }
}


TEST_SPACE()
{

struct TestFunctionPropertyStruct : TestFieldPropertyStruct
{
    int& WithContext() { return Property; } void WithContext(int& value) { Property = value; }
    int const& WithConstContext() { return Property; } void WithConstContext(int const& value) { Property = value; }
    int const& ConstWithConstContext() const { return Property; } void ConstWithConstContext(int const& value) { Property = value; }
    int NoContext() { return 0; } void NoContext(int) {}
    int ConstNoContext() const { return 0; } void ConstNoContext(int) {}

    int& ReadonlyWithContext() { return Property; }
    int const& ReadonlyWithConstContext() { return Property; }
    int const& ReadonlyConstWithConstContext() const { return Property; }
    int ReadonlyNoContext() { return 0; }
    int ReadonlyConstNoContext() const { return 0; }

    // we can also use function template as property
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFunctionPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFunctionPropertyStruct)
    PROPERTY(WithContext)
    PROPERTY(WithConstContext)
    PROPERTY(ConstWithConstContext)
    PROPERTY(NoContext)
    PROPERTY(ConstNoContext)

    PROPERTY(ReadonlyWithContext)
    PROPERTY(ReadonlyWithConstContext)
    PROPERTY(ReadonlyConstWithConstContext)
    PROPERTY(ReadonlyNoContext)
    PROPERTY(ReadonlyConstNoContext)
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestFunctionProperty)
{
    auto type = eightrefl::global()->find("TestFunctionPropertyStruct");

    ASSERT("type", type != nullptr);

    {
        auto with_context = type->property.find("WithContext");

        ASSERT("property-with_context", with_context != nullptr);
        EXPECT("property-with_context-get", with_context->get != nullptr);
        EXPECT("property-with_context-set", with_context->set != nullptr);
        EXPECT("property-with_context-context", with_context->context != nullptr);
    }
    {
        auto with_const_context = type->property.find("WithConstContext");

        ASSERT("property-with_const_context", with_const_context != nullptr);
        EXPECT("property-with_const_context-get", with_const_context->get != nullptr);
        EXPECT("property-with_const_context-set", with_const_context->set != nullptr);
        EXPECT("property-with_const_context-context", with_const_context->context != nullptr);
    }
    {
        auto const_with_const_context = type->property.find("ConstWithConstContext");

        ASSERT("property-const_with_const_context", const_with_const_context != nullptr);
        EXPECT("property-const_with_const_context-get", const_with_const_context->get != nullptr);
        EXPECT("property-const_with_const_context-set", const_with_const_context->set != nullptr);
        EXPECT("property-const_with_const_context-context", const_with_const_context->context != nullptr);
    }
    {
        auto no_context = type->property.find("NoContext");

        ASSERT("property-no_context", no_context != nullptr);
        EXPECT("property-no_context-get", no_context->get != nullptr);
        EXPECT("property-no_context-set", no_context->set != nullptr);
        EXPECT("property-no_context-context", no_context->context == nullptr);
    }
    {
        auto const_no_context = type->property.find("ConstNoContext");

        ASSERT("property-const_no_context", const_no_context != nullptr);
        EXPECT("property-const_no_context-get", const_no_context->get != nullptr);
        EXPECT("property-const_no_context-set", const_no_context->set != nullptr);
        EXPECT("property-const_no_context-context", const_no_context->context == nullptr);
    }

    {
        auto readonly_with_context = type->property.find("ReadonlyWithContext");

        ASSERT("property-readonly_with_context", readonly_with_context != nullptr);
        EXPECT("property-readonly_with_context-get", readonly_with_context->get != nullptr);
        EXPECT("property-readonly_with_context-set", readonly_with_context->set == nullptr);
        EXPECT("property-readonly_with_context-context", readonly_with_context->context != nullptr);
    }
    {
        auto readonly_with_const_context = type->property.find("ReadonlyWithConstContext");

        ASSERT("property-readonly_with_const_context", readonly_with_const_context != nullptr);
        EXPECT("property-readonly_with_const_context-get", readonly_with_const_context->get != nullptr);
        EXPECT("property-readonly_with_const_context-set", readonly_with_const_context->set == nullptr);
        EXPECT("property-readonly_with_const_context-context", readonly_with_const_context->context != nullptr);
    }
    {
        auto readonly_const_with_const_context = type->property.find("ReadonlyConstWithConstContext");

        ASSERT("property-readonly_const_with_const_context", readonly_const_with_const_context != nullptr);
        EXPECT("property-readonly_const_with_const_context-get", readonly_const_with_const_context->get != nullptr);
        EXPECT("property-readonly_const_with_const_context-set", readonly_const_with_const_context->set == nullptr);
        EXPECT("property-readonly_const_with_const_context-context", readonly_const_with_const_context->context != nullptr);
    }
    {
        auto readonly_no_context = type->property.find("ReadonlyNoContext");

        ASSERT("property-readonly_no_context", readonly_no_context != nullptr);
        EXPECT("property-readonly_no_context-get", readonly_no_context->get != nullptr);
        EXPECT("property-readonly_no_context-set", readonly_no_context->set == nullptr);
        EXPECT("property-readonly_no_context-context", readonly_no_context->context == nullptr);
    }
    {
        auto readonly_const_no_context = type->property.find("ReadonlyConstNoContext");

        ASSERT("property-readonly_const_no_context", readonly_const_no_context != nullptr);
        EXPECT("property-readonly_const_no_context-get", readonly_const_no_context->get != nullptr);
        EXPECT("property-readonly_const_no_context-set", readonly_const_no_context->set == nullptr);
        EXPECT("property-readonly_const_no_context-context", readonly_const_no_context->context == nullptr);
    }
}


TEST_SPACE()
{

struct TestStaticFunctionPropertyStruct : TestStaticFieldPropertyStruct
{
    static int& WithContext() { return Property; } static void WithContext(int& value) { Property = value; }
    static int const& WithConstContext() { return Property; } static void WithConstContext(int const& value) { Property = value; }
    static int NoContext() { return 0; } static void NoContext(int) {}

    static int& ReadonlyWithContext() { return Property; }
    static int const& ReadonlyWithConstContext() { return Property; }
    static int ReadonlyNoContext() { return 0; }
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestStaticFunctionPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestStaticFunctionPropertyStruct)
    PROPERTY(WithContext)
    PROPERTY(WithConstContext)
    PROPERTY(NoContext)

    PROPERTY(ReadonlyWithContext)
    PROPERTY(ReadonlyWithConstContext)
    PROPERTY(ReadonlyNoContext)
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestStaticFunctionProperty)
{
    auto type = eightrefl::global()->find("TestStaticFunctionPropertyStruct");

    ASSERT("type", type != nullptr);

    {
        auto with_context = type->property.find("WithContext");

        ASSERT("property-with_context", with_context != nullptr);
        EXPECT("property-with_context-get", with_context->get != nullptr);
        EXPECT("property-with_context-set", with_context->set != nullptr);
        EXPECT("property-with_context-context", with_context->context != nullptr);
    }
    {
        auto with_const_context = type->property.find("WithConstContext");

        ASSERT("property-with_const_context", with_const_context != nullptr);
        EXPECT("property-with_const_context-get", with_const_context->get != nullptr);
        EXPECT("property-with_const_context-set", with_const_context->set != nullptr);
        EXPECT("property-with_const_context-context", with_const_context->context != nullptr);
    }
    {
        auto no_context = type->property.find("NoContext");

        ASSERT("property-no_context", no_context != nullptr);
        EXPECT("property-no_context-get", no_context->get != nullptr);
        EXPECT("property-no_context-set", no_context->set != nullptr);
        EXPECT("property-no_context-context", no_context->context == nullptr);
    }

    {
        auto readonly_with_context = type->property.find("ReadonlyWithContext");

        ASSERT("property-readonly_with_context", readonly_with_context != nullptr);
        EXPECT("property-readonly_with_context-get", readonly_with_context->get != nullptr);
        EXPECT("property-readonly_with_context-set", readonly_with_context->set == nullptr);
        EXPECT("property-readonly_with_context-context", readonly_with_context->context != nullptr);
    }
    {
        auto readonly_with_const_context = type->property.find("ReadonlyWithConstContext");

        ASSERT("property-readonly_with_const_context", readonly_with_const_context != nullptr);
        EXPECT("property-readonly_with_const_context-get", readonly_with_const_context->get != nullptr);
        EXPECT("property-readonly_with_const_context-set", readonly_with_const_context->set == nullptr);
        EXPECT("property-readonly_with_const_context-context", readonly_with_const_context->context != nullptr);
    }
    {
        auto readonly_no_context = type->property.find("ReadonlyNoContext");

        ASSERT("property-readonly_no_context", readonly_no_context != nullptr);
        EXPECT("property-readonly_no_context-get", readonly_no_context->get != nullptr);
        EXPECT("property-readonly_no_context-set", readonly_no_context->set == nullptr);
        EXPECT("property-readonly_no_context-context", readonly_no_context->context == nullptr);
    }
}


TEST_SPACE()
{

struct TestFreeFunctionPropertyStruct {};

int& WithContext() { return Property; } void WithContext(int& value) { Property = value; }
int const& WithConstContext() { return Property; } void WithConstContext(int const& value) { Property = value; }
int NoContext() { return 0; } void NoContext(int) {}

int& ReadonlyWithContext() { return Property; }
int const& ReadonlyWithConstContext() { return Property; }
int ReadonlyNoContext() { return 0; }

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFreeFunctionPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFreeFunctionPropertyStruct)
    FREE_PROPERTY(WithContext)
    FREE_PROPERTY(WithConstContext)
    FREE_PROPERTY(NoContext)

    FREE_PROPERTY(ReadonlyWithContext)
    FREE_PROPERTY(ReadonlyWithConstContext)
    FREE_PROPERTY(ReadonlyNoContext)
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestFreeFunctionProperty)
{
    auto type = eightrefl::global()->find("TestFreeFunctionPropertyStruct");

    ASSERT("type", type != nullptr);

    {
        auto with_context = type->property.find("WithContext");

        ASSERT("property-with_context", with_context != nullptr);
        EXPECT("property-with_context-get", with_context->get != nullptr);
        EXPECT("property-with_context-set", with_context->set != nullptr);
        EXPECT("property-with_context-context", with_context->context != nullptr);
    }
    {
        auto with_const_context = type->property.find("WithConstContext");

        ASSERT("property-with_const_context", with_const_context != nullptr);
        EXPECT("property-with_const_context-get", with_const_context->get != nullptr);
        EXPECT("property-with_const_context-set", with_const_context->set != nullptr);
        EXPECT("property-with_const_context-context", with_const_context->context != nullptr);
    }
    {
        auto no_context = type->property.find("NoContext");

        ASSERT("property-no_context", no_context != nullptr);
        EXPECT("property-no_context-get", no_context->get != nullptr);
        EXPECT("property-no_context-set", no_context->set != nullptr);
        EXPECT("property-no_context-context", no_context->context == nullptr);
    }

    {
        auto readonly_with_context = type->property.find("ReadonlyWithContext");

        ASSERT("property-readonly_with_context", readonly_with_context != nullptr);
        EXPECT("property-readonly_with_context-get", readonly_with_context->get != nullptr);
        EXPECT("property-readonly_with_context-set", readonly_with_context->set == nullptr);
        EXPECT("property-readonly_with_context-context", readonly_with_context->context != nullptr);
    }
    {
        auto readonly_with_const_context = type->property.find("ReadonlyWithConstContext");

        ASSERT("property-readonly_with_const_context", readonly_with_const_context != nullptr);
        EXPECT("property-readonly_with_const_context-get", readonly_with_const_context->get != nullptr);
        EXPECT("property-readonly_with_const_context-set", readonly_with_const_context->set == nullptr);
        EXPECT("property-readonly_with_const_context-context", readonly_with_const_context->context != nullptr);
    }
    {
        auto readonly_no_context = type->property.find("ReadonlyNoContext");

        ASSERT("property-readonly_no_context", readonly_no_context != nullptr);
        EXPECT("property-readonly_no_context-get", readonly_no_context->get != nullptr);
        EXPECT("property-readonly_no_context-set", readonly_no_context->set == nullptr);
        EXPECT("property-readonly_no_context-context", readonly_no_context->context == nullptr);
    }
}


TEST_SPACE()
{

struct TestTypedFieldProperty
{
    int Property = 0;

    static int StaticProperty;

    template <typename T, typename... Args>
    static T Template;
};

int TestTypedFieldProperty::StaticProperty = 0;

template <typename T, typename... Args>
T TestTypedFieldProperty::Template = T();

int FreeProperty = 0;

template <typename T, typename... Args>
T FreeTemplate = T();

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestTypedFieldProperty)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestTypedFieldProperty)
    PROPERTY(Property, int)
    PROPERTY(StaticProperty, int)
    PROPERTY(Template<int>, int)
    PROPERTY((Template<int, float>), int)

    FREE_PROPERTY(FreeProperty, int)
    FREE_PROPERTY(FreeTemplate<int>, int)
    FREE_PROPERTY((FreeTemplate<int, float>), int)
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestTypedFieldProperty)
{
    auto type = eightrefl::global()->find("TestTypedFieldProperty");

    ASSERT("type", type != nullptr);

    {
        auto property = type->property.find("Property");

        ASSERT("property", property != nullptr);
        EXPECT("property-get", property->get != nullptr);
        EXPECT("property-set", property->set != nullptr);
        EXPECT("property-context", property->context != nullptr);
    }
    {
        auto static_property = type->property.find("StaticProperty");

        ASSERT("static_property", static_property != nullptr);
        EXPECT("static_property-get", static_property->get != nullptr);
        EXPECT("static_property-set", static_property->set != nullptr);
        EXPECT("static_property-context", static_property->context != nullptr);
    }
    {
        auto template_with_arg = type->property.find("Template<int>");

        ASSERT("template_with_arg", template_with_arg != nullptr);
        EXPECT("template_with_arg-get", template_with_arg->get != nullptr);
        EXPECT("template_with_arg-set", template_with_arg->set != nullptr);
        EXPECT("template_with_arg-context", template_with_arg->context != nullptr);
    }
    {
        auto template_with_args = type->property.find("Template<int, float>");

        ASSERT("template_with_args", template_with_args != nullptr);
        EXPECT("template_with_args-get", template_with_args->get != nullptr);
        EXPECT("template_with_args-set", template_with_args->set != nullptr);
        EXPECT("template_with_args-context", template_with_args->context != nullptr);
    }

    {
        auto free_property = type->property.find("FreeProperty");

        ASSERT("free_property", free_property != nullptr);
        EXPECT("free_property-get", free_property->get != nullptr);
        EXPECT("free_property-set", free_property->set != nullptr);
        EXPECT("free_property-context", free_property->context != nullptr);
    }
    {
        auto free_template_with_arg = type->property.find("FreeTemplate<int>");

        ASSERT("free_template_with_arg", free_template_with_arg != nullptr);
        EXPECT("free_template_with_arg-get", free_template_with_arg->get != nullptr);
        EXPECT("free_template_with_arg-set", free_template_with_arg->set != nullptr);
        EXPECT("free_template_with_arg-context", free_template_with_arg->context != nullptr);
    }
    {
        auto free_template_with_args = type->property.find("FreeTemplate<int, float>");

        ASSERT("free_template_with_args", free_template_with_args != nullptr);
        EXPECT("free_template_with_args-get", free_template_with_args->get != nullptr);
        EXPECT("free_template_with_args-set", free_template_with_args->set != nullptr);
        EXPECT("free_template_with_args-context", free_template_with_args->context != nullptr);
    }
}


TEST_SPACE()
{

// we can mix property type with cv-quialifiers: int const&, int&, int const, int
struct TestTypedFunctionProperty : TestTypedFieldProperty
{
    static int Static() { return StaticProperty; } static void Static(int value) { StaticProperty = value; }

    int ICostQualifiedAndONoQuilified() const { return Property; } void ICostQualifiedAndONoQuilified(int value) { Property = value; }
    int ICostQualifiedAndORefQuilified() const { return Property; } void ICostQualifiedAndORefQuilified(int value)& { Property = value; }

    int ICostRefQualifiedAndONoQuilified() const& { return Property; } void ICostRefQualifiedAndONoQuilified(int value) { Property = value; }
    int ICostRefQualifiedAndORefQuilified() const& { return Property; } void ICostRefQualifiedAndORefQuilified(int value)& { Property = value; }

    int INoQualifiedAndONoQualified() { return Property; } void INoQualifiedAndONoQualified(int value) { Property = value; }
    int INoQualifiedAndORefQualified() { return Property; } void INoQualifiedAndORefQualified(int value)& { Property = value; }

    int IRefQualifiedAndONoQualified()& { return Property; } void IRefQualifiedAndONoQualified(int value) { Property = value; }
    int IRefQualifiedAndORefQualified()& { return Property; } void IRefQualifiedAndORefQualified(int value)& { Property = value; }

    // we can also use function template as property
};

int Free() { return 0; } void Free(int) {}

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestTypedFunctionProperty)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestTypedFunctionProperty)
    PROPERTY(Static, int(), void(int))

    PROPERTY(ICostQualifiedAndONoQuilified, int() const, void(int))
    PROPERTY(ICostQualifiedAndORefQuilified, int() const, void(int)&)

    PROPERTY(ICostRefQualifiedAndONoQuilified, int() const&, void(int))
    PROPERTY(ICostRefQualifiedAndORefQuilified, int() const&, void(int)&)

    PROPERTY(INoQualifiedAndONoQualified, int(), void(int))
    PROPERTY(INoQualifiedAndORefQualified, int(), void(int)&)

    PROPERTY(IRefQualifiedAndONoQualified, int()&, void(int))
    PROPERTY(IRefQualifiedAndORefQualified, int()&, void(int)&)

    FREE_PROPERTY(Free, int(), void(int))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestTypedFunctionProperty)
{
    auto type = eightrefl::global()->find("TestTypedFunctionProperty");

    ASSERT("type", type != nullptr);

    {
        auto static_ = type->property.find("Static");

        ASSERT("static", static_ != nullptr);
        EXPECT("static-get", static_->get != nullptr);
        EXPECT("static-set", static_->set != nullptr);
        EXPECT("static-context", static_->context == nullptr);
    }

    {
        auto icost_qualified_and_ono_quilified = type->property.find("ICostQualifiedAndONoQuilified");

        ASSERT("icost_qualified_and_ono_quilified", icost_qualified_and_ono_quilified != nullptr);
        EXPECT("icost_qualified_and_ono_quilified-get", icost_qualified_and_ono_quilified->get != nullptr);
        EXPECT("icost_qualified_and_ono_quilified-set", icost_qualified_and_ono_quilified->set != nullptr);
        EXPECT("icost_qualified_and_ono_quilified-context", icost_qualified_and_ono_quilified->context == nullptr);
    }
    {
        auto icost_qualified_and_oref_quilified = type->property.find("ICostQualifiedAndORefQuilified");

        ASSERT("icost_qualified_and_oref_quilified", icost_qualified_and_oref_quilified != nullptr);
        EXPECT("icost_qualified_and_oref_quilified-get", icost_qualified_and_oref_quilified->get != nullptr);
        EXPECT("icost_qualified_and_oref_quilified-set", icost_qualified_and_oref_quilified->set != nullptr);
        EXPECT("icost_qualified_and_oref_quilified-context", icost_qualified_and_oref_quilified->context == nullptr);
    }

    {
        auto icostref_qualified_and_ono_quilified = type->property.find("ICostRefQualifiedAndONoQuilified");

        ASSERT("icostref_qualified_and_ono_quilified", icostref_qualified_and_ono_quilified != nullptr);
        EXPECT("icostref_qualified_and_ono_quilified-get", icostref_qualified_and_ono_quilified->get != nullptr);
        EXPECT("icostref_qualified_and_ono_quilified-set", icostref_qualified_and_ono_quilified->set != nullptr);
        EXPECT("icostref_qualified_and_ono_quilified-context", icostref_qualified_and_ono_quilified->context == nullptr);
    }
    {
        auto icostref_qualified_and_oref_quilified = type->property.find("ICostRefQualifiedAndORefQuilified");

        ASSERT("icostref_qualified_and_oref_quilified", icostref_qualified_and_oref_quilified != nullptr);
        EXPECT("icostref_qualified_and_oref_quilified-get", icostref_qualified_and_oref_quilified->get != nullptr);
        EXPECT("icostref_qualified_and_oref_quilified-set", icostref_qualified_and_oref_quilified->set != nullptr);
        EXPECT("icostref_qualified_and_oref_quilified-context", icostref_qualified_and_oref_quilified->context == nullptr);
    }

    {
        auto ino_qualified_and_ono_quilified = type->property.find("INoQualifiedAndONoQualified");

        ASSERT("ino_qualified_and_ono_quilified", ino_qualified_and_ono_quilified != nullptr);
        EXPECT("ino_qualified_and_ono_quilified-get", ino_qualified_and_ono_quilified->get != nullptr);
        EXPECT("ino_qualified_and_ono_quilified-set", ino_qualified_and_ono_quilified->set != nullptr);
        EXPECT("ino_qualified_and_ono_quilified-context", ino_qualified_and_ono_quilified->context == nullptr);
    }
    {
        auto ino_qualified_and_oref_quilified = type->property.find("INoQualifiedAndORefQualified");

        ASSERT("ino_qualified_and_oref_quilified", ino_qualified_and_oref_quilified != nullptr);
        EXPECT("ino_qualified_and_oref_quilified-get", ino_qualified_and_oref_quilified->get != nullptr);
        EXPECT("ino_qualified_and_oref_quilified-set", ino_qualified_and_oref_quilified->set != nullptr);
        EXPECT("ino_qualified_and_oref_quilified-context", ino_qualified_and_oref_quilified->context == nullptr);
    }

    {
        auto iref_qualified_and_ono_quilified = type->property.find("IRefQualifiedAndONoQualified");

        ASSERT("iref_qualified_and_ono_quilified", iref_qualified_and_ono_quilified != nullptr);
        EXPECT("iref_qualified_and_ono_quilified-get", iref_qualified_and_ono_quilified->get != nullptr);
        EXPECT("iref_qualified_and_ono_quilified-set", iref_qualified_and_ono_quilified->set != nullptr);
        EXPECT("iref_qualified_and_ono_quilified-context", iref_qualified_and_ono_quilified->context == nullptr);
    }
    {
        auto iref_qualified_and_oref_quilified = type->property.find("IRefQualifiedAndORefQualified");

        ASSERT("iref_qualified_and_oref_quilified", iref_qualified_and_oref_quilified != nullptr);
        EXPECT("iref_qualified_and_oref_quilified-get", iref_qualified_and_oref_quilified->get != nullptr);
        EXPECT("iref_qualified_and_oref_quilified-set", iref_qualified_and_oref_quilified->set != nullptr);
        EXPECT("iref_qualified_and_oref_quilified-context", iref_qualified_and_oref_quilified->context == nullptr);
    }

    {
        auto free_ = type->property.find("Free");

        ASSERT("free", free_ != nullptr);
        EXPECT("free-get", free_->get != nullptr);
        EXPECT("free-set", free_->set != nullptr);
        EXPECT("free-context", free_->context == nullptr);
    }
}