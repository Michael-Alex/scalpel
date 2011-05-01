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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_NAMESPACE_CONSTRUCTION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_NAMESPACE_CONSTRUCTION_IPP

#include "class_construction.hpp"
#include "enum_construction.hpp"
#include "function_construction.hpp"
#include "type_construction.hpp"
#include "other_entity_construction.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"
#include "syntax_node_analysis/class_specifier.hpp"
#include "syntax_node_analysis/function_definition.hpp"
#include "syntax_node_analysis/declarator.hpp"
#include "syntax_node_analysis/decl_specifier_seq.hpp"
#include <scalpel/cpp/semantic_entities/generic_queries/detail/get_members.hpp>
#include <iostream>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class Namespace>
void
fill_namespace
(
	Namespace& namespace_entity,
	const syntax_nodes::namespace_definition& namespace_definition_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const optional_node<declaration_seq>& opt_declaration_seq_node = get_declaration_seq(namespace_definition_node);
	if(opt_declaration_seq_node)
		fill_namespace(namespace_entity, *opt_declaration_seq_node);
}

template<class Namespace>
void
fill_namespace
(
	Namespace& namespace_entity,
	const syntax_nodes::declaration_seq& declaration_seq_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//add the declarations of the namespace definition in the namespace semantic entity
	for(auto i = declaration_seq_node.begin(); i != declaration_seq_node.end(); ++i)
	{
		auto declaration_node = *i;

		if(const boost::optional<const block_declaration&> opt_block_declaration_node = get<block_declaration>(&declaration_node))
		{
			const block_declaration& block_declaration_node = *opt_block_declaration_node;

			if(const boost::optional<const simple_declaration&> opt_simple_declaration_node = get<simple_declaration>(&block_declaration_node))
				fill_namespace(namespace_entity, *opt_simple_declaration_node);
			//else if(const boost::optional<const asm_definition&> opt_asm_definition_node = get<asm_definition>(&block_declaration_node))
			else if(const boost::optional<const namespace_alias_definition&> opt_namespace_alias_definition_node = get<namespace_alias_definition>(&block_declaration_node))
			{
				std::unique_ptr<namespace_alias> new_namespace_alias = create_namespace_alias(*opt_namespace_alias_definition_node, namespace_entity);
				namespace_entity.add_member(std::move(new_namespace_alias));
			}
			else if(const boost::optional<const using_declaration&> opt_using_declaration_node = get<using_declaration>(&block_declaration_node))
				fill_namespace(namespace_entity, *opt_using_declaration_node);
			else if(const boost::optional<const using_directive&> opt_using_directive_node = get<using_directive>(&block_declaration_node))
			{
				namespace_& new_using_directive = find_using_directive_namespace(*opt_using_directive_node, namespace_entity);
				namespace_entity.add_using_directive_namespace(new_using_directive);
			}
		}
		else if(const boost::optional<const function_definition&> opt_function_definition_node = get<function_definition>(&declaration_node))
			fill_namespace(namespace_entity, *opt_function_definition_node);
		//else if(const boost::optional<const template_declaration&> opt_template_declaration_node = get<template_declaration>(&declaration_node))
		//else if(const boost::optional<const explicit_instantiation&> opt_explicit_instantiation_node = get<explicit_instantiation>(&declaration_node))
		//else if(const boost::optional<const explicit_specialization&> opt_explicit_specialization_node = get<explicit_specialization>(&declaration_node))
		//else if(const boost::optional<const linkage_specification&> opt_linkage_specification_node = get<linkage_specification>(&declaration_node))
		else if(const boost::optional<const namespace_definition&> opt_namespace_definition_node = get<namespace_definition>(&declaration_node))
		{
			utility::variant<namespace_*, unnamed_namespace*> new_namespace =
				create_namespace(*opt_namespace_definition_node)
			;

			if(auto opt_namespace = utility::get<namespace_*>(&new_namespace))
			{
				namespace_& new_namespace_ref = **opt_namespace;
				namespace_entity.add_member(std::unique_ptr<namespace_>(*opt_namespace));
				fill_namespace(new_namespace_ref, *opt_namespace_definition_node);
			}
			else if(auto opt_namespace = utility::get<unnamed_namespace*>(&new_namespace))
			{
				unnamed_namespace& new_namespace_ref = **opt_namespace;
				namespace_entity.set_unnamed_namespace(std::unique_ptr<unnamed_namespace>(*opt_namespace));
				fill_namespace(new_namespace_ref, *opt_namespace_definition_node);
			}
			else
			{
				assert(false);
			}
		}
	}
}

