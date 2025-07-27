#include <EightreflTestingBase.hpp>

TEST_SPACE()
{

struct TestFactoryStruct {};

struct TestCustomFactoryStruct
{
    TestCustomFactoryStruct()
    {
        result = new TestFactoryStruct();
    }

    void* result = nullptr;
};

template <typename T>
struct TestCustomFactoryStructTemplate
{
    TestCustomFactoryStructTemplate()
    {
        result = new T();
    }
    
    T* result = nullptr;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestCustomFactoryStruct)
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, TestCustomFactoryStructTemplate<T>)
    REFLECTABLE_NAME("TestCustomFactoryStructTemplate<" + eightrefl::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, TestCustomFactoryStructTemplate<T>)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestFactoryStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFactoryStruct)
    FACTORY(R())
    FACTORY(TestCustomFactoryStruct())
    FACTORY(TestCustomFactoryStructTemplate<int>())
REFLECTABLE_INIT()

TEST(TestLibrary, TestFactoryStruct)
{
    auto type = eightrefl::global()->find("TestFactoryStruct");

    ASSERT("type", type != nullptr);

    {
        EXPECT("factory", type->factory.find("TestFactoryStruct()") != nullptr);
    }
    {
        auto custom = type->factory.find("TestCustomFactoryStruct()");
    
        EXPECT("custom-factory", custom != nullptr);
    
        auto object = custom->call({});
        auto object_ptr = std::any_cast<TestCustomFactoryStruct>(&object);
    
        EXPECT("custom-factory-object", object_ptr != nullptr && object_ptr->result);
    }
    {
        auto custom = type->factory.find("TestCustomFactoryStructTemplate<int>()");
    
        EXPECT("custom-factory-template", custom != nullptr);
    
        auto object = custom->call({});
        auto object_ptr = std::any_cast<TestCustomFactoryStructTemplate<int>>(&object);
    
        EXPECT("custom-factory-template-object", object_ptr != nullptr && object_ptr->result);
    }
}
