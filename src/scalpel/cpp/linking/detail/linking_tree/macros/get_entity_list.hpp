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

#define GENERATE_GET_ENTITY_LIST_SPECIALIZATION(CLASS, ENTITY_TYPE, VARIABLE) \
template<> \
entity_list<semantic_entities::ENTITY_TYPE>& \
get_entity_list(CLASS& o) \
{ \
	return o.VARIABLE; \
} \
 \
template<> \
const entity_list<semantic_entities::ENTITY_TYPE>& \
get_entity_list(const CLASS& o) \
{ \
	return o.VARIABLE; \
}

