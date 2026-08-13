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

#include "pss/astrotypes/units/test/DispersionMeasureTest.h"
#include "pss/astrotypes/units/DispersionMeasure.h"
#include <boost/units/derived_dimension.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/pow.hpp>

namespace pss {
namespace astrotypes {
namespace units {
namespace test {

DispersionMeasureTest::DispersionMeasureTest()
    : ::testing::Test()
{
}

DispersionMeasureTest::~DispersionMeasureTest()
{
}

void DispersionMeasureTest::SetUp()
{
}

void DispersionMeasureTest::TearDown()
{
}

TEST_F(DispersionMeasureTest, test_conversion_to_si)
{
    DispersionMeasure<double> dm(1.0 * parsec_per_cube_cm);
    boost::units::quantity<decltype(boost::units::pow<-2>(boost::units::si::meter)), double> dm_in_si(dm);
    // 1 pc = 3.0856775813e16 m, 1 cm = 1e-2 m
    // 1 pc/cm^3 = 3.0856775813e16/(1e-2)^3 = 3.0856775813e22 m^-2
    ASSERT_NEAR(dm_in_si.value(), 3.0856775813e22, 1e13);
}

TEST_F(DispersionMeasureTest, test_dimension)
{
    static_assert(std::is_same<DispersionMeasureUnit::dimension_type
                               , boost::units::derived_dimension<boost::units::length_base_dimension, -2>::type
                              >::value
                  , "Dispersion measure does not have dimension of 1/d^2"
                 );
}

TEST_F(DispersionMeasureTest, test_equality)
{
    ASSERT_EQ(1.0 * parsec_per_cube_cm, 1.0 * parsecs_per_cube_cm);
}

} // namespace test
} // namespace units
} // namespace astrotypes
} // namespace pss
