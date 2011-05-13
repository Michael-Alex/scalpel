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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_ENUM_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_ENUM_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

std::unique_ptr<semantic_entities::enum_>
create_enum(const syntax_nodes::enum_specifier& enum_specifier_node);

semantic_entities::enum_*
create_enum2(const syntax_nodes::enum_specifier& enum_specifier_node);

std::unique_ptr<semantic_entities::member_enum>
create_member_enum(const syntax_nodes::enum_specifier& enum_specifier_node, const semantic_entities::member_access access);

semantic_entities::member_enum*
create_member_enum2(const syntax_nodes::enum_specifier& enum_specifier_node, const semantic_entities::member_access access);

template<class Enum>
void
fill_enum
(
	Enum& enum_entity,
	const syntax_nodes::enum_specifier& enum_specifier_node
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#include "enum_construction.ipp"

#endif

