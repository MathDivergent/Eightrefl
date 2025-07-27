#include <EightreflTestingBase.hpp>

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Standard/string.hpp>
#endif // EIGHTREFL_STANDARD_ENABLE

TEST_SPACE()
{

struct TestExampleStruct
{
    TestExampleStruct() {}

    #ifdef EIGHTREFL_STANDARD_ENABLE
    int Function(std::string const& data) { return -1; }
    #else
    int Function(char const* data) { return -1; }
    #endif // EIGHTREFL_STANDARD_ENABLE

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

    eightrefl::factory_t* factory = type->factory.find("TestExampleStruct()");

    ASSERT("factory", factory != nullptr);

    eightrefl::attribute_t<eightrefl::function_t>* function_overloads = type->function.find("Function");

    ASSERT("function-overloads", function_overloads != nullptr);

    #ifdef EIGHTREFL_STANDARD_ENABLE
    eightrefl::function_t* function = function_overloads->find("int(std::string const&)");
    #else
    eightrefl::function_t* function = function_overloads->find("int(char const*)");
    #endif // EIGHTREFL_STANDARD_ENABLE

    ASSERT("function", function != nullptr);

    eightrefl::property_t* property = type->property.find("Property");

    ASSERT("property", property != nullptr);

    std::any object = factory->call({});
    std::any object_context = type->context(object);

    #ifdef EIGHTREFL_STANDARD_ENABLE
    std::string string = "text";
    std::any string_context = &string;
    #else
    char const* string = "text";
    std::any string_context = const_cast<char*>(string); // safe
    #endif // EIGHTREFL_STANDARD_ENABLE

    std::any result = function->call(object_context, { string_context });

    property->set(object_context, result);

    std::any property_context = property->context(object_context);

    EXPECT("result", *std::any_cast<int*>(property_context) == std::any_cast<int>(result));
}
