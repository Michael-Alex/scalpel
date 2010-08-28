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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CONST_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CONST_HPP

#include "type_variants.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents the const qualifier.
*/
class const_
{
	public:
		const_(const type_shared_ptr_variant& decorated_type);

		bool
		operator==(const const_& rhs) const;

		const type_shared_ptr_variant&
		decorated_type() const
		{
			return decorated_type_;
		}

	private:
		type_shared_ptr_variant decorated_type_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
