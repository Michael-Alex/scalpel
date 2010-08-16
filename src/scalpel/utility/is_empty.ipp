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

#ifndef SCALPEL_UTILITY_IS_EMPTY_IPP
#define SCALPEL_UTILITY_IS_EMPTY_IPP

namespace scalpel { namespace utility
{

template<class T>
bool
is_empty(vector<std::shared_ptr<T>>& container)
{
	return container.empty();
}

template<class T>
bool
is_empty(std::shared_ptr<T>& container)
{
	return !container;
}

template<class... Ts>
bool
is_empty(variant<Ts...>& container)
{
	return container.empty();
}

}} //namespace scalpel::utility

#endif

