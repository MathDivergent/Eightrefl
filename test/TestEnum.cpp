#include <EightreflTestingBase.hpp>

TEST_SPACE()
{

enum TestEnumType { Blue, Green, Red, Alpha };

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestEnumType)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestEnumType)
    META("Blue", TestEnumType::Blue)
    META("Green", TestEnumType::Green)
//  META("Red", TestEnumType::Red) // skip for test
    META("Alpha", Alpha) // since TestEnumType is no scoped enum, we can ommit 'TestEnum::'
REFLECTABLE_INIT()

TEST(TestEnum, TestEnum)
{
    auto type = eightrefl::global()->find("TestEnumType");

    ASSERT("type", type != nullptr);

    EXPECT("meta-1", type->meta.find("Blue") != nullptr);
    EXPECT("meta-2", type->meta.find("Green") != nullptr);
    EXPECT("meta-3", type->meta.find("Alpha") != nullptr);
}


TEST_SPACE()
{

enum class TestScopedEnumType { Up, Down, Size };

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestScopedEnumType)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestScopedEnumType)
    META("Up", TestScopedEnumType::Up)
    META("Down", TestScopedEnumType::Down)
REFLECTABLE_INIT()

TEST(TestEnum, TestScopedEnum)
{
    auto type = eightrefl::global()->find("TestScopedEnumType");

    ASSERT("type", type != nullptr);

    EXPECT("meta-1", type->meta.find("Up") != nullptr);
    EXPECT("meta-2", type->meta.find("Down") != nullptr);
}


struct TestEnumAsStringInjection : eightrefl::injectable_t
{
    eightrefl::type_t* xxtype = nullptr;
    std::vector<std::string> xxenum_as_string;

    TestEnumAsStringInjection(eightrefl::type_t* type) : xxtype(type)
    {
    }
    
    ~TestEnumAsStringInjection()
    {
        std::string const meta_name = "EnumAsString";
        xxtype->meta.add(meta_name, eightrefl::meta_t{ meta_name, xxenum_as_string });
    }

    template <typename ReflectableType>
    void type(eightrefl::type_t& type)
    {
        xxenum_as_string.resize((std::size_t)ReflectableType::Size);
    }

    template <typename ReflectableType, typename MetaType>
    void meta(eightrefl::meta_t& meta)
    {
        auto enumerator = (std::size_t)std::any_cast<MetaType&>(meta.value);
        if (enumerator < (std::size_t)ReflectableType::Size)
        {
            xxenum_as_string[enumerator] = meta.name;
        }
    }
};

REFLECTABLE_DECLARATION(TestEnumAsStringInjection)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestEnumAsStringInjection)
REFLECTABLE_INIT()

TEST(TestEnum, TestEnumAsString)
{
    auto type = eightrefl::global()->find("TestScopedEnumType");

    ASSERT("type", type != nullptr);

    eightrefl::find_or_add_injection<TestScopedEnumType, TestEnumAsStringInjection>(type);

    auto injection = type->injection.find("TestEnumAsStringInjection");

    ASSERT("injection", injection != nullptr);

    {
        auto enum_as_string = std::make_any<TestEnumAsStringInjection>(type);
        injection->call(injection->type->context(enum_as_string));
    }

    auto meta = type->meta.find("EnumAsString");

    ASSERT("enum_as_string", meta != nullptr);

    auto enum_as_string = std::any_cast<std::vector<std::string>>(&meta->value);

    EXPECT("enum_as_string-value", enum_as_string != nullptr && (*enum_as_string)[(std::size_t)TestScopedEnumType::Down] == "Down");
}
