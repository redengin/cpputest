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

#include <CppUTestExt/TestDoubleParameter.h>
#include <CppUTest/PlatformSpecificFunctions.h>
// CppUTest replaces string.h API but does not provide memcmp
extern "C" int memcmp ( const void * ptr1, const void * ptr2, size_t num );

namespace TestDouble {

bool Parameter::equals( const Parameter* const &pOther ) const
{
  if( type != pOther->type ) return false;

  if( 0 != buffer )
  {
    if( 0 == pOther->buffer ) return false;
    if( bufferSize_bytes != pOther->bufferSize_bytes ) return false;
    return ( 0 == memcmp( buffer, pOther->buffer, bufferSize_bytes ) );
  }

  if( type == typeid(void*).name() ) { return _variant.value.asPointer == pOther->_variant.value.asPointer; }
  if( type == typeid(const void*).name() ) { return _variant.value.asConstPointer == pOther->_variant.value.asConstPointer; }
  if( type == typeid(double).name() ) { return ( _variant.value.asDouble - pOther->_variant.value.asDouble) == 0.0; }
  if( type == typeid(float).name() ) { return ( _variant.value.asFloat - pOther->_variant.value.asFloat ) == 0.0f; }
  if( type == typeid(long long).name() ) { return _variant.value.asLongLong == pOther->_variant.value.asLongLong; }
  if( type == typeid(unsigned long long).name() ) { return _variant.value.asUnsignedLongLong == pOther->_variant.value.asUnsignedLongLong; }
  if( type == typeid(long).name() ) { return _variant.value.asLong == pOther->_variant.value.asLong; }
  if( type == typeid(unsigned long).name() ) { return _variant.value.asUnsignedLong == pOther->_variant.value.asUnsignedLong; }
  if( type == typeid(int).name() ) { return _variant.value.asInt == pOther->_variant.value.asInt; }
  if( type == typeid(unsigned int).name() ) { return _variant.value.asUnsignedInt == pOther->_variant.value.asUnsignedInt; }
  if( type == typeid(short).name() ) { return _variant.value.asShort == pOther->_variant.value.asShort; }
  if( type == typeid(unsigned short).name() ) { return _variant.value.asUnsignedShort == pOther->_variant.value.asUnsignedShort; }
  if( type == typeid(char).name() ) { return _variant.value.asChar == pOther->_variant.value.asChar; }
  if( type == typeid(unsigned char).name() ) { return _variant.value.asUnsignedChar == pOther->_variant.value.asUnsignedChar; }
  if( type == typeid(bool).name() ) { return _variant.value.asBool == pOther->_variant.value.asBool; }
  return _variant.value.asFunctionPointer == pOther->_variant.value.asFunctionPointer;
}

Parameter::Variant& Parameter::Variant::operator=( const TestDouble::Parameter::Variant &other )
{
  PlatformSpecificMemCpy( &value, &(other.value), sizeof(value) );
  return *this;
}



bool Parameter::setValue( const Parameter* const &pOther )
{
  if( 0 != pOther->buffer )
  {
    if( pOther->bufferSize_bytes != bufferSize_bytes ) return false;
    PlatformSpecificMemCpy( outputBuffer, pOther->buffer, bufferSize_bytes );
  }
  else PlatformSpecificMemCpy( outputBuffer, &(pOther->_variant.value), bufferSize_bytes );

  return true;
}

void Parameter::setDefault()
{
  if( 0 != buffer ) PlatformSpecificMemCpy( outputBuffer, buffer, bufferSize_bytes );
  else PlatformSpecificMemCpy( outputBuffer, &_variant.value, bufferSize_bytes );
}

SimpleString Parameter::toString()
{
  SimpleString ret = StringFromFormat( "\"%s\"\t\t", name.asCharString() );
  switch( _variant.type )
  {
    case Variant::FN_POINTER:
      return ret + "<function pointer>" + HexStringFrom(_variant.value.asFunctionPointer);

    case Variant::POINTER:
      return ret + "<pointer>" + HexStringFrom(_variant.value.asPointer);

    case Variant::CONST_POINTER:
      return ret + "<const pointer>" + HexStringFrom(_variant.value.asConstPointer);

    case Variant::DOUBLE:
      return ret + "<double>" + StringFrom( _variant.value.asDouble );

    case Variant::FLOAT:
      return ret + "<float>" + StringFrom( static_cast<double>(_variant.value.asFloat) );

    case Variant::LONG_LONG:
      return ret + "<long long>" + StringFrom( _variant.value.asLongLong );

    case Variant::UNSIGNED_LONG_LONG:
      return ret + "<unsigned long long>" + StringFrom( _variant.value.asUnsignedLongLong );

    case Variant::LONG:
      return ret + "<long>" + StringFrom( _variant.value.asLong );

    case Variant::UNSIGNED_LONG:
      return ret + "<unsigned long>" + StringFrom( _variant.value.asUnsignedLong );

    case Variant::INT:
      return ret + "<int>" + StringFrom( _variant.value.asInt );

    case Variant::UNSIGNED_INT:
      return ret + "<unsigned int>" + StringFrom( _variant.value.asUnsignedInt );

    case Variant::SHORT:
      return ret + "<short>" + StringFrom( _variant.value.asShort );

    case Variant::UNSIGNED_SHORT:
      return ret + "<unsigned short>" + StringFrom( _variant.value.asUnsignedShort );

    case Variant::CHAR:
      return ret + "<char>" + StringFrom( _variant.value.asChar );

    case Variant::UNSIGNED_CHAR:
      return ret + "<unsigned char>" + StringFrom( _variant.value.asUnsignedChar );

    case Variant::BOOL:
      return ret + StringFrom( _variant.value.asBool );

    case Variant::RETURN_VALUE:
      /// for unknown types display the largest union member in hex
      return ret + "<unknown type (" + type + ")>" + HexStringFrom(_variant.value.asLongLong );
  }
}

} // namespace TestDouble
