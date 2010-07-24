/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "nested_name_specifier.hpp"

#include "detail/macros/sequence_node_pimpl_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	nested_name_specifier,
	(identifier_or_template_id)
	(optional_node<space>)
	(predefined_text_node<str::double_colon>)
	(optional_node<space>)
	(optional_node<nested_name_specifier_last_part_seq>)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_definition_undef.hpp"

