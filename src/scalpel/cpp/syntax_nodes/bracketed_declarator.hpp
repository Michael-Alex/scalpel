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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BRACKETED_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BRACKETED_DECLARATOR_HPP

#include "common.hpp"
#include "declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
bracketed_declarator
	= '(' >> !s >> declarator >> !s >> ')'
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::opening_round_bracket>,
		optional_node<space>,
		declarator,
		optional_node<space>,
		predefined_text_node<str::closing_round_bracket>
	>
	bracketed_declarator
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
