/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SEMANTIC_GRAPH_SCOPE_HPP
#define SOCOA_CPP_SEMANTIC_GRAPH_SCOPE_HPP

#include <list>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include "named_entity.hpp"
#include "scope_visitor.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

struct scope
{
	typedef std::list<scope*> scopes_t;
	typedef scopes_t::const_iterator scope_const_iterator;
	typedef boost::indirect_iterator<scope_const_iterator, const scope&> scope_const_indirect_iterator;
	typedef boost::iterator_range<scope_const_indirect_iterator> scope_const_iterator_range;
	typedef scopes_t::iterator scope_iterator;
	typedef boost::indirect_iterator<scope_iterator, scope&> scope_indirect_iterator;
	typedef boost::iterator_range<scope_indirect_iterator> scope_iterator_range;

	typedef std::list<named_entity*> named_entities_t;
	typedef named_entities_t::const_iterator named_entity_const_iterator;
	typedef boost::indirect_iterator<named_entity_const_iterator, const named_entity&> named_entity_const_indirect_iterator;
	typedef boost::iterator_range<named_entity_const_indirect_iterator> named_entity_const_iterator_range;
	typedef named_entities_t::iterator named_entity_iterator;
	typedef boost::indirect_iterator<named_entity_iterator, named_entity&> named_entity_indirect_iterator;
	typedef boost::iterator_range<named_entity_indirect_iterator> named_entity_iterator_range;

	virtual
	~scope(){}

	virtual
	void
	accept(scope_visitor&) = 0;

	virtual
	const std::string&
	name() const = 0;

	virtual
	scope_iterator_range
	scopes() = 0;

	virtual
	scope_const_iterator_range
	scopes() const = 0;

	virtual
	named_entity_iterator_range
	named_entities() = 0;

	virtual
	named_entity_const_iterator_range
	named_entities() const = 0;

	/**
	@return true if the object has a enclosing scope scope
	*/
	virtual
	bool
	has_enclosing_scope() const = 0;

	/**
	@return the enclosing scope of the object
	*/
	virtual
	const scope&
	enclosing_scope() const = 0;

	/**
	@return the enclosing scope of the object
	*/
	virtual
	scope&
	enclosing_scope() = 0;
};

}}} //namespace socoa::cpp::semantic_graph

#endif
