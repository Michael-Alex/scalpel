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

#ifndef SCALPEL_CPP_SYNTAX_NODES_UNARY_OPERATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_UNARY_OPERATOR_HPP

#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		predefined_text_node<str::double_plus>,
		predefined_text_node<str::double_minus>,
		predefined_text_node<str::asterisk>,
		predefined_text_node<str::ampersand>,
		predefined_text_node<str::plus>,
		predefined_text_node<str::minus>,
		predefined_text_node<str::exclamation>,
		predefined_text_node<str::tilde>
	>
	unary_operator
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif

