#include <EightreflTestingBase.hpp>

#include <cstdint>

TEST_SPACE()
{

struct TestBitfieldStruct
{
    TestBitfieldStruct(bool flag0, char meta) : bFlag0(flag0), Meta(meta) {}

    std::uint8_t bFlag0 : 1;
    std::uint8_t Meta : 6;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestBitfieldStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestBitfieldStruct)
    FACTORY(R(bool, char))
    BITFIELD(bFlag0)
    BITFIELD(Meta)
REFLECTABLE_INIT()

TEST(TestLibrary, TestBitfield)
{
    auto type = eightrefl::global()->find("TestBitfieldStruct");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "TestBitfieldStruct");
    EXPECT("type-size", type->size == sizeof(TestBitfieldStruct));
    EXPECT("type-context", type->context != nullptr);

    auto factory = type->factory.find("TestBitfieldStruct(bool, char)");

    bool flag0 = true;
    char meta = '#';

    auto object = factory->call({flag0, meta});
    auto object_context = type->context(object);

    auto property0 = type->property.find("bFlag0");
    ASSERT("property0", property0 != nullptr);
    EXPECT("property0-context", property0->context == nullptr);
    EXPECT("property0-pointer", !property0->pointer.first.has_value() && !property0->pointer.second.has_value());
    ASSERT("property0-get", property0->get != nullptr);

    {
        std::any value;
        property0->get(object_context, value);

        auto value_ptr = std::any_cast<std::uint8_t>(&value);
        ASSERT("property0-get-value", value_ptr != nullptr && *value_ptr == flag0);
    }

    auto property1 = type->property.find("Meta");
    ASSERT("property1", property1 != nullptr);
    EXPECT("property1-context", property1->context == nullptr);
    EXPECT("property1-pointer", !property1->pointer.first.has_value() && !property1->pointer.second.has_value());
    ASSERT("property1-get", property1->get != nullptr);
    ASSERT("property1-set", property1->set != nullptr);

    {
        std::any value;
        property1->get(object_context, value);

        auto value_ptr = std::any_cast<std::uint8_t>(&value);
        EXPECT("property1-get-value", value_ptr != nullptr && *value_ptr == meta);

        //char other_meta = '*'; // we get bad_any_cast exception, if type not std::uint8_t
        std::uint8_t other_meta = '*';
        property1->set(object_context, other_meta);

        std::any other_value;
        property1->get(object_context, other_value);

        auto other_value_ptr = std::any_cast<std::uint8_t>(&other_value);
        EXPECT("property1-get-other_value", other_value_ptr != nullptr && *other_value_ptr == other_meta);
    }

    {
        std::any value;
        property0->get(object_context, value);

        auto value_ptr = std::any_cast<std::uint8_t>(&value);
        EXPECT("property0-get-poset_value", value_ptr != nullptr && *value_ptr == flag0);
    }
}
