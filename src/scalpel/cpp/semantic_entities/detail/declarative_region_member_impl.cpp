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

#include "declarative_region_member_impl.hpp"
#include <scalpel/utility/ptr_variant_conversion_functions.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace detail
{

bool
declarative_region_member_impl::has_enclosing_declarative_region() const
{
	return enclosing_declarative_region_;
}

declarative_region_shared_ptr_variant
declarative_region_member_impl::enclosing_declarative_region() const
{
	if(enclosing_declarative_region_)
		return utility::to_shared_ptr_variant(*enclosing_declarative_region_);
	else
		throw std::runtime_error("The declarative region is not set.");
}

void
declarative_region_member_impl::enclosing_declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	if(!enclosing_declarative_region_)
		enclosing_declarative_region_ = utility::to_weak_ptr_variant(decl_region);
	else
		throw std::runtime_error("The declarative region is already set.");
}

}}}} //namespace scalpel::cpp::semantic_entities::detail
