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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_CLASS_SPECIFIER_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_CLASS_SPECIFIER_H

#include <string>
#include "type_specifier.h"
#include "class_head.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class member_specification;

class class_specifier: public type_specifier
{
    public:
        class_specifier
        (
            class_head&& head,
            std::shared_ptr<member_specification> a_member_specification
        );

        const class_head&
        get_head() const;

        const std::shared_ptr<member_specification>
        get_member_specification() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        class_head head_;
        std::shared_ptr<member_specification> member_specification_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
