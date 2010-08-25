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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CLASS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CLASS_HPP

#include "variable.hpp"
#include "operator_function.hpp"
#include "simple_function.hpp"
#include "declarative_region_member_impl.hpp"
#include "declarative_region_variants.hpp"
#include "type.hpp"
#include <scalpel/utility/vector.hpp>
#include <boost/noncopyable.hpp>
#include <string>
#include <vector>
#include <map>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;

/**
Represents a C++ class.
*/
class class_:
	public type,
	public boost::noncopyable,
	public std::enable_shared_from_this<class_>
{
	public:
		class constructor;
		class destructor;
		class conversion_function;

		typedef
			utility::variant
			<
				std::shared_ptr<const class_>,
				std::shared_ptr<const constructor>,
				std::shared_ptr<const destructor>,
				std::shared_ptr<const simple_function>,
				std::shared_ptr<const conversion_function>,
				std::shared_ptr<const operator_function>,
				std::shared_ptr<const variable>
			>
			member_t
		;

		typedef utility::vector<member_t> members_t;
		typedef utility::vector<declarative_region_shared_ptr_variant> declarative_region_shared_ptr_variants_t;
		typedef utility::vector<std::shared_ptr<class_>> classes_t;
		typedef utility::vector<std::shared_ptr<constructor>> constructors_t;
		typedef utility::vector<std::shared_ptr<simple_function>> simple_functions_t;
		typedef utility::vector<std::shared_ptr<operator_function>> operator_functions_t;
		typedef utility::vector<std::shared_ptr<conversion_function>> conversion_functions_t;
		typedef utility::vector<std::shared_ptr<variable>> variables_t;

		enum access
		{
			PUBLIC,
			PROTECTED,
			PRIVATE
		};

        /**
        Creates a class.
        @param name the class' name
        */
        explicit
        class_(const std::string& name);

		/**
		 * Move constructor.
		 */
		class_(class_&& rhs);

		/**
		 * Move assignment operator.
		 */
		const class_&
		operator=(class_&& rhs);

        /**
        @return the name of the class
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

		const declarative_region_shared_ptr_variants_t&
		declarative_regions();

		classes_t::range
		base_classes();

		const classes_t&
		base_classes() const;

		classes_t::range
		nested_classes();

		const classes_t&
		nested_classes() const;

		constructors_t::range
		constructors();

		const constructors_t&
		constructors() const;

		std::shared_ptr<const destructor>
		get_destructor() const;

		simple_functions_t::range
		simple_functions();

		const simple_functions_t&
		simple_functions() const;

		operator_functions_t::range
		operator_functions();

		const operator_functions_t&
		operator_functions() const;

		conversion_functions_t::range
		conversion_functions();

		const conversion_functions_t&
		conversion_functions() const;

		variables_t::range
		variables();

		const variables_t&
		variables() const;

		/**
		Adds a base class.
		*/
        void
        add_base_class
		(
			std::shared_ptr<class_> base_class,
			const access acc = PUBLIC,
			bool virtual_specified = false
		);

        /**
        Adds a nested class.
        */
        void
        add(std::shared_ptr<class_> member, const access acc = PUBLIC);

        void
        add(std::shared_ptr<constructor> member, const access acc = PUBLIC);

		void
		set_destructor
		(
			std::shared_ptr<destructor> member,
			const access acc = PUBLIC,
			const bool virtual_specified = false,
			const bool pure_specified = false
		);

		void
		reset_destructor();

	public:
        void
        add
		(
			std::shared_ptr<simple_function> member,
			const access acc = PUBLIC,
			const bool const_qualified = false,
			const bool volatile_qualified = false,
			const bool virtual_specified = false,
			const bool pure_specified = false
		);

        void
        add
		(
			std::shared_ptr<operator_function> member,
			const access acc = PUBLIC,
			const bool const_qualified = false,
			const bool volatile_qualified = false,
			const bool virtual_specified = false,
			const bool pure_specified = false
		);

        void
        add
		(
			std::shared_ptr<conversion_function> member,
			const access acc = PUBLIC,
			const bool const_qualified = false,
			const bool volatile_qualified = false,
			const bool virtual_specified = false,
			const bool pure_specified = false
		);

		void
		add(std::shared_ptr<variable> member, const access acc);

		//get the access of the given base class
		access
		base_class_access(std::shared_ptr<const class_> base_class) const;

		bool
		is_virtual_base_class(std::shared_ptr<const class_> base_class) const;

		//get the access of the given class member
		access
		member_access(const member_t& member) const;

		bool
		is_const_member_function(const member_t& member) const;

		bool
		is_volatile_member_function(const member_t& member) const;

		bool
		is_virtual_member_function(const member_t& member) const;

		bool
		is_pure_member_function(const member_t& member) const;

    private:
        std::string name_;
		declarative_region_member_impl declarative_region_member_impl_;

		//polymorphic containers
		declarative_region_shared_ptr_variants_t declarative_regions_;
		std::map<std::shared_ptr<const class_>, access> base_class_access_;
		classes_t virtual_base_classes_;
		std::map<const member_t, access> member_access_;
		members_t const_member_functions_;
		members_t volatile_member_functions_;
		members_t virtual_member_functions_;
		members_t pure_member_functions_;

		//containers
		classes_t base_classes_;
		classes_t nested_classes_;
		constructors_t constructors_;
		std::shared_ptr<destructor> destructor_;
		simple_functions_t simple_functions_;
		operator_functions_t operator_functions_;
		conversion_functions_t conversion_functions_;
		variables_t variables_;
};

class class_::constructor
{
	public:
		typedef simple_function::parameter parameter;
		typedef simple_function::parameters_t parameters_t;

		constructor
		(
			parameters_t&& parameters,
			const bool is_inline_specified,
			const bool is_explicit_specified
		);

		constructor(constructor&& o);

		const parameters_t&
		parameters() const;

		bool
		inline_specified() const;

		bool
		explicit_specified() const;

		bool
		has_declarative_region() const;

		declarative_region_shared_ptr_variant
		declarative_region() const;

		void
		declarative_region(const declarative_region_shared_ptr_variant& declarative_region);

	private:
		semantic_entities::simple_function impl_;
		bool explicit_specified_;
		declarative_region_member_impl declarative_region_member_impl_;
};

class class_::destructor
{
	public:
		destructor(const bool is_inline_specified);

		destructor(destructor&& o);

		bool
		inline_specified() const;

		bool
		has_declarative_region() const;

		declarative_region_shared_ptr_variant
		declarative_region() const;

		void
		declarative_region(const declarative_region_shared_ptr_variant& declarative_region);

	private:
		bool inline_specified_;
		declarative_region_member_impl declarative_region_member_impl_;
};

class class_::conversion_function
{
	public:
		conversion_function
		(
			std::shared_ptr<const type> return_type,
			const bool is_inline_specified
		);

		conversion_function(conversion_function&& o);

		std::shared_ptr<const type>
		return_type() const;

		bool
		inline_specified() const;

		bool
		has_declarative_region() const;

		declarative_region_shared_ptr_variant
		declarative_region() const;

		void
		declarative_region(const declarative_region_shared_ptr_variant& declarative_region);

	private:
		std::shared_ptr<const type> return_type_;
		bool inline_specified_;
		declarative_region_member_impl declarative_region_member_impl_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

