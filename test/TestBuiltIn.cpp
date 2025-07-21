#include <EightreflTestingBase.hpp>

TEST(TestBuiltIn, TestVoid)
{
    auto type = eightrefl::builtin()->find("void");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "void");
    EXPECT("type-size", type->size == 0);
    EXPECT("type-context", type->context == nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "void");
}


TEST(TestBuiltIn, TestNullptrT)
{
    auto type = eightrefl::builtin()->find("std::nullptr_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::nullptr_t");
    EXPECT("type-size", type->size == sizeof(std::nullptr_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::nullptr_t");
}


TEST(TestBuiltIn, TestSizeT)
{
    auto type = eightrefl::builtin()->find("std::size_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::size_t");
    EXPECT("type-size", type->size == sizeof(std::size_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::size_t");

    EXPECT("factory-R()", reflection->factory.find("std::size_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("std::size_t(std::size_t)") != nullptr);
}

TEST(TestBuiltIn, TestPtrDiffT)
{
    auto type = eightrefl::builtin()->find("std::ptrdiff_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::ptrdiff_t");
    EXPECT("type-size", type->size == sizeof(std::ptrdiff_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::ptrdiff_t");

    EXPECT("factory-R()", reflection->factory.find("std::ptrdiff_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("std::ptrdiff_t(std::ptrdiff_t)") != nullptr);
}


TEST(TestBuiltIn, TestBool)
{
    auto type = eightrefl::builtin()->find("bool");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "bool");
    EXPECT("type-size", type->size == sizeof(bool));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "bool");

    EXPECT("factory-R()", reflection->factory.find("bool()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("bool(bool)") != nullptr);
}


TEST(TestBuiltIn, TestChar)
{
    auto type = eightrefl::builtin()->find("char");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "char");
    EXPECT("type-size", type->size == sizeof(char));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "char");

    EXPECT("factory-R()", reflection->factory.find("char()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("char(char)") != nullptr);
}

TEST(TestBuiltIn, TestWChar)
{
    auto type = eightrefl::builtin()->find("wchar_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "wchar_t");
    EXPECT("type-size", type->size == sizeof(wchar_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "wchar_t");

    EXPECT("factory-R()", reflection->factory.find("wchar_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("wchar_t(wchar_t)") != nullptr);
}

#if __cplusplus >= 202002L
TEST(TestBuiltIn, TestChar8)
{
    auto type = eightrefl::builtin()->find("char8_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "char8_t");
    EXPECT("type-size", type->size == sizeof(char8_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "char8_t");

    EXPECT("factory-R()", reflection->factory.find("char8_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("char8_t(char8_t)") != nullptr);
}
#endif // if

TEST(TestBuiltIn, TestChar16)
{
    auto type = eightrefl::builtin()->find("char16_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "char16_t");
    EXPECT("type-size", type->size == sizeof(char16_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "char16_t");

    EXPECT("factory-R()", reflection->factory.find("char16_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("char16_t(char16_t)") != nullptr);
}

TEST(TestBuiltIn, TestChar32)
{
    auto type = eightrefl::builtin()->find("char32_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "char32_t");
    EXPECT("type-size", type->size == sizeof(char32_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "char32_t");

    EXPECT("factory-R()", reflection->factory.find("char32_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("char32_t(char32_t)") != nullptr);
}


TEST(TestBuiltIn, TestSignedChar)
{
    auto type = eightrefl::builtin()->find("signed char");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "signed char");
    EXPECT("type-size", type->size == sizeof(signed char));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "signed char");

    EXPECT("factory-R()", reflection->factory.find("signed char()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("signed char(signed char)") != nullptr);
}

TEST(TestBuiltIn, TestUnsignedChar)
{
    auto type = eightrefl::builtin()->find("unsigned char");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "unsigned char");
    EXPECT("type-size", type->size == sizeof(unsigned char));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "unsigned char");

    EXPECT("factory-R()", reflection->factory.find("unsigned char()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("unsigned char(unsigned char)") != nullptr);
}

TEST(TestBuiltIn, TestInt)
{
    auto type = eightrefl::builtin()->find("int");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "int");
    EXPECT("type-size", type->size == sizeof(int));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "int");

    EXPECT("factory-R()", reflection->factory.find("int()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("int(int)") != nullptr);
}

TEST(TestBuiltIn, TestUnsignedInt)
{
    auto type = eightrefl::builtin()->find("unsigned int");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "unsigned int");
    EXPECT("type-size", type->size == sizeof(unsigned int));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "unsigned int");

    EXPECT("factory-R()", reflection->factory.find("unsigned int()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("unsigned int(unsigned int)") != nullptr);
}

TEST(TestBuiltIn, TestLong)
{
    auto type = eightrefl::builtin()->find("long");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "long");
    EXPECT("type-size", type->size == sizeof(long));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "long");

    EXPECT("factory-R()", reflection->factory.find("long()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("long(long)") != nullptr);
}

TEST(TestBuiltIn, TestUnsignedLong)
{
    auto type = eightrefl::builtin()->find("unsigned long");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "unsigned long");
    EXPECT("type-size", type->size == sizeof(unsigned long));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "unsigned long");

    EXPECT("factory-R()", reflection->factory.find("unsigned long()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("unsigned long(unsigned long)") != nullptr);
}

TEST(TestBuiltIn, TestLongLong)
{
    auto type = eightrefl::builtin()->find("long long");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "long long");
    EXPECT("type-size", type->size == sizeof(long long));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "long long");

    EXPECT("factory-R()", reflection->factory.find("long long()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("long long(long long)") != nullptr);
}

TEST(TestBuiltIn, TestUnsignedLongLong)
{
    auto type = eightrefl::builtin()->find("unsigned long long");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "unsigned long long");
    EXPECT("type-size", type->size == sizeof(unsigned long long));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "unsigned long long");

    EXPECT("factory-R()", reflection->factory.find("unsigned long long()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("unsigned long long(unsigned long long)") != nullptr);
}


TEST(TestBuiltIn, TestFloat)
{
    auto type = eightrefl::builtin()->find("float");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "float");
    EXPECT("type-size", type->size == sizeof(float));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "float");

    EXPECT("factory-R()", reflection->factory.find("float()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("float(float)") != nullptr);
}

TEST(TestBuiltIn, TestDouble)
{
    auto type = eightrefl::builtin()->find("double");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "double");
    EXPECT("type-size", type->size == sizeof(double));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "double");

    EXPECT("factory-R()", reflection->factory.find("double()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("double(double)") != nullptr);
}

TEST(TestBuiltIn, TestLongDouble)
{
    auto type = eightrefl::builtin()->find("long double");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "long double");
    EXPECT("type-size", type->size == sizeof(long double));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "long double");

    EXPECT("factory-R()", reflection->factory.find("long double()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("long double(long double)") != nullptr);
}
