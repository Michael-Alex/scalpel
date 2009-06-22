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

#ifndef SCALPEL_CPP_SYNTAX_NODES_PARAMETER_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_PARAMETER_DECLARATION_HPP

#include "common.hpp"
#include "declarator.hpp"
#include "abstract_declarator.hpp"
#include "decl_specifier_seq.hpp"
#include "assignment_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
parameter_declaration
	= decl_specifier_seq >> !s >> declarator >> !s >> '=' >> !s >> assignment_expression
	| decl_specifier_seq >> !s >> declarator
	| decl_specifier_seq >> !s >> abstract_declarator >> !s >> '=' >> !s >> assignment_expression
	| decl_specifier_seq >> !(!s >> abstract_declarator)
	| decl_specifier_seq >> !s >> '=' >> !s >> assignment_expression
;
\endverbatim
*/
typedef
	sequence_node
	<
		decl_specifier_seq,
		optional_node<space>,
		optional_node<declarator>,
		optional_node<abstract_declarator>,
		optional_node<space>,
		optional_node<predefined_text_node<str::equal>>,
		optional_node<space>,
		optional_node<assignment_expression>
	>
	parameter_declaration
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
