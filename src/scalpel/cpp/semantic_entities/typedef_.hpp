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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_TYPEDEF_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_TYPEDEF_HPP

#include "type.hpp"
#include "impl/detail/declarative_region_member_impl.hpp"
#include "macros/detail/declarative_region_member_impl.hpp"
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#define GENERATE_TYPEDEF_DECLARATION(CLASS_NAME, IS_MEMBER) \
class CLASS_NAME \
{ \
	public: \
		CLASS_NAME \
		( \
			const std::string& name, \
			const type_t& type BOOST_PP_COMMA_IF(IS_MEMBER) \
			BOOST_PP_IIF(IS_MEMBER, const member_accessibility access,) \
		); \
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
		const type_t& \
		type() const \
		{ \
			return type_; \
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
	private: \
		std::string name_; \
		type_t type_; \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_accessibility accessibility_;, \
		) \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			DECLARATIVE_REGION_MEMBER_IMPL(member_typedef_declarative_region_member_impl_t), \
			DECLARATIVE_REGION_MEMBER_IMPL(typedef_declarative_region_member_impl_t) \
		) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

typedef
	impl::detail::declarative_region_member_impl<namespace_, unnamed_namespace, linked_namespace, linked_unnamed_namespace>
	typedef_declarative_region_member_impl_t
;

typedef
	impl::detail::declarative_region_member_impl<class_, member_class, union_, member_union, anonymous_union, anonymous_member_union>
	member_typedef_declarative_region_member_impl_t
;

GENERATE_TYPEDEF_DECLARATION(typedef_, 0)
GENERATE_TYPEDEF_DECLARATION(member_typedef, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef GENERATE_TYPEDEF_DECLARATION

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#endif

