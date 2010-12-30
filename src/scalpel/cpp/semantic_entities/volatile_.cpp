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

#include "volatile_.hpp"
#include "type_variants.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

volatile_::volatile_(const type_variant& qualified_type):
	qualified_type_(qualified_type)
{
}

bool
operator==(const volatile_& lhs, const volatile_& rhs)
{
	return
		lhs.qualified_type() == rhs.qualified_type()
	;
}

bool
operator!=(const volatile_& lhs, const volatile_& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

