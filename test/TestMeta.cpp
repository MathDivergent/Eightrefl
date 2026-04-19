#include <EightreflTestingBase.hpp>

#include <vector> // vector
#include <string> // string

TEST_SPACE()
{

struct TestParentMetaStruct {};

struct TestMetaStruct : TestParentMetaStruct
{
    TestMetaStruct() {}
    static int Function() { return 0; }
    void Function([[maybe_unused]] double value) {}
    float Property = 0.f;
    int Constant = 0;

    inline static char* TestDescriptor = nullptr;
};

int TestMetaStructPropertyCast(float) { return 0; }

namespace TestMetaStructFlags
{

enum Type : long { Abstract, Internal, Serializable };

} // TestMetaStructFlags

struct TestMetaStructConfigs
{
    bool const IsVisible = false;
    float LifeTime = -1.f;
    char const* Name = "UNKNOWN";
};

std::string sMetaName = "Descriptors";
void* TestDescriptorReadOnly = nullptr;

struct FunctionHandlerStruct
{
    void operator()(double) {}

    bool IsAsync = true;
};

FunctionHandlerStruct FunctionHandler{ false };

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestParentMetaStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentMetaStruct)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestMetaStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestMetaStruct)
    META("DisplayName", "Meta Struct")
    META("Configs", TestMetaStructConfigs{ true, 100.f })
    META(sMetaName, std::vector<void*>{ &R::TestDescriptor, &TestDescriptorReadOnly })

    PARENT(TestParentMetaStruct) META("Hidden", true)

    FACTORY(R()) META("ConstructionType", std::string("PostLoad"))

    FUNCTION(Function, int()) META("MinValue", -1) META("MaxValue", 10) META("static", true)
    FUNCTION(Function, void(double)) META("Handler", FunctionHandler)

    PROPERTY(Property) META("Cast", &TestMetaStructPropertyCast)
    META("Serializable") // meta without value
    META("Flags", TestMetaStructFlags::Serializable | TestMetaStructFlags::Internal)

    PROPERTY(Constant) META("Mutable", true)
REFLECTABLE_INIT()

TEST(TestLibrary, TestMeta)
{
    auto type = eightrefl::global()->find("TestMetaStruct");

    ASSERT("type", type != nullptr);

    {
        auto meta0 = type->meta.find("DisplayName");

        ASSERT("type-meta0", meta0 != nullptr);

        auto value = std::any_cast<char const*>(&meta0->value);

        EXPECT("type-meta0-value", value != nullptr && std::string(*value) == "Meta Struct");
    }
    {
        auto meta1 = type->meta.find("Configs");

        ASSERT("type-meta1", meta1 != nullptr);

        auto value = std::any_cast<TestMetaStructConfigs>(&meta1->value);

        EXPECT("type-meta1-value", value != nullptr && value->IsVisible == true && value->LifeTime == 100.f);
    }
    {
        auto meta2 = type->meta.find(sMetaName);

        ASSERT("type-meta2", meta2 != nullptr);

        auto value = std::any_cast<std::vector<void*>>(&meta2->value);

        EXPECT("type-meta2-value", value != nullptr && value->size() == 2 && (*value)[0] == &TestMetaStruct::TestDescriptor && (*value)[1] == &TestDescriptorReadOnly);
    }

    auto parent = type->parent.find("TestParentMetaStruct");

    ASSERT("parent", parent != nullptr);

    {
        auto meta0 = parent->meta.find("Hidden");

        ASSERT("parent-meta0", meta0 != nullptr);

        auto value = std::any_cast<bool>(&meta0->value);

        EXPECT("parent-meta0-value-init", value != nullptr && *value == true);
    }

    auto factory = type->factory.find("TestMetaStruct()");

    ASSERT("factory", factory != nullptr);

    {
        auto meta0 = factory->meta.find("ConstructionType");

        ASSERT("factory-meta0", meta0 != nullptr);

        auto value = std::any_cast<std::string>(&meta0->value);

        EXPECT("factory-meta0-value", value != nullptr && *value == "PostLoad");
    }

    auto overloads = type->function.find("Function");

    ASSERT("overloads", overloads != nullptr);

    auto function0 = overloads->find("int()");

    ASSERT("function0", function0 != nullptr);

    {
        auto meta0 = function0->meta.find("MinValue");

        ASSERT("function0-meta0", meta0 != nullptr);

        auto value = std::any_cast<int>(&meta0->value);

        EXPECT("function0-meta0-value", value != nullptr && *value == -1);
    }
    {
        auto meta1 = function0->meta.find("MaxValue");

        ASSERT("function0-meta1", meta1 != nullptr);

        auto value = std::any_cast<int>(&meta1->value);

        EXPECT("function0-meta1-value", value != nullptr && *value == 10);
    }
    {
        auto meta2 = function0->meta.find("static");

        ASSERT("function0-meta2", meta2 != nullptr);

        auto value = std::any_cast<bool>(&meta2->value);

        EXPECT("function0-meta2-value", value != nullptr && *value == true);
    }

    auto function1 = overloads->find("void(double)");

    ASSERT("function1", function1 != nullptr);

    {
        auto meta0 = function1->meta.find("Handler");

        ASSERT("function1-meta0", meta0 != nullptr);

        auto value = std::any_cast<FunctionHandlerStruct>(&meta0->value);

        EXPECT("function1-meta0-value", value != nullptr && value->IsAsync == FunctionHandler.IsAsync);
    }

    auto property0 = type->property.find("Property");

    ASSERT("property0", property0 != nullptr);

    {
        using meta0_type = decltype(&TestMetaStructPropertyCast);

        auto meta0 = property0->meta.find("Cast");

        ASSERT("property0-meta0", meta0 != nullptr);

        auto value = std::any_cast<meta0_type>(&meta0->value);

        EXPECT("property0-meta0-value", value != nullptr && *value == &TestMetaStructPropertyCast);
    }
    {
        auto meta1 = property0->meta.find("Serializable");

        ASSERT("property0-meta1", meta1 != nullptr);
        EXPECT("property0-meta1-value", !meta1->value.has_value());
    }
    {
        auto meta2 = property0->meta.find("Flags");

        ASSERT("property0-meta2", meta2 != nullptr);

        auto value = std::any_cast<long>(&meta2->value);

        EXPECT("property0-meta2-value", value != nullptr && *value == (TestMetaStructFlags::Serializable | TestMetaStructFlags::Internal));
    }

    auto property1 = type->property.find("Constant");

    ASSERT("property1", property1 != nullptr);

    {
        auto meta0 = property1->meta.find("Mutable");

        ASSERT("meta0", meta0 != nullptr);

        auto value = std::any_cast<bool>(&meta0->value);

        EXPECT("Mutable", value != nullptr && *value == true);
    }
}
