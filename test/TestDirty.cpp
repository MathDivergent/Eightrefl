#include <EightreflTestingBase.hpp>

#include <cstdint> // int32_t

TEST_SPACE()
{

template <typename T>
struct TestContainerWithIteratorDirty
{
    struct Iterator {};

    TestContainerWithIteratorDirty(Iterator, Iterator) {}
    void Insert(Iterator, T) {}
    std::int32_t Size() const { return 0; }

    Iterator* Head = nullptr;
};

} // TEST_SPACE

REFLECTABLE_DIRTY(Test_std_int32_t, std::int32_t)

REFLECTABLE_DECLARATION(Test_std_int32_t)
    REFLECTABLE_NAME("std::int32_t")
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(Test_std_int32_t)
    FACTORY(Test_std_int32_t())
    FACTORY(R(R)) // same as Test_std_int32_t(Test_std_int32_t)
REFLECTABLE_INIT()

// will not compile!
// TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, TestContainerWithIteratorDirty<T>::Iterator)
//     REFLECTABLE_NAME(eightrefl::name_of<TestContainerWithIteratorDirty<T>>() + "::Iterator")
// REFLECTABLE_DECLARATION_INIT()

// TEMPLATE_REFLECTABLE(template <typename T>, TestContainerWithIteratorDirty<T>::Iterator)
// REFLECTABLE_INIT()

TEMPLATE_REFLECTABLE_DIRTY
(
    template <typename T>, TestContainerWithIteratorDirty_Iterator,
    TestContainerWithIteratorDirty_Iterator<T>, typename TestContainerWithIteratorDirty<T>::Iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, TestContainerWithIteratorDirty_Iterator<T>)
    REFLECTABLE_NAME(eightrefl::name_of<TestContainerWithIteratorDirty<T>>() + "::Iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, TestContainerWithIteratorDirty_Iterator<T>)
REFLECTABLE_INIT()

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, TestContainerWithIteratorDirty<T>)
    REFLECTABLE_NAME("TestContainerWithIteratorDirty<" + eightrefl::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, TestContainerWithIteratorDirty<T>)
    FUNCTION(Insert, void(TestContainerWithIteratorDirty_Iterator<T>, T))
    PROPERTY(Head, TestContainerWithIteratorDirty_Iterator<T>*)
    FACTORY(R(TestContainerWithIteratorDirty_Iterator<T>, TestContainerWithIteratorDirty_Iterator<T>))
    FUNCTION(Size, Test_std_int32_t() const)
REFLECTABLE_INIT()

TEST(TestLibrary, TestDirty)
{
    eightrefl::reflectable<TestContainerWithIteratorDirty<int>>();

    auto type = eightrefl::global()->find("TestContainerWithIteratorDirty<int>");

    ASSERT("type", type != nullptr);

    auto function0 = type->function.find("Insert");

    EXPECT("function0",
        function0 != nullptr &&
        function0->find("void(TestContainerWithIteratorDirty<int>::Iterator, int)") != nullptr);

    auto function1 = type->function.find("Size");

    EXPECT("function1",
        function1 != nullptr &&
        function1->find("std::int32_t() const") != nullptr);

    auto property = type->property.find("Head");

    EXPECT("property",
        property != nullptr &&
        property->type != nullptr &&
        property->type->name == "TestContainerWithIteratorDirty<int>::Iterator*");

    auto factory = type->factory.find("TestContainerWithIteratorDirty<int>(TestContainerWithIteratorDirty<int>::Iterator, TestContainerWithIteratorDirty<int>::Iterator)");

    EXPECT("factory", factory != nullptr);
}
