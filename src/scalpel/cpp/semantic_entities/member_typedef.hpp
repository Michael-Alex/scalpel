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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_MEMBER_TYPEDEF_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_MEMBER_TYPEDEF_HPP

#include "member_access.hpp"
#include "type_variant.hpp"
#include "detail/declarative_region_member_impl.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents the const qualifier.
*/
class member_typedef
{
	public:
		member_typedef(const std::string& name, const type_variant& type, const member_access access);

		member_typedef(const member_typedef&) = delete;

		member_typedef&
		operator=(const member_typedef&) = delete;

		const std::string&
		name() const
		{
			return name_;
		}

		const type_variant&
		type() const
		{
			return type_;
		}

		member_access
		access() const
		{
			return access_;
		}

		bool
		has_enclosing_declarative_region() const
		{
			return declarative_region_member_impl_.has_enclosing_declarative_region();
		}

		declarative_region_ptr_variant
		enclosing_declarative_region() const
		{
			return declarative_region_member_impl_.enclosing_declarative_region();
		}

		void
		enclosing_declarative_region(const declarative_region_ptr_variant& enclosing_declarative_region)
		{
			declarative_region_member_impl_.enclosing_declarative_region(enclosing_declarative_region);
		}

	private:
		std::string name_;
		type_variant type_;
		member_access access_;

		detail::declarative_region_member_impl declarative_region_member_impl_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

