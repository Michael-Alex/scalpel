/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_EXCEPTION_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EXCEPTION_DECLARATOR_HPP

#include "type_specifier_seq.hpp"
#include "declarator.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
exception_declarator
	= type_specifier_seq >> !s >> declarator
;
*/
typedef
	sequence_node
	<
		type_specifier_seq,
		optional_node<space>,
		declarator
	>
	exception_declarator
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
