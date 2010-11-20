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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_HPP

#include "syntax_tree.hpp"
#include "semantic_graph.hpp"
#include <memory>

namespace scalpel { namespace cpp
{

namespace semantic_analysis
{

std::shared_ptr<semantic_graph>
analyze(const syntax_tree& tree);

template<class DeclarativeRegionT>
void
analyze(const syntax_nodes::function_definition& function_definition_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region);



//
//namespace creation functions
//

std::shared_ptr<semantic_entities::namespace_>
create_namespace
(
	const syntax_nodes::namespace_definition& namespace_definition_node
);

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::namespace_definition& namespace_definition_node
);

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::simple_declaration& simple_declaration_node
);

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::declaration_seq& declaration_seq_node
);



//
//class creation functions
//

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



//
//function creation functions
//

std::shared_ptr<semantic_entities::operator_function>
create_operator_function
(
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::type_shared_ptr_variant type,
	const bool is_inline,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

semantic_entities::type_shared_ptr_variant
get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

semantic_entities::simple_function::parameters_t
create_parameters
(
	boost::optional<const syntax_nodes::parameter_declaration_list&> opt_parameter_declaration_list_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

semantic_entities::simple_function::parameters_t
create_parameters
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);



//
//type creation functions
//

//Create the type described by the given decl-specifier-seq.
//The returned type is not decorated by the qualifiers of
//the decl-specifier-seq.
semantic_entities::type_shared_ptr_variant
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

//Create the type described by the given type-specifier-seq.
//The returned type is not decorated by the qualifiers of
//the type-specifier-seq.
semantic_entities::type_shared_ptr_variant
create_type
(
	const syntax_nodes::type_specifier_seq& type_specifier_seq_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

//decorate type with decl-specifier-seq's const and volatile specifiers
semantic_entities::type_shared_ptr_variant
decorate_type
(
	semantic_entities::type_shared_ptr_variant type,
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node
);

//decorate type with declarator's pointers, references and arrays
semantic_entities::type_shared_ptr_variant
decorate_type
(
	semantic_entities::type_shared_ptr_variant type,
	const syntax_nodes::declarator& declarator_node
);

bool
has_type_decorators(const syntax_nodes::declarator& declarator_node);

//decorate type with ptr-operator-seq's pointers and references
semantic_entities::type_shared_ptr_variant
decorate_type
(
	semantic_entities::type_shared_ptr_variant type,
	const syntax_nodes::ptr_operator_seq& ptr_operator_seq_node
);

std::shared_ptr<const semantic_entities::fundamental_type>
get_fundamental_type
(
	const bool bool_type,
	const bool char_type,
	const bool double_type,
	const bool float_type,
	const bool int_type,
	const bool long_long_type,
	const bool long_type,
	const bool short_type,
	const bool signed_type,
	const bool unsigned_type,
	const bool void_type,
	const bool wchar_t_type
);



//
//other entities' creation functions
//

typedef
	utility::variant
	<
		std::shared_ptr<semantic_entities::class_::constructor>,
		std::shared_ptr<semantic_entities::class_::destructor>,
		std::shared_ptr<semantic_entities::operator_function>,
		std::shared_ptr<semantic_entities::class_::conversion_function>,
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

} //namespace semantic_analysis

}} //namespace scalpel::cpp

#include "semantic_analysis.ipp"

#endif

