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
#include "named_declarative_region.hpp"
#include "named_entity.hpp"
#include <boost/noncopyable.hpp>
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
	public named_declarative_region,
	public boost::noncopyable
{
    public:
		typedef utility::shared_ptr_vector<namespace_> namespaces_t;
		typedef utility::shared_ptr_vector<class_> classes_t;
		typedef utility::shared_ptr_vector<simple_function> simple_functions_t;
		typedef utility::shared_ptr_vector<operator_function> operator_functions_t;
		typedef utility::shared_ptr_vector<variable> variables_t;

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

		/**
		 * Move constructor.
		 */
		namespace_(namespace_&& n);

		/**
		 * Move assignment operator.
		 */
		const namespace_&
		operator=(namespace_&& n);

        /**
        @return the name of the namespace
        Anonymous namespaces return an empty string.
        */
        const std::string&
        name() const;

        /**
        @return true if the namespace is the global one, false otherwise
        */
        bool
        is_global() const;

        /**
        @return true
        */
		bool
		is_open_to_outside() const;

		named_declarative_regions_t::range
        named_declarative_regions();

		named_declarative_regions_t::const_range
        named_declarative_regions() const;

		named_entities_t::range
		named_entities();

		named_entities_t::const_range
		named_entities() const;

		namespaces_t::const_range
		namespaces() const;

		classes_t::const_range
		classes() const;

		simple_functions_t::const_range
		simple_functions() const;

		operator_functions_t::const_range
		operator_functions() const;

		variables_t::const_range
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

		//polymorphic containers
		named_entities_t named_entities_;
		named_declarative_regions_t named_declarative_regions_;

		//containers
        namespaces_t namespaces_;
        classes_t classes_;
        simple_functions_t simple_functions_;
        operator_functions_t operator_functions_;
        variables_t variables_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
