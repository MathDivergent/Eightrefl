#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Dev/Dev.hpp>
#include <Eightrefl/Dev/Attribute.hpp>

TEST(TestDev, TestAttribute)
{
    eightrefl::reflectable<eightrefl::attribute_t<int>>();

    auto type = eightrefl::dev()->find("eightrefl::attribute_t<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::attribute_t<int>");
    EXPECT("type-size", type->size == sizeof(eightrefl::attribute_t<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("function-find", type->function.find("find") != nullptr);
    EXPECT("function-add", type->function.find("add") != nullptr);
    EXPECT("property-all", type->property.find("all") != nullptr);
}

TEST(TestDev, TestChild)
{
    auto type = eightrefl::dev()->find("eightrefl::child_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::child_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::child_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("property-type", type->property.find("type") != nullptr);
    EXPECT("property-cast", type->property.find("cast") != nullptr);
}

TEST(TestDev, TestParent)
{
    auto type = eightrefl::dev()->find("eightrefl::parent_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::parent_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::parent_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("property-type", type->property.find("type") != nullptr);
    EXPECT("property-cast", type->property.find("cast") != nullptr);
    EXPECT("property-meta", type->property.find("meta") != nullptr);
}

TEST(TestDev, TestFactory)
{
    auto type = eightrefl::dev()->find("eightrefl::factory_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::factory_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::factory_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("property-name", type->property.find("name") != nullptr);
    EXPECT("property-call", type->property.find("call") != nullptr);
    EXPECT("property-arguments", type->property.find("arguments") != nullptr);
    EXPECT("property-meta", type->property.find("meta") != nullptr);
}

TEST(TestDev, TestFunction)
{
    auto type = eightrefl::dev()->find("eightrefl::function_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::function_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::function_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("property-name", type->property.find("name") != nullptr);
    EXPECT("property-call", type->property.find("call") != nullptr);
    EXPECT("property-arguments", type->property.find("arguments") != nullptr);
    EXPECT("property-result", type->property.find("result") != nullptr);
    EXPECT("property-pointer", type->property.find("pointer") != nullptr);
    EXPECT("property-meta", type->property.find("meta") != nullptr);
}

TEST(TestDev, TestProperty)
{
    auto type = eightrefl::dev()->find("eightrefl::property_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::property_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::property_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("property-name", type->property.find("name") != nullptr);
    EXPECT("property-type", type->property.find("type") != nullptr);
    EXPECT("property-get", type->property.find("get") != nullptr);
    EXPECT("property-set", type->property.find("set") != nullptr);
    EXPECT("property-context", type->property.find("context") != nullptr);
    EXPECT("property-meta", type->property.find("meta") != nullptr);
}

TEST(TestDev, TestDeleter)
{
    auto type = eightrefl::dev()->find("eightrefl::deleter_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::deleter_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::deleter_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("property-name", type->property.find("name") != nullptr);
    EXPECT("property-type", type->property.find("call") != nullptr);
    EXPECT("property-meta", type->property.find("meta") != nullptr);
}

TEST(TestDev, TestMeta)
{
    auto type = eightrefl::dev()->find("eightrefl::meta_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::meta_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::meta_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("property-name", type->property.find("name") != nullptr);
    EXPECT("property-value", type->property.find("value") != nullptr);
    EXPECT("property-meta", type->property.find("meta") != nullptr);
}

TEST(TestDev, TestInjection)
{
    auto type = eightrefl::dev()->find("eightrefl::injection_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::injection_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::injection_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("property-type", type->property.find("type") != nullptr);
    EXPECT("property-call", type->property.find("call") != nullptr);
}

TEST(TestDev, TestType)
{
    auto type = eightrefl::dev()->find("eightrefl::type_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::type_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::type_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("property-name", type->property.find("name") != nullptr);
    EXPECT("property-registry", type->property.find("registry") != nullptr);
    EXPECT("property-size", type->property.find("size") != nullptr);
    EXPECT("property-context", type->property.find("context") != nullptr);

    EXPECT("property-injection", type->property.find("injection") != nullptr);
    EXPECT("property-child", type->property.find("child") != nullptr);

    EXPECT("property-parent", type->property.find("parent") != nullptr);
    EXPECT("property-factory", type->property.find("factory") != nullptr);
    EXPECT("property-function", type->property.find("function") != nullptr);
    EXPECT("property-property", type->property.find("property") != nullptr);
    EXPECT("property-deleter", type->property.find("deleter") != nullptr);
    EXPECT("property-meta", type->property.find("meta") != nullptr);
}

TEST(TestDev, TestRegistry)
{
    auto type = eightrefl::dev()->find("eightrefl::registry_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::registry_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::registry_t));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("eightrefl::registry_t()") != nullptr);
    EXPECT("function-find", type->function.find("find") != nullptr);
    EXPECT("property-all", type->property.find("all") != nullptr);

    #ifdef EIGHTREFL_RTTI_ENABLE
    EXPECT("property-rtti_all", type->property.find("rtti_all") != nullptr);
    #endif // EIGHTREFL_RTTI_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE
