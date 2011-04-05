/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATOR_BIT_FIELD_MEMBER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATOR_BIT_FIELD_MEMBER_HPP

#include "identifier.hpp"
#include "conditional_expression.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
member_declarator_bit_field_member
	= !(identifier >> !s) >> ':' >> !s >> conditional_expression
;
*/
typedef
	sequence_node
	<
		optional_node<identifier>,
		predefined_text_node<str::colon>,
		conditional_expression
	>
	member_declarator_bit_field_member
;

inline
const optional_node<identifier>&
get_identifier(const member_declarator_bit_field_member& o)
{
	return get<0>(o);
}

inline
const conditional_expression&
get_conditional_expression(const member_declarator_bit_field_member& o)
{
	return get<2>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

