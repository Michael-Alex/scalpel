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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP

#include "variable.hpp"
#include "operator_function.hpp"
#include "simple_function.hpp"
#include "class_.hpp"
#include "declarative_region_member_impl.hpp"
#include "declarative_region_variants.hpp"
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <string>
#include <list>
#include <vector>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ namespace.
*/
class namespace_:
	public std::enable_shared_from_this<namespace_>,
	public boost::noncopyable
{
    public:
		typedef utility::vector<declarative_region_shared_ptr_variant> declarative_regions_t;
		typedef utility::vector<std::shared_ptr<namespace_>> namespaces_t;
		typedef utility::vector<std::shared_ptr<class_>> classes_t;
		typedef utility::vector<std::shared_ptr<simple_function>> simple_functions_t;
		typedef utility::vector<std::shared_ptr<operator_function>> operator_functions_t;
		typedef utility::vector<std::shared_ptr<variable>> variables_t;

	private:
        /**
        Creates an anonymous namespace. Equivalent to namespace_("").
        */
        namespace_();

        /**
        Creates a named namespace.
        @param name the namespace's name
        */
        explicit
		namespace_(const std::string& name);

	public:
        /**
        Creates an anonymous namespace. Equivalent to make_shared("").
        */
		static
		std::shared_ptr<namespace_>
		make_shared();

        /**
        Creates a named namespace.
        @param name the namespace's name
        */
		static
		std::shared_ptr<namespace_>
		make_shared(const std::string& name);

        /**
        @return the name of the namespace
        Anonymous namespaces return an empty string.
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
        @return true
        */
		bool
		is_open_to_outside() const;

		const declarative_regions_t&
		declarative_regions();

		namespaces_t::range
		namespaces();

		const namespaces_t&
		namespaces() const;

		classes_t::range
		classes();

		const classes_t&
		classes() const;

		simple_functions_t::range
		simple_functions();

		const simple_functions_t&
		simple_functions() const;

		operator_functions_t::range
		operator_functions();

		const operator_functions_t&
		operator_functions() const;

		variables_t::range
		variables();

		const variables_t&
		variables() const;

        void
        add(std::shared_ptr<namespace_> member);

        void
        add(std::shared_ptr<class_> member);

        void
        add(std::shared_ptr<simple_function> member);

        void
        add(std::shared_ptr<operator_function> member);

        void
        add(std::shared_ptr<variable> member);

    private:
        std::string name_;
		declarative_region_member_impl declarative_region_member_impl_;

		//polymorphic containers
		declarative_regions_t declarative_regions_;

		//containers
        namespaces_t namespaces_;
        classes_t classes_;
        simple_functions_t simple_functions_;
        operator_functions_t operator_functions_;
        variables_t variables_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
