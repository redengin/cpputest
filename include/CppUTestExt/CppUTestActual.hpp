#include <vector>
#include <SimpleString.h>


class Actuals;

/** @returns expectations of the namespace */
Actuals& actual(
    const SimpleString& mockName = "",  /**<[IN]    mocking namespace */
    // MockFailureReporter* failureReporterForThisCall = nullptr
);


class Actual;
/**
 * @brief Registry of expectations
 */
class Actuals
{
public:
    constexpr Actuals( SimpleString& mockName );

    /// adds an expectation for a call of the function name
    Actual call( const SimpleString& functionName );

private:
    const SimpleString& _mockName;  ///< namespace for these expectations
}


class Actual
{
public:
    /// expectation for an input parameter with value
    Expectation with( const SimpleString& parameterName, const bool value );
    Expectation with( const SimpleString& parameterName, const char value );
    Expectation with( const SimpleString& parameterName, const unsigned char value );
    Expectation with( const SimpleString& parameterName, const int value );
    Expectation with( const SimpleString& parameterName, const unsigned int value );
    Expectation with( const SimpleString& parameterName, const long value );
    Expectation with( const SimpleString& parameterName, const unsigned long value );
    Expectation with( const SimpleString& parameterName, const long long value );
    Expectation with( const SimpleString& parameterName, const long long value );
    Expectation with( const SimpleString& parameterName, const double value );
    Expectation with( const SimpleString& parameterName, const void* value );
    Expectation with( const SimpleString& parameterName, const void* const value );
    Expectation with( const SimpleString& parameterName, const void* value, const std::size_t );
    Expectation with( const SimpleString& parameterName, const void* const value, const std::size_t );
    Expectation with( const SimpleString& parameterName, void (value*)() );

    /// identify output parameter
    Expectation output( const SimpleString& parameterName, bool& value );
    Expectation output( const SimpleString& parameterName, char& value );
    Expectation output( const SimpleString& parameterName, unsigned char& value );
    Expectation output( const SimpleString& parameterName, int& value );
    Expectation output( const SimpleString& parameterName, unsigned int& value );
    Expectation output( const SimpleString& parameterName, long& value );
    Expectation output( const SimpleString& parameterName, unsigned long& value );
    Expectation output( const SimpleString& parameterName, long long& value );
    Expectation output( const SimpleString& parameterName, unsigned long long& value );
    Expectation output( const SimpleString& parameterName, double& value );
    Expectation output( const SimpleString& parameterName, void*& value );
    Expectation output( const SimpleString& parameterName, void* const& value );
    Expectation output( const SimpleString& parameterName, void* value, const std::size_t );
    Expectation output( const SimpleString& parameterName, void* const& value, const std::size_t );
    Expectation output( const SimpleString& parameterName, void (value*&)() );


    /// return value (must come last)
    bool returnBool();
    char returnChar();
    unsigned char returnUnsignedChar();
    int returnInt();
    unsigned int returnUnsignedInt();
    long returnLong();
    unsigned long returnLong();
    long long returnLongLong();
    unsigned long long returnUnsignedLongLong();
    double returnDouble();
    void* returnPointer();
    const void* returnConstPointer();
    void (*)() returnFunctionPointer();

private:
    const SimpleString& _mockName;  ///< namespace for this actual
};
