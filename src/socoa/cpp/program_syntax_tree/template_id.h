/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_TEMPLATE_ID_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_TEMPLATE_ID_H

#include <memory>
#include "../../util/sequence.h"
#include "../../util/extern_strings.h"
#include "visitor.h"
#include "identifier.h"
#include "identifier_or_template_id.h"
#include "unqualified_id.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class template_argument;

struct template_id: public identifier_or_template_id, public unqualified_id
{
    template_id
    (
        identifier&& an_identifier,
        std::shared_ptr<util::sequence<template_argument, util::comma>> a_template_argument_list
    );

    SOCOA_CPP_DEFINE_VISITABLE()

    const identifier identifier_;
    const std::shared_ptr<util::sequence<template_argument, util::comma>> template_argument_list_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif