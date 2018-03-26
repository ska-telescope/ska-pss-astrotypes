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
#include "../MultiArrayTest.h"
#include "pss/astrotypes/multiarray/MultiArray.h"
#include <algorithm>


namespace pss {
namespace astrotypes {
namespace test {


MultiArrayTest::MultiArrayTest()
    : ::testing::Test()
{
}

MultiArrayTest::~MultiArrayTest()
{
}

void MultiArrayTest::SetUp()
{
}

void MultiArrayTest::TearDown()
{
}

struct DimensionA {};
struct DimensionB {};
struct DimensionC {};

template<typename T, typename... Dimensions>
struct TestMultiArrayTraits
{
    typedef T* iterator;
    typedef T const* const_iterator;
};

template<typename T, typename... Dimensions>
//class TestMultiArray : public MultiArray<T, MultiArrayTraits<TestMultiArray<T, Dimensions...>>, Dimensions...>
class TestMultiArray : public MultiArray<T, Dimensions...>
{
        typedef MultiArray<T,  Dimensions...> BaseT;

    public:
        template<typename... Args>
        TestMultiArray(Args&&... args) : BaseT(std::forward<Args>(args)...) {}
};

TEST_F(MultiArrayTest, test_single_dimension_size)
{
    DimensionSize<DimensionA> size(10);
    TestMultiArray<int, DimensionA> ma(size);
    ASSERT_EQ(ma.size<DimensionA>(), size);
    ASSERT_EQ(ma.size<DimensionB>(), DimensionSize<DimensionB>(0U));
    ASSERT_EQ(ma.size<DimensionC>(), DimensionSize<DimensionC>(0U));
}

TEST_F(MultiArrayTest, test_single_dimension_slice)
{
    DimensionSize<DimensionA> size(30);
    TestMultiArray<int, DimensionA> ma(size);
    int slice = ma[DimensionIndex<DimensionA>(0)];
    ASSERT_EQ(0, slice);
}

TEST_F(MultiArrayTest, test_three_dimension_size)
{
    DimensionSize<DimensionA> size_a(10);
    DimensionSize<DimensionB> size_b(20);
    DimensionSize<DimensionC> size_c(30);
    TestMultiArray<unsigned, DimensionA, DimensionB, DimensionC> ma( size_a, size_b, size_c);
    ASSERT_EQ(ma.size<DimensionA>(), size_a);
    ASSERT_EQ(ma.size<DimensionB>(), size_b);
    ASSERT_EQ(ma.size<DimensionC>(), size_c);
}

TEST_F(MultiArrayTest, test_three_dimension_square_bracket_operator)
{
    DimensionSize<DimensionA> size_a(10);
    DimensionSize<DimensionB> size_b(20);
    DimensionSize<DimensionC> size_c(30);
    TestMultiArray<unsigned, DimensionA, DimensionB, DimensionC> ma( size_a, size_b, size_c);
    for(DimensionIndex<DimensionA> index(0); index < size_a; ++index)
    {
        auto slice = ma[index];
        //ASSERT_EQ(slice.size<DimensionA>(), DimensionIndex<DimensionA>(9) - index);
        ASSERT_EQ(slice.size<DimensionA>(), DimensionSize<DimensionA>(0));
        ASSERT_EQ(slice.size<DimensionB>(), size_b);
        ASSERT_EQ(slice.size<DimensionC>(), size_c);
    }
}

TEST_F(MultiArrayTest, test_three_dimension_slice_operator)
{
    DimensionSize<DimensionA> size_a(10);
    DimensionSize<DimensionB> size_b(20);
    DimensionSize<DimensionC> size_c(30);
    TestMultiArray<unsigned, DimensionA, DimensionB, DimensionC> ma( size_a, size_b, size_c);
    for(DimensionIndex<DimensionA> index(0); index < size_a; ++index)
    {
        for(DimensionIndex<DimensionA> index_2(index + DimensionSize<DimensionA>(1)); index_2 <= size_a; ++index_2)
        {
            auto slice = ma.slice(DimensionSpan<DimensionA>(index, index_2 ));
            ASSERT_EQ(slice.size<DimensionA>(), index_2 - index);
            ASSERT_EQ(slice.size<DimensionB>(), size_b);
            ASSERT_EQ(slice.size<DimensionC>(), size_c);
        }
    }
}

TEST_F(MultiArrayTest, test_three_dimension_std_copy)
{
    DimensionSize<DimensionA> size_a(10);
    DimensionSize<DimensionB> size_b(20);
    DimensionSize<DimensionC> size_c(30);
    // fill some data
    std::vector<unsigned> data(size_a * size_b * size_c);
    unsigned val=0;
    std::generate(data.begin(), data.end(), [&]() { return val++; } );
    
    TestMultiArray<unsigned, DimensionA, DimensionB, DimensionC> ma( size_a, size_b, size_c);
    std::copy(data.begin(), data.end(), ma.begin()); // copy in

    // ensure the [] operators return the correct values
    for(DimensionIndex<DimensionA> i(0); i < ma.size<DimensionA>(); ++i) {
        for(DimensionIndex<DimensionB> j(0); j < ma.size<DimensionB>(); ++j) {
            ASSERT_EQ( i * size_b * size_c + j * size_c + 20, ma[i][j][DimensionIndex<DimensionC>(20)]) << "i=" << i
                                                                                                        << " j=" << j;
        }
    }

    std::vector<unsigned> dst;
    dst.reserve(size_a * size_b * size_c);
    std::copy(ma.begin(), ma.end(), std::back_inserter(dst)); //copy our
    ASSERT_EQ(data.size(), dst.size());
    ASSERT_EQ(data, dst);

    // test cbegin/cend
    dst.clear();
    std::copy(ma.cbegin(), ma.cend(), std::back_inserter(dst)); //copy our
    ASSERT_EQ(data, dst);
}

} // namespace test
} // namespace astrotypes
} // namespace pss
