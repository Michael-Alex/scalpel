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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TYPE_ID_NEW_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TYPE_ID_NEW_EXPRESSION_HPP

#include "common.hpp"
#include "new_placement.hpp"
#include "type_id.hpp"
#include "new_initializer.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
type_id_new_expression
	= !(str_p("::") >> !s) >> str_p("new") >> !s >> !(new_placement >> !s) >> '(' >> !s >> type_id >> !s >> ')' >> !(!s >> new_initializer)
;
*/
typedef
	sequence_node
	<
		optional_node<simple_text_node<str::double_colon>>,
		optional_node<space>,
		simple_text_node<str::new_>,
		optional_node<space>,
		optional_node<new_placement>,
		optional_node<space>,
		simple_text_node<str::opening_round_bracket>,
		optional_node<space>,
		type_id,
		optional_node<space>,
		simple_text_node<str::closing_round_bracket>,
		optional_node<space>,
		optional_node<new_initializer>
	>
	type_id_new_expression
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
