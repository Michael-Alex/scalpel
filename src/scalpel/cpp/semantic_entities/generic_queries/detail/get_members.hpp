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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_MEMBERS_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_MEMBERS_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/single_object_range.hpp>
#include <scalpel/utility/single_object_const_range.hpp>
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <vector>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

template<class Entity, bool Const>
struct get_members_return_type;

template<class Entity>
struct get_members_return_type<Entity, false>
{
	typedef typename utility::unique_ptr_vector<Entity>::range type;
};

template<class Entity>
struct get_members_return_type<Entity, true>
{
	typedef const utility::unique_ptr_vector<Entity>& type;
};

template<>
struct get_members_return_type<semantic_entities::destructor, false>
{
	typedef utility::single_object_range<semantic_entities::destructor> type;
};

template<>
struct get_members_return_type<semantic_entities::destructor, true>
{
	typedef utility::single_object_const_range<semantic_entities::destructor> type;
};



//
//Main overloads (implemented in the .hpp file)
//

#define GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(PARENT_TYPE) \
template<class Member> \
typename get_members_return_type<Member, false>::type \
get_members(semantic_entities::PARENT_TYPE& parent); \
 \
template<class Member> \
typename get_members_return_type<Member, true>::type \
get_members(const semantic_entities::PARENT_TYPE& parent);

GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(namespace_)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(linked_namespace)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(unnamed_namespace)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(linked_unnamed_namespace)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(class_)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(member_class)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(constructor)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(destructor)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(operator_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(operator_member_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(conversion_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(simple_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(simple_member_function)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(statement_block)

#undef GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE



//
//Overloads for namespace_alias
//

template<class Member>
typename get_members_return_type<Member, false>::type
get_members(semantic_entities::namespace_alias& parent)
{
	semantic_entities::namespace_& n = parent.referred_namespace();
	return get_members<Member>(n);
}

template<class Member>
typename get_members_return_type<Member, true>::type
get_members(const semantic_entities::namespace_alias& parent)
{
	semantic_entities::namespace_& n = parent.referred_namespace();
	return get_members<Member>(n);
}



//
//Overloads for typedef_
//

template<class Member>
struct get_type_members_visitor: public utility::static_visitor<typename get_members_return_type<Member, false>::type>
{
	template<class T>
	typename get_members_return_type<Member, false>::type
	operator()(const T&) const
	{
		assert(false);
	}

	typename get_members_return_type<Member, false>::type
	operator()(class_* t) const
	{
		return get_members<Member>(*t);
	}

	typename get_members_return_type<Member, false>::type
	operator()(member_class* t) const
	{
		return get_members<Member>(*t);
	}

	typename get_members_return_type<Member, false>::type
	operator()(const cv_qualified_type& t) const
	{
		get_type_members_visitor<Member> visitor;
		return utility::apply_visitor(visitor, t.qualified_type());
	}
};

template<class Member>
typename get_members_return_type<Member, false>::type
get_members(semantic_entities::typedef_& parent)
{
	get_type_members_visitor<Member> visitor;
	return utility::apply_visitor(visitor, parent.type());
}



//
//Overloads for declarative region variants
//

template<class Member>
struct get_declarative_region_members_visitor: public utility::static_visitor<typename get_members_return_type<Member, false>::type>
{
	template<class T>
	typename get_members_return_type<Member, false>::type
	operator()(T* t) const
	{
		return get_members<Member>(*t);
	}
};

template<class Member, class... Entities>
typename get_members_return_type<Member, false>::type
get_members(utility::variant<Entities...>& parent)
{
	get_declarative_region_members_visitor<Member> visitor;
	return utility::apply_visitor(visitor, parent);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

