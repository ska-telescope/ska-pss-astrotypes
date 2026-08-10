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
#ifndef PSS_ASTROTYPES_UNITS_PHYSICALCONSTANTS_H
#define PSS_ASTROTYPES_UNITS_PHYSICALCONSTANTS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wpragmas"
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <boost/units/systems/si/codata/universal_constants.hpp>
#pragma GCC diagnostic pop

namespace pss {
namespace astrotypes {
namespace units {

static boost::units::quantity<boost::units::si::velocity, double> const speed_of_light
    = boost::units::si::constants::codata::c;

} // namespace units
} // namespace astrotypes
} // namespace pss

#endif // PSS_ASTROTYPES_UNITS_PHYSICALCONSTANTS_H