#ifdef EIGHTREFL_DEV_ENABLE
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

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::attribute_t<int>");

    EXPECT("function-find", reflection->function.find("find") != nullptr);
    EXPECT("function-add", reflection->function.find("add") != nullptr);
    EXPECT("property-all", reflection->property.find("all") != nullptr);
}

TEST(TestDev, TestParent)
{
    auto type = eightrefl::dev()->find("eightrefl::parent_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::parent_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::parent_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::parent_t");

    EXPECT("property-name", reflection->property.find("name") != nullptr);
    EXPECT("property-type", reflection->property.find("type") != nullptr);
    EXPECT("property-cast", reflection->property.find("cast") != nullptr);
    EXPECT("property-meta", reflection->property.find("meta") != nullptr);
}

TEST(TestDev, TestFactory)
{
    auto type = eightrefl::dev()->find("eightrefl::factory_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::factory_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::factory_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::factory_t");

    EXPECT("property-name", reflection->property.find("name") != nullptr);
    EXPECT("property-call", reflection->property.find("call") != nullptr);
    EXPECT("property-arguments", reflection->property.find("arguments") != nullptr);
    EXPECT("property-meta", reflection->property.find("meta") != nullptr);
}

TEST(TestDev, TestFunction)
{
    auto type = eightrefl::dev()->find("eightrefl::function_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::function_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::function_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::function_t");

    EXPECT("property-name", reflection->property.find("name") != nullptr);
    EXPECT("property-call", reflection->property.find("call") != nullptr);
    EXPECT("property-arguments", reflection->property.find("arguments") != nullptr);
    EXPECT("property-result", reflection->property.find("result") != nullptr);
    EXPECT("property-pointer", reflection->property.find("pointer") != nullptr);
    EXPECT("property-meta", reflection->property.find("meta") != nullptr);
}

TEST(TestDev, TestProperty)
{
    auto type = eightrefl::dev()->find("eightrefl::property_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::property_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::property_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::property_t");

    EXPECT("property-name", reflection->property.find("name") != nullptr);
    EXPECT("property-type", reflection->property.find("type") != nullptr);
    EXPECT("property-get", reflection->property.find("get") != nullptr);
    EXPECT("property-set", reflection->property.find("set") != nullptr);
    EXPECT("property-context", reflection->property.find("context") != nullptr);
    EXPECT("property-meta", reflection->property.find("meta") != nullptr);
}

TEST(TestDev, TestDeleter)
{
    auto type = eightrefl::dev()->find("eightrefl::deleter_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::deleter_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::deleter_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::deleter_t");

    EXPECT("property-name", reflection->property.find("name") != nullptr);
    EXPECT("property-type", reflection->property.find("call") != nullptr);
    EXPECT("property-meta", reflection->property.find("meta") != nullptr);
}

TEST(TestDev, TestMeta)
{
    auto type = eightrefl::dev()->find("eightrefl::meta_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::meta_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::meta_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::meta_t");

    EXPECT("property-name", reflection->property.find("name") != nullptr);
    EXPECT("property-value", reflection->property.find("value") != nullptr);
    EXPECT("property-meta", reflection->property.find("meta") != nullptr);
}

TEST(TestDev, TestReflection)
{
    auto type = eightrefl::dev()->find("eightrefl::reflection_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::reflection_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::reflection_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::reflection_t");

    EXPECT("property-name", reflection->property.find("name") != nullptr);
    EXPECT("property-parent", reflection->property.find("parent") != nullptr);
    EXPECT("property-function", reflection->property.find("function") != nullptr);
    EXPECT("property-factory", reflection->property.find("factory") != nullptr);
    EXPECT("property-property", reflection->property.find("property") != nullptr);
    EXPECT("property-meta", reflection->property.find("meta") != nullptr);
}

TEST(TestDev, TestInjection)
{
    auto type = eightrefl::dev()->find("eightrefl::injection_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::injection_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::injection_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::injection_t");

    EXPECT("property-name", reflection->property.find("name") != nullptr);
    EXPECT("property-call", reflection->property.find("call") != nullptr);
}

TEST(TestDev, TestType)
{
    auto type = eightrefl::dev()->find("eightrefl::type_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::type_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::type_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::type_t");

    EXPECT("property-name", reflection->property.find("name") != nullptr);
    EXPECT("property-reflection", reflection->property.find("reflection") != nullptr);
    EXPECT("property-registry", reflection->property.find("registry") != nullptr);
    EXPECT("property-size", reflection->property.find("size") != nullptr);
    EXPECT("property-context", reflection->property.find("context") != nullptr);
    EXPECT("property-injection", reflection->property.find("injection") != nullptr);
}

TEST(TestDev, TestRegistry)
{
    auto type = eightrefl::dev()->find("eightrefl::registry_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "eightrefl::registry_t");
    EXPECT("type-size", type->size == sizeof(eightrefl::registry_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "eightrefl::registry_t");

    EXPECT("factory-R()", reflection->factory.find("eightrefl::registry_t()") != nullptr);
    EXPECT("function-find", reflection->function.find("find") != nullptr);
    EXPECT("property-all", reflection->property.find("all") != nullptr);

    #ifdef EIGHTREFL_RTTI_ENABLE
    EXPECT("property-rtti_all", reflection->property.find("rtti_all") != nullptr);
    #endif // EIGHTREFL_RTTI_ENABLE
}
#endif // EIGHTREFL_DEV_ENABLE
