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

#include "CppUTest/TestHarness.h"
#include "CppUTest/TestTestingFixture.h"
#include "CppUTestExt/TestDouble.h"
#include "CppUTestExt/ExpectCall.h"
#include "CppUTestExt/ActualCall.h"

//======================================================================================================================
TEST_GROUP( MatchedOutputParameter )
{
  TEST_SETUP()
  {
    // clear any expectations
    checkExpectations();
  }

  TEST_TEARDOWN()
  {
    // clear any expectations resources
    checkExpectations();
  }
};

TEST( MatchedOutputParameter, match_bool )
{
  const bool value = true;
  expectCall("foo").output("value", value);
  bool actual = !value;
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_char )
{
  const char value = 'a';
  expectCall("foo").output("value", value);
  char actual = 'b';
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_unsigned_char )
{
  const unsigned char value = 'a';
  expectCall("foo").output("value", value);
  unsigned char actual = 'b';
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_int )
{
  const int value = 1;
  expectCall("foo").output("value", value);
  int actual = 2;
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_unsigned_int )
{
  const unsigned int value = 1;
  expectCall("foo").output("value", value);
  unsigned int actual = 2;
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_long )
{
  const long value = 1;
  expectCall("foo").output("value", value);
  long actual = 2;
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_unsigned_long )
{
  const unsigned long value = 1;
  expectCall("foo").output("value", value);
  unsigned long actual = 2;
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_long_long )
{
  const long long value = 1;
  expectCall("foo").output("value", value);
  long long actual = 2;
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_unsigned_long_long )
{
  const unsigned long long value = 1;
  expectCall("foo").output("value", value);
  unsigned long long actual = 2;
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_float )
{
  const float value = 1.1f;
  expectCall("foo").output("value", value);
  float actual = 2.2f;
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_double )
{
  const double value = 1.1;
  expectCall("foo").output("value", value);
  double actual = 2.2;
  actualCall("foo").output("value", &actual).returns();
  CHECK( value == actual );
}

TEST( MatchedOutputParameter, match_pointer )
{
  static char values[] = "HELLO";
  char* pValue = values;
  expectCall("foo").output("value", pValue);
  char* pActual = 0;
  actualCall("foo").output("value", &pActual).returns();
  CHECK( pValue == pActual );
}

TEST( MatchedOutputParameter, match_const_pointer )
{
  const char values[] = "HELLO";
  const char* pValue = values;
  expectCall("foo").output("value", pValue);
  const char* pActual = 0;
  actualCall("foo").output("value", &pActual).returns();
  CHECK( pValue == pActual );
}

typedef void (*fn_t)();
static fn_t fn { };
TEST( MatchedOutputParameter, match_fn )
{
  expectCall("foo").output("value", fn);
  fn_t pActual = 0;
  actualCall("foo").output("value", &pActual).returns();
  CHECK( fn == pActual );
}

TEST( MatchedOutputParameter, match_static_buffer )
{
  char values[6] = "HELLO";
  expectCall("foo").outputBuffer("value", values, sizeof(values));
  char actuals[6] = "UHTOH";
  actualCall("foo").outputBuffer("value", actuals, sizeof(actuals)).returns();
  MEMCMP_EQUAL( values, actuals, sizeof(values) );
}

static void foo( const int& value, int& actual )
{
  expectCall("foo").output("value", value);
  actualCall("foo").output("value", &actual);
}
TEST( MatchedOutputParameter, actualcall_destructor_sets_outputs )
{
  const int value = -1;
  int actual = 0;
  foo( value, actual );
  CHECK( value == actual );
}

//======================================================================================================================
TEST_GROUP( ActualDefaults )
{
  TEST_SETUP()
  {
    // clear any expectations
    checkExpectations();
  }

  TEST_TEARDOWN()
  {
    // clear any expectations resources
    checkExpectations();
  }
};

TEST( ActualDefaults, unexpected_without_default_is_true )
{
  bool actual = false;
  actualCall("foo").output("value", &actual).returns();
  CHECK( actual );
}

TEST( ActualDefaults, unexpected_with_default )
{
  int actual = 0;
  const int defaultValue = 2;
  actualCall("foo").output("value", &actual, defaultValue).returns();
  CHECK( defaultValue == actual );
}

TEST( ActualDefaults, unexpected_buffer_with_default )
{
  const char buffer[6] = "HELLO";
  char actuals[6] = "UHTOH";
  actualCall("foo").outputBuffer("value", actuals, sizeof(buffer), buffer).returns();
  MEMCMP_EQUAL( buffer, actuals, sizeof(buffer) );
}

static void bar( const int& value, int& actual )
{
  actualCall("bar").output("value", &actual, value);
}
TEST( ActualDefaults, actualcall_destructor_sets_outputs )
{
  const int value = -1;
  int actual = 0;
  bar( value, actual );
  CHECK( value == actual );
}

//======================================================================================================================
TEST_GROUP( TestDoubleOutputsFailures )
{
  TestTestingFixture fixture;

  TEST_SETUP()
  {
    // clear any expectations
    checkExpectations();
  }

  TEST_TEARDOWN()
  {
    // clear any expectations resources
    checkExpectations();
    CHECK( fixture.hasTestFailed() );
  }
};

static void mismatch_parameter( void )
{
  expectCall("foo").output( "value", true );
  actualCall("foo");
  checkExpectations();
}
TEST( TestDoubleOutputsFailures, mismatch_parameter_fails )
{
  fixture.runTestWithMethod( mismatch_parameter );
}

static void mismatch_type( void )
{
  expectCall("foo").output( "value", true );
  int actual = 0;
  actualCall("foo").output( "value", &actual );
  checkExpectations();
}
TEST( TestDoubleOutputsFailures, mismatch_type_fails )
{
  fixture.runTestWithMethod( mismatch_type );
}

static void mismatch_size( void )
{
  char values[1];
  expectCall("foo").outputBuffer("value", values, sizeof(values));
  char actuals[2];
  actualCall("foo").outputBuffer("value", actuals, sizeof(actuals)).returns();
}
TEST( TestDoubleOutputsFailures, mismatch_size_fails )
{
  fixture.runTestWithMethod( mismatch_size );
}

