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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_FUNCTION_CONSTRUCTION_IPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_FUNCTION_CONSTRUCTION_IPP

#include "semantic_graph_analysis.hpp"
#include "syntax_node_analysis.hpp"
#include <set>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

template<class FunctionT>
std::shared_ptr<FunctionT>
find_function
(
	const std::shared_ptr<const FunctionT> function_signature,
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;
	namespace detail = detail::semantic_analysis;

	//find the functions from the name
	std::set<std::shared_ptr<simple_function>> found_functions;
	if
	(
		boost::optional<const syntax_nodes::nested_identifier_or_template_id&> opt_nested_identifier_or_template_id_node =
			syntax_node_analysis::get_nested_identifier_or_template_id(syntax_node_analysis::get_declarator(function_definition_node))
	)
	{
		found_functions =
			semantic_graph_analysis::name_lookup::find<true, true, FunctionT>
			(
				*opt_nested_identifier_or_template_id_node,
				current_declarative_region,
				false
			)
		;
	}
	else
	{
		found_functions =
			semantic_graph_analysis::name_lookup::find<true, true, FunctionT>
			(
				identifier(function_signature->name()),
				current_declarative_region
			)
		;
	}

	//filter the found functions with the signature
	for
	(
		auto i = found_functions.begin();
		i != found_functions.end();
		++i
	)
	{
		std::shared_ptr<FunctionT> found_function = *i;
		if(found_function->has_same_signature(*function_signature))
		{
			return found_function;
			break;
		}
	}

	return std::shared_ptr<FunctionT>();
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif

