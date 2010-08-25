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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_SIMPLE_FUNCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_SIMPLE_FUNCTION_HPP

#include "variable.hpp"
#include "statement_block.hpp"
#include "declarative_region_member_impl.hpp"
#include "declarative_region_variants.hpp"
#include "type.hpp"
#include <boost/optional.hpp>
#include <string>
#include <list>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ non-special function (which is neither a constructor nor an
operator function nor a conversion function).
*/
class simple_function:
	public std::enable_shared_from_this<simple_function>
{
    public:
		class parameter;

		typedef utility::vector<declarative_region_shared_ptr_variant> declarative_region_shared_ptr_variants_t;
		typedef std::list<parameter> parameters_t;

        simple_function
		(
			const std::string& name,
			std::shared_ptr<const type> return_type,
			parameters_t&& parameters = parameters_t(),
			bool is_is_inline = false,
			bool is_is_static = false
		);

		//copy constructor
		simple_function(const simple_function&) = delete;

		//move constructor
		simple_function(simple_function&& rhs);

		const simple_function&
		operator=(const simple_function&) = delete;

		const simple_function&
		operator=(simple_function&& rhs);

		bool
		has_same_signature(const simple_function& f) const;

		bool
		has_same_parameters(const simple_function& f) const;

        /**
        @return the name of the function
        */
        const std::string&
        name() const;

		bool
		has_declarative_region() const;

		declarative_region_shared_ptr_variant
		declarative_region() const;

		void
		declarative_region(const declarative_region_shared_ptr_variant& declarative_region);

        /**
        @return false
        */
		bool
		is_open_to_outside() const;

		std::shared_ptr<const type>
		return_type() const;

		const parameters_t&
		parameters() const;

		bool
		is_inline() const;

		bool
		is_static() const;

		bool
		defined() const;

		void
		defined(bool d);

		const declarative_region_shared_ptr_variants_t&
		declarative_regions();

		std::shared_ptr<statement_block>
		body();

    private:
        std::string name_;
		std::shared_ptr<const type> return_type_;
		std::list<parameter> parameters_;
		bool is_inline_;
		bool is_static_;
		bool defined_;
		declarative_region_member_impl declarative_region_member_impl_;

		declarative_region_shared_ptr_variants_t declarative_regions_;

		std::shared_ptr<statement_block> body_;
};

class simple_function::parameter
{
	public:
		parameter(std::shared_ptr<const type> t, const std::string& name);

		parameter(const parameter& o);

		parameter(parameter&& o);

		const parameter&
		operator=(const parameter& o);

		const parameter&
		operator=(parameter&& o);

		bool
		operator==(const parameter& o) const;

		std::shared_ptr<const type>
		get_type() const;

		const std::string&
		name() const;

	private:
		std::shared_ptr<const type> type_;
		std::string name_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

