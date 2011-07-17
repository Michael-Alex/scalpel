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

#include "linkage.hpp"
#include "linkage/detail/assemble_final_graph.hpp"
#include "linkage/detail/create_final_graph_entities.hpp"
#include "linkage/detail/list_entities.hpp"
#include "linkage/detail/final_graph_entities.hpp"
#include "linkage/detail/entity_groups.hpp"
#include <iostream>

namespace scalpel { namespace cpp
{

namespace linkage
{

namespace
{
	template<class Entity>
	void
	print(const std::string& title, const typename detail::entity_groups_of_type<Entity>::type& group)
	{
		const unsigned int entity_count = group.size();
		if(entity_count > 0)
		{
			std::cout << title << ":\n";
			for(auto i = group.begin(); i != group.end(); ++i)
				std::cout << '"' << i->first << "\" (x" << i->second.size() << ")\n";
		}
	}

	void
	print(const detail::entity_groups& groups)
	{
		print<semantic_entities::namespace_>("namespace_", groups.namespaces);
		print<semantic_entities::class_>("class_", groups.classes);
		print<semantic_entities::member_class>("member_class", groups.member_classes);
		print<semantic_entities::enum_t>("enum_t", groups.enums);
		print<semantic_entities::member_enum_t>("member_enum_t", groups.member_enums);
		print<semantic_entities::typedef_>("typedef_", groups.typedefs);
		print<semantic_entities::member_typedef>("member_typedef", groups.member_typedefs);
		print<semantic_entities::constructor>("constructor", groups.constructors);
		print<semantic_entities::destructor>("destructor", groups.destructors);
		print<semantic_entities::operator_member_function>("operator_member_function", groups.operator_member_functions);
		print<semantic_entities::conversion_function>("conversion_function", groups.conversion_functions);
		print<semantic_entities::simple_member_function>("simple_member_function", groups.simple_member_functions);
		print<semantic_entities::operator_function>("operator_function", groups.operator_functions);
		print<semantic_entities::simple_function>("simple_function", groups.simple_functions);
		print<semantic_entities::variable>("variable", groups.variables);
		print<semantic_entities::member_variable>("member_variable", groups.member_variables);
	}
}

std::unique_ptr<semantic_entities::linked_namespace>
link(const utility::unique_ptr_vector<semantic_graph>& semantic_graphs)
{
	detail::entity_groups groups = detail::list_entities(semantic_graphs);
	//print(groups);
	detail::final_graph_entities final_graph_entities;
	detail::create_final_graph_entities(groups, final_graph_entities);
	return detail::assemble_final_graph(groups, final_graph_entities);
}

} //namespace semantic_analysis

}} //namespace scalpel::cpp

