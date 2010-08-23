/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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
	std::shared_ptr<const type> t,
	bool is_static_specified
):
	type_(t),
	name_(name),
	static_specified_(is_static_specified)
{
}

variable::variable(const variable& v):
	type_(v.type_),
	name_(v.name_),
	static_specified_(v.static_specified_)
{
}

variable::variable(variable&& v):
	type_(v.type_),
	name_(std::move(v.name_)),
	static_specified_(v.static_specified_)
{
}

const variable&
variable::operator=(variable&& v)
{
	type_ = v.type_;
	name_ = std::move(v.name_);
	static_specified_ = v.static_specified_;

	return *this;
}

std::shared_ptr<const type>
variable::get_type() const
{
	return type_;
}

const std::string&
variable::name() const
{
	return name_;
}

bool
variable::static_specified() const
{
	return static_specified_;
}

}}} //namespace scalpel::cpp::semantic_entities

