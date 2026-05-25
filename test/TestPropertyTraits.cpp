#include <EightreflTestingBase.hpp>

TEST(TestLibrary, TestPropertyTraits)
{
    {
        using property_traits = xxeightrefl_property_traits<int()>;

        static_assert(std::is_same_v<property_traits::dirty_type, int>);
        static_assert(std::is_same_v<property_traits::type, int>);
        static_assert(std::is_same_v<property_traits::backward_type, void>);
        static_assert(std::is_same_v<property_traits::forward_type, int>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }
    {
        using property_traits = xxeightrefl_property_traits<int const()>;

        static_assert(std::is_same_v<property_traits::dirty_type, int const>);
        static_assert(std::is_same_v<property_traits::type, int const>);
        static_assert(std::is_same_v<property_traits::backward_type, void>);
        static_assert(std::is_same_v<property_traits::forward_type, int const>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }
    {
        using property_traits = xxeightrefl_property_traits<int&()>;

        static_assert(std::is_same_v<property_traits::dirty_type, int&>);
        static_assert(std::is_same_v<property_traits::type, int&>);
        static_assert(std::is_same_v<property_traits::backward_type, void>);
        static_assert(std::is_same_v<property_traits::forward_type, int&>);
        static_assert(std::is_same_v<property_traits::context_type, int*>);
    }
    {
        using property_traits = xxeightrefl_property_traits<int const&()>;

        static_assert(std::is_same_v<property_traits::dirty_type, int const&>);
        static_assert(std::is_same_v<property_traits::type, int const&>);
        static_assert(std::is_same_v<property_traits::backward_type, void>);
        static_assert(std::is_same_v<property_traits::forward_type, int const&>);
        static_assert(std::is_same_v<property_traits::context_type, int*>);
    }
    {
        using property_traits = xxeightrefl_property_traits<int*()>;

        static_assert(std::is_same_v<property_traits::dirty_type, int*>);
        static_assert(std::is_same_v<property_traits::type, int*>);
        static_assert(std::is_same_v<property_traits::backward_type, void>);
        static_assert(std::is_same_v<property_traits::forward_type, int*>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }
    {
        using property_traits = xxeightrefl_property_traits<int const*()>;

        static_assert(std::is_same_v<property_traits::dirty_type, int const*>);
        static_assert(std::is_same_v<property_traits::type, int const*>);
        static_assert(std::is_same_v<property_traits::backward_type, void>);
        static_assert(std::is_same_v<property_traits::forward_type, int const*>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }

    {
        using property_traits = xxeightrefl_property_traits<void(int)>;

        static_assert(std::is_same_v<property_traits::dirty_type, int>);
        static_assert(std::is_same_v<property_traits::type, int>);
        static_assert(std::is_same_v<property_traits::backward_type, int>);
        static_assert(std::is_same_v<property_traits::forward_type, int>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }
    {
        using property_traits = xxeightrefl_property_traits<void(int const)>;

        static_assert(std::is_same_v<property_traits::dirty_type, int>);
        static_assert(std::is_same_v<property_traits::type, int>);
        static_assert(std::is_same_v<property_traits::backward_type, int>);
        static_assert(std::is_same_v<property_traits::forward_type, int>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }
    {
        using property_traits = xxeightrefl_property_traits<void(int&)>;

        static_assert(std::is_same_v<property_traits::dirty_type, int&>);
        static_assert(std::is_same_v<property_traits::type, int&>);
        static_assert(std::is_same_v<property_traits::backward_type, int&>);
        static_assert(std::is_same_v<property_traits::forward_type, int&>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }
    {
        using property_traits = xxeightrefl_property_traits<void(int const&)>;

        static_assert(std::is_same_v<property_traits::dirty_type, int const&>);
        static_assert(std::is_same_v<property_traits::type, int const&>);
        static_assert(std::is_same_v<property_traits::backward_type, int&>);
        static_assert(std::is_same_v<property_traits::forward_type, int const&>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }
    {
        using property_traits = xxeightrefl_property_traits<void(int*)>;

        static_assert(std::is_same_v<property_traits::dirty_type, int*>);
        static_assert(std::is_same_v<property_traits::type, int*>);
        static_assert(std::is_same_v<property_traits::backward_type, int*>);
        static_assert(std::is_same_v<property_traits::forward_type, int*>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }
    {
        using property_traits = xxeightrefl_property_traits<void(int const*)>;

        static_assert(std::is_same_v<property_traits::dirty_type, int const*>);
        static_assert(std::is_same_v<property_traits::type, int const*>);
        static_assert(std::is_same_v<property_traits::backward_type, int*>);
        static_assert(std::is_same_v<property_traits::forward_type, int const*>);
        static_assert(std::is_same_v<property_traits::context_type, void>);
    }
}
