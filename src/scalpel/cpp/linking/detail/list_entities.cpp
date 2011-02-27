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
#include "../../semantic_analysis/detail/semantic_entity_analysis/get_members.hpp"

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

namespace
{
	template<class Class, class ParentEntityTree>
	void
	list_class_child_entities(const Class& parent_entity, ParentEntityTree& tree);

	template<class ChildEntity, class ParentEntity, class ParentEntityTree>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, ParentEntityTree& tree);
}

namespace
{
	void
	list_child_entities(const namespace_& parent_entity, linking_tree::namespace_& tree)
	{
		//create and fill namespace subtrees
		const utility::unique_ptr_vector<namespace_>& child_namespaces = parent_entity.namespaces();
		for(auto i = child_namespaces.begin(); i != child_namespaces.end(); ++i)
		{
			const namespace_& child_namespace = *i;
			const std::string& namespace_name = child_namespace.name();

			auto it = tree.namespaces.find(namespace_name);
			if(it == tree.namespaces.end())
			{
				it = tree.namespaces.insert(std::pair<std::string, linking_tree::namespace_>(namespace_name, linking_tree::namespace_())).first;
			}

			list_child_entities(child_namespace, it->second);
		}

		//create and fill class subtrees
		const utility::unique_ptr_vector<class_>& child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			const class_& child_class = *i;
			const std::string& class_name = child_class.name();

			auto it = tree.classes.find(class_name);
			if(it == tree.classes.end())
			{
				it = tree.classes.insert(std::pair<std::string, linking_tree::class_>(class_name, linking_tree::class_())).first;
			}

			list_class_child_entities(child_class, it->second);
		}

		//fill current tree
		list_child_entities_of_type<class_>(parent_entity, tree);
		list_child_entities_of_type<enum_>(parent_entity, tree);
		list_child_entities_of_type<typedef_>(parent_entity, tree);
		list_child_entities_of_type<operator_function>(parent_entity, tree);
		list_child_entities_of_type<simple_function>(parent_entity, tree);
		list_child_entities_of_type<variable>(parent_entity, tree);
	}

	template<class Class, class ParentEntityTree>
	void
	list_class_child_entities(const Class& parent_entity, ParentEntityTree& tree)
	{
		//create and fill class subtrees
		const utility::unique_ptr_vector<member_class>& child_classes = parent_entity.nested_classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			const member_class& child_class = *i;
			const std::string& class_name = child_class.name();

			auto it = tree.classes.find(class_name);
			if(it == tree.classes.end())
			{
				it = tree.classes.insert(std::pair<std::string, linking_tree::class_>(class_name, linking_tree::class_())).first;
			}

			list_class_child_entities(child_class, it->second);
		}

		//fill current tree
		list_child_entities_of_type<member_enum>(parent_entity, tree);
		list_child_entities_of_type<member_typedef>(parent_entity, tree);
		list_child_entities_of_type<constructor>(parent_entity, tree);
		list_child_entities_of_type<destructor>(parent_entity, tree);
		list_child_entities_of_type<operator_member_function>(parent_entity, tree);
		list_child_entities_of_type<conversion_function>(parent_entity, tree);
		list_child_entities_of_type<simple_member_function>(parent_entity, tree);
		list_child_entities_of_type<member_variable>(parent_entity, tree);
	}

	template<class ChildEntity, class ParentEntity, class ParentEntityTree>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, ParentEntityTree& tree)
	{
		typename semantic_analysis::detail::semantic_entity_analysis::member_type_traits<ChildEntity, true>::return_type entities =
			semantic_analysis::detail::semantic_entity_analysis::get_members<ChildEntity>(parent_entity)
		;
		for(auto i = entities.begin(); i != entities.end(); ++i)
		{
			const ChildEntity& entity = *i;
			linking_tree::get_entity_list<ChildEntity>(tree).list[create_unique_id(entity)].push_back(&entity);
		}
	}
}

linking_tree::namespace_
list_entities(const utility::unique_ptr_vector<semantic_graph>& semantic_graphs)
{
	linking_tree::namespace_ tree;

	//for each semantic graph...
	for(auto i = semantic_graphs.begin(); i != semantic_graphs.end(); ++i)
	{
		const semantic_graph& graph = *i;
		list_child_entities(graph, tree);
	}

	return tree;
}

}}}} //namespace scalpel::cpp::linking::detail

