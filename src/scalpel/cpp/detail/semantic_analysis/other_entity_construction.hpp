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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_OTHER_ENTITY_CONSTRUCTION_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_OTHER_ENTITY_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/variant.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

typedef
	utility::variant
	<
		std::shared_ptr<semantic_entities::constructor>,
		std::shared_ptr<semantic_entities::destructor>,
		std::shared_ptr<semantic_entities::operator_function>,
		std::shared_ptr<semantic_entities::conversion_function>,
		std::shared_ptr<semantic_entities::simple_function>,
		std::shared_ptr<semantic_entities::variable>,
		std::shared_ptr<semantic_entities::typedef_>
	>
	declarator_entity_shared_ptr_variant
;

//Create variable/function/typedef/etc. corresponding to the given declarator.
declarator_entity_shared_ptr_variant
create_entity
(
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region,
	boost::optional<semantic_entities::type_shared_ptr_variant> opt_type,
	const bool has_typedef_specifier,
	const bool has_static_specifier,
	const bool has_inline_specifier,
	const bool has_explicit_specifier
);

std::shared_ptr<semantic_entities::namespace_alias>
create_namespace_alias
(
	const syntax_nodes::namespace_alias_definition& namespace_alias_definition_node,
	std::shared_ptr<semantic_entities::namespace_> current_namespace
);

std::shared_ptr<semantic_entities::namespace_>
create_using_directive
(
	const syntax_nodes::using_directive& using_directive_node,
	std::shared_ptr<semantic_entities::namespace_> current_namespace
);

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif
