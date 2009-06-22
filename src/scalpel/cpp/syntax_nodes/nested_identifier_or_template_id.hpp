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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NESTED_IDENTIFIER_OR_TEMPLATE_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NESTED_IDENTIFIER_OR_TEMPLATE_ID_HPP

#include "common.hpp"
#include "nested_name_specifier.hpp"
#include "identifier_or_template_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
nested_identifier_or_template_id
	= !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> identifier_or_template_id
;
*/
typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::double_colon>>,
		optional_node<space>,
		optional_node<nested_name_specifier>,
		optional_node<space>,
		identifier_or_template_id
	>
	nested_identifier_or_template_id
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
