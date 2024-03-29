/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 The SKA organisation
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

namespace pss {
namespace astrotypes {
namespace utils {

template<typename T>
ModuloOne<T>::ModuloOne(T const& val)
    : _val(std::fmod(val, 1.0))
{
}

template<typename T>
ModuloOne<T>::operator T const& () const
{
    return _val;
}

template<typename T>
ModuloOne<T>& ModuloOne<T>::operator=(T const& v)
{
    _val = std::fmod(v, 1.0);
    return *this;
}

template<typename T>
ModuloOne<T>& ModuloOne<T>::operator=(ModuloOne<T> const& v)
{
    _val = v;
    return *this;
}

template<typename T>
ModuloOne<T>& ModuloOne<T>::operator+=(T const& v)
{
    _val = std::fmod((_val + v), 1.0);
    return *this;
}

template<typename T>
ModuloOne<T>& ModuloOne<T>::operator-=(T const& v)
{
    T v2 = std::fmod(v, 1.0);
    if (_val >= v2) {
        _val -= v2;
    }
    else {
        _val = 1 - (v2 - _val);
    }
    return *this;
}

template<typename T>
ModuloOne<T>& ModuloOne<T>::operator+=(ModuloOne<T> const& v)
{
    _val = std::fmod((_val + static_cast<T>(v)), 1.0);
    return *this;
}

template<typename T>
ModuloOne<T>& ModuloOne<T>::operator-=(ModuloOne<T> const& v)
{
    return (*this) -= static_cast<T>(v);
}

template<typename T>
bool ModuloOne<T>::operator==(T const& val) const
{
    return _val == val;
}

template<typename T>
bool ModuloOne<T>::operator!=(T const& val) const
{
    return _val != val;
}

template<typename T>
inline bool ModuloOne<T>::operator==(ModuloOne<T> const& val) const
{
    return _val == static_cast<T const&>(val);
}

template<typename T>
inline bool ModuloOne<T>::operator!=(ModuloOne<T> const& val) const
{
    return _val != static_cast<T const&>(val);
}

template<typename T>
inline const ModuloOne<T>& ModuloOne<T>::operator++() const
{
    return *this;
}

template<typename T>
inline const ModuloOne<T>& ModuloOne<T>::operator++(int) const
{
    return *this;
}

template<typename T>
inline const ModuloOne<T>& ModuloOne<T>::operator--() const
{
    return *this;
}

template<typename T>
inline const ModuloOne<T>& ModuloOne<T>::operator--(int) const
{
    return *this;
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator+(T const& v) const
{
    return ModuloOne<T>(std::fmod((_val + v), 1.0));
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator-(T const& v) const
{
    T v2 = std::fmod(v, 1.0);
    return ModuloOne<T>((_val >= v2) ? (_val - v2) : (1 - (v2 - _val)));
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator+(ModuloOne<T> const& v) const
{
    return *this + static_cast<T>(v);
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator-(ModuloOne<T> const& v) const
{
    return *this - static_cast<T>(v);
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator*(T const& v)
{
    return ModuloOne<T>(std::fmod((_val * v), 1.0));
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator/(T const& v)
{
    return ModuloOne<T>(std::fmod((_val/v), 1.0));
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator*(ModuloOne<T> const& v)
{
    return *this * static_cast<T>(v);
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator/(ModuloOne<T> const& v)
{
    return std::fmod((*this)/static_cast<T>(v), 1);
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator*=(T const& v)
{
    _val = std::fmod((_val * v), 1.0);
    return *this;
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator/=(T const& v)
{
    _val = std::fmod((_val/v), 1.0);
    return *this;
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator*=(ModuloOne<T> const& v)
{
    _val = std::fmod((_val * static_cast<T>(v)), 1.0);
    return *this;
}

template<typename T>
ModuloOne<T> ModuloOne<T>::operator/=(ModuloOne<T> const& v)
{
    return (*this) /= static_cast<T>(v);
}

template<typename T>
bool ModuloOne<T>::operator<(T const& v) const
{
    T v2 = v - std::trunc(v);
    return (v2 < 0) ? (_val < (1 + v2)) : (_val < v2);
}

template<typename T>
bool ModuloOne<T>::operator<(ModuloOne<T> const& v) const
{
    return operator<(static_cast<T const&>(v));
}

} // namespace utils
} // namespace astrotypes
} // namespace pss



namespace boost {
namespace units {

// Multiplication helpers

// Returns the results of the multiplication {X * ModuloOne<X>} with the type that matches the templated class X
template<class Unit, class X>
inline
typename multiply_typeof_helper<quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>, X>::type
operator*(const X& lhs, const quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>& rhs)
{
    typedef typename multiply_typeof_helper<X, quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>>::type type;

    return type::from_value(lhs * static_cast<X>(rhs.value()));
}

// Returns the results of the multiplication {ModuloOne<X> * X} with the type that matches the templated class X
template<class Unit, class X>
inline
typename multiply_typeof_helper<quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>, X>::type
operator*(const quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>& lhs, const X& rhs)
{
    typedef typename multiply_typeof_helper<quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>, X>::type type;

    return type::from_value(rhs * static_cast<X>(lhs.value()));
}

// Division helpers

// Returns the results of the division {X/ModuloOne<X>} with the type that matches the templated class X
template<class Unit, class X>
inline
typename divide_typeof_helper<quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>, X>::type
operator/(const X& lhs, const quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>& rhs)
{
    typedef typename divide_typeof_helper<X, quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>>::type type;

    return type::from_value(lhs/static_cast<X>(rhs.value()));
}

// Returns the results of the division {ModuloOne<X>/X} with the type that matches the templated class X
template<class Unit, class X>
inline
typename divide_typeof_helper<quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>, X>::type
operator/(const quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>& lhs, const X& rhs)
{
    typedef typename divide_typeof_helper<quantity<Unit, pss::astrotypes::utils::ModuloOne<X>>, X >::type type;

    return type::from_value(lhs.value()/static_cast<X>(rhs));
}

} // namespace units
} // namespace boost
