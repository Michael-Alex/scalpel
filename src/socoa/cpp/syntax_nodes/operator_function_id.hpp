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

#ifndef SOCOA_CPP_SYNTAX_NODES_OPERATOR_FUNCTION_ID_HPP
#define SOCOA_CPP_SYNTAX_NODES_OPERATOR_FUNCTION_ID_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "operator_.hpp"
#include "space.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
operator_function_id
	= str_p("operator") >> !s >> operator_
;
*/
class operator_function_id: public composite_node
{
    public:
		operator_function_id
		(
			boost::optional<space>&& post_operator_keyword_space_node,
			operator_&& operator_node
		);

		operator_function_id(const operator_function_id& o);

		operator_function_id(operator_function_id&& o);

		const operator_function_id&
		operator=(const operator_function_id& o);

    private:
		void
		update_node_list();

		boost::optional<space> post_operator_keyword_space_;
		operator_ operator__;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
