#include <EightreflTestingBase.hpp>

TEST_SPACE()
{

struct TestFunctionStruct
{
    void Function() {}
    void Reference()& {}
    void Const() const {}
    void ConstReference() const& {}

    void Overload()& {}
    void Overload() const& {}
    void Overload(int) {}
    void Overload(int) const {}

    template <typename... Args>
    void Template() {}

    template <typename... Args, typename T>
    void Template(T) {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFunctionStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFunctionStruct)
    FUNCTION(Function)
    FUNCTION(Reference)
    FUNCTION(Const)
    FUNCTION(ConstReference)
    FUNCTION(Overload, void()&)
    FUNCTION(Overload, void() const&)
    FUNCTION(Overload, void(int))
    FUNCTION(Overload, void(int) const)
    FUNCTION(Template, void(float))
    FUNCTION(Template<int>, void())
    FUNCTION(Template<int>, void(float))
    FUNCTION((Template<int, bool>), void(float))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryFunction, TestFunction)
{
    auto type = eightrefl::global()->find("TestFunctionStruct");

    ASSERT("type", type != nullptr);

    {
        auto function = type->function.find("Function");

        ASSERT("function", function != nullptr);
        ASSERT("function-overload", function->all.size() == 1);

        auto function_overload_1 = function->find("void()");

        ASSERT("function-overload-1", function_overload_1 != nullptr);
        EXPECT("function-overload-1-result", function_overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-overload-1-arguments", function_overload_1->arguments.size() == 0);
        EXPECT("function-overload-1-pointer", std::any_cast<void(TestFunctionStruct::*)()>(&function_overload_1->pointer) != nullptr);
    }
    {
        auto reference = type->function.find("Reference");

        ASSERT("function-reference", reference != nullptr);
        ASSERT("function-reference-overload", reference->all.size() == 1);

        auto reference_overload_1 = reference->find("void()&");

        ASSERT("function-reference-overload-1", reference_overload_1 != nullptr);
        EXPECT("function-reference-overload-1-result", reference_overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-reference-overload-1-arguments", reference_overload_1->arguments.size() == 0);
        EXPECT("function-reference-overload-1-pointer", std::any_cast<void(TestFunctionStruct::*)()&>(&reference_overload_1->pointer) != nullptr);
        
    }
    {
        auto const_func = type->function.find("Const");

        ASSERT("function-const", const_func != nullptr);
        ASSERT("function-const-overload", const_func->all.size() == 1);

        auto const_func_overload_1 = const_func->find("void() const");

        ASSERT("function-const-overload-1", const_func_overload_1 != nullptr);
        EXPECT("function-const-overload-1-result", const_func_overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-const-overload-1-arguments", const_func_overload_1->arguments.size() == 0);
        EXPECT("function-const-overload-1-pointer", std::any_cast<void(TestFunctionStruct::*)() const>(&const_func_overload_1->pointer) != nullptr);
    }
    {
        auto const_reference = type->function.find("ConstReference");

        ASSERT("function-const_reference", const_reference != nullptr);
        ASSERT("function-const_reference-overload", const_reference->all.size() == 1);

        auto const_reference_overload_1 = const_reference->find("void() const&");

        ASSERT("function-const_reference-overload-1", const_reference_overload_1 != nullptr);
        EXPECT("function-const_reference-overload-1-result", const_reference_overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-const_reference-overload-1-arguments", const_reference_overload_1->arguments.size() == 0);
        EXPECT("function-const_reference-overload-1-pointer", std::any_cast<void(TestFunctionStruct::*)() const&>(&const_reference_overload_1->pointer) != nullptr);
    }
    {
        auto overload = type->function.find("Overload");

        ASSERT("function-overload", overload != nullptr);
        ASSERT("function-overload", overload->all.size() == 4);

        auto overload_1 = overload->find("void()&");

        ASSERT("function-overload-1", overload_1 != nullptr);
        EXPECT("function-overload-1-result", overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-overload-1-arguments", overload_1->arguments.size() == 0);
        EXPECT("function-overload-1-pointer", std::any_cast<void(TestFunctionStruct::*)()&>(&overload_1->pointer) != nullptr);

        auto overload_2 = overload->find("void() const&");

        ASSERT("function-overload-2", overload_2 != nullptr);
        EXPECT("function-overload-2-result", overload_2->result == eightrefl::builtin()->find("void"));
        EXPECT("function-overload-2-arguments", overload_2->arguments.size() == 0);
        EXPECT("function-overload-2-pointer", std::any_cast<void(TestFunctionStruct::*)() const&>(&overload_2->pointer) != nullptr);

        auto overload_3 = overload->find("void(int)");

        ASSERT("function-overload-3", overload_3 != nullptr);
        EXPECT("function-overload-3-result", overload_3->result == eightrefl::builtin()->find("void"));
        ASSERT("function-overload-3-arguments", overload_3->arguments.size() == 1);
        EXPECT("function-overload-3-arguments-type", overload_3->arguments[0] == eightrefl::builtin()->find("int"));
        EXPECT("function-overload-3-pointer", std::any_cast<void(TestFunctionStruct::*)(int)>(&overload_3->pointer) != nullptr);

        auto overload_4 = overload->find("void(int) const");

        ASSERT("function-overload-4", overload_4 != nullptr);
        EXPECT("function-overload-4-result", overload_4->result == eightrefl::builtin()->find("void"));
        ASSERT("function-overload-4-arguments", overload_4->arguments.size() == 1);
        EXPECT("function-overload-4-arguments-type", overload_4->arguments[0] == eightrefl::builtin()->find("int"));
        EXPECT("function-overload-4-pointer", std::any_cast<void(TestFunctionStruct::*)(int) const>(&overload_4->pointer) != nullptr);
    }
    {
        auto template_ = type->function.find("Template");

        ASSERT("function-template", template_ != nullptr);

        auto template_overload_1 = template_->find("void(float)");

        ASSERT("function-template-overload-1", template_overload_1 != nullptr);
        EXPECT("function-template-overload-1-result", template_overload_1->result == eightrefl::builtin()->find("void"));
        ASSERT("function-template-overload-1-arguments", template_overload_1->arguments.size() == 1);
        EXPECT("function-template-overload-1-arguments-type", template_overload_1->arguments[0] == eightrefl::builtin()->find("float"));
        EXPECT("function-template-overload-1-pointer", std::any_cast<void(TestFunctionStruct::*)(float)>(&template_overload_1->pointer) != nullptr);
    }
    {
        auto template_with_arg = type->function.find("Template<int>");

        ASSERT("function-template_with_arg",template_with_arg != nullptr);
        ASSERT("function-template_with_arg-overload", template_with_arg->all.size() == 2);

        auto template_with_arg_overload_1 = template_with_arg->find("void()");

        ASSERT("function-template_with_arg-overload-1", template_with_arg_overload_1 != nullptr);
        EXPECT("function-template_with_arg-overload-1-result", template_with_arg_overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-template_with_arg-overload-1-arguments", template_with_arg_overload_1->arguments.size() == 0);
        EXPECT("function-template_with_arg-overload-1-pointer", std::any_cast<void(TestFunctionStruct::*)()>(&template_with_arg_overload_1->pointer) != nullptr);

        auto template_with_arg_overload_2 = template_with_arg->find("void(float)");

        ASSERT("function-template_with_arg-overload-2", template_with_arg_overload_2 != nullptr);
        EXPECT("function-template_with_arg-overload-2-result", template_with_arg_overload_2->result == eightrefl::builtin()->find("void"));
        ASSERT("function-template_with_arg-overload-2-arguments", template_with_arg_overload_2->arguments.size() == 1);
        EXPECT("function-template_with_arg-overload-2-arguments-type", template_with_arg_overload_2->arguments[0] == eightrefl::builtin()->find("float"));
        EXPECT("function-template_with_arg-overload-2-pointer", std::any_cast<void(TestFunctionStruct::*)(float)>(&template_with_arg_overload_2->pointer) != nullptr);
    }
    {
        auto template_with_args = type->function.find("Template<int, bool>");

        ASSERT("function-template_with_args", template_with_args != nullptr);
        ASSERT("function-template_with_args-overload", template_with_args->all.size() == 1);

        auto template_with_args_overload_1 = template_with_args->find("void(float)");

        ASSERT("function-template_with_args-overload-1", template_with_args_overload_1 != nullptr);
        EXPECT("function-template_with_args-overload-1-result", template_with_args_overload_1->result == eightrefl::builtin()->find("void"));
        ASSERT("function-template_with_args-overload-1-arguments", template_with_args_overload_1->arguments.size() == 1);
        EXPECT("function-template_with_args-overload-1-arguments-type", template_with_args_overload_1->arguments[0] == eightrefl::builtin()->find("float"));
        EXPECT("function-template_with_args-overload-1-pointer", std::any_cast<void(TestFunctionStruct::*)(float)>(&template_with_args_overload_1->pointer) != nullptr);
    }
}


TEST_SPACE()
{

struct TestStaticFunctionStruct
{
    static void Function() {}
    static void Overload() {}
    static void Overload(int) {}

    template <typename... Args>
    static void Template() {}

    template <typename... Args, typename T>
    static void Template(T) {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestStaticFunctionStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestStaticFunctionStruct)
    FUNCTION(Function)
    FUNCTION(Overload, void())
    FUNCTION(Overload, void(int))
    FUNCTION(Template, void(float))
    FUNCTION(Template<int>, void())
    FUNCTION(Template<int>, void(float))
    FUNCTION((Template<int, bool>), void(float))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryFunction, TestStaticFunction)
{
    auto type = eightrefl::global()->find("TestStaticFunctionStruct");

    ASSERT("type", type != nullptr);

    {
        auto function = type->function.find("Function");

        ASSERT("function", function != nullptr);
        ASSERT("function-overload", function->all.size() == 1);

        auto function_overload_1 = function->find("void()");

        ASSERT("function-overload-1", function_overload_1 != nullptr);
        EXPECT("function-overload-1-result", function_overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-overload-1-arguments", function_overload_1->arguments.size() == 0);
        EXPECT("function-overload-1-pointer", std::any_cast<void(*)()>(&function_overload_1->pointer) != nullptr);
    }
    {
        auto overload = type->function.find("Overload");

        ASSERT("function-overload", overload != nullptr);
        ASSERT("function-overload", overload->all.size() == 2);

        auto overload_1 = overload->find("void()");

        ASSERT("function-overload-1", overload_1 != nullptr);
        EXPECT("function-overload-1-result", overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-overload-1-arguments", overload_1->arguments.size() == 0);
        EXPECT("function-overload-1-pointer", std::any_cast<void(*)()>(&overload_1->pointer) != nullptr);

        auto overload_2 = overload->find("void(int)");

        ASSERT("function-overload-2", overload_2 != nullptr);
        EXPECT("function-overload-2-result", overload_2->result == eightrefl::builtin()->find("void"));
        ASSERT("function-overload-2-arguments", overload_2->arguments.size() == 1);
        EXPECT("function-overload-2-arguments-type", overload_2->arguments[0] == eightrefl::builtin()->find("int"));
        EXPECT("function-overload-2-pointer", std::any_cast<void(*)(int)>(&overload_2->pointer) != nullptr);
    }
    {
        auto template_ = type->function.find("Template");

        ASSERT("function-template", template_ != nullptr);
        ASSERT("function-template-overload-1", template_->all.size() == 1);

        auto template_overload_1 = template_->find("void(float)");

        ASSERT("function-template-overload-1", template_overload_1 != nullptr);
        EXPECT("function-template-overload-1-result", template_overload_1->result == eightrefl::builtin()->find("void"));
        ASSERT("function-template-overload-1-arguments", template_overload_1->arguments.size() == 1);
        EXPECT("function-template-overload-1-arguments-type", template_overload_1->arguments[0] == eightrefl::builtin()->find("float"));
        EXPECT("function-template-overload-1-pointer", std::any_cast<void(*)(float)>(&template_overload_1->pointer) != nullptr);
    }
    {
        auto template_with_arg = type->function.find("Template<int>");

        ASSERT("function-template_with_arg",template_with_arg != nullptr);
        ASSERT("function-template_with_arg-overload", template_with_arg->all.size() == 2);

        auto template_with_arg_overload_1 = template_with_arg->find("void()");

        ASSERT("function-template_with_arg-overload-1", template_with_arg_overload_1 != nullptr);
        EXPECT("function-template_with_arg-overload-1-result", template_with_arg_overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-template_with_arg-overload-1-arguments", template_with_arg_overload_1->arguments.size() == 0);
        EXPECT("function-template_with_arg-overload-1-pointer", std::any_cast<void(*)()>(&template_with_arg_overload_1->pointer) != nullptr);

        auto template_with_arg_overload_2 = template_with_arg->find("void(float)");

        ASSERT("function-template_with_arg-overload-2", template_with_arg_overload_2 != nullptr);
        EXPECT("function-template_with_arg-overload-2-result", template_with_arg_overload_2->result == eightrefl::builtin()->find("void"));
        ASSERT("function-template_with_arg-overload-2-arguments", template_with_arg_overload_2->arguments.size() == 1);
        EXPECT("function-template_with_arg-overload-2-arguments-type", template_with_arg_overload_2->arguments[0] == eightrefl::builtin()->find("float"));
        EXPECT("function-template_with_arg-overload-2-pointer", std::any_cast<void(*)(float)>(&template_with_arg_overload_2->pointer) != nullptr);
    }
    {
        auto template_with_args = type->function.find("Template<int, bool>");

        ASSERT("function-template_with_args", template_with_args != nullptr);
        ASSERT("function-template_with_args-overload", template_with_args->all.size() == 1);

        auto template_with_args_overload_1 = template_with_args->find("void(float)");

        ASSERT("function-template_with_args-overload-1", template_with_args_overload_1 != nullptr);
        EXPECT("function-template_with_args-overload-1-result", template_with_args_overload_1->result == eightrefl::builtin()->find("void"));
        ASSERT("function-template_with_args-overload-1-arguments", template_with_args_overload_1->arguments.size() == 1);
        EXPECT("function-template_with_args-overload-1-arguments-type", template_with_args_overload_1->arguments[0] == eightrefl::builtin()->find("float"));
        EXPECT("function-template_with_args-overload-1-pointer", std::any_cast<void(*)(float)>(&template_with_args_overload_1->pointer) != nullptr);
    }
}


TEST_SPACE()
{

struct TestExternalFunctionStruct {};

void Function() {}
void Overload() {}
void Overload(int) {}

template <typename... Args>
void Template() {}

template <typename... Args, typename T>
void Template(T) {}

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestExternalFunctionStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestExternalFunctionStruct)
    EXTERNAL_FUNCTION(Function)
    EXTERNAL_FUNCTION(Overload, void())
    EXTERNAL_FUNCTION(Overload, void(int))
    EXTERNAL_FUNCTION(Template, void(float))
    EXTERNAL_FUNCTION(Template<int>, void())
    EXTERNAL_FUNCTION(Template<int>, void(float))
    EXTERNAL_FUNCTION((Template<int, bool>), void(float))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryFunction, TestExternalFunction)
{
    auto type = eightrefl::global()->find("TestExternalFunctionStruct");

    ASSERT("type", type != nullptr);

    {
        auto function = type->function.find("Function");

        ASSERT("function", function != nullptr);
        ASSERT("function-overload", function->all.size() == 1);

        auto function_overload_1 = function->find("void()");
    
        ASSERT("function-1", function_overload_1 != nullptr);
        EXPECT("function-1-result", function_overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-1-arguments", function_overload_1->arguments.size() == 0);
        EXPECT("function-1-pointer", std::any_cast<void(*)()>(&function_overload_1->pointer) != nullptr);
    }
    {
        auto overload = type->function.find("Overload");

        ASSERT("function-overload", overload != nullptr);
        ASSERT("function-overload", overload->all.size() == 2);

        auto overload_1 = overload->find("void()");

        ASSERT("function-overload-1", overload_1 != nullptr);
        EXPECT("function-overload-1-result", overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-overload-1-arguments", overload_1->arguments.size() == 0);
        EXPECT("function-overload-1-pointer", std::any_cast<void(*)()>(&overload_1->pointer) != nullptr);

        auto overload_2 = overload->find("void(int)");

        ASSERT("function-overload-2", overload_2 != nullptr);
        EXPECT("function-overload-2-result", overload_2->result == eightrefl::builtin()->find("void"));
        ASSERT("function-overload-2-arguments", overload_2->arguments.size() == 1);
        EXPECT("function-overload-2-arguments-type", overload_2->arguments[0] == eightrefl::builtin()->find("int"));
        EXPECT("function-overload-2-pointer", std::any_cast<void(*)(int)>(&overload_2->pointer) != nullptr);
    }

    {
        auto overload = type->function.find("Overload");

        ASSERT("function-overload", overload != nullptr);
        ASSERT("function-overload", overload->all.size() == 2);

        auto overload_1 = overload->find("void()");

        ASSERT("function-overload-1", overload_1 != nullptr);
        EXPECT("function-overload-1-result", overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-overload-1-arguments", overload_1->arguments.size() == 0);
        EXPECT("function-overload-1-pointer", std::any_cast<void(*)()>(&overload_1->pointer) != nullptr);

        auto overload_2 = overload->find("void(int)");

        ASSERT("function-overload-2", overload_2 != nullptr);
        EXPECT("function-overload-2-result", overload_2->result == eightrefl::builtin()->find("void"));
        ASSERT("function-overload-2-arguments", overload_2->arguments.size() == 1);
        EXPECT("function-overload-2-arguments-type", overload_2->arguments[0] == eightrefl::builtin()->find("int"));
        EXPECT("function-overload-2-pointer", std::any_cast<void(*)(int)>(&overload_2->pointer) != nullptr);
    }
    {
        auto template_ = type->function.find("Template");

        ASSERT("function-template", type->function.find("Template") != nullptr);
        ASSERT("function-template-overload-1", template_ != nullptr && template_->all.size() == 1);

        auto template_overload_1 = template_->find("void(float)");

        ASSERT("function-template-overload-1", template_overload_1 != nullptr);
        EXPECT("function-template-overload-1-result", template_overload_1->result == eightrefl::builtin()->find("void"));
        ASSERT("function-template-overload-1-arguments", template_overload_1->arguments.size() == 1);
        EXPECT("function-template-overload-1-arguments-type", template_overload_1->arguments[0] == eightrefl::builtin()->find("float"));
        EXPECT("function-template-overload-1-pointer", std::any_cast<void(*)(float)>(&template_overload_1->pointer) != nullptr);
    }
    {
        auto template_with_arg = type->function.find("Template<int>");

        ASSERT("function-template_with_arg",template_with_arg != nullptr);
        ASSERT("function-template_with_arg-overload", template_with_arg->all.size() == 2);

        auto template_with_arg_overload_1 = template_with_arg->find("void()");

        ASSERT("function-template_with_arg-overload-1", template_with_arg_overload_1 != nullptr);
        EXPECT("function-template_with_arg-overload-1-result", template_with_arg_overload_1->result == eightrefl::builtin()->find("void"));
        EXPECT("function-template_with_arg-overload-1-arguments", template_with_arg_overload_1->arguments.size() == 0);
        EXPECT("function-template_with_arg-overload-1-pointer", std::any_cast<void(*)()>(&template_with_arg_overload_1->pointer) != nullptr);

        auto template_with_arg_overload_2 = template_with_arg->find("void(float)");

        ASSERT("function-template_with_arg-overload-2", template_with_arg_overload_2 != nullptr);
        EXPECT("function-template_with_arg-overload-2-result", template_with_arg_overload_2->result == eightrefl::builtin()->find("void"));
        ASSERT("function-template_with_arg-overload-2-arguments", template_with_arg_overload_2->arguments.size() == 1);
        EXPECT("function-template_with_arg-overload-2-arguments-type", template_with_arg_overload_2->arguments[0] == eightrefl::builtin()->find("float"));
        EXPECT("function-template_with_arg-overload-2-pointer", std::any_cast<void(*)(float)>(&template_with_arg_overload_2->pointer) != nullptr);
    }
    {
        auto template_with_args = type->function.find("Template<int, bool>");

        ASSERT("function-template_with_args", template_with_args != nullptr);
        ASSERT("function-template_with_args-overload", template_with_args->all.size() == 1);

        auto template_with_args_overload_1 = template_with_args->find("void(float)");

        ASSERT("function-template_with_args-overload-1", template_with_args_overload_1 != nullptr);
        EXPECT("function-template_with_args-overload-1-result", template_with_args_overload_1->result == eightrefl::builtin()->find("void"));
        ASSERT("function-template_with_args-overload-1-arguments", template_with_args_overload_1->arguments.size() == 1);
        EXPECT("function-template_with_args-overload-1-arguments-type", template_with_args_overload_1->arguments[0] == eightrefl::builtin()->find("float"));
        EXPECT("function-template_with_args-overload-1-pointer", std::any_cast<void(*)(float)>(&template_with_args_overload_1->pointer) != nullptr);
    }
}
