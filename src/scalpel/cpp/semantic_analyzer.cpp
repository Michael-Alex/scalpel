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

#include "semantic_analyzer.hpp"
#include "detail/semantic_analysis/name_lookup.hpp"
#include "detail/semantic_analysis/basic_functions.hpp"
#include <iostream>
#include <stdexcept>

namespace scalpel { namespace cpp
{

using namespace syntax_nodes;
using namespace semantic_entities;
using namespace detail::semantic_analysis;

std::shared_ptr<semantic_graph>
semantic_analyzer::operator()(const syntax_tree& tree)
{
	//create semantic graph
	std::shared_ptr<namespace_> global_namespace = namespace_::make_shared();

	auto opt_declaration_seq_node = get_declaration_seq_node(tree);
	if(opt_declaration_seq_node)
		analyze(*opt_declaration_seq_node, global_namespace);

	return global_namespace;
}

std::shared_ptr<class_>
semantic_analyzer::create_class(const class_specifier& syntax_node)
{
	//get the name of the class
	std::string class_name;
	const optional_node<identifier_or_template_id>& opt_id_or_templ = get_identifier_or_template_id(get_class_head(syntax_node));
	if(opt_id_or_templ)
	{
		const boost::optional<const identifier&> id = get<identifier>(&*opt_id_or_templ);

		if(id)
		{
			class_name = id->value();
		}
	}

	//create the class
	assert(class_name != "");
	return class_::make_shared(class_name);
}

void
semantic_analyzer::fill_class
(
	std::shared_ptr<class_> c,
	const class_specifier& class_specifier_node
)
{
	auto class_head_node = get_class_head(class_specifier_node);

	//get base classes
	if(auto opt_base_clause_node = get_base_clause(class_head_node))
	{
		auto base_specifier_list_node = get_base_specifier_list(*opt_base_clause_node);
		for
		(
			auto i = base_specifier_list_node.begin();
			i != base_specifier_list_node.end();
			++i
		)
		{
			auto base_specifier_node = i->main_node();

			//is it virtual inheritance?
			bool is_virtual = has_virtual_keyword(base_specifier_node);

			//get base class access
			class_::access access = class_::access::PRIVATE; //if nothing is specified, the access is private
			if(auto opt_access_specifier_node = get_access_specifier(base_specifier_node))
			{
				access = get_access(*opt_access_specifier_node);
			}

			//get base class
			auto nested_identifier_or_template_id_node = get_nested_identifier_or_template_id(base_specifier_node);
			std::shared_ptr<class_> base_class =
				name_lookup::find_entities<false, false, class_>(nested_identifier_or_template_id_node, c)
			;

			c->add_base_class(base_class, access, is_virtual);
		}
	}

	//default current_access
	auto class_key_node = get_class_key(class_head_node);
	class_::access current_access = class_::access::PUBLIC; //the default current_access is public...
	if(get<predefined_text_node<str::class_>>(&class_key_node)) //... unless the syntax node represents a class (neither a struct nor a union)
	{
		current_access = class_::access::PRIVATE;
	}

	//get the members of the class
	auto opt_member_specification = get_member_specification(class_specifier_node);
	if(opt_member_specification)
	{
		auto member_specification_node = *opt_member_specification;
		for(auto i = member_specification_node.begin(); i != member_specification_node.end(); ++i) //for each part
		{
			auto part = i->main_node();

			if(auto opt_member_declaration_node = get<member_declaration>(&part))
			{
				if(auto opt_member_declaration_function_definition_node = get<member_declaration_function_definition>(&*opt_member_declaration_node))
				{
					auto function_definition_node = get_function_definition(*opt_member_declaration_function_definition_node);
					//analyze(function_definition_node, c);
				}
				else if(auto opt_member_declaration_member_declarator_list_node = get<member_declaration_member_declarator_list>(&*opt_member_declaration_node))
				{
					auto opt_decl_specifier_seq_node = get_decl_specifier_seq(*opt_member_declaration_member_declarator_list_node);
					auto opt_member_declarator_list_node = get_member_declarator_list(*opt_member_declaration_member_declarator_list_node);

					if(opt_member_declarator_list_node)
					{
						auto member_declarator_list_node = *opt_member_declarator_list_node;
						for
						(
							auto j = member_declarator_list_node.begin();
							j != member_declarator_list_node.end();
							++j
						)
						{
							auto member_declarator_node = j->main_node();
							if(auto opt_member_declarator_declarator_node = get<member_declarator_declarator>(&member_declarator_node))
							{
								auto member_declarator_declarator_node = *opt_member_declarator_declarator_node;
								auto declarator_node = get_declarator(member_declarator_declarator_node);
								if(opt_decl_specifier_seq_node)
								{
									auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
									if(is_function_declaration(declarator_node))
									{
										if(is_operator_function_declaration(declarator_node)) //operator function
										{
											c->add_member
											(
												create_operator_function(decl_specifier_seq_node, declarator_node, c),
												current_access,
												is_qualified<str::const_>(declarator_node),
												is_qualified<str::volatile_>(declarator_node),
												has_virtual_specifier(decl_specifier_seq_node),
												has_pure_specifier(member_declarator_declarator_node)
											);
										}
										else if(is_conversion_function_declaration(declarator_node)) //conversion function
										{
											c->add_member
											(
												std::make_shared<class_::conversion_function>
												(
													get_conversion_function_type(declarator_node, c),
													has_inline_specifier(decl_specifier_seq_node)
												),
												current_access,
												is_qualified<str::const_>(declarator_node),
												is_qualified<str::volatile_>(declarator_node),
												has_virtual_specifier(decl_specifier_seq_node),
												has_pure_specifier(member_declarator_declarator_node)
											);
										}
										else if(c->name() == get_identifier(declarator_node).value()) //constructor or destructor
										{
											if(!is_destructor_declaration(declarator_node)) //constructor
											{
												c->add_member
												(
													std::make_shared<class_::constructor>
													(
														std::move(create_parameters(declarator_node, c)),
														has_inline_specifier(decl_specifier_seq_node),
														has_explicit_specifier(decl_specifier_seq_node)
													),
													current_access
												);
											}
											else //destructor
											{
												c->set_destructor
												(
													std::make_shared<class_::destructor>
													(
														has_inline_specifier(decl_specifier_seq_node)
													),
													current_access,
													has_virtual_specifier(decl_specifier_seq_node),
													has_pure_specifier(member_declarator_declarator_node)
												);
											}
										}
										else //simple function
										{
											c->add_member
											(
												create_simple_function(decl_specifier_seq_node, declarator_node, c),
												current_access,
												is_qualified<str::const_>(declarator_node),
												is_qualified<str::volatile_>(declarator_node),
												has_virtual_specifier(decl_specifier_seq_node),
												has_pure_specifier(member_declarator_declarator_node)
											);
										}
									}
									else //variable
									{
										c->add_member
										(
											create_variable(decl_specifier_seq_node, declarator_node, c),
											current_access,
											has_mutable_specifier(decl_specifier_seq_node)
										);
									}
								}
								else
								{
									if(is_conversion_function_declaration(declarator_node)) //conversion function
									{
										c->add_member
										(
											std::make_shared<class_::conversion_function>
											(
												get_conversion_function_type(declarator_node, c),
												false
											),
											current_access,
											is_qualified<str::const_>(declarator_node),
											is_qualified<str::volatile_>(declarator_node),
											false,
											false
										);
									}
									else if(c->name() == get_identifier(declarator_node).value()) //constructor or destructor
									{
										if(!is_destructor_declaration(declarator_node)) //constructor
										{
											c->add_member
											(
												std::make_shared<class_::constructor>
												(
													std::move(create_parameters(declarator_node, c)),
													false,
													false
												),
												current_access
											);
										}
										else //destructor
										{
											c->set_destructor
											(
												std::make_shared<class_::destructor>(false),
												current_access,
												false,
												false
											);
										}
									}
								}
							}
						}
					}
					else if(opt_decl_specifier_seq_node)
					{
						auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
						for(auto j = decl_specifier_seq_node.begin(); j != decl_specifier_seq_node.end(); ++j)
						{
							auto decl_specifier_node = j->main_node();
							if(auto opt_type_specifier_node = get<type_specifier>(&decl_specifier_node))
							{
								auto type_specifier_node = *opt_type_specifier_node;
								if(auto opt_class_specifier_node = get<class_specifier>(&type_specifier_node))
								{
									auto class_specifier_node = *opt_class_specifier_node;

									std::shared_ptr<class_> new_nested_class = create_class(class_specifier_node);
									c->add_member
									(
										new_nested_class,
										current_access
									);
									fill_class(new_nested_class, class_specifier_node);
								}
							}
						}
					}
					else
					{
						assert(false);
					}
				}
				else if(auto opt_member_declaration_unqualified_id_node = get<member_declaration_unqualified_id>(&*opt_member_declaration_node))
				{
				}
				else if(auto opt_using_declaration_node = get<using_declaration>(&*opt_member_declaration_node))
				{
				}
				else if(auto opt_template_declaration_node = get<template_declaration>(&*opt_member_declaration_node))
				{
				}
				else
				{
					assert(false);
				}
			}
			else if(auto opt_member_specification_access_specifier_node = get<member_specification_access_specifier>(&part))
			{
				auto access_specifier_node = get_access_specifier(*opt_member_specification_access_specifier_node);
				current_access = get_access(access_specifier_node);
			}
			else
			{
				assert(false);
			}
		}
	}
}

semantic_entities::type_shared_ptr_variant
semantic_analyzer::decorate_type
(
	semantic_entities::type_shared_ptr_variant return_type,
	const bool is_const,
	const bool is_volatile
)
{
	if(is_const)
		return_type = std::make_shared<const const_>(return_type);
	if(is_volatile)
		return_type = std::make_shared<const volatile_>(return_type);

	return return_type;
}

semantic_entities::type_shared_ptr_variant
semantic_analyzer::decorate_type
(
	semantic_entities::type_shared_ptr_variant return_type,
	const syntax_nodes::ptr_operator_seq& ptr_operator_seq_node
)
{
	for(auto i = ptr_operator_seq_node.begin(); i != ptr_operator_seq_node.end(); ++i)
	{
		auto ptr_operator_node = i->main_node();
		if(auto opt_ptr_ptr_operator_node = get<ptr_ptr_operator>(&ptr_operator_node))
		{
			auto ptr_ptr_operator_node = *opt_ptr_ptr_operator_node;

			return_type = std::make_shared<const pointer>(return_type);

			if(auto opt_cv_qualifier_seq_node = get_cv_qualifier_seq(ptr_ptr_operator_node))
			{
				auto cv_qualifier_seq_node = *opt_cv_qualifier_seq_node;
				for
				(
					auto i = cv_qualifier_seq_node.begin();
					i != cv_qualifier_seq_node.end();
					++i
				)
				{
					auto cv_qualifier_node = i->main_node();

					if(get<predefined_text_node<str::const_>>(&cv_qualifier_node))
					{
						return_type = std::make_shared<const const_>(return_type);
					}
					else if(get<predefined_text_node<str::volatile_>>(&cv_qualifier_node))
					{
						return_type = std::make_shared<const volatile_>(return_type);
					}
				}
			}
		}
		else if(auto ref_ptr_operator_node = get<ref_ptr_operator>(&ptr_operator_node))
		{
			return_type = std::make_shared<const reference>(return_type);
		}
	}

	return return_type;
}

std::shared_ptr<const semantic_entities::built_in_type>
semantic_analyzer::get_built_in_type
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
)
{
	if
	(
		bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::bool_;
	}
	else if
	(
		!bool_type &&
		char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::char_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::double_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::float_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		(signed_type || int_type) &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::int_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::long_double;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//int_type &&
		!long_long_type &&
		long_type &&
		!short_type &&
		//signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::long_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//int_type &&
		long_long_type &&
		//long_type &&
		!short_type &&
		//signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::long_long_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		!long_long_type &&
		!long_type &&
		short_type &&
		//!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::short_int;
	}
	else if
	(
		!bool_type &&
		char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::unsigned_char;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::unsigned_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		!long_long_type &&
		long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::unsigned_long_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		long_long_type &&
		//!long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::unsigned_long_long_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		!long_long_type &&
		!long_type &&
		short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::unsigned_short_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		void_type &&
		!wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::void_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		wchar_t_type
	)
	{
		return built_in_type_shared_ptrs::wchar_t_;
	}

	throw std::runtime_error("Incorrect built-in type");
}

}} //namespace scalpel::cpp

