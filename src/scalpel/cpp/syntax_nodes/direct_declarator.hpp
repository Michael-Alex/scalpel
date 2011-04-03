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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DIRECT_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DIRECT_DECLARATOR_HPP

#include "declarator_id.hpp"
#include "declarator.hpp"
#include "parameter_declaration_clause.hpp"
#include "cv_qualifier_seq.hpp"
#include "bracketed_declarator.hpp"
#include "exception_specification.hpp"
#include "conditional_expression.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/*
\verbatim
direct_declarator
	= direct_declarator::first_part, [direct_declarator_last_part_seq]
;

direct_declarator::first_part
	= bracketed_declarator
	| declarator_id
;

direct_declarator::last_part_seq
	= {direct_declarator_last_part}
;

direct_declarator::last_part
	= direct_declarator::function_part
	| direct_declarator::array_part
;

direct_declarator::array_part
	= '[' >> !s >> !(conditional_expression >> !s) >> ']'
;
\endverbatim
*/

typedef
	sequence_node
	<
		predefined_text_node<str::opening_round_bracket>,
		optional_node<parameter_declaration_clause>,
		predefined_text_node<str::closing_round_bracket>,
		optional_node<cv_qualifier_seq>,
		optional_node<exception_specification>
	>
	direct_declarator_function_part
;

inline
const optional_node<parameter_declaration_clause>&
get_parameter_declaration_clause(const direct_declarator_function_part& o)
{
	return get<1>(o);
}

inline
const optional_node<cv_qualifier_seq>&
get_cv_qualifier_seq(const direct_declarator_function_part& o)
{
	return get<3>(o);
}


typedef
	sequence_node
	<
		predefined_text_node<str::opening_square_bracket>,
		optional_node<conditional_expression>,
		predefined_text_node<str::closing_square_bracket>
	>
	direct_declarator_array_part
;

inline
const optional_node<conditional_expression>&
get_conditional_expression(const direct_declarator_array_part& o)
{
	return get<1>(o);
}



typedef
	alternative_node
	<
		bracketed_declarator,
		declarator_id
	>
	direct_declarator_first_part
;

typedef
	alternative_node
	<
		direct_declarator_function_part,
		direct_declarator_array_part
	>
	direct_declarator_last_part
;

typedef
	list_node
	<
		direct_declarator_last_part
	>
	direct_declarator_last_part_seq
;

SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	direct_declarator,
	(direct_declarator_first_part)
	(optional_node<direct_declarator_last_part_seq>)
)

inline
const direct_declarator_first_part&
get_first_part(const direct_declarator& o)
{
	return get<0>(o);
}

inline
const optional_node<direct_declarator_last_part_seq>&
get_last_part_seq(const direct_declarator& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

