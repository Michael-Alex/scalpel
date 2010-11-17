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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_BASIC_FUNCTIONS_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_BASIC_FUNCTIONS_HPP

#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

//TODO A lot of syntax checks are done in some of these functions.
//That kind of work should be done by the syntax analyzer.
//The grammar should be reformulated so the semantic analysis
//can be performed more straightforwardly.

//
//class related
//

semantic_entities::class_::access
get_access(const syntax_nodes::access_specifier access_specifier_node);



//
//function related
//

bool
is_function_declaration(const syntax_nodes::declarator& declarator_node);

bool
is_simple_function_declaration(const syntax_nodes::declarator& declarator_node);

bool
is_operator_function_declaration(const syntax_nodes::declarator& declarator_node);

bool
is_conversion_function_declaration(const syntax_nodes::declarator& declarator_node);

bool
is_destructor_declaration(const syntax_nodes::declarator& declarator_node);

bool
has_pure_specifier(const syntax_nodes::member_declarator_declarator& member_declarator_declarator_node);



//
//decl_specifier_seq related
//

enum decl_specifier_seq_type
{
	SIMPLE_DECL_SPECIFIER_SEQ,
	CONSTRUCTOR_DECL_SPECIFIER_SEQ,
	CLASS_DECL_SPECIFIER_SEQ,
	CLASS_FORWARD_DECL_SPECIFIER_SEQ
};

decl_specifier_seq_type
get_decl_specifier_seq_type(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

const syntax_nodes::class_specifier&
get_class_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

const syntax_nodes::class_elaborated_specifier&
get_class_elaborated_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

template<class SpecifierNodeT, const std::string& Specifier>
bool
has_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

inline
bool
has_inline_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::function_specifier, utility::extern_strings::inline_>(decl_specifier_seq_node);
}

inline
bool
has_virtual_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::function_specifier, utility::extern_strings::virtual_>(decl_specifier_seq_node);
}

inline
bool
has_explicit_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::function_specifier, utility::extern_strings::explicit_>(decl_specifier_seq_node);
}

inline
bool
has_static_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::storage_class_specifier, utility::extern_strings::static_>(decl_specifier_seq_node);
}

inline
bool
has_mutable_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::storage_class_specifier, utility::extern_strings::mutable_>(decl_specifier_seq_node);
}

bool
has_typedef_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);



//
//declarator related
//

enum declarator_type
{
	SIMPLE_FUNCTION_DECLARATOR,
	OPERATOR_FUNCTION_DECLARATOR,
	CONVERSION_FUNCTION_DECLARATOR,
	VARIABLE_DECLARATOR
};

declarator_type
get_declarator_type(const syntax_nodes::declarator& declarator_node);



//
//qualifier related
//

template<const std::string& Qualifier>
bool
is_qualified(const syntax_nodes::declarator& declarator_node);



//
//common
//

syntax_nodes::identifier
get_identifier(const syntax_nodes::declarator& declarator_node);

bool
has_identifier(const syntax_nodes::declarator& declarator_node);

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#include "basic_functions.ipp"

#endif

