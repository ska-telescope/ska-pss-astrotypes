/*
 * MIT License
 *
 * Copyright (c) 2018 PulsarSearchSoft
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
#include "pss/astrotypes/units/test/PhaseTest.h"
#include "pss/astrotypes/units/Phase.h"
#include "pss/astrotypes/units/Frequency.h"
#include "pss/astrotypes/units/Time.h"
#include <type_traits>


namespace pss {
namespace astrotypes {
namespace units {
namespace test {


PhaseTest::PhaseTest()
    : ::testing::Test()
{
}

PhaseTest::~PhaseTest()
{
}

void PhaseTest::SetUp()
{
}

void PhaseTest::TearDown()
{
}

TEST_F(PhaseTest, test_modulo)
{
    Phase<double> p1(1.0);
    Phase<double> p2(0.0);
    ASSERT_EQ(p1, p2);
}

TEST_F(PhaseTest, test_construction_from_time_freq)
{
    auto f = 5.5 * hertz;
    auto t = 2.1 * seconds;
    auto phase1 = f * t;
    static_assert(std::is_same<decltype(phase1), Phase<double>>::value, "Expecting a phase type");
    auto phase2 = t * f;
    static_assert(std::is_same<decltype(phase2), Phase<double>>::value, "Expecting a phase type");
    ASSERT_EQ(phase1, phase2);
}

TEST_F(PhaseTest, test_concersion_from_radians)
{
    boost::units::quantity<boost::units::si::plane_angle, double> radians(PI);
    Phase<double> phase(radians);
    ASSER_EQ(phase, Phase<double>(0.5));
}

TEST_F(PhaseTest, test_compatability_with_dimensionless)
{
    Phase<double> phase(0.5);
    ASSERT_EQ(phase, boost::units::quantity<boost::units::si::dimensionless, double>(0.5));
}

TEST_F(PhaseTest, test_operatpr_add)
{
    Phase<double> phase1(0.5);
    Phase<double> phase2(0.7);
    ASSERT_EQ(phase1 + phase2, Phase<double>(0.2));
    ASSERT_EQ(phase2 + phase1, Phase<double>(0.2));
}

TEST_F(PhaseTest, test_operatpr_subtract)
{
    Phase<double> phase1(0.5);
    Phase<double> phase2(0.7);
    ASSERT_EQ(phase1 - phase2, Phase<double>(0.8));
    ASSERT_EQ(phase2 - phase1, Phase<double>(0.2));
}

} // namespace test
} // namespace units
} // namespace astrotypes
} // namespace pss