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

#include "class_.hpp"
#include "namespace_.hpp"
#include "built_in_type.hpp"
#include <scalpel/utility/null_deleter.hpp>
#include <iostream>
#include <memory>
#include <cassert>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class_::class_(const std::string& name):
    name_(name),
	destructor_(new destructor(access::PUBLIC, true, false, false, true)) //implicitly declared destructor
{
	std::cout << "New class " << name << '\n';
}

class_::class_(class_&& c):
	name_(std::move(c.name_)),
	named_entities_(std::move(c.named_entities_)),
	named_declarative_regions_(std::move(c.named_declarative_regions_)),
	nested_classes_(std::move(c.nested_classes_)),
	constructors_(std::move(c.constructors_)),
	destructor_(std::move(c.destructor_)),
	simple_functions_(std::move(c.simple_functions_)),
	operator_functions_(std::move(c.operator_functions_)),
	conversion_functions_(std::move(c.conversion_functions_)),
	variables_(std::move(c.variables_))
{
}

const class_&
class_::operator=(class_&& c)
{
	name_ = std::move(c.name_);
	named_entities_ = std::move(c.named_entities_);
	named_declarative_regions_ = std::move(c.named_declarative_regions_);
	nested_classes_ = std::move(c.nested_classes_);
	constructors_ = std::move(c.constructors_);
	destructor_ = std::move(c.destructor_);
	simple_functions_ = std::move(c.simple_functions_);
	operator_functions_ = std::move(c.operator_functions_);
	conversion_functions_ = std::move(c.conversion_functions_);
	variables_ = std::move(c.variables_);

	return *this;
}

const std::string&
class_::name() const
{
    return name_;
}

bool
class_::is_global() const
{
    return false;
}

bool
class_::is_open_to_outside() const
{
	return true;
}

class_::named_entities_t::range
class_::named_entities()
{
	return named_entities_;
}

class_::named_entities_t::const_range
class_::named_entities() const
{
	return named_entities_;
}

class_::named_declarative_regions_t::range
class_::named_declarative_regions()
{
	return named_declarative_regions_;
}

class_::named_declarative_regions_t::const_range
class_::named_declarative_regions() const
{
	return named_declarative_regions_;
}

class_::base_classes_t::const_range
class_::base_classes() const
{
	return base_classes_;
}

class_::nested_classes_t::const_range
class_::nested_classes() const
{
	return nested_classes_;
}

class_::constructors_t::const_range
class_::constructors() const
{
	return constructors_;
}

std::shared_ptr<const class_::destructor>
class_::get_destructor() const
{
	return destructor_;
}

void
class_::set_destructor(std::shared_ptr<destructor> d)
{
	destructor_ = d;
}

class_::simple_functions_t::const_range
class_::simple_functions() const
{
	return simple_functions_;
}

class_::operator_functions_t::const_range
class_::operator_functions() const
{
	return operator_functions_;
}

class_::conversion_functions_t::const_range
class_::conversion_functions() const
{
	return conversion_functions_;
}

class_::variables_t::const_range
class_::variables() const
{
	return variables_;
}

void
class_::add(std::shared_ptr<base_class> c)
{
	base_classes_.push_back(c);
}

void
class_::add(std::shared_ptr<class_> member, access acc)
{
	nested_classes_.push_back(member);
	named_entities_.push_back(member);
	named_declarative_regions_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
}

void
class_::add(std::shared_ptr<constructor> member)
{
    constructors_.push_back(member);
}

void
class_::add
(
	std::shared_ptr<simple_function> member,
	access acc,
	bool const_qualified,
	bool volatile_qualified,
	bool virtual_specified,
	bool pure_specified
)
{
    simple_functions_.push_back(member);
	named_entities_.push_back(member);
	named_declarative_regions_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
	if(const_qualified) const_member_functions_.push_back(member);
	if(volatile_qualified) volatile_member_functions_.push_back(member);
	if(virtual_specified) virtual_member_functions_.push_back(member);
	if(pure_specified) pure_member_functions_.push_back(member);
}

void
class_::add
(
	std::shared_ptr<operator_function> member,
	access acc,
	bool const_qualified,
	bool volatile_qualified,
	bool virtual_specified,
	bool pure_specified
)
{
    operator_functions_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
	if(const_qualified) const_member_functions_.push_back(member);
	if(volatile_qualified) volatile_member_functions_.push_back(member);
	if(virtual_specified) virtual_member_functions_.push_back(member);
	if(pure_specified) pure_member_functions_.push_back(member);
}

void
class_::add(std::shared_ptr<conversion_function> member)
{
    conversion_functions_.push_back(member);
}

