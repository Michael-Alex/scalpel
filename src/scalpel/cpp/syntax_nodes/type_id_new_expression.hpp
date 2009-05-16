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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TYPE_ID_NEW_EXPRESION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TYPE_ID_NEW_EXPRESION_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
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
class type_id_new_expression: public composite_node
{
	public:
		type_id_new_expression
		(
			bool leading_double_colon,
			optional_node<space>&& post_double_colon_space_node,
			optional_node<space>&& post_new_keyword_space_node,
			optional_node<new_placement>&& new_placement_node,
			optional_node<space>&& post_new_placement_space_node,
			optional_node<space>&& post_opening_bracket_space_node,
			type_id&& type_id_node,
			optional_node<space>&& post_type_id_space_node,
			optional_node<space>&& pre_new_initializer_space_node,
			optional_node<new_initializer>&& new_initializer_node
		);

		type_id_new_expression(const type_id_new_expression& o);

		type_id_new_expression(type_id_new_expression&& o);

		const type_id_new_expression&
		operator=(const type_id_new_expression& o);

	private:
		void
		update_node_list();

		bool leading_double_colon_;
		optional_node<space> post_double_colon_space_;
		optional_node<space> post_new_keyword_space_;
		optional_node<new_placement> new_placement_;
		optional_node<space> post_new_placement_space_;
		optional_node<space> post_opening_bracket_space_;
		type_id type_id_;
		optional_node<space> post_type_id_space_;
		optional_node<space> pre_new_initializer_space_;
		optional_node<new_initializer> new_initializer_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
