#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/complex.hpp>

TEST(TestBuiltin, TestComplex)
{
    eightrefl::reflectable<std::complex<float>>();

    auto type = eightrefl::standard()->find("std::complex<float>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::complex<float>");
    EXPECT("type-size", type->size == sizeof(std::complex<float>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::complex<float>()") != nullptr);
    EXPECT("factory-R(value_type, value_type)", type->factory.find("std::complex<float>(float, float)") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::complex<float>(std::complex<float> const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);
    EXPECT("function-operator+=", type->function.find("operator+=") != nullptr);
    EXPECT("function-operator-=", type->function.find("operator-=") != nullptr);
    EXPECT("function-operator*=", type->function.find("operator*=") != nullptr);
    EXPECT("function-operator/=", type->function.find("operator/=") != nullptr);

    EXPECT("property-real", type->property.find("real") != nullptr);
    EXPECT("property-imag", type->property.find("imag") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