template<class Namespace>
void
fill_namespace
(
	Namespace& namespace_entity,
	const syntax_nodes::simple_declaration& simple_declaration_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	boost::optional<type_variant> opt_unqualified_type;
	bool has_typedef_specifier = false;
	bool has_static_specifier = false;
	bool has_inline_specifier = false;

	if(const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node))
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		has_typedef_specifier = syntax_node_analysis::has_typedef_specifier(decl_specifier_seq_node);
		has_static_specifier = syntax_node_analysis::has_static_specifier(decl_specifier_seq_node);
		has_inline_specifier = syntax_node_analysis::has_inline_specifier(decl_specifier_seq_node);

		//create and/or get undecorated type
		switch(syntax_node_analysis::get_decl_specifier_seq_type(decl_specifier_seq_node))
		{
			case syntax_node_analysis::type_specifier_seq_type::CLASS_DECLARATION:
			{
				const class_specifier& class_specifier_node =
					syntax_node_analysis::get_class_specifier(decl_specifier_seq_node)
				;
				const class_head& class_head_node = get_class_head(class_specifier_node);
				const optional_node<nested_name_specifier>& opt_nested_name_specifier_node =
					get_nested_name_specifier(class_head_node)
				;

				if(opt_nested_name_specifier_node)
				{
					//find the class
					class_* found_class =
						name_lookup::find
						<
							semantic_entity_analysis::identification_policies::by_name,
							false,
							false,
							class_
						>
						(
							false,
							opt_nested_name_specifier_node,
							syntax_node_analysis::get_identifier(class_specifier_node),
							&namespace_entity,
							false
						)
					;

					//and define it
					fill_class(*found_class, class_specifier_node);

					opt_unqualified_type = found_class;
				}
				else
				{
					std::unique_ptr<class_> new_class = create_class<class_>(class_specifier_node);
					class_& added_class = add_class(namespace_entity, std::move(new_class));
					fill_class(added_class, class_specifier_node);

					opt_unqualified_type = &added_class;
				}

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
			{
				const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
					syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
				;

				std::unique_ptr<class_> new_class = create_class<class_>(class_elaborated_specifier_node);
				class_& added_class = add_class(namespace_entity, std::move(new_class));

				opt_unqualified_type = &added_class;

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::UNION_DECLARATION:
			{
				const class_specifier& class_specifier_node =
					syntax_node_analysis::get_class_specifier(decl_specifier_seq_node)
				;
				const class_head& class_head_node = get_class_head(class_specifier_node);
				const optional_node<nested_name_specifier>& opt_nested_name_specifier_node =
					get_nested_name_specifier(class_head_node)
				;

				if(opt_nested_name_specifier_node)
				{
					//find the union
					union_* found_union =
						name_lookup::find
						<
							semantic_entity_analysis::identification_policies::by_name,
							false,
							false,
							union_
						>
						(
							false,
							opt_nested_name_specifier_node,
							syntax_node_analysis::get_identifier(class_specifier_node),
							&namespace_entity,
							false
						)
					;

					//and define it
					fill_class(*found_union, class_specifier_node);

					opt_unqualified_type = found_union;
				}
				else
				{
					//is it an anonymous union?
					const bool anonymous =
						syntax_node_analysis::get_identifier(class_specifier_node).empty() &&
						!get_init_declarator_list(simple_declaration_node)
					;

					if(anonymous)
					{
						std::unique_ptr<anonymous_union> new_union(new anonymous_union());
						anonymous_union& added_union = *new_union;
						namespace_entity.add_member(std::move(new_union));
						fill_class(added_union, class_specifier_node);

						opt_unqualified_type = &added_union;
					}
					else
					{
						std::unique_ptr<union_> new_union = create_class<union_>(class_specifier_node);
						union_& added_union = add_class(namespace_entity, std::move(new_union));
						fill_class(added_union, class_specifier_node);

						opt_unqualified_type = &added_union;
					}
				}

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::UNION_FORWARD_DECLARATION:
			{
				const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
					syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
				;

				std::unique_ptr<union_> new_union = create_class<union_>(class_elaborated_specifier_node);
				union_& added_union = add_class(namespace_entity, std::move(new_union));

				opt_unqualified_type = &added_union;

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::ENUMERATION_DECLARATION:
			{
				const enum_specifier& enum_specifier_node =
					syntax_node_analysis::get_enum_specifier(decl_specifier_seq_node)
				;

				std::unique_ptr<enum_> new_enum = create_enum(enum_specifier_node);
				enum_& new_enum_ref = *new_enum;
				namespace_entity.add_member(std::move(new_enum));
				fill_enum(new_enum_ref, enum_specifier_node);

				opt_unqualified_type = &new_enum_ref;

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::SIMPLE_TYPE:
			{
				opt_unqualified_type = create_type(decl_specifier_seq_node, &namespace_entity);
				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::NO_TYPE:
			{
				break;
			}
		}

		//qualify type
		if(opt_unqualified_type)
			opt_unqualified_type = qualify_type(*opt_unqualified_type, decl_specifier_seq_node);
	}

	if(const optional_node<init_declarator_list>& opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node))
	{
		const init_declarator_list& init_declarator_list_node = *opt_init_declarator_list_node;

		for(auto i = init_declarator_list_node.begin(); i != init_declarator_list_node.end(); ++i)
		{
			const init_declarator& init_declarator_node = *i;
			const declarator& declarator_node = get_declarator(init_declarator_node);

			declarator_entity_ptr_variant declarator_entity = create_entity
			(
				declarator_node,
				&namespace_entity,
				opt_unqualified_type,
				has_typedef_specifier,
				false,
				has_static_specifier,
				has_inline_specifier,
				false,
				false,
				false,
				false,
				member_access::PUBLIC
			);

			if(auto opt_simple_function_entity = get<simple_function*>(&declarator_entity))
				namespace_entity.add_member(std::unique_ptr<simple_function>(*opt_simple_function_entity));
			else if(auto opt_operator_function_entity = get<operator_function*>(&declarator_entity))
				namespace_entity.add_member(std::unique_ptr<operator_function>(*opt_operator_function_entity));
			else if(auto opt_variable_entity = get<variable*>(&declarator_entity))
				namespace_entity.add_member(std::unique_ptr<variable>(*opt_variable_entity));
			else if(auto opt_typedef_entity = get<typedef_*>(&declarator_entity))
				namespace_entity.add_member(std::unique_ptr<typedef_>(*opt_typedef_entity));
			else
				assert(false);
		}
	}
}

template<class Namespace>
void
fill_namespace
(
	Namespace& namespace_entity,
	const syntax_nodes::using_declaration& using_declaration_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const unqualified_id& unqualified_id_node = get_unqualified_id(using_declaration_node);
	const optional_node<nested_name_specifier>& opt_nested_name_specifier_node = get_nested_name_specifier(using_declaration_node);

	if(has_typename_keyword(using_declaration_node))
		assert(false); //not implemented yet

	//find the designated entity(ies)'s declarative region
	open_declarative_region_ptr_variant found_declarative_region =
		name_lookup::find_declarative_region
		(
			has_leading_double_colon(using_declaration_node),
			opt_nested_name_specifier_node,
			&namespace_entity
		)
	;

	//find the designated entity(ies)
	if(boost::optional<const identifier&> opt_identifier_node = get<identifier>(&unqualified_id_node))
	{
		//first, try to find a class, enum, typedef or variable
		typename boost::optional<utility::ptr_variant<class_, enum_, typedef_, variable>::type> found_entity =
			name_lookup::find_local
			<
				semantic_entity_analysis::identification_policies::by_name,
				open_declarative_region_ptr_variant,
				true,
				false,
				class_, enum_, typedef_, variable
			>
			(
				opt_identifier_node->value(),
				found_declarative_region
			)
		;

		if(found_entity) //if an entity has been found
		{
			//add the entity alias to the namespace
			add_alias(namespace_entity, *found_entity);
		}
		else
		{
			//if no entity has been found, try to find functions
			std::set<simple_function*> found_entities =
				name_lookup::find_local
				<
					semantic_entity_analysis::identification_policies::by_name,
					open_declarative_region_ptr_variant,
					false,
					true,
					simple_function
				>
				(
					opt_identifier_node->value(),
					found_declarative_region
				)
			;

			//add the functions to the namespace (as entity aliases)
			for(auto i = found_entities.begin(); i != found_entities.end(); ++i)
			{
				simple_function& entity = **i;
				namespace_entity.add_member(entity_alias<simple_function>(entity));
			}
		}
	}
	else if(boost::optional<const operator_function_id&> opt_operator_function_id_node = get<operator_function_id>(&unqualified_id_node))
	{
		//if no entity has been found, try to find functions
		std::set<operator_function*> found_entities =
			name_lookup::find_local
			<
				semantic_entity_analysis::identification_policies::by_overloaded_operator,
				open_declarative_region_ptr_variant,
				false,
				true,
				operator_function
			>
			(
				get_operator_function_operator(get_operator(*opt_operator_function_id_node)),
				found_declarative_region
			)
		;

		//add the functions to the namespace (as entity aliases)
		for(auto i = found_entities.begin(); i != found_entities.end(); ++i)
		{
			operator_function& entity = **i;
			namespace_entity.add_member(entity_alias<operator_function>(entity));
		}
	}
	else
	{
		assert(false); //not implemented yet
	}
}

template<class Namespace>
void
fill_namespace
(
	Namespace& namespace_entity,
	const syntax_nodes::function_definition& function_definition_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const declarator& declarator_node = syntax_node_analysis::get_declarator(function_definition_node);
	const bool has_leading_double_colon = syntax_node_analysis::has_leading_double_colon(declarator_node);
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node =
		syntax_node_analysis::get_nested_name_specifier(declarator_node)
	;
	//is the function's identifier qualified (xxx::f())?
	const bool is_qualified = has_leading_double_colon || opt_nested_name_specifier_node;

	//find the enclosing declarative region of the function (xxx in void xxx::f())
	function_enclosing_declarative_region_ptr_variant function_declarative_region =
		is_qualified ?
		find_function_enclosing_declarative_region
		(
			has_leading_double_colon,
			opt_nested_name_specifier_node,
			&namespace_entity
		):
		&namespace_entity
	;

	//is it a class member function?
	const bool is_class_member =
		utility::get<class_*>(&function_declarative_region) ||
		utility::get<member_class*>(&function_declarative_region)
	;

	//create an empty function corresponding to the function-definition
	function_ptr_variant function_entity = create_function
	(
		function_definition_node,
		&namespace_entity,
		is_class_member,
		false,
		member_access::PUBLIC
	);

	//The function entity may have already been declared previously in the code.
	//If so, the function entity corresponding to the function-definition
	//(and to the previous function declaration) already exists.
	//Let's try to find it.
	boost::optional<function_ptr_variant> opt_already_existing_function_entity =
		find_function
		(
			function_entity,
			function_declarative_region
		)
	;

	if(is_qualified)
	{
		if(opt_already_existing_function_entity)
		{
			//define the function
			define_function(*opt_already_existing_function_entity, function_definition_node, &namespace_entity);
		}
		else
		{
			//since the identifier of the function is qualified,
			//the function should have been declared
			throw std::runtime_error("error: function declaration missing");
		}
	}
	else
	{
		if(opt_already_existing_function_entity)
		{
			//define the function
			define_function
			(
				*opt_already_existing_function_entity,
				function_definition_node,
				&namespace_entity
			);
		}
		else
		{
			//declare the function
			if(is_class_member)
			{
				std::runtime_error("error: this function must be a nonstatic member function");
			}
			else if(auto opt_operator_function_entity = get<operator_function*>(&function_entity))
				namespace_entity.add_member(std::unique_ptr<operator_function>(*opt_operator_function_entity));
			else if(auto opt_simple_function_entity = get<simple_function*>(&function_entity))
				namespace_entity.add_member(std::unique_ptr<simple_function>(*opt_simple_function_entity));
			else
				assert(false);

			//define the function
			define_function
			(
				function_entity,
				function_definition_node,
				&namespace_entity
			);
		}
	}
}

template<class Namespace, class Class>
Class&
add_class
(
	Namespace& namespace_entity,
	std::unique_ptr<Class>&& class_entity
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	typename generic_queries::detail::get_members_return_type<Namespace, Class, false>::type classes =
		generic_queries::detail::get_members<Class>(namespace_entity)
	;
	for(auto i = classes.begin(); i != classes.end(); ++i)
	{
		Class& current_class = *i;
		if(!current_class.complete() && current_class.name() == class_entity->name())
			return current_class;
	}

	Class& class_entity_ref = *class_entity;
	namespace_entity.add_member(std::move(class_entity));
	return class_entity_ref;
}



template<class Namespace>
class add_alias_visitor: public utility::static_visitor<void>
{
	public:
		add_alias_visitor(Namespace& namespace_entity):
			namespace_entity_(namespace_entity)
		{
		}

		template<class Entity>
		void
		operator()(Entity* entity)
		{
			namespace_entity_.add_member(semantic_entities::entity_alias<Entity>(*entity));
		}

	private:
		Namespace& namespace_entity_;
};

template<class Namespace, class... Entities>
void
add_alias
(
	Namespace& namespace_entity,
	const utility::variant<Entities...>& entity
)
{
	add_alias_visitor<Namespace> visitor(namespace_entity);
	apply_visitor(visitor, entity);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

