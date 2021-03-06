/*
 * Copyright (c) 2018, Stephen Holstein
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EXPECT_CALL_H
#define EXPECT_CALL_H

namespace TestDouble
{
/// Abstract actual call for model usage
class AActualCall
{
public:
  virtual const TestDouble::ParameterChain* getInputs() const = 0;
  virtual TestDouble::ParameterChain* getOutputs() const = 0;

  template<typename T>
  void setOutput( const SimpleString& _name, T value )
  {
    const TestDouble::Parameter::Variant variant( value );
    for( TestDouble::ParameterChain* pActualEntry=getOutputs(); 0 != pActualEntry; pActualEntry = pActualEntry->pNext )
    {
      if( ( pActualEntry->pParameter->name == _name )   &&
          ( variant.type == pActualEntry->pParameter->_variant.type ) )
      {
        pActualEntry->pParameter->_variant = variant;
      }
    }
  }

  template<typename T>
  void setReturn( T value )
  {
    _return = TestDouble::Parameter::Variant(value);
  }

  virtual ~AActualCall() {}

protected:
  TestDouble::Parameter::Variant  _return;
};

/// Behavior handler for an expectation (e.g. Aspect Oriented Programming AoP)
class IModel
{
public:
  /// @note implementation must call setReturn()
  virtual void model( AActualCall &call ) = 0;
  virtual ~IModel() {}
};



/// A builder for an expectation
class ExpectedCall
{
public:
  const SimpleString  name;

  ExpectedCall( const SimpleString &_name )
    : name(_name), _count(EXPECT_ALWAYS), _inputs(0), _outputs(0), _returnValue(0), _pModel(0) {}

  ~ExpectedCall()
  {
    delete _inputs;
    delete _outputs;
  }


  static const int EXPECT_ALWAYS = -1;
  ExpectedCall& times( const unsigned int &count )
  {
    _count = (int)count;
    return *this;
  }

  template<typename T>
  ExpectedCall& with( const SimpleString &_name, const T &value )
  {
    TestDouble::Parameter* pParameter = new TestDouble::Parameter( _name, value );
    _inputs = new TestDouble::ParameterChain( pParameter, _inputs );
    return *this;
  }

  ExpectedCall& withBuffer( const SimpleString &_name, const void* const &staticBuffer, const std::size_t &size )
  {
    TestDouble::Parameter* pParameter = new TestDouble::Parameter( _name, staticBuffer, size );
    _inputs = new TestDouble::ParameterChain( pParameter, _inputs );
    return *this;
  }

  template<typename T>
  ExpectedCall& output( const SimpleString &_name, const T &value )
  {
    TestDouble::Parameter* pParameter = new TestDouble::Parameter( _name, value );
    _outputs = new TestDouble::ParameterChain( pParameter, _outputs );
    return *this;
  }

  ExpectedCall& outputBuffer( const SimpleString &_name, void* const &staticBuffer, const std::size_t &size_bytes )
  {
    TestDouble::Parameter* pParameter = new TestDouble::Parameter( _name, staticBuffer, size_bytes );
    _outputs = new TestDouble::ParameterChain( pParameter, _outputs );
    return *this;
  }

  void use( IModel &staticModel ) { _pModel = &staticModel; }
  bool hasModel() const { return 0 != _pModel; }
  void handleModel( AActualCall &actual ) const
  {
    if( 0 == _pModel ) return;
    else _pModel->model( actual );
  }

  template<typename T > 
  void returns( const T& value ) { _returnValue.value = value; }


  int getCount() const { return _count; }
  const TestDouble::ParameterChain* getInputs() const { return _inputs; }
  const TestDouble::ParameterChain* getOutputs() const { return _outputs; }
  const TestDouble::Parameter::Variant getReturn() const { return _returnValue; }

private:
  int   _count;
  TestDouble::ParameterChain*     _inputs;
  TestDouble::ParameterChain*     _outputs;
  TestDouble::Parameter::Variant  _returnValue;
  IModel* _pModel;
};

} //namespace TestDouble


#endif /* EXPECT_CALL_H */
