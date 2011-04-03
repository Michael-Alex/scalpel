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

#include "abstract_declarator.hpp"
#include "direct_abstract_declarator.hpp"

#include "detail/macros/sequence_node_pimpl_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	abstract_declarator,
	(optional_node<ptr_operator_seq>)
	(optional_node<direct_abstract_declarator>)
)

const optional_node<ptr_operator_seq>&
get_ptr_operator_seq(const abstract_declarator& o)
{
	return get<0>(o);
}

const optional_node<direct_abstract_declarator>&
get_direct_abstract_declarator(const abstract_declarator& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_definition_undef.hpp"

