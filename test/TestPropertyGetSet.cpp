#include <EightreflTestingBase.hpp>

TEST_SPACE()
{

struct TestPropertyGetSetStruct
{
    int Property = 8;
    int const ConstProperty = 8;

    int& GetPropertyRef() { return Property; }
    int const& GetPropertyConstRef() const { return Property; }
    int GetProperty() const { return Property; }

    void SetPropertyRef(int& value) { Property = value; }
    void SetPropertyConstRef(int const& value) { Property = value; }
    void SetProperty(int value) { Property = value; }
};

} // TEST_SPACE

TEST(TestLibrary, TestPropertyGetSet)
{
    {
        auto property_get = eightrefl::handler_property_get(&TestPropertyGetSetStruct::Property);
        auto property_set = eightrefl::handler_property_set(&TestPropertyGetSetStruct::Property);

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        std::any property_value = property_get(object_context);

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("handler-property-get", std::any_cast<int*>(property_value) == &object.Property);
        #else
        EXPECT("handler-property-get", std::any_cast<int>(property_value) == object.Property);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int value = 8888;
        property_set(object_context, eightrefl::backward(value));
        #else
        property_set(object_context, 8888);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        EXPECT("handler-property-set", object.Property == 8888);
    }
    {
        auto const_property_get = eightrefl::handler_property_get(&TestPropertyGetSetStruct::ConstProperty);
        auto const_property_set = eightrefl::handler_property_set(&TestPropertyGetSetStruct::ConstProperty);

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        std::any const_property_value = const_property_get(object_context);
        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("handler-const_property-get", &eightrefl::forward<int const&>(const_property_value) == &object.ConstProperty);
        #else
        EXPECT("handler-const_property-get", eightrefl::forward<int>(const_property_value) == object.ConstProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        EXPECT("handler-const_property-set", const_property_set == nullptr);
    }

    {
        auto property_get = eightrefl::handler_property_get((int&(TestPropertyGetSetStruct::*)(void) const)&TestPropertyGetSetStruct::GetPropertyRef);

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        EXPECT("handler-function-ref_property-get", &eightrefl::forward<int&>(property_get(object_context)) == &object.Property);
    }
    {
        auto const_ref_property_get = eightrefl::handler_property_get((int const&(TestPropertyGetSetStruct::*)(void) const)&TestPropertyGetSetStruct::GetPropertyConstRef);

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        EXPECT("handler-function-const_ref_property-get", &eightrefl::forward<int const&>(const_ref_property_get(object_context)) == &object.Property);
    }
    {
        auto property_get = eightrefl::handler_property_get((int(TestPropertyGetSetStruct::*)(void) const)&TestPropertyGetSetStruct::GetProperty);

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        EXPECT("handler-function-property-get", eightrefl::forward<int>(property_get(object_context)) == object.Property);
    }

    {
        auto property_set = eightrefl::handler_property_set((void(TestPropertyGetSetStruct::*)(int&))&TestPropertyGetSetStruct::SetPropertyRef);

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        int value = 8888;
        property_set(object_context, eightrefl::backward(value));

        EXPECT("handler-function-ref_property-set", object.Property == 8888);
    }
    {
        auto const_ref_property_set = eightrefl::handler_property_set(static_cast<void(TestPropertyGetSetStruct::*)(int const&)>(&TestPropertyGetSetStruct::SetPropertyConstRef));

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        int value = 8888;
        const_ref_property_set(object_context, eightrefl::backward(value));

        EXPECT("handler-function-const_ref_property-set", object.Property == 8888);
    }
    {
        auto property_set = eightrefl::handler_property_set(static_cast<void(TestPropertyGetSetStruct::*)(int)>(&TestPropertyGetSetStruct::SetProperty));

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        property_set(object_context, 8888);
        EXPECT("handler-function-property-set", object.Property == 8888);
    }
 
    {
        eightrefl::property_t property
        {
            .name = "Property",
            .get = eightrefl::handler_property_get(&TestPropertyGetSetStruct::Property),
            .set = eightrefl::handler_property_set(&TestPropertyGetSetStruct::Property)
        };

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int value = 8888;
        property.set(object_context, eightrefl::backward(value));

        EXPECT("property-set0", object.Property == 8888);

        std::any value_as_any0 = property.get(object_context);

        EXPECT("property-get0", eightrefl::forward<int&>(value_as_any0) == object.Property);

        property.set(object_context, eightrefl::backward<int const&>(88));

        EXPECT("property-set1", object.Property == 88);

        std::any value_as_any1 = property.get(object_context);

        EXPECT("property-get1", eightrefl::forward<int&>(value_as_any1) == object.Property);

        property.set(object_context, eightrefl::backward<int&&>(8888));

        EXPECT("property-set2", object.Property == 8888);

        std::any value_as_any2 = property.get(object_context);

        EXPECT("property-get2", eightrefl::forward<int&>(value_as_any2) == object.Property);

        bool success = false;
        try { property.set(object_context, 8888); }
        catch (...) { success = true; }
    
        EXPECT("property-set3", success);
        #else
        property.set(object_context, 8888);

        EXPECT("property-set0", object.Property == 8888);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    }
    {
        eightrefl::property_t const_property
        {
            .name = "ConstProperty",
            .get = eightrefl::handler_property_get(&TestPropertyGetSetStruct::ConstProperty)
        };

        TestPropertyGetSetStruct object;
        std::any object_context = &object;

        std::any const_value_as_any = const_property.get(object_context);

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("const_ref_property-get", &eightrefl::forward<int const&>(const_value_as_any) == &object.ConstProperty);
        #else
        EXPECT("const_ref_property-get", eightrefl::forward<int>(const_value_as_any) == object.ConstProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("const_ref_property-set", const_property.set == nullptr);
    }
}


TEST_SPACE()
{

struct TestStaticPropertyGetSetStruct
{
    static int StaticProperty;
    static int const StaticConstProperty;

    static int& StaticGetPropertyRef() { return StaticProperty; }
    static int const& StaticGetPropertyConstRef() { return StaticProperty; }
    static int StaticGetProperty() { return StaticProperty; }

    static void StaticSetPropertyRef(int& value) { StaticProperty = value; }
    static void StaticSetPropertyConstRef(int const& value) { StaticProperty = value; }
    static void StaticSetProperty(int value) { StaticProperty = value; }
};

int TestStaticPropertyGetSetStruct::StaticProperty = 8;
int const TestStaticPropertyGetSetStruct::StaticConstProperty = 8;

} // TEST_SPACE

TEST(TestLibrary, TestStaticPropertyGetSet)
{
    {
        auto property_get = eightrefl::handler_property_get(&TestStaticPropertyGetSetStruct::StaticProperty);
        auto property_set = eightrefl::handler_property_set(&TestStaticPropertyGetSetStruct::StaticProperty);

        std::any property_value = property_get({});

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("handler-property-get", std::any_cast<int*>(property_value) == &TestStaticPropertyGetSetStruct::StaticProperty);
        #else
        EXPECT("handler-property-get", std::any_cast<int>(property_value) == TestStaticPropertyGetSetStruct::StaticProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int value = 8888;
        property_set({}, eightrefl::backward(value));
        #else
        property_set({}, 8888);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        EXPECT("handler-property-set", TestStaticPropertyGetSetStruct::StaticProperty == 8888);
    }
    {
        auto const_property_get = eightrefl::handler_property_get(&TestStaticPropertyGetSetStruct::StaticConstProperty);
        auto const_property_set = eightrefl::handler_property_set(&TestStaticPropertyGetSetStruct::StaticConstProperty);

        std::any const_property_value = const_property_get({});
        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("handler-const_property-get", &eightrefl::forward<int const&>(const_property_value) == &TestStaticPropertyGetSetStruct::StaticConstProperty);
        #else
        EXPECT("handler-const_property-get", eightrefl::forward<int>(const_property_value) == TestStaticPropertyGetSetStruct::StaticConstProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        EXPECT("handler-const_property-set", const_property_set == nullptr);
    }

    {
        auto property_get = eightrefl::handler_property_get((int&(*)(void))&TestStaticPropertyGetSetStruct::StaticGetPropertyRef);

        EXPECT("handler-function-ref_property-get", &eightrefl::forward<int&>(property_get({})) == &TestStaticPropertyGetSetStruct::StaticProperty);
    }
    {
        auto const_ref_property_get = eightrefl::handler_property_get((int const&(*)(void))&TestStaticPropertyGetSetStruct::StaticGetPropertyConstRef);

        EXPECT("handler-function-const_ref_property-get", &eightrefl::forward<int const&>(const_ref_property_get({})) == &TestStaticPropertyGetSetStruct::StaticProperty);
    }
    {
        auto property_get = eightrefl::handler_property_get((int(*)(void))&TestStaticPropertyGetSetStruct::StaticGetProperty);

        EXPECT("handler-function-property-get", eightrefl::forward<int>(property_get({})) == TestStaticPropertyGetSetStruct::StaticProperty);
    }

    {
        auto property_set = eightrefl::handler_property_set((void(*)(int&))&TestStaticPropertyGetSetStruct::StaticSetPropertyRef);

        int value = 88;
        property_set({}, eightrefl::backward(value));

        EXPECT("handler-function-ref_property-set", TestStaticPropertyGetSetStruct::StaticProperty == 88);
    }
    {
        auto const_ref_property_set = eightrefl::handler_property_set(static_cast<void(*)(int const&)>(&TestStaticPropertyGetSetStruct::StaticSetPropertyConstRef));

        int value = 8888;
        const_ref_property_set({}, eightrefl::backward(value));

        EXPECT("handler-function-const_ref_property-set", TestStaticPropertyGetSetStruct::StaticProperty == 8888);
    }
    {
        auto property_set = eightrefl::handler_property_set(static_cast<void(*)(int)>(&TestStaticPropertyGetSetStruct::StaticSetProperty));

        property_set({}, 88);
        EXPECT("handler-function-property-set", TestStaticPropertyGetSetStruct::StaticProperty == 88);
    }

    {
        eightrefl::property_t property
        {
            .name = "Property",
            .get = eightrefl::handler_property_get(&TestStaticPropertyGetSetStruct::StaticProperty),
            .set = eightrefl::handler_property_set(&TestStaticPropertyGetSetStruct::StaticProperty)
        };

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int value = 8888;
        property.set({}, eightrefl::backward(value));

        EXPECT("property-set0", TestStaticPropertyGetSetStruct::StaticProperty == 8888);

        std::any value_as_any0 = property.get({});

        EXPECT("property-get0", eightrefl::forward<int&>(value_as_any0) == TestStaticPropertyGetSetStruct::StaticProperty);

        property.set({}, eightrefl::backward<int const&>(88));

        EXPECT("property-set1", TestStaticPropertyGetSetStruct::StaticProperty == 88);

        std::any value_as_any1 = property.get({});

        EXPECT("property-get1", eightrefl::forward<int&>(value_as_any1) == TestStaticPropertyGetSetStruct::StaticProperty);

        property.set({}, eightrefl::backward<int&&>(8888));

        EXPECT("property-set2", TestStaticPropertyGetSetStruct::StaticProperty == 8888);

        std::any value_as_any2 = property.get({});

        EXPECT("property-get2", eightrefl::forward<int&>(value_as_any2) == TestStaticPropertyGetSetStruct::StaticProperty);

        bool success = false;
        try { property.set({}, 8888); }
        catch (...) { success = true; }
    
        EXPECT("property-set3", success);
        #else
        property.set({}, 8888);

        EXPECT("property-set0", TestStaticPropertyGetSetStruct::StaticProperty == 8888);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    }
    {
        eightrefl::property_t const_property
        {
            .name = "ConstProperty",
            .get = eightrefl::handler_property_get(&TestStaticPropertyGetSetStruct::StaticConstProperty)
        };

        std::any const_value_as_any = const_property.get({});

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("const_ref_property-get", &eightrefl::forward<int const&>(const_value_as_any) == &TestStaticPropertyGetSetStruct::StaticConstProperty);
        #else
        EXPECT("const_ref_property-get", eightrefl::forward<int>(const_value_as_any) == TestStaticPropertyGetSetStruct::StaticConstProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("const_ref_property-set", const_property.set == nullptr);
    }
}


TEST_SPACE()
{

int ExternalProperty = 8;
int const ExternalConstProperty = 8;

int& ExternalGetPropertyRef() { return ExternalProperty; }
int const& ExternalGetPropertyConstRef() { return ExternalProperty; }
int ExternalGetProperty() { return ExternalProperty; }

void ExternalSetPropertyRef(int& value) { ExternalProperty = value; }
void ExternalSetPropertyConstRef(int const& value) { ExternalProperty = value; }
void ExternalSetProperty(int value) { ExternalProperty = value; }

} // TEST_SPACE

TEST(TestLibrary, TestExternalPropertyGetSet)
{
    {
        auto property_get = eightrefl::handler_property_get(&ExternalProperty);
        auto property_set = eightrefl::handler_property_set(&ExternalProperty);

        std::any property_value = property_get({});

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("handler-property-get", std::any_cast<int*>(property_value) == &ExternalProperty);
        #else
        EXPECT("handler-property-get", std::any_cast<int>(property_value) == ExternalProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int value = 8888;
        property_set({}, eightrefl::backward(value));
        #else
        property_set({}, 8888);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        EXPECT("handler-property-set", ExternalProperty == 8888);
    }
    {
        auto const_property_get = eightrefl::handler_property_get(&ExternalConstProperty);
        auto const_property_set = eightrefl::handler_property_set(&ExternalConstProperty);

        std::any const_property_value = const_property_get({});
        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("handler-const_property-get", &eightrefl::forward<int const&>(const_property_value) == &ExternalConstProperty);
        #else
        EXPECT("handler-const_property-get", eightrefl::forward<int>(const_property_value) == ExternalConstProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE

        EXPECT("handler-const_property-set", const_property_set == nullptr);
    }

    {
        auto property_get = eightrefl::handler_property_get((int&(*)(void))&ExternalGetPropertyRef);

        EXPECT("handler-function-ref_property-get", &eightrefl::forward<int&>(property_get({})) == &ExternalProperty);
    }
    {
        auto const_ref_property_get = eightrefl::handler_property_get((int const&(*)(void))&ExternalGetPropertyConstRef);

        EXPECT("handler-function-const_ref_property-get", &eightrefl::forward<int const&>(const_ref_property_get({})) == &ExternalProperty);
    }
    {
        auto property_get = eightrefl::handler_property_get((int(*)(void))&ExternalGetProperty);

        EXPECT("handler-function-property-get", eightrefl::forward<int>(property_get({})) == ExternalProperty);
    }

    {
        auto property_set = eightrefl::handler_property_set((void(*)(int&))&ExternalSetPropertyRef);

        int value = 88;
        property_set({}, eightrefl::backward(value));

        EXPECT("handler-function-ref_property-set", ExternalGetPropertyRef() == 88);
    }
    {
        auto const_ref_property_set = eightrefl::handler_property_set(static_cast<void(*)(int const&)>(&ExternalSetPropertyConstRef));

        int value = 8888;
        const_ref_property_set({}, eightrefl::backward(value));

        EXPECT("handler-function-const_ref_property-set", ExternalProperty == 8888);
    }
    {
        auto property_set = eightrefl::handler_property_set(static_cast<void(*)(int)>(&ExternalSetProperty));

        property_set({}, 88);
        EXPECT("handler-function-property-set", ExternalProperty == 88);
    }

    {
        eightrefl::property_t property
        {
            .name = "Property",
            .get = eightrefl::handler_property_get(&ExternalProperty),
            .set = eightrefl::handler_property_set(&ExternalProperty)
        };

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        int value = 8888;
        property.set({}, eightrefl::backward(value));

        EXPECT("property-set0", ExternalProperty == 8888);

        std::any value_as_any0 = property.get({});

        EXPECT("property-get0", eightrefl::forward<int&>(value_as_any0) == ExternalProperty);

        property.set({}, eightrefl::backward<int const&>(88));

        EXPECT("property-set1", ExternalProperty == 88);

        std::any value_as_any1 = property.get({});

        EXPECT("property-get1", eightrefl::forward<int&>(value_as_any1) == ExternalProperty);

        property.set({}, eightrefl::backward<int&&>(8888));

        EXPECT("property-set2", ExternalProperty == 8888);

        std::any value_as_any2 = property.get({});

        EXPECT("property-get2", eightrefl::forward<int&>(value_as_any2) == ExternalProperty);

        bool success = false;
        try { property.set({}, 8888); }
        catch (...) { success = true; }
    
        EXPECT("property-set3", success);
        #else
        property.set({}, 8888);

        EXPECT("property-set0", ExternalProperty == 8888);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    }
    {
        eightrefl::property_t const_property
        {
            .name = "ConstProperty",
            .get = eightrefl::handler_property_get(&ExternalConstProperty)
        };

        std::any const_value_as_any = const_property.get({});

        #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("const_ref_property-get", &eightrefl::forward<int const&>(const_value_as_any) == &ExternalConstProperty);
        #else
        EXPECT("const_ref_property-get", eightrefl::forward<int>(const_value_as_any) == ExternalConstProperty);
        #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
        EXPECT("const_ref_property-set", const_property.set == nullptr);
    }
}
