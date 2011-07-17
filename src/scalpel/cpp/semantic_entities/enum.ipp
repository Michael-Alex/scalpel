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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_IPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_IPP

namespace scalpel { namespace cpp { namespace semantic_entities
{

template<typename UnderlyingType>
basic_enum<UnderlyingType>::basic_enum(const std::string& name):
    name_(name)
{
}

template<typename UnderlyingType>
basic_enum<UnderlyingType>::basic_enum(basic_enum&& rhs):
	name_(std::move(rhs.name_)),
	constants_(std::move(rhs.constants_))
{
}

template<typename UnderlyingType>
basic_enum<UnderlyingType>&
basic_enum<UnderlyingType>::operator=(basic_enum&& rhs)
{
	name_ = std::move(rhs.name_);
	constants_ = std::move(rhs.constants_);
}



template<typename UnderlyingType>
basic_member_enum<UnderlyingType>::basic_member_enum(const std::string& name, const member_access access):
    name_(name),
	access_(access)
{
}

template<typename UnderlyingType>
basic_member_enum<UnderlyingType>::basic_member_enum(basic_member_enum&& rhs):
	name_(std::move(rhs.name_)),
	constants_(std::move(rhs.constants_)),
	access_(rhs.access_)
{
}

template<typename UnderlyingType>
basic_member_enum<UnderlyingType>&
basic_member_enum<UnderlyingType>::operator=(basic_member_enum&& rhs)
{
	name_ = std::move(rhs.name_);
	constants_ = std::move(rhs.constants_);
	access_ = rhs.access_;
}

}}} //namespace scalpel::cpp::semantic_entities

#endif

