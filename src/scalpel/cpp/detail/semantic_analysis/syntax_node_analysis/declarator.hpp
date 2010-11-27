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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SYNTAX_NODE_ANALYSIS_DECLARATOR_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SYNTAX_NODE_ANALYSIS_DECLARATOR_HPP

#include <scalpel/cpp/syntax_tree.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace syntax_node_analysis
{

enum class declarator_type
{
	DESTRUCTOR_DECLARATOR,
	OPERATOR_FUNCTION_DECLARATOR,
	CONVERSION_FUNCTION_DECLARATOR,
	SIMPLE_FUNCTION_DECLARATOR,
	VARIABLE_DECLARATOR
};

declarator_type
get_declarator_type(const syntax_nodes::declarator& declarator_node);

boost::optional<const syntax_nodes::parameter_declaration_list&>
get_parameter_declaration_list(const syntax_nodes::declarator& declarator_node);

template<const std::string& Qualifier>
bool
is_qualified(const syntax_nodes::declarator& declarator_node);

syntax_nodes::identifier
get_identifier(const syntax_nodes::declarator& declarator_node);

bool
has_identifier(const syntax_nodes::declarator& declarator_node);

boost::optional<const syntax_nodes::nested_identifier_or_template_id&>
get_nested_identifier_or_template_id(const syntax_nodes::declarator& declarator_node);

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::syntax_node_analysis

#include "declarator.ipp"

#endif
