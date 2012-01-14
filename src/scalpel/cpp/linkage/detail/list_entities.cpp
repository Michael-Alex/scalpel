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

#include "list_entities.hpp"
#include "create_unique_id.hpp"
#include <scalpel/cpp/semantic_entities/generic_queries/detail/get_members.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/has_external_linkage.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/has_members_of_type.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/is_class.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/is_union.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/is_enum.hpp>

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

using namespace semantic_entities;

namespace
{
	void
	list_child_entities(const unnamed_namespace& parent_entity, entity_groups& groups);

	template<bool force_internal_linkage, class Class>
	void
	list_child_entities
	(
		const Class& parent_entity,
		entity_groups& groups,
		typename boost::enable_if_c
		<
			semantic_entities::type_traits::is_class<Class>::value ||
			semantic_entities::type_traits::is_union<Class>::value
		>::type* = 0
	);

	template<bool force_internal_linkage, class Enum>
	void
	list_child_entities
	(
		const Enum& parent_entity,
		entity_groups& groups,
		typename boost::enable_if<semantic_entities::type_traits::is_enum<Enum>>::type* = 0
	);
}

namespace
{
	template<bool force_internal_linkage, class Entity>
	struct list_entity_impl;

	template<class Entity>
	struct list_entity_impl<true, Entity>
	{
		static
		void
		list_entity
		(
			const Entity& entity,
			entity_groups& groups
		)
		{
			groups.internal_entities_of_type<Entity>().push_back(&entity);
		}
	};

	template<class Entity>
	struct list_entity_impl<false, Entity>
	{
		static
		void
		list_entity
		(
			const Entity& entity,
			entity_groups& groups
		)
		{
			if(generic_queries::detail::has_external_linkage(entity))
			{
				const std::string unique_id = create_unique_id(entity);
				get_entity_groups_of_type<Entity>(groups)[unique_id].push_back(&entity); //list and group by unique id
			}
			else
			{
				list_entity_impl<true, Entity>::list_entity(entity, groups);
			}
		}
	};



	template<bool force_internal_linkage, class ChildEntity, class ParentEntity>
	void
	list_child_entities_of_type
	(
		const ParentEntity& parent_entity,
		entity_groups& groups,
		typename boost::enable_if<type_traits::has_members_of_type<ParentEntity, ChildEntity>>::type* = 0
	)
	{
		typename generic_queries::detail::get_members_return_type<ParentEntity, ChildEntity, true>::type entities =
			generic_queries::detail::get_members<ChildEntity>(parent_entity)
		;
		for(auto i = entities.begin(); i != entities.end(); ++i)
		{
			const ChildEntity& entity = *i;
			list_entity_impl<force_internal_linkage, ChildEntity>::list_entity(entity, groups);
		}
	}

	template<bool force_internal_linkage, class ChildEntity, class ParentEntity>
	inline
	void
	list_child_entities_of_type
	(
		const ParentEntity&,
		entity_groups&,
		typename boost::disable_if<type_traits::has_members_of_type<ParentEntity, ChildEntity>>::type* = 0
	)
	{
		//does nothing
	}



	template<bool force_internal_linkage>
	void
	list_child_entities(const namespace_& parent_entity, entity_groups& groups)
	{
		const utility::unique_ptr_vector_const_range<namespace_>::type child_namespaces = parent_entity.namespaces();
		for(auto i = child_namespaces.begin(); i != child_namespaces.end(); ++i)
		{
			list_child_entities<force_internal_linkage>(*i, groups);
		}

		if(const unnamed_namespace* opt_unnamed_namespace = parent_entity.get_unnamed_namespace())
		{
			groups.internal_unnamed_namespaces.push_back(opt_unnamed_namespace);
			list_child_entities(*opt_unnamed_namespace, groups);
		}

		const utility::unique_ptr_vector_const_range<class_>::type child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities<force_internal_linkage>(*i, groups);
		}

		const utility::unique_ptr_vector_const_range<union_>::type child_unions = parent_entity.unions();
		for(auto i = child_unions.begin(); i != child_unions.end(); ++i)
		{
			list_child_entities<force_internal_linkage>(*i, groups);
		}

		const utility::unique_ptr_vector_const_range<anonymous_union>::type child_anonymous_unions = parent_entity.anonymous_unions();
		for(auto i = child_anonymous_unions.begin(); i != child_anonymous_unions.end(); ++i)
		{
			list_child_entities<true>(*i, groups);
		}

		const utility::unique_ptr_vector_const_range<enum_>::type child_enums = parent_entity.enums();
		for(auto i = child_enums.begin(); i != child_enums.end(); ++i)
		{
			list_child_entities<force_internal_linkage>(*i, groups);
		}

