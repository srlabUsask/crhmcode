/*=============================================================================
    Spirit v1.6.2
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_REGEX_HPP
#define BOOST_SPIRIT_REGEX_HPP

#include <boost/spirit/core/impl/msvc.hpp>

#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)
#define BOOST_SPIRIT_IT_NS impl
#else
#define BOOST_SPIRIT_IT_NS std
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  Include the regular expression library of boost (Boost.Regex)
//
//  Note that this library is not available with the Spirit only distribution.
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/regex.hpp>

#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/core/meta/impl/parser_type.hpp>
#include <boost/spirit/core/parser.hpp>
#include <boost/spirit/utility/impl/regex.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

///////////////////////////////////////////////////////////////////////////////
// rxstrlit class
template <typename CharT = char>
struct rxstrlit : public parser<rxstrlit<CharT> > {

    typedef rxstrlit self_t;

    rxstrlit(CharT const *first, CharT const *last)
    : rx(first, last) {}
    rxstrlit(CharT const *first)
    : rx(first) {}

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
    //  Due to limitations in the boost::regex library the iterators wrapped in
    //  the ScannerT object should be at least bidirectional iterators. Plain
    //  forward iterators do not work here.
        typedef typename ScannerT::iterator_t iterator_t;
        typedef
            typename BOOST_SPIRIT_IT_NS::iterator_traits<iterator_t>::iterator_category
            iterator_category;

        BOOST_STATIC_ASSERT((
            boost::is_convertible<iterator_category,
                std::bidirectional_iterator_tag>::value
        ));

        typedef typename parser_result<self_t, ScannerT>::type result_t;
        return impl::contiguous_parser_parse<result_t>(rx, scan, scan);
    }

private:
    impl::rx_parser<CharT> rx;   // contains the boost regular expression parser
};

///////////////////////////////////////////////////////////////////////////////
// Generator functions
template <typename CharT>
inline rxstrlit<CharT>
regex_p(CharT const *first)
{ return rxstrlit<CharT>(first); }

//////////////////////////////////
template <typename CharT>
inline rxstrlit<CharT>
regex_p(CharT const *first, CharT const *last)
{ return rxstrlit<CharT>(first, last); }

///////////////////////////////////////////////////////////////////////////////
}} // namespace boost::spirit

#undef BOOST_SPIRIT_IT_NS

#endif // BOOST_SPIRIT_REGEX_HPP
