/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008  Florian Goujeon

This file is part of CppParser.

CppParser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

CppParser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CppParser.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "program.h"

namespace cppparser { namespace program_model
{

namespace
{
struct null_deleter
{
    void operator()(void const *) const
    {
    }
};
}

program::program():
    m_global_namespace_ptr(&m_global_namespace, null_deleter())
{
    m_global_namespace.shared_this(m_global_namespace_ptr);
}

std::shared_ptr<namespace_>
program::global_namespace()
{
    return m_global_namespace_ptr;
}

}} //namespace cppparser::program_model
