/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2026 The SKA organisation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "pss/astrotypes/units/test/PhysicalConstantsTest.h"
#include "pss/astrotypes/units/PhysicalConstants.h"
#include "pss/astrotypes/units/Time.h"

namespace pss {
namespace astrotypes {
namespace units {
namespace test {

PhysicalConstantsTest::PhysicalConstantsTest()
    : ::testing::Test()
{
}

PhysicalConstantsTest::~PhysicalConstantsTest()
{
}

void PhysicalConstantsTest::SetUp()
{
}

void PhysicalConstantsTest::TearDown()
{
}

// Test if the value of the speed of light unit
// has the exact standardised value (in m/s).
TEST_F(PhysicalConstantsTest, test_speed_of_light_value)
{
    ASSERT_DOUBLE_EQ(speed_of_light.value(), 299792458.0);
}

// Test that unit analysis proves that the speed of light is a veolicty
TEST_F(PhysicalConstantsTest, test_speed_of_light_is_velocity)
{
    static_assert(std::is_same<decltype(speed_of_light)
                               , boost::units::quantity<boost::units::si::velocity, double> const
                              >::value
                  , "Expecting a velocity quantity");
}

// Test that multiplying the speed of light with
// a time gives a distance (with the correct length).
TEST_F(PhysicalConstantsTest, test_speed_of_light_in_calculation)
{
    auto distance = speed_of_light * (1.0 * seconds);
    static_assert(boost::units::is_unit_of_dimension<decltype(distance)::unit_type
                                                     , boost::units::length_dimension
                                                    >::value
                  , "Calculated distance does not have length dimension"
                 );
    ASSERT_DOUBLE_EQ(distance.value(), 299792458.0); // One light-second, in metres
}

} // namespace test
} // namespace units
} // namespace astrotypes
} // namespace pss
