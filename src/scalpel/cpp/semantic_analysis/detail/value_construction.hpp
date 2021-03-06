/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_VALUE_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_VALUE_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

semantic_entities::expression_t
create_integer_value(const syntax_nodes::integer_literal& integer_literal_node);

semantic_entities::expression_t
create_boolean_value(const syntax_nodes::boolean_literal& boolean_literal_node);

semantic_entities::expression_t
create_floating_value(const syntax_nodes::floating_literal& floating_literal_node);

semantic_entities::expression_t
create_character_value(const syntax_nodes::character_literal& character_literal_node);

semantic_entities::expression_t
create_string_value(const syntax_nodes::string_literal& string_literal_node);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

