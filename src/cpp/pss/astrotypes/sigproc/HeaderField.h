/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018-2026 The SKA organisation
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
#ifndef PSS_ASTROTYPES_SIGPROC_HEADERFIELD_H
#define PSS_ASTROTYPES_SIGPROC_HEADERFIELD_H

#include "pss/astrotypes/sigproc/detail/SigProcVariable.h"
#include "pss/astrotypes/utils/Optional.h"
#include <boost/units/io.hpp>
#include <string>
#include <vector>

namespace pss {
namespace astrotypes {
namespace sigproc {

class Header;

/**
 *  @brief   Class to provide a virtual lookup table for reading/writing the
 *           various types of SigProc variables.
 */
class HeaderFieldBase
{
    protected:
        // Allows us to hide HeaderFields from the writer
        HeaderFieldBase(){};

        // Add the provided field as a read-only parameter
        void add_read(SigProcLabel const& header_label
                      , HeaderFieldBase& field
                      , Header& header
                     );

    public:
        // Registers the Field to be read/written by the Header parser
        HeaderFieldBase(SigProcLabel const& header_name, Header& h);
        ~HeaderFieldBase(){}; // Virtual not needed, we never expect to pass these around

        /**
         *  @brief   Read from a stream into a variable
         *  @return   The number of bytes read
         */
        virtual unsigned read(std::istream&) { return 0; };

        /**
         *  @brief   Write a variable in sigproc header format to a stream
         *  @return   The number of bytes written
         */
        virtual unsigned write(std::ostream&) const { return 0; };

        /**
         *  @brief   An information string about the value in the field (for debugging)
         */
        virtual void write_info(std::ostream&) const {};

        /**
         *  @return   The required header string to be used in info output
         */
        virtual std::string const& header_info(std::string const& h) const { return h; };

        /**
         *   @brief   Reset the variable to undefined state
         */
        virtual void reset() = 0;

        /**
         *  @return   True if the variable has been set, false otherwise
         */
        virtual bool is_set() const = 0;

        virtual bool operator==(const HeaderFieldBase&) const { return true; };

        virtual void operator=(const HeaderFieldBase&) = 0;
};

template<typename T>
class HeaderField : public HeaderFieldBase
{
        using BaseT = HeaderFieldBase;

    protected:
        // For expansion only, not to be used as a public interface
        HeaderField(){};

    public:
        // Add the provided field as a read/write parameter
        HeaderField(SigProcLabel const& header_label, Header& header);
        HeaderField(SigProcLabel const& header_label, Header& header, T const& to_copy);

        // Warning: HeaderFieldBase must be convertible to HeaderField
        HeaderField(SigProcLabel const& header_label, Header& header, HeaderField const&);

        operator T const&() const { return *_var; }
        operator T&() { return *_var; }
        operator utils::Optional<T> const&() const { return _var; }
        HeaderField& operator=(T const& var);
        void operator=(const HeaderFieldBase&) override;

        unsigned read(std::istream &) override;
        unsigned write(std::ostream &) const override;
        void write_info(std::ostream &) const override;
        void reset() override;
        bool is_set() const override;
        bool operator==(const HeaderFieldBase&) const override;
        bool operator==(const HeaderField&) const;

    protected:
        utils::Optional<T> _var;
};

/**
 *  @brief   Specialisation to allow the operator== to return true if the
 *           values are within specified tolerance.
 */
template<typename T, typename ToleranceType>
class HeaderFieldWithTolerance : public HeaderField<T>
{
        using BaseT = HeaderField<T>;

    public:
        using HeaderField<T>::operator=;

    public:
        HeaderFieldWithTolerance(SigProcLabel const& header_label
                                 , Header& header
                                 , ToleranceType const&
                                );
        HeaderFieldWithTolerance(SigProcLabel const& header_label
                                 , Header& header
                                 , ToleranceType const&
                                 , HeaderFieldWithTolerance const&
                                );
        HeaderFieldWithTolerance& operator=(T const& var);

        bool operator==(const HeaderFieldBase&) const override;
        bool operator==(const HeaderFieldWithTolerance&) const;

    private:
        ToleranceType _tolerance;
};

/**
 *  @brief   Specialisation for writing and reading the sigproc vector type
 *
 *  @details   The start of a vector in the header is marked with a start label
 *             (e.g. FREQUENCY_START). The end of a vector in the header is
 *             marked with an end label (e.g. FREQUENCY_END). In between, each
 *             element is marked with its own item tag (e.g. fchannel).
 */
template<typename T>
class HeaderField<std::vector<T>> : public HeaderFieldBase
{
        using BaseT = HeaderFieldBase;

        // Vectors are marked with start and end tags
        class NullField : public HeaderFieldBase
        {
            public:
                NullField(){}
                // No content other than the label
                bool is_set() const override { return false; }
                void reset() override {};
                void operator=(const HeaderFieldBase&) override {};
        };

        class ItemField : public HeaderFieldBase
        {
            // Only needs to read
            public:
                ItemField(std::vector<T>& vec) : _vec(vec) {}
                bool is_set() const override { return false; }
                unsigned read(std::istream &) override;
                void reset() override {};
                void operator=(const HeaderFieldBase&) override {}

            private:
                std::vector<T>& _vec;
        };

    public:
        HeaderField(SigProcLabel const& start_label
                    , SigProcLabel const& item_label
                    , SigProcLabel const& end_label
                    , Header& header
                   );
        HeaderField(SigProcLabel const& start_label
                    , SigProcLabel const& item_label
                    , SigProcLabel const& end_label
                    , Header& header
                    , HeaderField const& copy
                   );

        operator std::vector<T> const&() const { return _var; }
        operator std::vector<T>&() { return _var; }
        operator utils::Optional<std::vector<T>> const&() const { return _var; }
        HeaderField& operator=(std::vector<T> const& var);

        unsigned read(std::istream &) override;
        unsigned write(std::ostream &) const override;
        std::string const& header_info(std::string const& h) const override;
        void write_info(std::ostream &) const override;
        bool is_set() const override;
        void reset() override;

        std::vector<T> const& operator*() const { return _var; };
        std::vector<T>& operator*() { return _var; };

        bool operator==(const HeaderFieldBase&) const override;
        bool operator==(const HeaderField&) const;
        void operator=(const HeaderFieldBase&) override;

    private:
        std::vector<T>  _var;
        ItemField       _item_label_handler;
        NullField       _end_label_handler;
        SigProcLabel    _end_label;
        SigProcLabel    _item_label;
};

} // namespace sigproc
} // namespace astrotypes
} // namespace pss

#endif // PSS_ASTROTYPES_SIGPROC_HEADERFIELD_H
