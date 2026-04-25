#include <EightreflTestingBase.hpp>
#include <Eightrefl/Utility.hpp>

TEST(TestLibrary, TestBackward)
{
    {
        int glvalue = 8;

        std::any as_any = eightrefl::backward(glvalue);
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("glvalue", as_value == &glvalue && *as_value == 8);
    }
    {
        int glvalue = 8;

        std::any as_any = eightrefl::backward(std::move(glvalue));

        EXPECT("xvalue", std::any_cast<int>(as_any) == 8);
    }
    {
        std::any as_any = eightrefl::backward(8);

        EXPECT("prvalue", std::any_cast<int>(as_any) == 8);
    }

    {
        int glvalue = 8;
        int* glvalue_pointer = &glvalue;

        std::any as_any = eightrefl::backward(glvalue_pointer);
        int** as_value = std::any_cast<int**>(as_any);

        EXPECT("glvalue-pointer", as_value == &glvalue_pointer && *as_value == &glvalue && **as_value == 8);
    }
    {
        int glvalue = 8;
        int* glvalue_pointer = &glvalue;

        std::any as_any = eightrefl::backward(std::move(glvalue_pointer));
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("xvalue-pointer", as_value == &glvalue && *as_value == 8);
    }
    {
        int glvalue = 8;

        std::any as_any = eightrefl::backward(&glvalue);
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("prvalue-pointer", as_value == &glvalue && *as_value == 8);
    }

    {
        int const const_glvalue = 8;
        int const* const_glvalue_pointer = &const_glvalue;

        std::any as_any = eightrefl::backward(const_glvalue_pointer);
        int const** as_value = std::any_cast<int const**>(as_any);

        EXPECT("const-glvalue-pointer", as_value == &const_glvalue_pointer && *as_value == &const_glvalue && **as_value == 8);
    }
    {
        int const const_glvalue = 8;
        int const* const_glvalue_pointer = &const_glvalue;

        std::any as_any = eightrefl::backward(std::move(const_glvalue_pointer));
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("const-xvalue-pointer", as_value == &const_glvalue && *as_value == 8);
    }
    {
        int const const_glvalue = 8;

        std::any as_any = eightrefl::backward(static_cast<int const*>(&const_glvalue));
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("const-prvalue-pointer", as_value == &const_glvalue && *as_value == 8);
    }

    {
        int glvalue = 8;
        int& glvalue_reference = glvalue;

        std::any as_any = eightrefl::backward(glvalue_reference);
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("glvalue-reference", as_value == &glvalue && *as_value == 8);
    }
    {
        int const const_glvalue = 8;
        int const& const_glvalue_reference = const_glvalue;

        std::any as_any = eightrefl::backward(const_glvalue_reference);
        int* as_value = std::any_cast<int*>(as_any);

        EXPECT("const-glvalue-reference", as_value == &const_glvalue && *as_value == 8);
    }

    {
        int glvalue = 8;
        int* glvalue_pointer = &glvalue;
        int*& glvalue_pointer_reference = glvalue_pointer;

        std::any as_any = eightrefl::backward(glvalue_pointer_reference);
        int** as_value = std::any_cast<int**>(as_any);

        EXPECT("glvalue-pointer-reference", as_value == &glvalue_pointer && *as_value == &glvalue && **as_value == 8);
    }
    {
        int const const_glvalue = 8;
        int const* const_glvalue_pointer = &const_glvalue;
        int const*& const_glvalue_pointer_reference = const_glvalue_pointer;

        std::any as_any = eightrefl::backward(const_glvalue_pointer_reference);
        int const** as_value = std::any_cast<int const**>(as_any);

        EXPECT("const-glvalue-pointer-reference", as_value == &const_glvalue_pointer && *as_value == &const_glvalue && **as_value == 8);
    }

    {
        int glvalue[4] = {8, 8, 8, 8};
        int (*glvalue_pointer)[4] = &glvalue;

        std::any as_any = eightrefl::backward(glvalue_pointer);
        int (**as_value)[4] = std::any_cast<int(**)[4]>(as_any);

        EXPECT("glvalue-array-glvalue-pointer", as_value == &glvalue_pointer && *as_value == &glvalue);
    }
    {
        int glvalue[4] = {8, 8, 8, 8};
        int (*glvalue_pointer)[4] = &glvalue;

        std::any as_any = eightrefl::backward(std::move(glvalue_pointer));
        int (*as_value)[4] = std::any_cast<int(*)[4]>(as_any);

        EXPECT("glvalue-array-xvalue-pointer", as_value == &glvalue);
    }
    {
        int glvalue[4] = {8, 8, 8, 8};

        std::any as_any = eightrefl::backward(&glvalue);
        int (*as_value)[4] = std::any_cast<int(*)[4]>(as_any);

        EXPECT("glvalue-array-prvalue-pointer", as_value == &glvalue);
    }

    {
        int glvalue[4] = {8, 8, 8, 8};
        int (&glvalue_reference)[4] = glvalue;

        std::any as_any = eightrefl::backward(glvalue_reference);
        int (*as_value)[4] = std::any_cast<int(*)[4]>(as_any);

        EXPECT("glvalue-array-reference", as_value == &glvalue);
    }
    {
        int const glvalue[4] = {8, 8, 8, 8};
        int const (&glvalue_reference)[4] = glvalue;

        std::any as_any = eightrefl::backward(glvalue_reference);
        int (*as_value)[4] = std::any_cast<int(*)[4]>(as_any);

        EXPECT("const-glvalue-array-reference", as_value == &glvalue);
    }
}

