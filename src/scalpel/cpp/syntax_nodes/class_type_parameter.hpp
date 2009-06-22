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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CLASS_TYPE_PARAMETER
#define SCALPEL_CPP_SYNTAX_NODES_CLASS_TYPE_PARAMETER

#include "common.hpp"
#include "identifier.hpp"
#include "type_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
class_type_parameter
	= str_p("class") >> !(!s >> identifier) >> !(!s >> '=' >> !s >> type_id)
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::class_>,
		optional_node<space>,
		optional_node<identifier>,
		optional_node<space>,
		optional_node<predefined_text_node<str::equal>>,
		optional_node<space>,
		optional_node<type_id>
	>
	class_type_parameter
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
