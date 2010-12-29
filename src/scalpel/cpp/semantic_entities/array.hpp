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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ARRAY_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ARRAY_HPP

#include "type_variants_fwd.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents the const qualifier.
*/
class array
{
	public:
		array
		(
			const unsigned int size,
			const type_variant& qualified_type
		);

		unsigned int
		size() const
		{
			return size_;
		}

		type_variant
		qualified_type() const
		{
			return to_type_variant(qualified_type_);
		}

	private:
		unsigned int size_;
		weak_type_variant qualified_type_;
};

bool
operator==(const array& lhs, const array& rhs);

bool
operator!=(const array& lhs, const array& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

