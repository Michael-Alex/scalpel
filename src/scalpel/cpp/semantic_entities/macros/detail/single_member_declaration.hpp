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

#define SINGLE_MEMBER_DECLARATION(TYPE, NAME) \
	public: \
		TYPE* \
		get_##NAME() \
		{ \
			return NAME##_.get(); \
		} \
 \
		const TYPE* \
		get_##NAME() const \
		{ \
			return NAME##_.get(); \
		} \
 \
		void \
		set_##NAME(std::unique_ptr<TYPE>&& member); \
 \
	private: \
		std::unique_ptr<TYPE> NAME##_;

