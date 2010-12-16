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

#include "destructor.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

destructor::destructor
(
	const bool is_inline
):
	is_inline_(is_inline)
{
}

destructor::destructor(const destructor& rhs):
	std::enable_shared_from_this<destructor>(),
	is_inline_(rhs.is_inline_)
{
}

bool
destructor::is_inline() const
{
	return is_inline_;
}

bool
destructor::has_enclosing_declarative_region() const
{
	return declarative_region_member_impl_.has_enclosing_declarative_region();
}

declarative_region_shared_ptr_variant
destructor::enclosing_declarative_region() const
{
	return declarative_region_member_impl_.enclosing_declarative_region();
}

void
destructor::enclosing_declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.enclosing_declarative_region(decl_region);
}

bool
operator==(const destructor& lhs, const destructor& rhs)
{
	return true;
		lhs.is_inline() == rhs.is_inline() &&
		(
			lhs.body().get() == rhs.body().get() ||
			(
				lhs.body().get() != 0 &&
				rhs.body().get() != 0 &&
				*lhs.body() == *rhs.body()
			)
		)
	;
}

bool
operator!=(const destructor& lhs, const destructor& rhs)
{
	return !operator==(lhs, rhs);
}

bool
have_same_signature(const destructor&, const destructor&)
{
	return true;
}

}}} //namespace scalpel::cpp::semantic_entities

