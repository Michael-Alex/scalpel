/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_SCANNER_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_SCANNER_HPP

#ifndef BOOST_SPIRIT_USE_OLD_NAMESPACE
#define BOOST_SPIRIT_USE_OLD_NAMESPACE
#endif

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis
{

//scanner type of boost::spirit::pt_parse() function
typedef
	boost::spirit::scanner
	<
		const char*,
		boost::spirit::scanner_policies
		<
			boost::spirit::iteration_policy,
			boost::spirit::pt_match_policy
			<
				const char*,
				boost::spirit::node_val_data_factory<boost::spirit::nil_t>,
				boost::spirit::nil_t
			>,
			boost::spirit::action_policy
		>
	>
	scanner_t
;

}}}} //namespace scalpel::cpp::detail::syntax_analysis

#endif