		list_child_entities_of_type<force_internal_linkage, namespace_>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, class_>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, union_>(parent_entity, groups);
		list_child_entities_of_type<true, anonymous_union>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, enum_>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, typedef_>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, operator_function>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, simple_function>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, variable>(parent_entity, groups);
	}

	void
	list_child_entities(const unnamed_namespace& parent_entity, entity_groups& groups)
	{
		const utility::unique_ptr_vector_const_range<namespace_>::type child_namespaces = parent_entity.namespaces();
		for(auto i = child_namespaces.begin(); i != child_namespaces.end(); ++i)
		{
			list_child_entities<true>(*i, groups);
		}

		if(const unnamed_namespace* opt_unnamed_namespace = parent_entity.get_unnamed_namespace())
		{
			groups.internal_unnamed_namespaces.push_back(opt_unnamed_namespace);
			list_child_entities(*opt_unnamed_namespace, groups);
		}

		const utility::unique_ptr_vector_const_range<class_>::type child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities<true>(*i, groups);
		}

		const utility::unique_ptr_vector_const_range<union_>::type child_unions = parent_entity.unions();
		for(auto i = child_unions.begin(); i != child_unions.end(); ++i)
		{
			list_child_entities<true>(*i, groups);
		}

		const utility::unique_ptr_vector_const_range<anonymous_union>::type child_anonymous_unions = parent_entity.anonymous_unions();
		for(auto i = child_anonymous_unions.begin(); i != child_anonymous_unions.end(); ++i)
		{
			list_child_entities<true>(*i, groups);
		}

		const utility::unique_ptr_vector_const_range<enum_>::type child_enums = parent_entity.enums();
		for(auto i = child_enums.begin(); i != child_enums.end(); ++i)
		{
			list_child_entities<true>(*i, groups);
		}

		list_child_entities_of_type<true, namespace_>(parent_entity, groups);
		list_child_entities_of_type<true, class_>(parent_entity, groups);
		list_child_entities_of_type<true, union_>(parent_entity, groups);
		list_child_entities_of_type<true, anonymous_union>(parent_entity, groups);
		list_child_entities_of_type<true, enum_>(parent_entity, groups);
		list_child_entities_of_type<true, typedef_>(parent_entity, groups);
		list_child_entities_of_type<true, operator_function>(parent_entity, groups);
		list_child_entities_of_type<true, simple_function>(parent_entity, groups);
		list_child_entities_of_type<true, variable>(parent_entity, groups);
	}

	template<bool force_internal_linkage, class Class>
	void
	list_child_entities
	(
		const Class& parent_entity,
		entity_groups& groups,
		typename boost::enable_if_c
		<
			semantic_entities::type_traits::is_class<Class>::value ||
			semantic_entities::type_traits::is_union<Class>::value
		>::type*
	)
	{
		const utility::unique_ptr_vector_const_range<member_class>::type child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities<force_internal_linkage>(*i, groups);
		}

		const utility::unique_ptr_vector_const_range<member_union>::type child_unions = parent_entity.unions();
		for(auto i = child_unions.begin(); i != child_unions.end(); ++i)
		{
			list_child_entities<force_internal_linkage>(*i, groups);
		}

		const utility::unique_ptr_vector_const_range<anonymous_member_union>::type child_anonymous_unions = parent_entity.anonymous_unions();
		for(auto i = child_anonymous_unions.begin(); i != child_anonymous_unions.end(); ++i)
		{
			list_child_entities<true>(*i, groups);
		}

		const utility::unique_ptr_vector_const_range<member_enum>::type child_enums = parent_entity.enums();
		for(auto i = child_enums.begin(); i != child_enums.end(); ++i)
		{
			list_child_entities<force_internal_linkage>(*i, groups);
		}

		list_child_entities_of_type<force_internal_linkage, member_class>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, member_union>(parent_entity, groups);
		list_child_entities_of_type<true, anonymous_member_union>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, member_enum>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, member_typedef>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, constructor>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, destructor>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, operator_member_function>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, conversion_function>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, simple_member_function>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, member_variable>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, static_member_variable>(parent_entity, groups);
		list_child_entities_of_type<force_internal_linkage, bit_field>(parent_entity, groups);
	}

	template<bool force_internal_linkage>
	class list_enum_child_entities_visitor: public utility::static_visitor<void>
	{
		public:
			list_enum_child_entities_visitor(entity_groups& groups):
				groups_(groups)
			{
			}

			template<typename UnderlyingType>
			void
			operator()(const enum_constant_list<UnderlyingType>& list)
			{
				for(const enum_constant<UnderlyingType>& c: list.constants())
				{
					list_entity_impl<force_internal_linkage, enum_constant<UnderlyingType>>::list_entity(c, groups_);
				}
			}

		private:
			entity_groups& groups_;
	};

	template<bool force_internal_linkage, class Enum>
	void
	list_child_entities
	(
		const Enum& parent_entity,
		entity_groups& groups,
		typename boost::enable_if<semantic_entities::type_traits::is_enum<Enum>>::type*
	)
	{
		list_enum_child_entities_visitor<force_internal_linkage> visitor(groups);
		apply_visitor(visitor, parent_entity.constants());
	}
}

entity_groups
list_entities(const utility::unique_ptr_vector_const_range<semantic_graph>::type& semantic_graphs)
{
	entity_groups groups;

	//for each semantic graph...
	for(auto i = semantic_graphs.begin(); i != semantic_graphs.end(); ++i)
	{
		const semantic_graph& graph = *i;
		list_child_entities<false>(graph, groups);
		groups.global_namespaces.push_back(&graph);
	}

	return groups;
}

}}}} //namespace scalpel::cpp::linkage::detail

