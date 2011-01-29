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

#ifndef SCALPEL_UTILITY_VARIANT_DEREFERENCE_IF_HPP
#define SCALPEL_UTILITY_VARIANT_DEREFERENCE_IF_HPP

namespace scalpel { namespace utility
{

template<bool Cond, bool Const, typename T>
struct dereference_if_impl;

template<typename T>
struct dereference_if_impl<true, false, T*>
{
	typedef T& return_type;

	static
	return_type
	result(T* t)
	{
		return *t;
	}
};

template<typename T>
struct dereference_if_impl<false, false, T>
{
	typedef T& return_type;

	static
	return_type
	result(T& t)
	{
		return t;
	}
};

template<typename T>
struct dereference_if_impl<true, true, T*>
{
	typedef const T& return_type;

	static
	return_type
	result(const T* t)
	{
		return *t;
	}
};

template<typename T>
struct dereference_if_impl<false, true, T>
{
	typedef const T& return_type;

	static
	return_type
	result(const T& t)
	{
		return t;
	}
};

template<bool Cond, typename T>
typename dereference_if_impl<Cond, false, T>::return_type
dereference_if(T& t)
{
	return dereference_if_impl<Cond, false, T>::result(t);
}

template<bool Cond, typename T>
typename dereference_if_impl<Cond, true, T>::return_type
dereference_if(const T& t)
{
	return dereference_if_impl<Cond, true, T>::result(t);
}

}} //namespace scalpel::utility

#endif

