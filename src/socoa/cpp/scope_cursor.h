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

#ifndef SOCOA_CPP_SCOPE_CURSOR_H
#define SOCOA_CPP_SCOPE_CURSOR_H

#include <memory>
#include "program_tree/namespace_.h"

namespace socoa { namespace cpp
{

/**
Used by grammar.
Its instance points to the currently scanned scope.
*/
class scope_cursor
{
    public:
        explicit
        scope_cursor(std::shared_ptr<program_tree::namespace_> global_namespace);

        void
        reset();

        const std::shared_ptr<program_tree::name_tree_composite>
        get_current_scope() const;

        void
        enter_scope(std::shared_ptr<program_tree::name_tree_composite> scope);

        void
        leave_current_scope();

        /*!
         * Sets the corresponding scope of the last encountered scope's header.\n
         * E.g. in this context:
         * \code
         * namespace n //when the scanner is at this point
         * {
         *     //...
         * }
         * \endcode
         * 'n' is the scope of last encountered scope's header.
         */
        void
        set_last_encountered_scope_header_scope(std::shared_ptr<program_tree::name_tree_composite> scope);

        void
        enter_last_encountered_scope_header_scope();

    private:
        std::shared_ptr<program_tree::name_tree_composite> global_namespace_;
        std::shared_ptr<program_tree::name_tree_composite> current_scope_;
        std::shared_ptr<program_tree::name_tree_composite> last_encountered_scope_header_scope_;
};

}} //namespace socoa::cpp

#endif
