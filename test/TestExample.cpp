#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/string.hpp>

TEST_SPACE()
{

struct TestExampleStruct
{
    TestExampleStruct() {}

    int Function(const std::string& data) { return -1; }
    int Property = 0;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestExampleStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestExampleStruct)
    FACTORY(R())
    FUNCTION(Function)
    PROPERTY(Property)
REFLECTABLE_INIT()

TEST(TestExample, TestSimple)
{
    eightrefl::type_t* type = eightrefl::global()->find("TestExampleStruct");

    ASSERT("type", type != nullptr);

    eightrefl::reflection_t* reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    eightrefl::factory_t* factory = reflection->factory.find("TestExampleStruct()");

    ASSERT("factory", factory != nullptr);

    eightrefl::attribute_t<eightrefl::function_t>* function_overloads = reflection->function.find("Function");

    ASSERT("function-overloads", function_overloads != nullptr);

    eightrefl::function_t* function = function_overloads->find("int(std::string const&)");

    ASSERT("function", function != nullptr);

    eightrefl::property_t* property = reflection->property.find("Property");

    ASSERT("property", property != nullptr);

    std::any object = factory->call({});
    std::any object_context = type->context(object);

    std::string string = "text";
    std::any string_context = &string;

    std::any result = function->call(object_context, { string_context });

    property->set(object_context, result);

    std::any property_context = property->context(object_context);

    EXPECT("result", *std::any_cast<int*>(property_context) == std::any_cast<int>(result));
}
