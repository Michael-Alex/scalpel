/*
Scalpel _ Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_ARGUMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_ARGUMENT_HPP

#include "alternative_node.hpp"
#include "composite_node.hpp"
#include "template_argument_assignment_expression.hpp"
#include "type_id.hpp"
#include "id_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		template_argument_assignment_expression,
		type_id,
		id_expression
	>
	template_argument_t
;

class template_argument: public template_argument_t
{
	public:
		template_argument(template_argument_assignment_expression&& o): template_argument_t(o){}
		template_argument(type_id&& o): template_argument_t(o){}
		template_argument(id_expression&& o): template_argument_t(o){}

		template_argument(const template_argument& o): template_argument_t(static_cast<const template_argument_t&>(o)){}

		template_argument(template_argument&& o): template_argument_t(static_cast<template_argument_t&&>(o)){}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