void
class_::add(std::shared_ptr<variable> member, access acc)
{
    variables_.push_back(member);
	named_entities_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
}



class_::base_class::base_class
(
	std::shared_ptr<class_> base,
	class_::access access,
	const bool is_virtual_specified
):
	base_(base),
	access_(access),
	virtual_specified_(is_virtual_specified)
{
}

class_::base_class::base_class(base_class&& o):
	base_(o.base_),
	access_(o.access_),
	virtual_specified_(o.virtual_specified_)
{
}

std::shared_ptr<const class_>
class_::base_class::base() const
{
	return base_;
}

class_::access
class_::base_class::access() const
{
	return access_;
}

bool
class_::base_class::virtual_specified() const
{
	return virtual_specified_;
}



class_::constructor::constructor
(
	parameters_t&& parameters,
	class_::access access,
	const bool is_inline_specified,
	const bool is_explicit_specified
):
	impl_
	(
		"_",
		std::shared_ptr<const built_in_type>(&built_in_type::void_, scalpel::utility::null_deleter()),
		std::move(parameters),
		is_inline_specified,
		false
	),
	access_(access),
	explicit_specified_(is_explicit_specified)
{
}

class_::constructor::constructor(constructor&& o):
	impl_(std::move(o.impl_)),
	access_(o.access_),
	explicit_specified_(o.explicit_specified_)
{
}

const class_::constructor::parameters_t&
class_::constructor::parameters() const
{
	return impl_.parameters();
}

class_::access
class_::constructor::access() const
{
	return access_;
}

bool
class_::constructor::inline_specified() const
{
	return impl_.inline_specified();
}

bool
class_::constructor::explicit_specified() const
{
	return explicit_specified_;
}



class_::destructor::destructor
(
	class_::access access,
	const bool is_inline_specified,
	const bool is_virtual_specified,
	const bool is_pure_specified,
	const bool is_implicitly_declared
):
	access_(access),
	inline_specified_(is_inline_specified),
	virtual_specified_(is_virtual_specified),
	pure_specified_(is_pure_specified),
	implicitly_declared_(is_implicitly_declared)
{
}

class_::destructor::destructor
(
	class_::access access,
	const bool is_inline_specified,
	const bool is_virtual_specified,
	const bool is_pure_specified
):
	access_(access),
	inline_specified_(is_inline_specified),
	virtual_specified_(is_virtual_specified),
	pure_specified_(is_pure_specified),
	implicitly_declared_(false)
{
}

class_::destructor::destructor(destructor&& o):
	access_(o.access_),
	inline_specified_(o.inline_specified_),
	virtual_specified_(o.virtual_specified_),
	pure_specified_(o.pure_specified_),
	implicitly_declared_(o.implicitly_declared_)
{
}

class_::access
class_::destructor::access() const
{
	return access_;
}

bool
class_::destructor::inline_specified() const
{
	return inline_specified_;
}

bool
class_::destructor::virtual_specified() const
{
	return virtual_specified_;
}

bool
class_::destructor::pure_specified() const
{
	return pure_specified_;
}

bool
class_::destructor::implicitly_declared() const
{
	return implicitly_declared_;
}



class_::conversion_function::conversion_function
(
	std::shared_ptr<const type> t,
	class_::access access,
	const bool is_const_qualified,
	const bool is_volatile_qualified,
	const bool is_inline_specified,
	const bool is_virtual_specified,
	const bool is_pure_specified
):
	type_(t),
	access_(access),
	const_qualified_(is_const_qualified),
	volatile_qualified_(is_volatile_qualified),
	inline_specified_(is_inline_specified),
	virtual_specified_(is_virtual_specified),
	pure_specified_(is_pure_specified)
{
}

class_::conversion_function::conversion_function(conversion_function&& o):
	type_(std::move(o.type_)),
	access_(o.access_),
	const_qualified_(o.const_qualified_),
	volatile_qualified_(o.volatile_qualified_),
	inline_specified_(o.inline_specified_),
	virtual_specified_(o.virtual_specified_),
	pure_specified_(o.pure_specified_)
{
}

std::shared_ptr<const type>
class_::conversion_function::get_type() const
{
	return type_;
}

class_::access
class_::conversion_function::access() const
{
	return access_;
}

bool
class_::conversion_function::const_qualified() const
{
	return const_qualified_;
}

bool
class_::conversion_function::volatile_qualified() const
{
	return volatile_qualified_;
}

bool
class_::conversion_function::inline_specified() const
{
	return inline_specified_;
}

bool
class_::conversion_function::virtual_specified() const
{
	return virtual_specified_;
}

bool
class_::conversion_function::pure_specified() const
{
	return pure_specified_;
}

}}} //namespace scalpel::cpp::semantic_entities

