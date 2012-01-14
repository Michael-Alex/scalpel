/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#include "assignment_expression.hpp"
#include "expressions.hpp"
#include "conditional_expression.hpp"

#include "detail/macros/alternative_node_pimpl_definition.hpp"
#include "detail/macros/sequence_node_pimpl_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

SCALPEL_ALTERNATIVE_NODE_PIMPL_DEFINITION
(
	assignment_expression,
	(assignment_assignment_expression)
	(conditional_expression)
	(throw_expression)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	assignment_assignment_expression,
	(logical_or_expression)
	(assignment_operator)
	(assignment_expression)
)

const logical_or_expression&
get_left_operand(const assignment_assignment_expression& o)
{
	return get<0>(o);
}

const assignment_operator&
get_operator(const assignment_assignment_expression& o)
{
	return get<1>(o);
}

const assignment_expression&
get_right_operand(const assignment_assignment_expression& o)
{
	return get<2>(o);
}



SCALPEL_ALTERNATIVE_NODE_PIMPL_DEFINITION
(
	template_argument_assignment_expression,
	(template_argument_assignment_assignment_expression)
	(template_argument_conditional_expression)
	(throw_expression)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	template_argument_assignment_assignment_expression,
	(template_argument_logical_or_expression)
	(assignment_operator)
	(template_argument_assignment_expression)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_definition_undef.hpp"
#include "detail/macros/alternative_node_pimpl_definition_undef.hpp"

