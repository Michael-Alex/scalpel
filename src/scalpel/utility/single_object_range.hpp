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

#ifndef SCALPEL_UTILITY_SINGLE_OBJECT_RANGE_HPP
#define SCALPEL_UTILITY_SINGLE_OBJECT_RANGE_HPP

namespace scalpel { namespace utility
{

template<typename T>
class single_object_range
{
	public:
		class iterator;

		//empty range
		single_object_range();

		single_object_range(const T& object);

		iterator
		begin();

		iterator
		end();

	private:
		const T* object_;
};

template<typename T>
class single_object_range<T>::iterator
{
	public:
		iterator();

		iterator(const T& object);

		bool
		operator==(const iterator& rhs);

		bool
		operator!=(const iterator& rhs);

		iterator
		operator++();

		const T&
		operator*();

	private:
		const T* object_;
};

}} //namespace scalpel::utility

#include "single_object_range.ipp"

#endif

