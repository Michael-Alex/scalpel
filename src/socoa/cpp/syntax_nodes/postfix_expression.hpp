/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_NODES_POSTFIX_EXPRESSION_HPP
#define SOCOA_CPP_SYNTAX_NODES_POSTFIX_EXPRESSION_HPP

#include "../../util/extern_strings.hpp"
#include "composite_node.hpp"
#include "alternative_node.hpp"
#include "primary_expression.hpp"
#include "simple_type_specifier_postfix_expression.hpp"
#include "typename_expression.hpp"
#include "template_typename_expression.hpp"
#include "dynamic_cast_expression.hpp"
#include "static_cast_expression.hpp"
#include "reinterpret_cast_expression.hpp"
#include "const_cast_expression.hpp"
#include "typeid_expression.hpp"
#include "type_id_typeid_expression.hpp"
#include "square_bracketed_expression.hpp"
#include "bracketed_expression_list.hpp"
#include "dot_id_expression.hpp"
#include "arrow_id_expression.hpp"
#include "dot_pseudo_destructor_name.hpp"
#include "arrow_pseudo_destructor_name.hpp"
#include "simple_text_node.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
postfix_expression
	= postfix_expression::first_part, [postfix_expression::last_part_seq]
;
\endverbatim
*/
class postfix_expression: public composite_node
{
	public:
		typedef
			alternative_node
			<
				primary_expression,
				simple_type_specifier_postfix_expression,
				typename_expression,
				template_typename_expression,
				dynamic_cast_expression,
				static_cast_expression,
				reinterpret_cast_expression,
				const_cast_expression,
				typeid_expression,
				type_id_typeid_expression
			>
			first_part
		;

		typedef
			alternative_node
			<
				square_bracketed_expression,
				bracketed_expression_list,
				dot_id_expression,
				arrow_id_expression,
				dot_pseudo_destructor_name,
				arrow_pseudo_destructor_name,
				simple_text_node<util::extern_strings::double_plus>,
				simple_text_node<util::extern_strings::double_minus>
			>
			last_part
		;

		typedef sequence_node<last_part> last_part_seq;

		postfix_expression
		(
			first_part&& first_part_node,
			boost::optional<space>&& space_node,
			boost::optional<last_part_seq>&& last_part_seq_node
		);

		postfix_expression(const postfix_expression& o);

		postfix_expression(postfix_expression&& o);

		const postfix_expression&
		operator=(const postfix_expression& o);

	private:
		void
		update_node_list();

		first_part first_part_;
		boost::optional<space> space_;
		boost::optional<last_part_seq> last_part_seq_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif