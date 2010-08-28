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

#ifndef SCALPEL_UTILITY_VECTOR_IPP
#define SCALPEL_UTILITY_VECTOR_IPP

namespace scalpel { namespace utility
{

template<typename T>
vector<T>::vector()
{
}

template<typename T>
vector<T>::vector(vector&& o):
	raw_vector_(std::move(o.raw_vector_))
{
}

template<typename T>
const vector<T>&
vector<T>::operator=(vector&& o)
{
	raw_vector_ = std::move(o.raw_vector_);
	return *this;
}



template<typename T>
vector<std::shared_ptr<T>>::vector()
{
}

template<typename T>
vector<std::shared_ptr<T>>::vector(vector&& o):
	raw_vector_(std::move(o.raw_vector_))
{
}

template<typename T>
const vector<std::shared_ptr<T>>&
vector<std::shared_ptr<T>>::operator=(vector&& o)
{
	raw_vector_ = std::move(o.raw_vector_);
	return *this;
}

}} //namespace scalpel::utility

#endif

