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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_DECLARATIVE_REGION_VARIANT_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_DECLARATIVE_REGION_VARIANT_HPP

#include "namespace_.hpp"
#include "class_.hpp"
#include "statement_block.hpp"
#include <boost/variant.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

typedef
	boost::variant
	<
		std::shared_ptr<namespace_>,
		std::shared_ptr<class_>,
		std::shared_ptr<statement_block>
	>
	declarative_region_variant
;

}}} //namespace scalpel::cpp::semantic_entities

#endif
