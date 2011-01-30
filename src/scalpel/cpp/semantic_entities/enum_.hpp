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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_HPP

#include "detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <string>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ enum.
*/
class enum_
{
	public:
		class constant;
		typedef utility::unique_ptr_vector<constant> constants_t;

        explicit
        enum_(const std::string& name);

        enum_(const enum_&) = delete;

        enum_&
		operator=(const enum_&) = delete;

		const std::string&
		name() const
		{
			return name_;
		}

		const constants_t&
		constants() const
		{
			return constants_;
		}

		void
		add(std::unique_ptr<constant>&& c)
		{
			constants_.push_back(std::move(c));
		}

		bool
		has_enclosing_declarative_region() const
		{
			return declarative_region_member_impl_.has_enclosing_declarative_region();
		}

		declarative_region_ptr_variant
		enclosing_declarative_region() const
		{
			return declarative_region_member_impl_.enclosing_declarative_region();
		}

		void
		enclosing_declarative_region(const declarative_region_ptr_variant& enclosing_declarative_region)
		{
			declarative_region_member_impl_.enclosing_declarative_region(enclosing_declarative_region);
		}

    private:
        std::string name_;
		constants_t constants_;
		detail::declarative_region_member_impl declarative_region_member_impl_;
};

class enum_::constant
{
	public:
        constant(const std::string& name, const int value);

        constant(const constant&) = delete;

        constant&
		operator=(const constant&) = delete;

		const std::string&
		name() const
		{
			return name_;
		}

		int
		value() const
		{
			return value_;
		}

	private:
		std::string name_;
		int value_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

