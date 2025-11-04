#include <EightreflTestingBase.hpp>

TEST_SPACE()
{

struct TestReflectableDeclaratonOnlyStruct {};
struct TestReflectableDeclaratonOnlyWithUsingStruct {};

struct TestReflectableStruct
{
    void Foo(TestReflectableDeclaratonOnlyWithUsingStruct) {}
};

struct TestReflectableWithoutDeclarationStruct {};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestReflectableDeclaratonOnlyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(TestReflectableDeclaratonOnlyWithUsingStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(TestReflectableStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestReflectableStruct)
    FUNCTION(Foo) // will implicitly add TestReflectableDeclaratonOnlyWithUsingStruct to registry
REFLECTABLE_INIT()

// will not compile, since rrquires REFLECTABLE_DECLARATION(...), that contains xxeightrefl_traits
//REFLECTABLE(TestReflectableWithoutDeclarationStruct)
//REFLECTABLE_INIT()

TEST(TestLibrary, TestReflectableRegistry)
{
    {
        // will not compile, since requires REFLECTABLE(...)
        //eightrefl::reflectable<TestReflectableDeclaratonOnlyStruct>();
        ASSERT("type0", eightrefl::global()->find("TestReflectableDeclaratonOnlyStruct") == nullptr);
    }
    {
        // will explicitly add type to registry, no requires REFLECTABLE(...), since can add incomplete types
        eightrefl::find_or_add_type<TestReflectableDeclaratonOnlyStruct>();
        ASSERT("type1", eightrefl::global()->find("TestReflectableDeclaratonOnlyStruct") != nullptr);
    }
    {
        ASSERT("type2", eightrefl::global()->find("TestReflectableDeclaratonOnlyWithUsingStruct") != nullptr);
    }
    {
        ASSERT("type3", eightrefl::global()->find("TestReflectableStruct") != nullptr);
    }
}


TEST_SPACE()
{

struct TestDeparenStruct
{
    void Function() {}
    void FunctionWithParentheses(float) {}

    template <typename... Args>
    void Template() {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestDeparenStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestDeparenStruct)
    FUNCTION(Function)
    FUNCTION((FunctionWithParentheses))
    FUNCTION(Template<int>, void())
    FUNCTION((Template<float, bool>), void())
REFLECTABLE_INIT()

TEST(TestLibrary, TestDeparen)
{
    auto type = eightrefl::global()->find("TestDeparenStruct");

    ASSERT("type", type != nullptr);

    EXPECT("function", type->function.find("Function") != nullptr);
    EXPECT("function_with_parentheses", type->function.find("FunctionWithParentheses") != nullptr);
    EXPECT("template", type->function.find("Template<int>") != nullptr);
    EXPECT("template_with_parentheses", type->function.find("Template<float, bool>") != nullptr);
}


TEST_SPACE()
{

struct TestParentTopBaseStruct {};
struct TestParentBaseStruct : TestParentTopBaseStruct {};

struct TestParentInterface
{
    virtual void Foo() = 0;
};

struct TestParentDerivedStruct : TestParentBaseStruct, TestParentInterface
{
    void Foo() override {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestParentTopBaseStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentTopBaseStruct)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestParentBaseStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentBaseStruct)
    PARENT(TestParentTopBaseStruct)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestParentInterface)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentInterface)
    FUNCTION(Foo)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestParentDerivedStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentDerivedStruct)
    PARENT(TestParentBaseStruct)
    PARENT(TestParentInterface)
    FUNCTION(Foo)
REFLECTABLE_INIT()

TEST(TestLibrary, TestParent)
{
    auto type = eightrefl::global()->find("TestParentDerivedStruct");

    ASSERT("type", type != nullptr);

    auto base = type->parent.find("TestParentBaseStruct");

    ASSERT("base", base != nullptr);
    EXPECT("base-type", base->type == eightrefl::global()->find(base->type->name));

    auto base_base = base->type->parent.find("TestParentTopBaseStruct");

    ASSERT("base-base", base_base != nullptr);
    EXPECT("base-base-type", base_base->type == eightrefl::global()->find(base_base->type->name));
    EXPECT("non_directed_base", type->parent.find(base_base->type->name) == nullptr);

    auto interface = type->parent.find("TestParentInterface");

    ASSERT("interface", interface != nullptr);
    EXPECT("interface-type", interface->type == eightrefl::global()->find(interface->type->name));
}


TEST_SPACE()
{

struct TestCustomRegistryStruct {};

eightrefl::registry_t CustomRegistry;

} // TEST_SPACE

// REFLECTABLE_DECLARATION uses REFLECTABLE_NAME(typename)
REFLECTABLE_DECLARATION(TestCustomRegistryStruct)
    REFLECTABLE_REGISTRY(&CustomRegistry)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestCustomRegistryStruct)
REFLECTABLE_INIT()

TEST(TestLibrary, TestCustomRegistry)
{
    auto registry = ::xxeightrefl_traits<TestCustomRegistryStruct>::registry();

    ASSERT("registry", registry == &CustomRegistry);

    auto type = CustomRegistry.find("TestCustomRegistryStruct");

    ASSERT("type", type != nullptr);
}


TEST_SPACE()
{

struct TestTypedPropertyStruct
{
    int& FunctionProperty() { return Property; }
    void FunctionProperty(int& value) { Property = value; }

    int& OtherFunctionProperty() { return Property; }
    int const& OtherFunctionProperty() const { return Property; }
    void OtherFunctionProperty(int& value) { Property = value; }

    template <typename T> T TemplateFunctionProperty() { return T(); }

    int Property = 0;
    static constexpr int ConstProperty = 0;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestTypedPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestTypedPropertyStruct)
    PROPERTY(FunctionProperty, int&())
    PROPERTY(OtherFunctionProperty, int const&() const)
    PROPERTY(TemplateFunctionProperty<char>, char())
    PROPERTY(Property, int)
    PROPERTY(ConstProperty, int const)
REFLECTABLE_INIT()

TEST(TestLibrary, TestTypedProperty)
{
    auto type = eightrefl::global()->find("TestTypedPropertyStruct");

    ASSERT("type", type != nullptr);

    auto function_property = type->property.find("FunctionProperty");

    ASSERT("function_property", function_property != nullptr);
    EXPECT("function_property-get", function_property->get != nullptr);
    EXPECT("function_property-set", function_property->set != nullptr);
    EXPECT("function_property-context", function_property->context != nullptr);

    auto other_function_property = type->property.find("OtherFunctionProperty");

    ASSERT("other_function_property", other_function_property != nullptr);
    EXPECT("other_function_property-get", other_function_property->get != nullptr);
    EXPECT("other_function_property-set", other_function_property->set == nullptr);
    EXPECT("other_function_property-context", other_function_property->context != nullptr);

    auto template_function_property = type->property.find("TemplateFunctionProperty<char>");

    ASSERT("template_function_property", template_function_property != nullptr);
    EXPECT("template_function_property-get", template_function_property->get != nullptr);
    EXPECT("template_function_property-set", template_function_property->set == nullptr);
    EXPECT("template_function_property-context", template_function_property->context == nullptr);

    auto property = type->property.find("Property");

    ASSERT("property", property != nullptr);
    EXPECT("property-get", property->get != nullptr);
    EXPECT("property-set", property->set != nullptr);
    EXPECT("property-context", property->context != nullptr);

    auto const_property = type->property.find("ConstProperty");

    ASSERT("const_property", const_property != nullptr);
    EXPECT("const_property-get", const_property->get != nullptr);
    EXPECT("const_property-set", const_property->set == nullptr);
    EXPECT("const_property-context", const_property->context != nullptr);
}


TEST_SPACE()
{

struct TestNamedPropertyStruct
{
    bool IsActivated() const { return bIsActivated; }

    void Activate(bool yes)
    {
        bIsActivatedBuffer = bIsActivated;
        bIsActivated = yes;
    }

    bool bIsActivated = false;
    bool bIsActivatedBuffer = false;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestNamedPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

// without macro using we can put function get and variable set to one or inverse,
// just if u want max flexibility, please, use no macro version
REFLECTABLE(TestNamedPropertyStruct)
    NAMED_PROPERTY("IsActivated", IsActivated, Activate)
    NAMED_PROPERTY("Flag", bIsActivated, bIsActivatedBuffer)
REFLECTABLE_INIT()

TEST(TestLibrary, TestNamedProperty)
{
    auto type = eightrefl::global()->find("TestNamedPropertyStruct");

    ASSERT("type", type != nullptr);

    auto function_property = type->property.find("IsActivated");

    ASSERT("function_property", function_property != nullptr);
    ASSERT("function_property-get", function_property->get != nullptr);
    ASSERT("function_property-set", function_property->set != nullptr);
    EXPECT("function_property-context", function_property->context == nullptr);

    auto [function_property_get_ptr, function_property_set_ptr] = function_property->pointer;

    EXPECT("function_property-get-pointer",
        std::any_cast<bool(TestNamedPropertyStruct::*)() const>(function_property_get_ptr) ==
        &TestNamedPropertyStruct::IsActivated
    );
    EXPECT("function_property-set-pointer",
        std::any_cast<void(TestNamedPropertyStruct::*)(bool)>(function_property_set_ptr) ==
        &TestNamedPropertyStruct::Activate
    );

    auto property = type->property.find("Flag");

    ASSERT("property", property != nullptr);
    ASSERT("property-get", property->get != nullptr);
    ASSERT("function_property-set", function_property->set != nullptr);
    EXPECT("property-context", property->context != nullptr);

    auto [property_get_ptr, property_set_ptr] = property->pointer;

    EXPECT("property-get-pointer",
        std::any_cast<bool TestNamedPropertyStruct::*>(property_get_ptr) ==
        &TestNamedPropertyStruct::bIsActivated
    );
    EXPECT("property-set-pointer",
        std::any_cast<bool TestNamedPropertyStruct::*>(property_set_ptr) ==
        &TestNamedPropertyStruct::bIsActivatedBuffer
    );
}


TEST_SPACE()
{

struct TestBaseWithReflection {};
struct TestWrongMediatorWithReflection : TestBaseWithReflection {};
struct TestRightMediatorWithReflection : TestBaseWithReflection {};

struct TestWrongDerivedWithReflection : TestWrongMediatorWithReflection {};
struct TestRightDerivedWithReflection : TestRightMediatorWithReflection {};

struct TestDerivedWithReflection
    : TestWrongMediatorWithReflection, TestRightMediatorWithReflection {};


bool is_parent_of(eightrefl::type_t const* parent, eightrefl::type_t const* type)
{
    if (parent == type)
    {
        return true;
    }
    for (auto& [name, search] : type->parent.all)
    {
        if (is_parent_of(parent, search->type))
        {
            return true;
        }
    }
    return false;
}

bool is_child_of(eightrefl::type_t const* child, eightrefl::type_t const* type)
{
    if (child == type)
    {
        return true;
    }
    for (auto& [name, search] : type->child.all)
    {
        if (is_child_of(child, search->type))
        {
            return true;
        }
    }
    return false;
}

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestBaseWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestBaseWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestWrongMediatorWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestWrongMediatorWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestRightMediatorWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestRightMediatorWithReflection)
    PARENT(TestBaseWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestWrongDerivedWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestWrongDerivedWithReflection)
    PARENT(TestWrongMediatorWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestRightDerivedWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestRightDerivedWithReflection)
    PARENT(TestRightMediatorWithReflection)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestDerivedWithReflection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestDerivedWithReflection)
    PARENT(TestWrongMediatorWithReflection)
    PARENT(TestRightMediatorWithReflection)
REFLECTABLE_INIT()

TEST(TestLibrary, TestIsParentChildOf)
{
    auto base = eightrefl::global()->find("TestBaseWithReflection");

    ASSERT("base-type", base != nullptr);

    {
        auto type = eightrefl::global()->find("TestRightMediatorWithReflection");

        ASSERT("right-mediator-type", type != nullptr);
        EXPECT("right-mediator-is_child_of", is_child_of(type, base));
    }
    {
        auto type = eightrefl::global()->find("TestWrongMediatorWithReflection");

        ASSERT("wrong-mediator-type", type != nullptr);
        EXPECT("wrong-mediator-is_child_of", !is_child_of(type, base));
    }
    {
        auto type = eightrefl::global()->find("TestWrongDerivedWithReflection");

        ASSERT("wrong-derived-type", type != nullptr);
        EXPECT("wrong-derived-is_child_of", !is_child_of(type, base));
    }
    {
        auto type = eightrefl::global()->find("TestRightDerivedWithReflection");

        ASSERT("right-derived-type", type != nullptr);
        EXPECT("right-derived-is_child_of", is_child_of(type, base));
    }
    {
        auto type = eightrefl::global()->find("TestDerivedWithReflection");

        ASSERT("derived-type", type != nullptr);
        EXPECT("derived-is_parent_of", is_parent_of(base, type));
    }
}


TEST_SPACE()
{

struct TestTypeDeductionStruct {};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestTypeDeductionStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestTypeDeductionStruct)
REFLECTABLE_INIT()

TEST(TestLibrary, TestTypeDeduction)
{
    {
        auto type = eightrefl::find_or_add_type<TestTypeDeductionStruct>();

        EXPECT("type", eightrefl::global()->find("TestTypeDeductionStruct") == type);
    }
    {
        auto const_type = eightrefl::find_or_add_type<TestTypeDeductionStruct const>();

        EXPECT("const_type", eightrefl::global()->find("TestTypeDeductionStruct") == const_type);
    }
    {
        auto reference_type = eightrefl::find_or_add_type<TestTypeDeductionStruct&>();

        EXPECT("reference_type", eightrefl::builtin()->find("TestTypeDeductionStruct*") == reference_type);
    }
    {
        auto const_reference_type = eightrefl::find_or_add_type<TestTypeDeductionStruct const&>();

        EXPECT("const_reference_type", eightrefl::builtin()->find("TestTypeDeductionStruct*") == const_reference_type);
    }
    {
        auto pointer_type = eightrefl::find_or_add_type<TestTypeDeductionStruct*>();

        EXPECT("pointer_type", eightrefl::builtin()->find("TestTypeDeductionStruct*") == pointer_type);
    }
    {
        auto pointer_to_const_type = eightrefl::find_or_add_type<TestTypeDeductionStruct const*>();

        EXPECT("pointer_to_const_type", eightrefl::builtin()->find("TestTypeDeductionStruct*") == pointer_to_const_type);
    }
    {
        auto const_pointer_to_const_type = eightrefl::find_or_add_type<TestTypeDeductionStruct const* const>();

        EXPECT("const_pointer_to_const_type", eightrefl::builtin()->find("TestTypeDeductionStruct*") == const_pointer_to_const_type);
    }
    {
        auto pointer_type_reference = eightrefl::find_or_add_type<TestTypeDeductionStruct*&>();

        EXPECT("pointer_type_reference", eightrefl::builtin()->find("TestTypeDeductionStruct**") == pointer_type_reference);
    }
    {
        auto pointer_to_const_type_reference = eightrefl::find_or_add_type<TestTypeDeductionStruct const*&>();

        EXPECT("pointer_to_const_type_reference", eightrefl::builtin()->find("TestTypeDeductionStruct const**") == pointer_to_const_type_reference);
    }
    {
        auto const_pointer_to_const_type_reference = eightrefl::find_or_add_type<TestTypeDeductionStruct const* const&>();

        EXPECT("const_pointer_to_const_type_reference", eightrefl::builtin()->find("TestTypeDeductionStruct const**") == const_pointer_to_const_type_reference);
    }
    {
        auto mixed_type = eightrefl::find_or_add_type<TestTypeDeductionStruct const** const&>();

        EXPECT("mixed_type", eightrefl::builtin()->find("TestTypeDeductionStruct const***") == mixed_type);
    }
}

#ifdef EIGHTREFL_RTTI_ENABLE
TEST_SPACE()
{

struct TestRTTIRegistryStruct {};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestRTTIRegistryStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestRTTIRegistryStruct)
REFLECTABLE_INIT()

TEST(TestLibrary, TestRTTIRegistry)
{
    auto type = eightrefl::find_or_add_type<TestRTTIRegistryStruct>();
    auto const_type = eightrefl::find_or_add_type<TestRTTIRegistryStruct const>();
    auto reference_type = eightrefl::find_or_add_type<TestRTTIRegistryStruct&>(); // will break to TestRTTIRegistryStruct*
    auto const_reference_type = eightrefl::find_or_add_type<TestRTTIRegistryStruct const&>(); // will break to TestRTTIRegistryStruct*
    auto pointer_type = eightrefl::find_or_add_type<TestRTTIRegistryStruct*>();
    auto pointer_to_const_type = eightrefl::find_or_add_type<TestRTTIRegistryStruct const*>(); // will break to TestRTTIRegistryStruct*
    auto const_pointer_to_const_type = eightrefl::find_or_add_type<TestRTTIRegistryStruct const* const>(); // will break to TestRTTIRegistryStruct*
    auto pointer_type_reference = eightrefl::find_or_add_type<TestRTTIRegistryStruct*&>();
    auto pointer_to_const_type_reference = eightrefl::find_or_add_type<TestRTTIRegistryStruct const*&>(); // will break to TestRTTIRegistryStruct const**
    auto const_pointer_to_const_type_reference = eightrefl::find_or_add_type<TestRTTIRegistryStruct const* const&>(); // will break to TestRTTIRegistryStruct const**
    auto mixed_type = eightrefl::find_or_add_type<TestRTTIRegistryStruct const** const&>();

    EXPECT("type-typeid", eightrefl::global()->find(typeid(TestRTTIRegistryStruct)) == type);
    EXPECT("const_type-typeid", eightrefl::global()->find(typeid(TestRTTIRegistryStruct const)) == const_type);
    EXPECT("reference_type-typeid", eightrefl::builtin()->find(typeid(TestRTTIRegistryStruct*)) == reference_type);
    EXPECT("const_reference_type-typeid", eightrefl::builtin()->find(typeid(TestRTTIRegistryStruct*)) == const_reference_type);
    EXPECT("pointer_type-typeid", eightrefl::builtin()->find(typeid(TestRTTIRegistryStruct*)) == pointer_type);
    EXPECT("pointer_to_const_type-typeid", eightrefl::builtin()->find(typeid(TestRTTIRegistryStruct*)) == pointer_to_const_type);
    EXPECT("const_pointer_to_const_type-typeid", eightrefl::builtin()->find(typeid(TestRTTIRegistryStruct*)) == const_pointer_to_const_type);
    EXPECT("pointer_type_reference-typeid", eightrefl::builtin()->find(typeid(TestRTTIRegistryStruct**)) == pointer_type_reference);
    EXPECT("pointer_to_const_type_reference-typeid", eightrefl::builtin()->find(typeid(TestRTTIRegistryStruct const**)) == pointer_to_const_type_reference);
    EXPECT("const_pointer_to_const_type_reference-typeid", eightrefl::builtin()->find(typeid(TestRTTIRegistryStruct const**)) == const_pointer_to_const_type_reference);
    EXPECT("mixed_type-typeid", eightrefl::builtin()->find(typeid(TestRTTIRegistryStruct const***)) == mixed_type);
}
#endif // EIGHTREFL_RTTI_ENABLE

TEST_SPACE()
{

struct TestImplicitRegistryStruct
{
    TestImplicitRegistryStruct** const* Data = nullptr;
    static TestImplicitRegistryStruct* Instance;
};

TestImplicitRegistryStruct* TestImplicitRegistryStruct::Instance = nullptr;

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestImplicitRegistryStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestImplicitRegistryStruct)
    PROPERTY(Data)
    PROPERTY(Instance)
REFLECTABLE_INIT()

TEST(TestLibrary, TestImplicitRegistry)
{
    EXPECT("type", eightrefl::global()->find("TestImplicitRegistryStruct") != nullptr);
    EXPECT("type-property0", eightrefl::builtin()->find("TestImplicitRegistryStruct***") != nullptr);
    EXPECT("type-property1", eightrefl::builtin()->find("TestImplicitRegistryStruct*") != nullptr);
}


#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Standard/shared_ptr.hpp>
#endif // EIGHTREFL_STANDARD_ENABLE

TEST_SPACE()
{

struct TestFactorArgumentsAndResultStruct
{
    TestFactorArgumentsAndResultStruct() {}
    TestFactorArgumentsAndResultStruct(float const*, unsigned) {}
};

struct TestFactorArgumentsAndResultProxy
{
    TestFactorArgumentsAndResultProxy(TestFactorArgumentsAndResultStruct const&) {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFactorArgumentsAndResultStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFactorArgumentsAndResultStruct)
    FACTORY(TestFactorArgumentsAndResultStruct())
    FACTORY(TestFactorArgumentsAndResultStruct(float const*, unsigned))
    #ifdef EIGHTREFL_STANDARD_ENABLE
    FACTORY(std::shared_ptr<TestFactorArgumentsAndResultStruct>())
    #endif // EIGHTREFL_STANDARD_ENABLE
    FACTORY(TestFactorArgumentsAndResultProxy(TestFactorArgumentsAndResultStruct const&))
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestFactorArgumentsAndResultProxy)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFactorArgumentsAndResultProxy)
REFLECTABLE_INIT()

TEST(TestLibrary, TestFactorArgumentsAndResult)
{
    auto type = eightrefl::global()->find("TestFactorArgumentsAndResultStruct");

    ASSERT("type", type != nullptr);

    {
        auto without_arguments_with_return = type->factory.find("TestFactorArgumentsAndResultStruct()");

        ASSERT("factory-without_arguments_with_return", without_arguments_with_return != nullptr);
        EXPECT("without_arguments_with_return-result", without_arguments_with_return->result == type);
        EXPECT("without_arguments_with_return-argumens", without_arguments_with_return->arguments.size() == 0);
    }
    {
        auto with_arguments_with_return = type->factory.find("TestFactorArgumentsAndResultStruct(float const*, unsigned int)");

        ASSERT("with_arguments_with_return", with_arguments_with_return != nullptr);
        EXPECT("with_arguments_with_return-result", with_arguments_with_return->result == type);
        EXPECT("with_arguments_with_return-arguments", with_arguments_with_return->arguments.size() == 2 && with_arguments_with_return->arguments[0] == eightrefl::builtin()->find("float*") && with_arguments_with_return->arguments[1] == eightrefl::builtin()->find("unsigned int"));
    }
    #ifdef EIGHTREFL_STANDARD_ENABLE
    {
        auto without_arguments_withother_return = type->factory.find("std::shared_ptr<TestFactorArgumentsAndResultStruct>()");

        ASSERT("without_arguments_withother_return", without_arguments_withother_return != nullptr);
        EXPECT("without_arguments_withother_return-result", without_arguments_withother_return->result == eightrefl::standard()->find("std::shared_ptr<TestFactorArgumentsAndResultStruct>"));
        EXPECT("without_arguments_withother_return-arguments", without_arguments_withother_return->arguments.size() == 0);
    }
    #endif // EIGHTREFL_STANDARD_ENABLE
    {
        auto with_arguments_withother_return = type->factory.find("TestFactorArgumentsAndResultProxy(TestFactorArgumentsAndResultStruct const&)");

        ASSERT("with_arguments_withother_return", with_arguments_withother_return != nullptr);
        EXPECT("with_arguments_withother_return-result", with_arguments_withother_return->result == eightrefl::global()->find("TestFactorArgumentsAndResultProxy"));
        EXPECT("with_arguments_withother_return-arguments", with_arguments_withother_return->arguments.size() == 1 && with_arguments_withother_return->arguments[0] == eightrefl::builtin()->find("TestFactorArgumentsAndResultStruct*"));
    }
}


TEST_SPACE()
{

struct TestFunctionArgumentsAndResultStruct
{
    void WithoutArgumentsWithoutReturn() {}
    char const* WithoutArgumentsWithReturn() { return nullptr; }
    void WithArgumentsWithoutReturn(int, void(*)()) {}
    bool WithArgumentsWithReturn(std::nullptr_t) { return false; }
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFunctionArgumentsAndResultStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFunctionArgumentsAndResultStruct)
    FUNCTION(WithoutArgumentsWithoutReturn)
    FUNCTION(WithoutArgumentsWithReturn)
    FUNCTION(WithArgumentsWithoutReturn)
    FUNCTION(WithArgumentsWithReturn)
REFLECTABLE_INIT()

TEST(TestLibrary, TestFunctionArgumentsAndResult)
{
    auto type = eightrefl::global()->find("TestFunctionArgumentsAndResultStruct");

    ASSERT("type", type != nullptr);

    {
        auto without_arguments_without_return_overloads = type->function.find("WithoutArgumentsWithoutReturn");

        ASSERT("function-without_arguments_without_return-result-overloads", without_arguments_without_return_overloads != nullptr);

        auto without_arguments_without_return = without_arguments_without_return_overloads->find("void()");

        ASSERT("function-without_arguments_without_return", without_arguments_without_return != nullptr);
        EXPECT("function-without_arguments_without_return-result", without_arguments_without_return->result == eightrefl::builtin()->find("void"));
        EXPECT("function-without_arguments_without_return-arguments", without_arguments_without_return->arguments.size() == 0);
    }
    {
        auto without_arguments_with_return_overloads = type->function.find("WithoutArgumentsWithReturn");

        ASSERT("function-without_arguments_with_return-result-overloads", without_arguments_with_return_overloads != nullptr);

        auto without_arguments_with_return = without_arguments_with_return_overloads->find("char const*()");

        ASSERT("function-without_arguments_with_return", without_arguments_with_return != nullptr);
        EXPECT("function-without_arguments_with_return-result", without_arguments_with_return->result == eightrefl::builtin()->find("char*"));
        EXPECT("function-without_arguments_with_return-arguments", without_arguments_with_return->arguments.size() == 0);
    }
    {
        auto with_arguments_without_return_overloads = type->function.find("WithArgumentsWithoutReturn");

        ASSERT("function-with_arguments_without_return-overloads", with_arguments_without_return_overloads != nullptr);

        auto with_arguments_without_return = with_arguments_without_return_overloads->find("void(int, std::type_identity_t<void()>*)");

        ASSERT("function-with_arguments_without_return", with_arguments_without_return != nullptr);
        EXPECT("function-with_arguments_without_return-result", with_arguments_without_return->result == eightrefl::builtin()->find("void"));
        EXPECT("function-with_arguments_without_return-arguments-type", with_arguments_without_return->arguments.size() == 2 && with_arguments_without_return->arguments[0] == eightrefl::builtin()->find("int") && with_arguments_without_return->arguments[1] == eightrefl::builtin()->find("std::type_identity_t<void()>*"));
    }
    {
        auto with_arguments_with_return_overloads = type->function.find("WithArgumentsWithReturn");

        ASSERT("function-with_arguments_with_return-overloads", with_arguments_with_return_overloads != nullptr);

        auto with_arguments_with_return = with_arguments_with_return_overloads->find("bool(std::nullptr_t)");

        ASSERT("function-with_arguments_with_return", with_arguments_with_return != nullptr);
        EXPECT("function-with_arguments_with_return-result", with_arguments_with_return->result == eightrefl::builtin()->find("bool"));
        EXPECT("function-with_arguments_with_return-arguments-type", with_arguments_with_return->arguments.size() == 1 && with_arguments_with_return->arguments[0] == eightrefl::builtin()->find("std::nullptr_t"));
    }
}


TEST_SPACE()
{

// volatile and rvalue reference qualified functions - not supported by eightrefl library
struct TestConstReferenceQualifiedFunctionStruct
{
    void WithoutConstReferenceQualifier() {}
    void WithReferenceQualifier()& {}
    void WithConstQualifier() const {}
    void WithConstReferenceQualifier() const& {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestConstReferenceQualifiedFunctionStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestConstReferenceQualifiedFunctionStruct)
    FUNCTION(WithoutConstReferenceQualifier)
    FUNCTION(WithReferenceQualifier)
    FUNCTION(WithConstQualifier)
    FUNCTION(WithConstReferenceQualifier)
REFLECTABLE_INIT()

TEST(TestLibrary, TestConstReferenceQualifiedFunction)
{
    auto type = eightrefl::global()->find("TestConstReferenceQualifiedFunctionStruct");

    ASSERT("type", type != nullptr);

    {
        auto without_const_reference_qualifier = type->function.find("WithoutConstReferenceQualifier");

        EXPECT("function-without_const_reference_qualifier", without_const_reference_qualifier != nullptr && without_const_reference_qualifier->find("void()") != nullptr);
    }
    {
        auto with_reference_qualifier = type->function.find("WithReferenceQualifier");

        EXPECT("function-with_reference_qualifier", with_reference_qualifier != nullptr && with_reference_qualifier->find("void()&") != nullptr);
    }
    {
        auto with_const_qualifier = type->function.find("WithConstQualifier");

        EXPECT("function-with_const_qualifier", with_const_qualifier != nullptr && with_const_qualifier->find("void() const") != nullptr);
    }
    {
        auto with_const_reference_qualifier = type->function.find("WithConstReferenceQualifier");

        EXPECT("function-with_const_reference_qualifier", with_const_reference_qualifier != nullptr && with_const_reference_qualifier->find("void() const&") != nullptr);
    }
}


TEST_SPACE()
{

struct TestObjectContextStruct
{
    void Function0(TestObjectContextStruct*) {}
    void Function0(TestObjectContextStruct const*) {}
    void Function0(TestObjectContextStruct&) {}
    void Function0(TestObjectContextStruct const& ) {}
    void Function1(TestObjectContextStruct* const) {}
    void Function2(TestObjectContextStruct const* const) {}
    void Function3(TestObjectContextStruct) {}

    TestObjectContextStruct* Function4() { return this; }
    TestObjectContextStruct const* Function5() { return this; }
    TestObjectContextStruct& Function6() { return *this; }
    TestObjectContextStruct const& Function7() { return *this; }
    TestObjectContextStruct* const Function8() { return this; }
    TestObjectContextStruct const* const Function9() { return this; }
    TestObjectContextStruct Function10() { return *this; }

    static void StaticMemberFunction() {}
};

void NonMemberFunction() {}

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestObjectContextStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestObjectContextStruct)
    FACTORY(R())

    FUNCTION(Function0, void(R*))
    FUNCTION(Function0, void(R const*))
    FUNCTION(Function0, void(R&))
    FUNCTION(Function0, void(R const&))
    FUNCTION(Function1)
    FUNCTION(Function2)
    FUNCTION(Function3)

    FUNCTION(Function4)
    FUNCTION(Function5)
    FUNCTION(Function6)
    FUNCTION(Function7)
    FUNCTION(Function8)
    FUNCTION(Function9)
    FUNCTION(Function10)

    FUNCTION(StaticMemberFunction)
    FREE_FUNCTION(NonMemberFunction)
REFLECTABLE_INIT()

TEST(TestLibrary, TestTypeContext)
{
    auto type = eightrefl::global()->find("TestObjectContextStruct");

    ASSERT("type", type != nullptr);

    auto factory = type->factory.find("TestObjectContextStruct()");

    ASSERT("factory", factory != nullptr);

    auto object = factory->call({});

    ASSERT("object", object.has_value());

    std::any handle_object_context = &std::any_cast<TestObjectContextStruct&>(object);
    std::any object_context = type->context(object); // same as std::addressof(std::any_cast<TestObjectContextStruct&>(object))

    EXPECT("object-context", std::any_cast<TestObjectContextStruct*>(handle_object_context) == std::any_cast<TestObjectContextStruct*>(object_context));

    auto other_object = factory->call({});
    auto other_object_context = type->context(object);

    {
        auto function0 = type->function.find("Function0");

        ASSERT("function0", function0 != nullptr);
        {
            auto function0_with_pointer_arg = function0->find("void(TestObjectContextStruct*)");

            ASSERT("function0-with_pointer_arg", function0_with_pointer_arg != nullptr);

            auto success = true;
            try { function0_with_pointer_arg->call(object_context, {other_object_context}); }
            catch(...) { success = false; }

            EXPECT("function0-with_pointer_arg-call", success);
        }
        {
            auto function0_with_pointer_to_const_arg = function0->find("void(TestObjectContextStruct const*)");

            ASSERT("function0-with_pointer_to_const_arg", function0_with_pointer_to_const_arg != nullptr);

            auto success = true;
            try { function0_with_pointer_to_const_arg->call(object_context, {other_object_context}); }
            catch(...) { success = false; }

            EXPECT("function0-with_pointer_to_const_arg-call", success);
        }
        {
            auto function0_with_reference_arg = function0->find("void(TestObjectContextStruct&)");

            ASSERT("function0-with_reference_arg", function0_with_reference_arg != nullptr);

            auto success = true;
            try { function0_with_reference_arg->call(object_context, {other_object_context}); }
            catch(...) { success = false; }

            EXPECT("function0-with_reference_arg-call", success);
        }
        {
            auto function0_with_reference_to_const_arg = function0->find("void(TestObjectContextStruct const&)");

            ASSERT("function0-with_reference_to_const_arg", function0_with_reference_to_const_arg != nullptr);

            auto success = true;
            try { function0_with_reference_to_const_arg->call(object_context, {other_object_context}); }
            catch(...) { success = false; }

            EXPECT("function0-with_reference_to_const_arg-call", success);
        }
    }
    {
        auto function1 = type->function.find("Function1");

        ASSERT("function1", function1 != nullptr);
        {
            // TestObjectContextStruct* const == TestObjectContextStruct*
            auto function1_with_const_pointer_arg = function1->find("void(TestObjectContextStruct*)");

            ASSERT("function1-with_const_pointer_arg", function1_with_const_pointer_arg != nullptr);

            auto success = true;
            try { function1_with_const_pointer_arg->call(object_context, {other_object_context}); }
            catch(...) { success = false; }

            EXPECT("function1-with_const_pointer_arg-call", success);
        }
    }
    {
        auto function2 = type->function.find("Function2");

        ASSERT("function2", function2 != nullptr);
        {
            // TestObjectContextStruct const* const == TestObjectContextStruct const*
            auto function2_with_const_pointer_to_const_arg = function2->find("void(TestObjectContextStruct const*)");

            ASSERT("function2-with_const_pointer_to_const_arg", function2_with_const_pointer_to_const_arg != nullptr);

            auto success = true;
            try { function2_with_const_pointer_to_const_arg->call(object_context, {other_object_context}); }
            catch(...) { success = false; }

            EXPECT("function0-with_const_pointer_to_const_arg-call", success);
        }
    }
    {
        auto function3 = type->function.find("Function3");

        ASSERT("function3", function3 != nullptr);
        {
            auto function3_with_value_arg = function3->find("void(TestObjectContextStruct)");

            ASSERT("function3-with_value_arg", function3_with_value_arg != nullptr);

            auto success = true;
            try { function3_with_value_arg->call(object_context, {other_object}); }
            catch(...) { success = false; }

            EXPECT("function3-with_value_arg-call", success);
        }
    }

    {
        auto function4 = type->function.find("Function4");

        ASSERT("function4", function4 != nullptr);
        {
            auto function4_with_return_pointer = function4->find("TestObjectContextStruct*()");

            ASSERT("function4-with_return_pointer", function4_with_return_pointer != nullptr);

            std::any result;

            auto success = true;
            try { result = function4_with_return_pointer->call(object_context, {}); }
            catch(...) { success = false; }

            ASSERT("function4-with_return_pointer-call", success);
            EXPECT("function4-with_return_pointer-result", std::any_cast<TestObjectContextStruct*>(object_context) == std::any_cast<TestObjectContextStruct*>(result));
        }
    }
    {
        auto function5 = type->function.find("Function5");

        ASSERT("function5", function5 != nullptr);
        {
            auto function5_with_return_pointer_to_const = function5->find("TestObjectContextStruct const*()");

            ASSERT("function5-with_return_pointer_to_const", function5_with_return_pointer_to_const != nullptr);

            std::any result;

            auto success = true;
            try { result = function5_with_return_pointer_to_const->call(object_context, {}); }
            catch(...) { success = false; }

            ASSERT("function5-with_return_pointer_to_const-call", success);
            EXPECT("function5-with_return_pointer_to_const-result", std::any_cast<TestObjectContextStruct*>(object_context) == std::any_cast<TestObjectContextStruct*>(result));
        }
    }
    {
        auto function6 = type->function.find("Function6");

        ASSERT("function6", function6 != nullptr);
        {
            auto function6_with_return_reference = function6->find("TestObjectContextStruct&()");

            ASSERT("function6-with_return_reference", function6_with_return_reference != nullptr);

            std::any result;

            auto success = true;
            try { result = function6_with_return_reference->call(object_context, {}); }
            catch(...) { success = false; }

            ASSERT("function6-with_return_reference-call", success);
            EXPECT("function6-with_return_reference-result", std::any_cast<TestObjectContextStruct*>(object_context) == std::any_cast<TestObjectContextStruct*>(result));
        }
    }
    {
        auto function7 = type->function.find("Function7");

        ASSERT("function7", function7 != nullptr);
        {
            auto function7_with_return_reference_to_const = function7->find("TestObjectContextStruct const&()");

            ASSERT("function7-with_return_reference_to_const", function7_with_return_reference_to_const != nullptr);

            std::any result;

            auto success = true;
            try { result = function7_with_return_reference_to_const->call(object_context, {}); }
            catch(...) { success = false; }

            ASSERT("function7-with_return_reference_to_const-call", success);
            EXPECT("function7-with_return_reference_to_const-result", std::any_cast<TestObjectContextStruct*>(object_context) == std::any_cast<TestObjectContextStruct*>(result));
        }
    }
    {
        auto function8 = type->function.find("Function8");

        ASSERT("function8", function8 != nullptr);
        {
            auto function8_with_return_const_pointer = function8->find("TestObjectContextStruct* const()");

            ASSERT("function8-with_return_const_pointer", function8_with_return_const_pointer != nullptr);

            std::any result;

            auto success = true;
            try { result = function8_with_return_const_pointer->call(object_context, {}); }
            catch(...) { success = false; }

            ASSERT("function8-with_return_const_pointer-call", success);
            EXPECT("function6-with_return_const_pointer-result", std::any_cast<TestObjectContextStruct*>(object_context) == std::any_cast<TestObjectContextStruct*>(result));
        }
    }
    {
        auto function9 = type->function.find("Function9");

        ASSERT("function9", function9 != nullptr);
        {
            auto function9_with_return_const_pointer_to_const = function9->find("TestObjectContextStruct const* const()");

            ASSERT("function9-with_return_const_pointer_to_const", function9_with_return_const_pointer_to_const != nullptr);

            std::any result;

            auto success = true;
            try { result = function9_with_return_const_pointer_to_const->call(object_context, {}); }
            catch(...) { success = false; }

            ASSERT("function9-with_return_const_pointer_to_const-call", success);
            EXPECT("function9-with_return_const_pointer_to_const-result", std::any_cast<TestObjectContextStruct*>(object_context) == std::any_cast<TestObjectContextStruct*>(result));
        }
    }
    {
        auto function10 = type->function.find("Function10");

        ASSERT("function10", function10 != nullptr);
        {
            auto function10_with_return_value = function10->find("TestObjectContextStruct()");

            ASSERT("function10-with_return_value", function10_with_return_value != nullptr);

            std::any result;

            auto success = true;
            try { result = function10_with_return_value->call(object_context, {}); }
            catch(...) { success = false; }

            ASSERT("function10-with_return_value-call", success);
            EXPECT("function10-with_return_value-result", std::any_cast<TestObjectContextStruct*>(object_context) != &std::any_cast<TestObjectContextStruct&>(result));
        }
    }

    {
        auto static_member_function = type->function.find("StaticMemberFunction");

        ASSERT("static_member_function", static_member_function != nullptr);
        {
            auto static_member_function_without_args = static_member_function->find("void()");

            ASSERT("static_member_function-without_args", static_member_function_without_args != nullptr);

            std::any no_context;
            auto success = true;
            try { static_member_function_without_args->call(no_context, {}); }
            catch(...) { success = false; }

            EXPECT("static_member_function-without_args-call", success);
        }
    }
    {
        auto non_member_function = type->function.find("StaticMemberFunction");

        ASSERT("non_member_function", non_member_function != nullptr);
        {
            auto non_member_function_without_args = non_member_function->find("void()");

            ASSERT("non_member_function-without_args", non_member_function_without_args != nullptr);

            std::any no_context;
            auto success = true;
            try { non_member_function_without_args->call(no_context, {}); }
            catch(...) { success = false; }

            EXPECT("non_member_function-without_args-call", success);
        }
    }
}


TEST_SPACE()
{

struct TestPointerDereferenceTypeStruct {};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestPointerDereferenceTypeStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestPointerDereferenceTypeStruct)
REFLECTABLE_INIT()

TEST(TestLibrary, TestPointerDereferenceType)
{
    eightrefl::reflectable<TestPointerDereferenceTypeStruct*>();

    auto type = eightrefl::builtin()->find("TestPointerDereferenceTypeStruct*");

    ASSERT("type", type != nullptr);

    auto meta = type->meta.find("*");
    ASSERT("type.meta", meta != nullptr);

    auto value = std::any_cast<eightrefl::type_t*>(&meta->value);
    ASSERT("type.meta.value", value != nullptr && *value != nullptr && *value == eightrefl::global()->find("TestPointerDereferenceTypeStruct"));
}

#ifdef EIGHTREFL_MEMBER_ENABLE
TEST_SPACE()
{

struct TestMemberPointerStruct
{
    void (TestMemberPointerStruct::*Function)() = nullptr;
    void (TestMemberPointerStruct::*FunctionReference)()& = nullptr;
    void (TestMemberPointerStruct::*FunctionConst)() const = nullptr;
    void (TestMemberPointerStruct::*FunctionConstReference)() const& = nullptr;
    int TestMemberPointerStruct::*Property = nullptr;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestMemberPointerStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestMemberPointerStruct)
    PROPERTY(Function)
    PROPERTY(FunctionReference)
    PROPERTY(FunctionConst)
    PROPERTY(FunctionConstReference)
    PROPERTY(Property)
REFLECTABLE_INIT()

TEST(TestLibrary, TestMemberPointer)
{
    auto type = eightrefl::global()->find("TestMemberPointerStruct");

    ASSERT("type", type != nullptr);

    {
        auto property = type->property.find("Function");

        EXPECT("type.property.function", property != nullptr && property->type == eightrefl::builtin()->find("std::type_identity_t<void()> TestMemberPointerStruct::*"));
    }
    {
        auto property = type->property.find("FunctionReference");

        EXPECT("type.property.function_reference", property != nullptr && property->type == eightrefl::builtin()->find("std::type_identity_t<void()&> TestMemberPointerStruct::*"));
    }
    {
        auto property = type->property.find("FunctionConst");

        EXPECT("type.property.function_const", property != nullptr && property->type == eightrefl::builtin()->find("std::type_identity_t<void() const> TestMemberPointerStruct::*"));
    }
    {
        auto property = type->property.find("FunctionConstReference");

        EXPECT("type.property.function_const_reference", property != nullptr && property->type == eightrefl::builtin()->find("std::type_identity_t<void() const&> TestMemberPointerStruct::*"));
    }
    {
        auto property = type->property.find("Property");

        EXPECT("type.property.property", property != nullptr && property->type == eightrefl::builtin()->find("int TestMemberPointerStruct::*"));
    }
}
#endif // EIGHTREFL_MEMBER_ENABLE
