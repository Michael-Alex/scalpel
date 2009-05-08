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

#ifndef SOCOA_CPP_SYNTAX_NODES_BRACKETED_INITIALIZER_HPP
#define SOCOA_CPP_SYNTAX_NODES_BRACKETED_INITIALIZER_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "expression_list.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
bracketed_initializer
	= ch_p('(') >> !s >> expression_list >> !s >> ')'
;
*/
class bracketed_initializer: public composite_node
{
	public:
		bracketed_initializer
		(
			boost::optional<space>&& post_opening_bracket_space_node,
			expression_list&& expression_list_node,
			boost::optional<space>&& post_expression_list_space_node
		);

		bracketed_initializer(const bracketed_initializer& o);

		bracketed_initializer(bracketed_initializer&& o);

		const bracketed_initializer&
		operator=(const bracketed_initializer& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_opening_bracket_space_;
		expression_list expression_list_;
		boost::optional<space> post_expression_list_space_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
