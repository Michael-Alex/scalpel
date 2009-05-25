/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_CAST_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CAST_EXPRESSION_HPP

#include "composite_node.hpp"
#include "sequence_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class unary_expression;

typedef
	sequence_node
	<
		unary_expression
	>
	cast_expression_t
;

typedef
	sequence_node
	<
	>
	cast_expression_tail_t
;

class cast_expression: public composite_node
{
	public:
		typedef cast_expression_t type;
		typedef unary_expression head_node_t;
		typedef sequence_node<> tail_sequence_node_t;

		cast_expression
		(
			unary_expression&& unary_expression_node
		);

		cast_expression
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		cast_expression(const cast_expression& o);

		cast_expression(cast_expression&& o);

		~cast_expression();

		const cast_expression&
		operator=(const cast_expression& o);

	private:
		cast_expression_t* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
