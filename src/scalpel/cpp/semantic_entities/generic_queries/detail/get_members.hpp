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
struct member_type_traits;

template<class Entity>
struct member_type_traits<Entity, false>
{
	typedef typename utility::unique_ptr_vector<Entity>::range return_type;
	typedef typename return_type::reference reference;
};

template<class Entity>
struct member_type_traits<Entity, true>
{
	typedef const utility::unique_ptr_vector<Entity>& return_type;
	typedef typename utility::unique_ptr_vector<Entity>::const_reference reference;
};

template<>
struct member_type_traits<semantic_entities::open_declarative_region_ptr_variant, false>
{
	typedef const std::vector<semantic_entities::open_declarative_region_ptr_variant>& return_type;
	typedef std::vector<semantic_entities::open_declarative_region_ptr_variant>::const_reference reference;
};

template<>
struct member_type_traits<semantic_entities::open_declarative_region_ptr_variant, true>:
	member_type_traits<semantic_entities::open_declarative_region_ptr_variant, false>
{
};

template<>
struct member_type_traits<semantic_entities::destructor, false>
{
	typedef utility::single_object_range<semantic_entities::destructor> return_type;
	typedef typename return_type::reference reference;
};

template<>
struct member_type_traits<semantic_entities::destructor, true>
{
	typedef utility::single_object_const_range<semantic_entities::destructor> return_type;
	typedef typename return_type::reference reference;
};



#define GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(PARENT_TYPE) \
template<class MemberT> \
typename member_type_traits<MemberT, false>::return_type \
get_members(semantic_entities::PARENT_TYPE& parent); \
 \
template<class MemberT> \
typename member_type_traits<MemberT, true>::return_type \
get_members(const semantic_entities::PARENT_TYPE& parent);

GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(namespace_)
GENERATE_GET_MEMBERS_FUNCTION_TEMPLATE(unnamed_namespace)
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

template<class MemberT>
typename member_type_traits<MemberT, false>::return_type
get_members(semantic_entities::namespace_alias& parent)
{
	semantic_entities::namespace_& n = parent.referred_namespace();
	return get_members<MemberT>(n);
}

template<class MemberT>
typename member_type_traits<MemberT, true>::return_type
get_members(const semantic_entities::namespace_alias& parent)
{
	semantic_entities::namespace_& n = parent.referred_namespace();
	return get_members<MemberT>(n);
}



//visitor template for declarative region variants
template<class MemberT>
struct get_declarative_region_members_visitor: public utility::static_visitor<typename member_type_traits<MemberT, false>::return_type>
{
	template<class T>
	typename member_type_traits<MemberT, false>::return_type
	operator()(T* t) const
	{
		return get_members<MemberT>(*t);
	}
};

template<class MemberT>
typename member_type_traits<MemberT, false>::return_type
get_members(semantic_entities::declarative_region_ptr_variant& parent)
{
	get_declarative_region_members_visitor<MemberT> visitor;
	return utility::apply_visitor(visitor, parent);
}

template<class MemberT>
typename member_type_traits<MemberT, false>::return_type
get_members(semantic_entities::open_declarative_region_ptr_variant& parent)
{
	get_declarative_region_members_visitor<MemberT> visitor;
	return utility::apply_visitor(visitor, parent);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

