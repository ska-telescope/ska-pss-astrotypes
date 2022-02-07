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
#include <boost/math/constants/constants.hpp>
#include <boost/units/systems/si/dimensionless.hpp>
#include <boost/units/systems/angle/degrees.hpp>
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
    Phase<double> p1(1.0 * fractional_revolution);
    Phase<double> p2(0.0 * fractional_revolution);
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

TEST_F(PhaseTest, test_phase_decay_time)
{
//    auto f = 1.0 * hertz;
//    Phase<double> phase(1.0 * fractional_revolution);
//    auto t = phase/f;
//    static_assert(std::is_same<decltype(t), boost::units::quantity<boost::units::unit<boost::units::time_dimension, boost::units::si::system>, double>>::value, "Expecting a time type");
}

TEST_F(PhaseTest, test_phase_decay_freq)
{
//    auto t = 1.0 * seconds;
//    Phase<double> phase(1.0 * fractional_revolution);
//    auto f = phase/t;
//    static_assert(std::is_same<decltype(f), boost::units::quantity<boost::units::unit<boost::units::frequency_dimension, boost::units::si::system>, double>>::value, "Expecting a frequency type");
}

TEST_F(PhaseTest, test_conversion_from_radians)
{
//    boost::units::quantity<boost::units::si::plane_angle, utils::ModuloOne<double>> radians(boost::math::constants::pi<double>()/4 * boost::units::si::radians);
//std::cout << radians.value() << std::endl;
//    Phase<double> phase(radians);
//std::cout << phase.value() << std::endl;
//    ASSERT_FLOAT_EQ(phase.value(), Phase<double>(0.125 * fractional_revolution).value());
}

TEST_F(PhaseTest, test_conversion_to_radians)
{
//    typedef boost::units::quantity<boost::units::si::plane_angle, double> Radians;
//    Radians expected_radians(boost::math::constants::pi<double>()/4 * boost::units::si::radians);
//std::cout << expected_radians.value() << std::endl;
//    Phase<double> phase(0.125 * fractional_revolution);
//std::cout << phase.value() << std::endl;
//    ASSERT_FLOAT_EQ(Radians(phase).value(), expected_radians.value());
}

/*
TEST_F(PhaseTest, test_compatability_with_dimensionless)
{
    Phase<double> phase(0.5 * fractional_revolution);
    static_assert(std::is_same<Phase<double>, boost::units::quantity<boost::units::si::dimensionless, double>>::value, "Expecting a phase type");
    ASSERT_EQ(phase.value(), boost::units::quantity<boost::units::si::dimensionless, double>(0.5).value());
}
*/

TEST_F(PhaseTest, test_operator_scalar_multiply)
{
//    Phase<double> phase1(0.5 * fractional_revolution);
//    auto res = phase1 * 3.0;
//std::cout << "phase1 = " << phase1.value() << std::endl;
//std::cout << "res = " << res.value() << std::endl;
//    static_assert(std::is_same<decltype(res), Phase<double>>::value, "Expecting a phase type");
//    ASSERT_EQ(res, phase1);
//    auto res2 = 3.0 * phase1;
//    static_assert(std::is_same<decltype(res2), Phase<double>>::value, "Expecting a phase type");
//    ASSERT_EQ(res2, phase1);
}

TEST_F(PhaseTest, test_operator_add)
{
//    Phase<double> phase1(0.5 * fractional_revolution);
//    Phase<double> phase2(0.7 * fractional_revolution);
//    ASSERT_EQ(phase1 + phase2, Phase<double>(0.2 * fractional_revolution));
//    ASSERT_EQ(phase2 + phase1, Phase<double>(0.2 * fractional_revolution));
}

TEST_F(PhaseTest, test_operator_subtract)
{
//    Phase<double> phase1(0.5 * fractional_revolution);
//    Phase<double> phase2(0.7 * fractional_revolution);
//    ASSERT_EQ(phase1 - phase2, Phase<double>(0.8 * fractional_revolution));
//    ASSERT_EQ(phase2 - phase1, Phase<double>(0.2 * fractional_revolution));
}

} // namespace test
} // namespace units
} // namespace astrotypes
} // namespace pss