TEST(TestLibrary, TestForward)
{
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int*>(&glvalue);
        int& as_value = eightrefl::forward<int&>(as_any);

        EXPECT("glvalue", &as_value == &glvalue && as_value == 8);
    }
    {
        int glvalue = 8;

        // will not work, since reflectable reference storing as mutable
        // std::any as_any = std::make_any<int const*>(&glvalue);
        std::any as_any = std::make_any<int*>(&glvalue);
        int const& as_value = eightrefl::forward<int const&>(as_any);
    
        EXPECT("const-glvalue", &as_value == &glvalue && as_value == 8);
    }
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int*>(&glvalue);
        int* as_value = eightrefl::forward<int*>(as_any);

        EXPECT("glvalue-pointer", as_value == &glvalue && *as_value == 8);
    }
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int*>(&glvalue);
        int const* as_value = eightrefl::forward<int const*>(as_any);

        EXPECT("const-glvalue-pointer", as_value == &glvalue && *as_value == 8);
    }
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int>(glvalue);
        int as_value = eightrefl::forward<int>(as_any);

        EXPECT("xlvalue", as_value == 8);
    }
    {
        int glvalue = 8;

        std::any as_any = std::make_any<int>(glvalue);
        const int as_value = eightrefl::forward<int const>(as_any);

        EXPECT("const-xlvalue", as_value == 8);
    }

    // same as xvalue
    {
        std::any as_any = std::make_any<int>(8);
        int as_value = eightrefl::forward<int>(as_any);

        EXPECT("prvalue", as_value == 8);
    }
    {
        std::any as_any = std::make_any<int>(8);
        int as_value = eightrefl::forward<int const>(as_any);

        EXPECT("const-prvalue", as_value == 8);
    }
}

TEST(TestLibrary, TestBackwardForward)
{
    {
        int glvalue = 8;
        std::any as_any = eightrefl::backward(glvalue);
        int& as_value = eightrefl::forward<int&>(as_any);

        EXPECT("glvalue", &as_value == &glvalue && as_value == 8);
    }
    {
        int glvalue = 8;
        std::any as_any = eightrefl::backward(std::move(glvalue));
        int as_value = eightrefl::forward<int>(as_any);

        EXPECT("xlvalue", as_value == 8);
    }
    {
        std::any as_any = eightrefl::backward(8);
        int as_value = eightrefl::forward<int>(as_any);

        EXPECT("prvalue", as_value == 8);
    }
}
