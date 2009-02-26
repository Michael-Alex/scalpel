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

#include "template_id.h"

#include "template_id_impl.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

template_id::template_id
(
    identifier&& an_identifier,
    boost::optional<util::sequence<template_argument, util::extern_strings::comma>> a_template_argument_list
):
	pimpl_
	(
		std::make_shared<template_id_impl>
		(
			an_identifier,
			a_template_argument_list
		)
	)
{
}

const identifier&
template_id::get_identifier() const
{
	return pimpl_->get_identifier();
}

const boost::optional<const util::sequence<template_argument, util::extern_strings::comma>&>
template_id::get_template_argument_list() const
{
	return pimpl_->get_template_argument_list();
}

}}} //namespace socoa::cpp::syntax_tree