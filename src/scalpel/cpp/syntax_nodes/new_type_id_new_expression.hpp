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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NEW_TYPE_ID_NEW_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NEW_TYPE_ID_NEW_EXPRESSION_HPP

#include "round_bracketed_expression.hpp"
#include "new_type_id.hpp"
#include "new_initializer.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
new_type_id_new_expression
	= ["::"], "new", [round_bracketed_expression], new_type_id, [new_initializer]
;
*/
typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::double_colon>>,
		optional_node<space>,
		predefined_text_node<str::new_>,
		optional_node<space>,
		optional_node<round_bracketed_expression>,
		optional_node<space>,
		new_type_id,
		optional_node<space>,
		optional_node<new_initializer>
	>
	new_type_id_new_expression
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
