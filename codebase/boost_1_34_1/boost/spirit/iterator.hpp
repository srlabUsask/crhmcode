/*=============================================================================
    Spirit v1.6.2
    Copyright (c) 2001-2003 Daniel Nuffer
    Copyright (c) 2002 Jeff Westfahl
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_ITERATOR_MAIN_HPP)
#define BOOST_SPIRIT_ITERATOR_MAIN_HPP

#include <boost/spirit/version.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Master header for Spirit.Iterators
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/spirit/iterator/fixed_size_queue.hpp>
#include <boost/spirit/iterator/position_iterator.hpp>

#include <boost/config.hpp>
#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1300)
#include <boost/spirit/iterator/multi_pass.hpp>
#endif

#endif // !defined(BOOST_SPIRIT_ITERATOR_MAIN_HPP)
