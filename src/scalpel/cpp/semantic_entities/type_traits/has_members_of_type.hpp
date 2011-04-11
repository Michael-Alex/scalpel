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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_MEMBERS_OF_TYPE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_MEMBERS_OF_TYPE_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace type_traits
{

template<class DeclarativeRegion, class Member>
struct has_members_of_type
{
	static const bool value = false;
};

#define HAS_MEMBERS_OF_TYPE(DECLARATIVE_REGION_TYPE, MEMBER_TYPE) \
template<> \
struct has_members_of_type<DECLARATIVE_REGION_TYPE, MEMBER_TYPE> \
{ \
	static const bool value = true; \
};

HAS_MEMBERS_OF_TYPE(namespace_, namespace_)
HAS_MEMBERS_OF_TYPE(namespace_, unnamed_namespace)
HAS_MEMBERS_OF_TYPE(namespace_, class_)
HAS_MEMBERS_OF_TYPE(namespace_, enum_)
HAS_MEMBERS_OF_TYPE(namespace_, typedef_)
HAS_MEMBERS_OF_TYPE(namespace_, operator_function)
HAS_MEMBERS_OF_TYPE(namespace_, simple_function)
HAS_MEMBERS_OF_TYPE(namespace_, variable)
HAS_MEMBERS_OF_TYPE(namespace_, namespace_alias)

HAS_MEMBERS_OF_TYPE(linked_namespace, unnamed_namespace)
HAS_MEMBERS_OF_TYPE(linked_namespace, class_)
HAS_MEMBERS_OF_TYPE(linked_namespace, enum_)
HAS_MEMBERS_OF_TYPE(linked_namespace, typedef_)
HAS_MEMBERS_OF_TYPE(linked_namespace, operator_function)
HAS_MEMBERS_OF_TYPE(linked_namespace, simple_function)
HAS_MEMBERS_OF_TYPE(linked_namespace, variable)

HAS_MEMBERS_OF_TYPE(unnamed_namespace, namespace_)
HAS_MEMBERS_OF_TYPE(unnamed_namespace, unnamed_namespace)
HAS_MEMBERS_OF_TYPE(unnamed_namespace, class_)
HAS_MEMBERS_OF_TYPE(unnamed_namespace, enum_)
HAS_MEMBERS_OF_TYPE(unnamed_namespace, typedef_)
HAS_MEMBERS_OF_TYPE(unnamed_namespace, operator_function)
HAS_MEMBERS_OF_TYPE(unnamed_namespace, simple_function)
HAS_MEMBERS_OF_TYPE(unnamed_namespace, variable)
HAS_MEMBERS_OF_TYPE(unnamed_namespace, namespace_alias)

HAS_MEMBERS_OF_TYPE(linked_unnamed_namespace, unnamed_namespace)
HAS_MEMBERS_OF_TYPE(linked_unnamed_namespace, class_)
HAS_MEMBERS_OF_TYPE(linked_unnamed_namespace, enum_)
HAS_MEMBERS_OF_TYPE(linked_unnamed_namespace, typedef_)
HAS_MEMBERS_OF_TYPE(linked_unnamed_namespace, operator_function)
HAS_MEMBERS_OF_TYPE(linked_unnamed_namespace, simple_function)
HAS_MEMBERS_OF_TYPE(linked_unnamed_namespace, variable)

HAS_MEMBERS_OF_TYPE(class_, member_class)
HAS_MEMBERS_OF_TYPE(class_, member_enum)
HAS_MEMBERS_OF_TYPE(class_, member_typedef)
HAS_MEMBERS_OF_TYPE(class_, constructor)
HAS_MEMBERS_OF_TYPE(class_, destructor)
HAS_MEMBERS_OF_TYPE(class_, operator_member_function)
HAS_MEMBERS_OF_TYPE(class_, conversion_function)
HAS_MEMBERS_OF_TYPE(class_, simple_member_function)
HAS_MEMBERS_OF_TYPE(class_, member_variable)
HAS_MEMBERS_OF_TYPE(class_, bit_field)

HAS_MEMBERS_OF_TYPE(member_class, member_class)
HAS_MEMBERS_OF_TYPE(member_class, member_enum)
HAS_MEMBERS_OF_TYPE(member_class, member_typedef)
HAS_MEMBERS_OF_TYPE(member_class, constructor)
HAS_MEMBERS_OF_TYPE(member_class, destructor)
HAS_MEMBERS_OF_TYPE(member_class, operator_member_function)
HAS_MEMBERS_OF_TYPE(member_class, conversion_function)
HAS_MEMBERS_OF_TYPE(member_class, simple_member_function)
HAS_MEMBERS_OF_TYPE(member_class, member_variable)
HAS_MEMBERS_OF_TYPE(member_class, bit_field)

HAS_MEMBERS_OF_TYPE(statement_block, namespace_alias)

#undef HAS_MEMBERS_OF_TYPE

}}}} //namespace scalpel::cpp::semantic_entities::type_traits

#endif

