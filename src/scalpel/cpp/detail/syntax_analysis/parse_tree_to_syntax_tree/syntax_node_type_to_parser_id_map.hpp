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

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SYNTAX_NODE_TYPE_TO_PARSER_ID_MAP_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SYNTAX_NODE_TYPE_TO_PARSER_ID_MAP_HPP

#include "../../../syntax_tree.hpp"
#include "../grammar.hpp"

#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR(correct_id, node_type)\
template<>														\
struct syntax_node_type_to_parser_id_map<syntax_nodes::node_type>	\
{																\
	static														\
	boost::spirit::parser_id									\
	parser_id()													\
	{															\
		return id_t::correct_id;								\
	}															\
};

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

template<class SyntaxNodeT>
struct syntax_node_type_to_parser_id_map;

SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ASSIGNMENT_EXPRESSION,
	assignment_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ASSIGNMENT_EXPRESSION_CONDITION,
	assignment_expression_condition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ASSIGNMENT_EXPRESSION_FIRST_PART,
	assignment_expression_first_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ASSIGNMENT_EXPRESSION_FIRST_PART_SEQ,
	assignment_expression_first_part_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ASSIGNMENT_EXPRESSION_LAST_PART,
	assignment_expression_last_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION,
	template_argument_assignment_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION_FIRST_PART,
	template_argument_assignment_expression_first_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION_FIRST_PART_SEQ,
	template_argument_assignment_expression_first_part_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION_LAST_PART,
	template_argument_assignment_expression_last_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	BASE_CLAUSE,
	base_clause
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	BASE_SPECIFIER_LIST,
	base_specifier_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	BASE_SPECIFIER,
	base_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	BLOCK_DECLARATION,
	block_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	BOOLEAN_LITERAL,
	boolean_literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	BREAK_STATEMENT,
	break_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	BUILT_IN_TYPE_SPECIFIER,
	built_in_type_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CAST_EXPRESSION,
	cast_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CLASS_SPECIFIER,
	class_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	COMPOUND_STATEMENT,
	compound_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CONDITION,
	condition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CONDITIONAL_EXPRESSION,
	conditional_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_CONDITIONAL_EXPRESSION,
	template_argument_conditional_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CONTINUE_STATEMENT,
	continue_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CONVERSION_FUNCTION_ID,
	conversion_function_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CTOR_INITIALIZER,
	ctor_initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DECL_SPECIFIER,
	decl_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DECLARATION,
	declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DECLARATOR,
	declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DECLARATOR_ID,
	declarator_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DELETE_EXPRESSION,
	delete_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DESTRUCTOR_NAME,
	destructor_name
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DIRECT_DECLARATOR,
	direct_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DIRECT_DECLARATOR_ARRAY_PART,
	direct_declarator_array_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DIRECT_DECLARATOR_FUNCTION_PART,
	direct_declarator_function_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DIRECT_DECLARATOR_FIRST_PART,
	direct_declarator_first_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DIRECT_DECLARATOR_LAST_PART,
	direct_declarator_last_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DIRECT_DECLARATOR_LAST_PART_SEQ,
	direct_declarator_last_part_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DO_WHILE_STATEMENT,
	do_while_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ELABORATED_TYPE_SPECIFIER,
	elaborated_type_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EQUAL_INITIALIZER,
	equal_initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EXPRESSION,
	expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EXPRESSION_STATEMENT,
	expression_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	FOR_INIT_STATEMENT,
	for_init_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	FOR_STATEMENT,
	for_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	FUNCTION_DEFINITION,
	function_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SIMPLE_FUNCTION_DEFINITION,
	simple_function_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TRY_BLOCK_FUNCTION_DEFINITION,
	try_block_function_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	FUNCTION_SPECIFIER,
	function_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	GOTO_STATEMENT,
	goto_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ID_EXPRESSION,
	id_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	IDENTIFIER_OR_TEMPLATE_ID,
	identifier_or_template_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	INIT_DECLARATOR,
	init_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	INITIALIZER,
	initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	INITIALIZER_CLAUSE,
	initializer_clause
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	INITIALIZER_LIST,
	initializer_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	INITIALIZER_LIST_INITIALIZER_CLAUSE,
	initializer_list_initializer_clause
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ITERATION_STATEMENT,
	iteration_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	JUMP_STATEMENT,
	jump_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	LABELED_STATEMENT,
	labeled_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	LITERAL,
	literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEM_INITIALIZER_LIST,
	mem_initializer_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEM_INITIALIZER,
	mem_initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEM_INITIALIZER_ID,
	mem_initializer_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_DECLARATION,
	member_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_DECLARATION_FUNCTION_DEFINITION,
	member_declaration_function_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST,
	member_declaration_member_declarator_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_DECLARATION_UNQUALIFIED_ID,
	member_declaration_unqualified_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_DECLARATOR,
	member_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_DECLARATOR_BIT_FIELD_MEMBER,
	member_declarator_bit_field_member
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_DECLARATOR_DECLARATOR,
	member_declarator_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_SPECIFICATION_PART,
	member_specification_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_SPECIFICATION_ACCESS_SPECIFIER,
	member_specification_access_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NAMESPACE_DEFINITION,
	namespace_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NESTED_IDENTIFIER_OR_TEMPLATE_ID,
	nested_identifier_or_template_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NESTED_NAME_SPECIFIER,
	nested_name_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NESTED_NAME_SPECIFIER_LAST_PART,
	nested_name_specifier_last_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NESTED_NAME_SPECIFIER_LAST_PART_SEQ,
	nested_name_specifier_last_part_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NEW_EXPRESSION,
	new_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	OPERATOR_FUNCTION_ID,
	operator_function_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PARAMETER_DECLARATION,
	parameter_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PARAMETER_DECLARATION_LIST,
	parameter_declaration_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PARAMETER_DECLARATION_CLAUSE,
	parameter_declaration_clause
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	POSTFIX_EXPRESSION_LAST_PART_SEQ,
	postfix_expression_last_part_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	POSTFIX_EXPRESSION,
	postfix_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PRIMARY_EXPRESSION,
	primary_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PTR_OPERATOR,
	ptr_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PTR_PTR_OPERATOR,
	ptr_ptr_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	REF_PTR_OPERATOR,
	ref_ptr_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	QUALIFIED_ID,
	qualified_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	QUALIFIED_NESTED_ID,
	qualified_nested_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	QUALIFIED_OPERATOR_FUNCTION_ID,
	qualified_operator_function_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	QUALIFIED_TEMPLATE_ID,
	qualified_template_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	QUALIFIED_IDENTIFIER,
	qualified_identifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	RETURN_STATEMENT,
	return_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SELECTION_STATEMENT,
	selection_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SIMPLE_DECLARATION,
	simple_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SIMPLE_TYPE_SPECIFIER,
	simple_type_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SIMPLE_TEMPLATE_TYPE_SPECIFIER,
	simple_template_type_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	STATEMENT,
	statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	STORAGE_CLASS_SPECIFIER,
	storage_class_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT,
	template_argument
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_DECLARATION,
	template_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ID,
	template_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TRANSLATION_UNIT,
	translation_unit
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TRY_BLOCK,
	try_block
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPE_ID,
	type_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPE_SPECIFIER,
	type_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	UNARY_EXPRESSION,
	unary_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	UNARY_OPERATOR_UNARY_EXPRESSION,
	unary_operator_unary_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	UNQUALIFIED_ID,
	unqualified_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	USING_DECLARATION,
	using_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	USING_DIRECTIVE,
	using_directive
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	WHILE_STATEMENT,
	while_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	POSTFIX_EXPRESSION_FIRST_PART,
	postfix_expression_first_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SIMPLE_TYPE_SPECIFIER_POSTFIX_EXPRESSION,
	simple_type_specifier_postfix_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPENAME_EXPRESSION,
	typename_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_TYPENAME_EXPRESSION,
	template_typename_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DYNAMIC_CAST_EXPRESSION,
	dynamic_cast_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	STATIC_CAST_EXPRESSION,
	static_cast_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	REINTERPRET_CAST_EXPRESSION,
	reinterpret_cast_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CONST_CAST_EXPRESSION,
	const_cast_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPEID_EXPRESSION,
	typeid_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPE_ID_TYPEID_EXPRESSION,
	type_id_typeid_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	POSTFIX_EXPRESSION_LAST_PART,
	postfix_expression_last_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ROUND_BRACKETED_OPTIONAL_EXPRESSION,
	round_bracketed_optional_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DOT_ID_EXPRESSION,
	dot_id_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ARROW_ID_EXPRESSION,
	arrow_id_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DOT_PSEUDO_DESTRUCTOR_NAME,
	dot_pseudo_destructor_name
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ARROW_PSEUDO_DESTRUCTOR_NAME,
	arrow_pseudo_destructor_name
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	IF_STATEMENT,
	if_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SWITCH_STATEMENT,
	switch_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CASE_STATEMENT,
	case_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DEFAULT_STATEMENT,
	default_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CLASSIC_LABELED_STATEMENT,
	classic_labeled_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ROUND_BRACKETED_EXPRESSION,
	round_bracketed_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	HANDLER_SEQ,
	handler_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	HANDLER,
	handler
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	THROW_EXPRESSION,
	throw_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EXCEPTION_DECLARATION,
	exception_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EXCEPTION_DECLARATOR,
	exception_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EXCEPTION_ABSTRACT_DECLARATOR,
	exception_abstract_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPE_SPECIFIER_SEQ,
	type_specifier_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DIRECT_ABSTRACT_DECLARATOR,
	direct_abstract_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PTR_OPERATOR_SEQ,
	ptr_operator_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ABSTRACT_DECLARATOR,
	abstract_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	FUNCTION_TRY_BLOCK,
	function_try_block
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	OPERATOR,
	operator_
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ARRAY_OPERATOR,
	array_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NEW_ARRAY_OPERATOR,
	new_array_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DELETE_ARRAY_OPERATOR,
	delete_array_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SIMPLE_OPERATOR,
	simple_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CLASS_ELABORATED_SPECIFIER,
	class_elaborated_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ENUM_ELABORATED_SPECIFIER,
	enum_elaborated_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPENAME_TEMPLATE_ELABORATED_SPECIFIER,
	typename_template_elaborated_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPENAME_ELABORATED_SPECIFIER,
	typename_elaborated_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPE_ID_NEW_EXPRESSION,
	type_id_new_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NEW_TYPE_ID_NEW_EXPRESSION,
	new_type_id_new_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NEW_TYPE_ID,
	new_type_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NEW_DECLARATOR,
	new_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPEOF_KEYWORD,
	typeof_keyword
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPEOF_EXPRESSION,
	typeof_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ENUM_SPECIFIER,
	enum_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SIMPLE_DELETE_EXPRESSION,
	simple_delete_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ARRAY_DELETE_EXPRESSION,
	array_delete_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	BRACKETED_DECLARATOR,
	bracketed_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EXCEPTION_SPECIFICATION,
	exception_specification
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DIRECT_NEW_DECLARATOR,
	direct_new_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_SPECIFICATION,
	member_specification
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	STATEMENT_SEQ,
	statement_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SQUARE_BRACKETED_EXPRESSION,
	square_bracketed_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ACCESS_SPECIFIER,
	access_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ASSIGNMENT_OPERATOR,
	assignment_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CV_QUALIFIER,
	cv_qualifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CV_QUALIFIER_SEQ,
	cv_qualifier_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPE_ID_LIST,
	type_id_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DECLARATION_SEQ,
	declaration_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	UNARY_OPERATOR,
	unary_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CLASS_KEY,
	class_key
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_LIST,
	template_argument_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPE_PARAMETER,
	type_parameter
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CLASS_TYPE_PARAMETER,
	class_type_parameter
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_TYPE_PARAMETER,
	template_type_parameter
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPENAME_TYPE_PARAMETER,
	typename_type_parameter
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EXPLICIT_SPECIALIZATION,
	explicit_specialization
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EXPLICIT_INSTANTIATION,
	explicit_instantiation
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PM_PTR_EXPRESSION,
	pm_ptr_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PM_REF_EXPRESSION,
	pm_ref_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MODULO_EXPRESSION,
	modulo_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DIVISIVE_EXPRESSION,
	divisive_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MULTIPLICATIVE_EXPRESSION,
	multiplicative_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SUBTRACTIVE_EXPRESSION,
	subtractive_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ADDITIVE_EXPRESSION,
	additive_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	LEFT_SHIFT_EXPRESSION,
	left_shift_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	RIGHT_SHIFT_EXPRESSION,
	right_shift_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	LESS_THAN_OR_EQUAL_TO_EXPRESSION,
	less_than_or_equal_to_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	LESS_THAN_EXPRESSION,
	less_than_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	GREATER_THAN_OR_EQUAL_TO_EXPRESSION,
	greater_than_or_equal_to_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	GREATER_THAN_EXPRESSION,
	greater_than_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	INEQUALITY_EXPRESSION,
	inequality_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EQUALITY_EXPRESSION,
	equality_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	AND_EXPRESSION,
	and_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	EXCLUSIVE_OR_EXPRESSION,
	exclusive_or_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	INCLUSIVE_OR_EXPRESSION,
	inclusive_or_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	LOGICAL_AND_EXPRESSION,
	logical_and_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	LOGICAL_OR_EXPRESSION,
	logical_or_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ROUND_BRACKETED_RIGHT_SHIFT_EXPRESSION,
	round_bracketed_right_shift_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ROUND_BRACKETED_GREATER_THAN_EXPRESSION,
	round_bracketed_greater_than_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_RIGHT_SHIFT_EXPRESSION,
	template_argument_right_shift_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_LESS_THAN_OR_EQUAL_TO_EXPRESSION,
	template_argument_less_than_or_equal_to_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_LESS_THAN_EXPRESSION,
	template_argument_less_than_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_GREATER_THAN_OR_EQUAL_TO_EXPRESSION,
	template_argument_greater_than_or_equal_to_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_GREATER_THAN_EXPRESSION,
	template_argument_greater_than_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_INEQUALITY_EXPRESSION,
	template_argument_inequality_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_EQUALITY_EXPRESSION,
	template_argument_equality_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_AND_EXPRESSION,
	template_argument_and_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_EXCLUSIVE_OR_EXPRESSION,
	template_argument_exclusive_or_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_INCLUSIVE_OR_EXPRESSION,
	template_argument_inclusive_or_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_LOGICAL_AND_EXPRESSION,
	template_argument_logical_and_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_ARGUMENT_LOGICAL_OR_EXPRESSION,
	template_argument_logical_or_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CAST_EXPRESSION_FIRST_PART,
	cast_expression_first_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CAST_EXPRESSION_FIRST_PART_SEQ,
	cast_expression_first_part_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DECL_SPECIFIER_SEQ,
	decl_specifier_seq
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	INIT_DECLARATOR_LIST,
	init_declarator_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	BRACKETED_ABSTRACT_DECLARATOR,
	bracketed_abstract_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ASM_DEFINITION,
	asm_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	QUALIFIED_NAMESPACE_SPECIFIER,
	qualified_namespace_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	NAMESPACE_ALIAS_DEFINITION,
	namespace_alias_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	LINKAGE_SPECIFICATION,
	linkage_specification
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DECLARATION_LINKAGE_SPECIFICATION,
	declaration_linkage_specification
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	DECLARATION_SEQ_LINKAGE_SPECIFICATION,
	declaration_seq_linkage_specification
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ENUMERATOR_LIST,
	enumerator_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	ENUMERATOR_DEFINITION,
	enumerator_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_DECLARATOR_DECLARATOR_LAST_PART,
	member_declarator_declarator_last_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	PURE_SPECIFIER,
	pure_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CONSTANT_INITIALIZER,
	constant_initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TYPE_ID_SIZEOF_EXPRESSION,
	type_id_sizeof_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	UNARY_SIZEOF_EXPRESSION,
	unary_sizeof_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	MEMBER_DECLARATOR_LIST,
	member_declarator_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_PARAMETER_LIST,
	template_parameter_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	TEMPLATE_PARAMETER,
	template_parameter
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CLASS_HEAD,
	class_head
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	IDENTIFIER,
	identifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	CHARACTER_LITERAL,
	character_literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	FLOATING_LITERAL,
	floating_literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	INTEGER_LITERAL,
	integer_literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	SPACE,
	space
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR
(
	STRING_LITERAL,
	string_literal
)

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#undef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_TYPE_PAIR

#endif
