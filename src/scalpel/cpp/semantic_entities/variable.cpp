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

#include "variable.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

variable::variable
(
	const std::string& name,
	const type_variant& type,
	bool is_static
):
	type_(type),
	name_(name),
	is_static_(is_static)
{
}

variable::variable(const variable& rhs):
	type_(rhs.type_),
	name_(rhs.name_),
	is_static_(rhs.is_static_)
{
}

variable::variable(variable&& rhs):
	type_(rhs.type_),
	name_(std::move(rhs.name_)),
	is_static_(rhs.is_static_)
{
}

const variable&
variable::operator=(variable&& rhs)
{
	type_ = rhs.type_;
	name_ = std::move(rhs.name_);
	is_static_ = rhs.is_static_;

	return *this;
}

const type_variant&
variable::type() const
{
	return type_;
}

const std::string&
variable::name() const
{
	return name_;
}

bool
variable::is_static() const
{
	return is_static_;
}

bool
variable::has_enclosing_declarative_region() const
{
	return declarative_region_member_impl_.has_enclosing_declarative_region();
}

declarative_region_ptr_variant
variable::enclosing_declarative_region() const
{
	return declarative_region_member_impl_.enclosing_declarative_region();
}

void
variable::enclosing_declarative_region(const declarative_region_ptr_variant& decl_region)
{
	declarative_region_member_impl_.enclosing_declarative_region(decl_region);
}

}}} //namespace scalpel::cpp::semantic_entities

