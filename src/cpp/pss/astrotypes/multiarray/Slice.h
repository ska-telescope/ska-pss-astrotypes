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
#ifndef PSS_ASTROTYPES_MULTIARRAY_SLICE_H
#define PSS_ASTROTYPES_MULTIARRAY_SLICE_H
#include "DimensionSpan.h"
#include <utility>

namespace pss {
namespace astrotypes {

/**
 * @brief
 *      Representation of a Slice through a Data Array
 * @details
 */

template<typename Parent, typename Dimension, typename... Dimensions>
class Slice : private Slice<Parent, Dimensions...>
{
        typedef Slice<Parent, Dimensions...> BaseT;
        typedef Slice<Parent, Dimension, Dimensions...> SelfType;
        typedef typename Parent::value_type value_type;
        typedef typename Parent::reference_type reference_type;

        typedef typename Parent::iterator iterator;

    public:
        Slice( Parent& parent
             , DimensionSpan<Dimension> const&
             , DimensionSpan<Dimensions> const&...
        );

        /**
         * @ brief return the size of the slice in the specified dimension
         * @code
         *      Slice<DimesionA, DimensionB> slice(...some initialisers...);
         *      DimensionSize<DimensionA> size_of_A = slice.size<DimensionA>();
         *      DimensionSize<DimensionB> size_of_B = slice.size<DimensionB>();
         *      // note you can rmeomve the dimension tagging on the DimesionSize
         *      // objects for compatibilty with less strongly types libs
         *      // with a static_cast
         *      std::size_t size_A_as_size_t = static_cast<std::size_t>(size_of_A);
         * @endcode
         * @details
         *      If you intend to inherit from this class you may need to call this method with the 
         *      template keyword.
         *      e,g, 
         *      @code
         *      slice.template size<DimensionA>();
         *      @endcode
         */
        template<typename Dim>
        typename std::enable_if<std::is_same<Dim, Dimension>::value, DimensionSize<Dimension>>::type 
        size() const;

        template<typename Dim>
        typename std::enable_if<!std::is_same<Dim, Dimension>::value, DimensionSize<Dim>>::type 
        size() const;

        /**
         * @brief Take a slice in the specified dimension one channel thick
         */
        Slice<Parent, Dimensions...> operator[](std::size_t) const;

        /**
         * @brief Take a slice from this slice
         */
        Slice<Parent, Dimension, Dimensions...> slice(DimensionSpan<Dimension> const& span) const;

    protected:
        template<typename P, typename D, typename... Ds> friend class Slice;

        // return the span of memory to add on to the outer dimension index
        std::size_t span() const;
        void offset(iterator const&); // init the offset relative to the top parent

        // init for inheriting classes only
        Slice( DimensionSpan<Dimension> const&
             , DimensionSpan<Dimensions> const&...
             , Parent const& parent
        );

        // increment pointer by a n * span length
        SelfType& operator+=(std::size_t n);

        // increment pointer by a n * base span length
        SelfType& operator+=(DimensionSize<Dimension> n);

        // return the span of the underlying parent in the Dimension
        DimensionSize<Dimension> parent_span() const;

    private:
        DimensionSpan<Dimension> _span;
        DimensionSize<Dimension> _base_span;
        iterator _ptr;  // start of block
};

// specialisation for 0 dimensional slice
// which should return a single element
template<typename Parent, typename Dimension>
class Slice<Parent, Dimension>
{
        typedef Slice<Parent, Dimension> SelfType;


        typedef typename Parent::reference_type reference_type;
        typedef typename Parent::iterator iterator;

    public:
        Slice(Parent& parent, DimensionSpan<Dimension> const&);
        ~Slice();

        /**
         * @ brief return the size of the slice in the specified dimension
         */
        template<typename Dim>
        typename std::enable_if<std::is_same<Dim, Dimension>::value, DimensionSize<Dimension>>::type 
        size() const;

        /**
         * @ brief return the size of the slice in the specified dimension (will always be zero)
         */
        template<typename Dim>
        typename std::enable_if<!std::is_same<Dim, Dimension>::value, DimensionSize<Dim>>::type 
        size() const;

        /**
         * @brief return the value at the position specified in this Dimension
         */
        reference_type operator[](std::size_t index) const;
        reference_type operator[](DimensionIndex<Dimension> const& index) const;

    protected:
        template<typename P, typename D, typename... Ds> friend class Slice;

        // return the span of memory to add on to the outer dimension index
        std::size_t span() const;
        void offset(iterator const&); // init the offset relative to the top parent
        Slice(DimensionSpan<Dimension> const&, Parent const&);
        SelfType& operator+=(DimensionSize<Dimension> const&);

    protected:
        DimensionSize<Dimension> parent_span() const;

    private:
        DimensionSpan<Dimension> _span;
        DimensionSize<Dimension> _base_span;
        typename Parent::iterator _ptr;   // start, to extent _ptr + _span
};

} // namespace astrotypes
} // namespace pss

#include "detail/Slice.cpp"

#endif // PSS_ASTROTYPES_MULTIARRAY_SLICE_H