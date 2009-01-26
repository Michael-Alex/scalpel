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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_ASSIGNMENT_EXPRESSION_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_ASSIGNMENT_EXPRESSION_H

#include "assignment_operator.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

struct assignment_expression
{
    //const logical_or_expression logical_or_expression_;
    const assignment_operator assignment_operator_;
    //const std::shared_ptr<> ;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
