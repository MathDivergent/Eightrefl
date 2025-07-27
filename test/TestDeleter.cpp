#include <EightreflTestingBase.hpp>

TEST_SPACE()
{

struct TestDeleterStruct {};

void SetMetaValue(TestDeleterStruct* object, char value)
{
    *((char*)object+sizeof(TestDeleterStruct)) = value;
}

bool TestMetaValue(TestDeleterStruct* object, char value)
{
    return *((char*)object+sizeof(TestDeleterStruct)) == value;
}

struct TestCustomDeleterStruct
{
    TestCustomDeleterStruct(TestDeleterStruct* object)
    {
        object->~TestDeleterStruct();
        SetMetaValue(object, 'd');
    }
};

template <typename T>
struct TestCustomDeleterStructTemplate
{
    TestCustomDeleterStructTemplate(T* object)
    {
        object->~T();
        SetMetaValue(object, 'd');
    }
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestCustomDeleterStruct)
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, TestCustomDeleterStructTemplate<T>)
    REFLECTABLE_NAME("TestCustomDeleterStructTemplate<" + eightrefl::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, TestCustomDeleterStructTemplate<T>)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestDeleterStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestDeleterStruct)
    DELETER(void(R*))
    DELETER(TestCustomDeleterStruct(R*))
    DELETER(TestCustomDeleterStructTemplate<R>(R*))
REFLECTABLE_INIT()

TEST(TestLibrary, TestDeleter)
{
    auto type = eightrefl::global()->find("TestDeleterStruct");

    ASSERT("type", type != nullptr);

    std::unique_ptr<char[]> memory(new char[sizeof(TestDeleterStruct)+1]);

    {
        auto deleter = type->deleter.find("void(TestDeleterStruct*)");

        ASSERT("deleter", deleter != nullptr);

        auto object = new (memory.get()) TestDeleterStruct();
        SetMetaValue(object, 'v');
        deleter->call(object);

        EXPECT("deleter-call", TestMetaValue(object, 'v'));
    }
    {
        auto custom = type->deleter.find("TestCustomDeleterStruct(TestDeleterStruct*)");

        ASSERT("custom-deleter", custom != nullptr);

        auto object = new (memory.get()) TestDeleterStruct();
        SetMetaValue(object, 'c');
        custom->call(object);

        EXPECT("custom-deleter-call", TestMetaValue(object, 'd'));
    }
    {
        auto custom = type->deleter.find("TestCustomDeleterStructTemplate<TestDeleterStruct>(TestDeleterStruct*)");

        ASSERT("custom-deleter-template", custom != nullptr);

        auto object = new (memory.get()) TestDeleterStruct();
        SetMetaValue(object, 'c');
        custom->call(object);

        EXPECT("custom-deleter-template-call", TestMetaValue(object, 'd'));
    }
}
