
#include <vector>
#include <SimpleString.h>



class Expectations;

/** @returns expectations of the namespace */
Expectations& expect(
    const SimpleString& mockName = "",  /**<[IN]    mocking namespace */
    // MockFailureReporter* failureReporterForThisCall = nullptr
);


class Expectation;

/**
 * @brief Registry of expectations
 */
class Expectations
{
public:
    constexpr Expectations( SimpleString& mockName );

    /// whether to FAIL when a mocked call has no matching expectation
    void requireExpectation( const bool = false );


    /// adds an expectation for a call of the function name
    Expectation call( const SimpleString& functionName );
    /// adds an expectation for a calls matched by comparator
    Expectation call( const CallComparator& );

private:
    const SimpleString& _mockName;  ///< namespace for these expectations
}


class IModel;
class Expectation
{
public:
    /// expectation of position in sequence
    Expectation inSequence( Sequence& );


    /// expectation for an input parameter with value
    Expectation with( const SimpleString& parameterName, const bool value );
    Expectation with( const SimpleString& parameterName, const char value );
    Expectation with( const SimpleString& parameterName, const unsigned char value );
    Expectation with( const SimpleString& parameterName, const int value );
    Expectation with( const SimpleString& parameterName, const unsigned int value );
    Expectation with( const SimpleString& parameterName, const long value );
    Expectation with( const SimpleString& parameterName, const unsigned long value );
    Expectation with( const SimpleString& parameterName, const long long value );
    Expectation with( const SimpleString& parameterName, const unsigned long long value );
    Expectation with( const SimpleString& parameterName, const double value );
    Expectation with( const SimpleString& parameterName, const void* value );
    Expectation with( const SimpleString& parameterName, const void* const value );
    Expectation with( const SimpleString& parameterName, const void* value, const std::size_t );
    Expectation with( const SimpleString& parameterName, const void* const value, const std::size_t );
    Expectation with( const SimpleString& parameterName, void (value*)() );
    /// expectation for an input parameter matched by comparator with value
    Expectation with( const ParameterComparator&, const bool value );
    Expectation with( const ParameterComparator&, const char value );
    Expectation with( const ParameterComparator&, const unsigned char value );
    Expectation with( const ParameterComparator&, const int value );
    Expectation with( const ParameterComparator&, const unsigned int value );
    Expectation with( const ParameterComparator&, const long value );
    Expectation with( const ParameterComparator&, const unsigned long value );
    Expectation with( const ParameterComparator&, const long long value );
    Expectation with( const ParameterComparator&, const unsigned long long value );
    Expectation with( const ParameterComparator&, const double value );
    Expectation with( const ParameterComparator&, const void* value ) ;
    Expectation with( const ParameterComparator&, const void* const value ) ;
    Expectation with( const ParameterComparator&, const void* value, const std::size_t ) ;
    Expectation with( const ParameterComparator&, const void* const value, const std::size_t ) ;
    Expectation with( const ParameterComparator&, void (value*)() );


    /// expectation for the number of calls (cardinality)
    Expectation times( const std::size_t count );


    /// use model to perform behavior (i.e. use this to extend a mock into a model)
    Expectation use( IModel& );


    /// handle output parameter
    Expectation output( const SimpleString& parameterName, const bool value );
    Expectation output( const SimpleString& parameterName, const char value );
    Expectation output( const SimpleString& parameterName, const unsigned char value );
    Expectation output( const SimpleString& parameterName, const int value );
    Expectation output( const SimpleString& parameterName, const unsigned int value );
    Expectation output( const SimpleString& parameterName, const long value );
    Expectation output( const SimpleString& parameterName, const unsigned long value );
    Expectation output( const SimpleString& parameterName, const long long value );
    Expectation output( const SimpleString& parameterName, const long long value );
    Expectation output( const SimpleString& parameterName, const double value );
    Expectation output( const SimpleString& parameterName, const void* value );
    Expectation output( const SimpleString& parameterName, const void* const value );
    Expectation output( const SimpleString& parameterName, const void* value, const std::size_t );
    Expectation output( const SimpleString& parameterName, const void* const value, const std::size_t );
    Expectation output( const SimpleString& parameterName, void (value*)() );
    /// handle output parameter matching comparator
    Expectation output( const ParameterComparator&, const bool value );
    Expectation output( const ParameterComparator&, const char value );
    Expectation output( const ParameterComparator&, const unsigned char value );
    Expectation output( const ParameterComparator&, const int value );
    Expectation output( const ParameterComparator&, const unsigned int value );
    Expectation output( const ParameterComparator&, const long value );
    Expectation output( const ParameterComparator&, const unsigned long value );
    Expectation output( const ParameterComparator&, const long long value );
    Expectation output( const ParameterComparator&, const unsigned long long value );
    Expectation output( const ParameterComparator&, const double value );
    Expectation output( const ParameterComparator&, const void* value ) ;
    Expectation output( const ParameterComparator&, const void* const value ) ;
    Expectation output( const ParameterComparator&, const void* value, const std::size_t ) ;
    Expectation output( const ParameterComparator&, const void* const value, const std::size_t ) ;
    Expectation output( const ParameterComparator&, void (value*)() );


    /// return value (must come last)
    void andReturn( const bool value );
    void andReturn( const char value );
    void andReturn( const unsigned char value );
    void andReturn( const int value );
    void andReturn( const unsigned int value );
    void andReturn( const long value );
    void andReturn( const unsigned long value );
    void andReturn( const long long value );
    void andReturn( const long long value );
    void andReturn( const double value );
    void andReturn( const void* value );
    void andReturn( const void* const value );
    void andReturn( const void* value, const std::size_t );
    void andReturn( const void* const value, const std::size_t );
    void andReturn( void (value*)() );
};


class Actual;
/// Behavior handler for an expectation (e.g. Aspect Oriented Programming AoP)
class IModel
{
    /// modifies the actual call instance based on expectation and model state
    virtual void behave( const Expectation&, Actual& ) = 0;
};

