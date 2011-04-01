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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_TYPE_VARIANT_FWD_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_TYPE_VARIANT_FWD_HPP

#include "fundamental_type.hpp"
#include <scalpel/utility/variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class array;
class class_;
class member_class;
class cv_qualified_type;
class enum_;
class member_enum;
class function_type;
class pointer;
class pointer_to_member;
class reference;

typedef
	utility::variant
	<
		array,
		fundamental_type,
		function_type,
		class_*,
		member_class*,
		cv_qualified_type,
		enum_*,
		member_enum*,
		pointer,
		pointer_to_member,
		reference
	>
	type_variant
;

}}} //namespace scalpel::cpp::semantic_entities

#endif

