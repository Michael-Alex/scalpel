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

#ifndef SOCOA_CPP_SYNTAX_NODES_AROW_ID_EXPRESION_HPP
#define SOCOA_CPP_SYNTAX_NODES_AROW_ID_EXPRESION_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "id_expression.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
arrow_id_expression
	= "->" >> !s >> !(str_p("template") >> !s) >> id_expression
;
*/
class arrow_id_expression: public composite_node
{
	public:
		arrow_id_expression
		(
			boost::optional<space>&& post_arrow_space_node,
			bool template_keyword,
			boost::optional<space>&& post_template_keyword_space_node,
			id_expression&& id_expression_node
		);

		arrow_id_expression(const arrow_id_expression& o);

		arrow_id_expression(arrow_id_expression&& o);

		const arrow_id_expression&
		operator=(const arrow_id_expression& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_arrow_space_;
		bool template_keyword_;
		boost::optional<space> post_template_keyword_space_;
		id_expression id_expression_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
