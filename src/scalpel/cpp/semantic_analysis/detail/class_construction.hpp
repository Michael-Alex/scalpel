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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CLASS_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CLASS_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

std::shared_ptr<semantic_entities::class_>
create_class(const syntax_nodes::class_specifier& syntax_node);

std::shared_ptr<semantic_entities::class_>
create_class(const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node);

void
fill_class
(
	std::shared_ptr<semantic_entities::class_> class_entity,
	const syntax_nodes::class_specifier& class_specifier_node
);

void
fill_class
(
	const std::shared_ptr<semantic_entities::class_> class_entity,
	const semantic_entities::class_::access current_access,
	const syntax_nodes::member_declaration_member_declarator_list& member_declaration_member_declarator_list_node
);

void
fill_class
(
	const std::shared_ptr<semantic_entities::class_> class_entity,
	const semantic_entities::class_::access function_access,
	const syntax_nodes::function_definition& function_definition_node
);

//Check whether the given class hasn't been forward declared in the given
//parent class.
//If so, return the forward declared class.
//If not, add the given class to the given parent class
//and return the given class.
std::shared_ptr<semantic_entities::class_>
add_class
(
	const std::shared_ptr<semantic_entities::class_>& parent_class_entity,
	const std::shared_ptr<semantic_entities::class_>& class_entity,
	const semantic_entities::class_::access current_access
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

