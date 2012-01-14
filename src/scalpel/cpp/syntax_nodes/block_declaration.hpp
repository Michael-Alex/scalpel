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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BLOCK_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BLOCK_DECLARATION_HPP

#include "asm_definition.hpp"
#include "namespace_alias_definition.hpp"
#include "using_directive.hpp"
#include "using_declaration.hpp"

#include "detail/macros/alternative_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class simple_declaration;

SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION
(
	block_declaration,
	(simple_declaration)
	(asm_definition)
	(namespace_alias_definition)
	(using_declaration)
	(using_directive)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/alternative_node_pimpl_declaration_undef.hpp"

#endif
