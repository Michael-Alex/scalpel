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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_HPP

#include "enum_constant.hpp"
#include "enum_constant_list.hpp"
#include "member_accessibility.hpp"
#include "impl/detail/declarative_region_member_impl.hpp"
#include "macros/detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/unique_ptr_vector_range.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <string>

#define SCALPEL_ENUM(CLASS_NAME, IS_MEMBER) \
class CLASS_NAME \
{ \
	private: \
		template<typename UnderlyingType> \
		CLASS_NAME \
		( \
			const std::string& name, \
			BOOST_PP_IIF(IS_MEMBER, const member_accessibility access,) BOOST_PP_COMMA_IF(IS_MEMBER) \
			UnderlyingType* \
		): \
			name_(name), \
			BOOST_PP_IIF(IS_MEMBER, accessibility_(access),) BOOST_PP_COMMA_IF(IS_MEMBER) \
			constants_(enum_constant_list<UnderlyingType>(*this)) \
		{ \
		} \
 \
	public: \
		template<typename UnderlyingType> \
		static \
		CLASS_NAME* \
		create \
		( \
			const std::string& name BOOST_PP_COMMA_IF(IS_MEMBER) \
			BOOST_PP_IIF(IS_MEMBER, const member_accessibility access,) \
		) \
		{ \
			return new CLASS_NAME \
			( \
				name, \
				BOOST_PP_IIF(IS_MEMBER, access,) BOOST_PP_COMMA_IF(IS_MEMBER) \
				static_cast<UnderlyingType*>(nullptr) \
			); \
		} \
 \
		CLASS_NAME(const CLASS_NAME&) = delete; \
 \
		CLASS_NAME& \
		operator=(const CLASS_NAME&) = delete; \
 \
		const std::string& \
		name() const \
		{ \
			return name_; \
		} \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_accessibility \
			accessibility() const \
			{ \
				return accessibility_; \
			}, \
		) \
 \
		enum_constant_list_t& \
		constants() \
		{ \
			return constants_; \
		} \
 \
		const enum_constant_list_t& \
		constants() const \
		{ \
			return constants_; \
		} \
 \
	private: \
		std::string name_; \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_accessibility accessibility_;, \
		) \
		enum_constant_list_t constants_; \
 \
	BOOST_PP_IIF \
	( \
		IS_MEMBER, \
		DECLARATIVE_REGION_MEMBER_IMPL(member_enum_declarative_region_member_impl_t), \
		DECLARATIVE_REGION_MEMBER_IMPL(enum_declarative_region_member_impl_t) \
	) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class unnamed_namespace;
class linked_namespace;
class linked_unnamed_namespace;
class class_;
class member_class;
class union_;
class member_union;
class anonymous_union;
class anonymous_member_union;

typedef
	utility::variant
	<
		enum_constant_list<int>,
		enum_constant_list<unsigned int>,
		enum_constant_list<long int>,
		enum_constant_list<unsigned long int>
	>
	enum_constant_list_t
;

typedef
	impl::detail::declarative_region_member_impl<namespace_, unnamed_namespace, linked_namespace, linked_unnamed_namespace>
	enum_declarative_region_member_impl_t
;

typedef
	impl::detail::declarative_region_member_impl<class_, member_class, union_, member_union, anonymous_union, anonymous_member_union>
	member_enum_declarative_region_member_impl_t
;

SCALPEL_ENUM(enum_, 0)
SCALPEL_ENUM(member_enum, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef SCALPEL_ENUM

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#endif

