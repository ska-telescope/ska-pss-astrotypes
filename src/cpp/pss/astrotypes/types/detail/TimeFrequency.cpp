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

namespace pss {
namespace astrotypes {

template<typename T, typename Alloc>
TimeFrequency<T, Alloc>::TimeFrequency(DimensionSize<Time> time_size, DimensionSize<Frequency> freq_size)
    : BaseT(time_size, freq_size)
{
}

template<typename T, typename Alloc>
TimeFrequency<T, Alloc>::TimeFrequency(DimensionSize<Frequency> freq_size, DimensionSize<Time> time_size)
    : BaseT(time_size, freq_size)
{
}

template<typename T, typename Alloc>
TimeFrequency<T, Alloc>::~TimeFrequency()
{
}

template<typename T, typename Alloc>
typename TimeFrequency<T, Alloc>::Spectra TimeFrequency<T, Alloc>::spectrum(std::size_t offset)
{
    return (*this)[DimensionIndex<Time>(offset)];
}

template<typename T, typename Alloc>
typename TimeFrequency<T, Alloc>::ConstSpectra TimeFrequency<T, Alloc>::spectrum(std::size_t offset) const
{
    return (*this)[DimensionIndex<Time>(offset)];
}

template<typename T, typename Alloc>
typename TimeFrequency<T, Alloc>::Channel TimeFrequency<T, Alloc>::channel(std::size_t offset)
{
    return Channel(*this, DimensionSpan<Time>(DimensionIndex<Time>(0), this->template size<Time>())
                        , DimensionSpan<Frequency>(DimensionIndex<Frequency>(offset), DimensionSize<Frequency>(1)));
}

template<typename T, typename Alloc>
typename TimeFrequency<T, Alloc>::ConstChannel TimeFrequency<T, Alloc>::channel(std::size_t offset) const
{
    return ConstChannel(*this, DimensionSpan<Time>(DimensionIndex<Time>(0), this->template size<Time>())
                        , DimensionSpan<Frequency>(DimensionIndex<Frequency>(offset), DimensionSize<Frequency>(1)));
}

// ***************************************************************
// --------------    FrequencyTime    ----------------------------
// ***************************************************************
//
template<typename T, typename Alloc>
FrequencyTime<T, Alloc>::FrequencyTime(DimensionSize<Frequency> freq_size, DimensionSize<Time> time_size)
    : BaseT(freq_size, time_size)
{
}

template<typename T, typename Alloc>
FrequencyTime<T, Alloc>::FrequencyTime(DimensionSize<Time> time_size, DimensionSize<Frequency> freq_size)
    : BaseT(freq_size, time_size)
{
}

template<typename T, typename Alloc>
FrequencyTime<T, Alloc>::~FrequencyTime()
{
}

template<typename T, typename Alloc>
typename FrequencyTime<T, Alloc>::Channel FrequencyTime<T, Alloc>::channel(std::size_t offset)
{
    return (*this)[DimensionIndex<Frequency>(offset)];
}

template<typename T, typename Alloc>
typename FrequencyTime<T, Alloc>::ConstChannel FrequencyTime<T, Alloc>::channel(std::size_t offset) const
{
    return (*this)[DimensionIndex<Frequency>(offset)];
}

template<typename T, typename Alloc>
typename FrequencyTime<T, Alloc>::Spectra FrequencyTime<T, Alloc>::spectrum(std::size_t offset)
{
    return Spectra(*this, DimensionSpan<Frequency>(DimensionIndex<Frequency>(0), this->template size<Frequency>())
                        , DimensionSpan<Time>(DimensionIndex<Time>(offset), DimensionSize<Time>(1)));
}

template<typename T, typename Alloc>
typename FrequencyTime<T, Alloc>::ConstSpectra FrequencyTime<T, Alloc>::spectrum(std::size_t offset) const
{
    return ConstSpectra(*this, DimensionSpan<Frequency>(DimensionIndex<Frequency>(0), this->template size<Frequency>())
                        , DimensionSpan<Time>(DimensionIndex<Time>(offset), DimensionSize<Time>(1)));
}

} // namespace astrotypes
} // namespace pss
