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

#include "list_entities.hpp"
#include "create_unique_id.hpp"
#include <scalpel/cpp/semantic_entities/generic_queries/detail/get_members.hpp>

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

namespace
{
	template<class Class>
	void
	list_child_entities(const Class& parent_entity, entity_groups& groups);

	template<class ChildEntity, class ParentEntity>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, entity_groups& groups);
}

namespace
{
	void
	list_child_entities(const namespace_& parent_entity, entity_groups& groups)
	{
		const utility::unique_ptr_vector<namespace_>& child_namespaces = parent_entity.namespaces();
		for(auto i = child_namespaces.begin(); i != child_namespaces.end(); ++i)
		{
			list_child_entities(*i, groups);
		}

		const utility::unique_ptr_vector<class_>& child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities(*i, groups);
		}

		list_child_entities_of_type<namespace_>(parent_entity, groups);
		list_child_entities_of_type<class_>(parent_entity, groups);
		list_child_entities_of_type<enum_>(parent_entity, groups);
		list_child_entities_of_type<typedef_>(parent_entity, groups);
		list_child_entities_of_type<operator_function>(parent_entity, groups);
		list_child_entities_of_type<simple_function>(parent_entity, groups);
		list_child_entities_of_type<variable>(parent_entity, groups);
	}

	template<class Class>
	void
	list_child_entities(const Class& parent_entity, entity_groups& groups)
	{
		const utility::unique_ptr_vector<member_class>& child_classes = parent_entity.nested_classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities(*i, groups);
		}

		list_child_entities_of_type<member_class>(parent_entity, groups);
		list_child_entities_of_type<member_enum>(parent_entity, groups);
		list_child_entities_of_type<member_typedef>(parent_entity, groups);
		list_child_entities_of_type<constructor>(parent_entity, groups);
		list_child_entities_of_type<destructor>(parent_entity, groups);
		list_child_entities_of_type<operator_member_function>(parent_entity, groups);
		list_child_entities_of_type<conversion_function>(parent_entity, groups);
		list_child_entities_of_type<simple_member_function>(parent_entity, groups);
		list_child_entities_of_type<member_variable>(parent_entity, groups);
	}

	template<class ChildEntity, class ParentEntity>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, entity_groups& groups)
	{
		typename generic_queries::detail::member_type_traits<ChildEntity, true>::return_type entities =
			generic_queries::detail::get_members<ChildEntity>(parent_entity)
		;
		for(auto i = entities.begin(); i != entities.end(); ++i)
		{
			const ChildEntity& entity = *i;
			get_entity_groups_of_type<ChildEntity>(groups)[create_unique_id(entity)].push_back(&entity);
		}
	}
}

entity_groups
list_entities(const utility::unique_ptr_vector<semantic_graph>& semantic_graphs)
{
	entity_groups groups;

	//for each semantic graph...
	for(auto i = semantic_graphs.begin(); i != semantic_graphs.end(); ++i)
	{
		const semantic_graph& graph = *i;
		list_child_entities(graph, groups);
		groups.global_namespaces.push_back(&graph);
	}

	return groups;
}

}}}} //namespace scalpel::cpp::linking::detail

