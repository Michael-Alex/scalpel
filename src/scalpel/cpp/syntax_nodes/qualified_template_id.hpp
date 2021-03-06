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

#ifndef SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_TEMPLATE_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_TEMPLATE_ID_HPP

#include "template_id.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
qualified_template_id
	= str_p("::") >> !s >> template_id
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::double_colon>,
		template_id
	>
	qualified_template_id
;

inline
const template_id&
get_template_id(const qualified_template_id& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

