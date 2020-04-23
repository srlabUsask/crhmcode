/*=============================================================================
    Spirit v1.6.2
    Copyright (c) 2001-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_BASICS_HPP)
#define BOOST_SPIRIT_BASICS_HPP

#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x561)
#include <boost/spirit/core/impl/borland.hpp>
#endif

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>

#if defined(BOOST_MSVC) || defined(BOOST_INTEL_CXX_VERSION)
#include <boost/spirit/core/impl/msvc.hpp>
#endif

#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)
#define BOOST_SPIRIT_TYPENAME
#else
#define BOOST_SPIRIT_TYPENAME typename
#endif

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

    struct nil_t {};

}} // namespace boost::spirit

#endif

