// An implementation of a tables attribute data structure
// Copyright (C) 2017 Marcus Pinnecke
//
// This program is free software: you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see <http://www.gnu.org/licenses/>.

#pragma once

// ---------------------------------------------------------------------------------------------------------------------
// I N C L U D E S
// ---------------------------------------------------------------------------------------------------------------------

#include <defs.h>
#include <types.h>

// ---------------------------------------------------------------------------------------------------------------------
// D A T A   T Y P E S
// ---------------------------------------------------------------------------------------------------------------------

enum mdb_attr_flags
{
    AF_AUTOINC     = 1 << 1,
    AF_PRIMARY_KEY = 1 << 2,
    AF_NON_NULL    = 1 << 3,
    AF_UNIQUE      = 1 << 4
};

typedef struct
{
    enum mdb_type type;
    size_t length;
    const char *name;
    struct {
        short non_null    : 1;
        short primary_key : 1;
        short auto_inc    : 1;
        short unique      : 1;
    } flags;
} mdb_attribute;

// ---------------------------------------------------------------------------------------------------------------------
// I N T E R F A C E   F U N C T I O N S
// ---------------------------------------------------------------------------------------------------------------------

mdb_attribute *mdb_attribute_alloc(enum mdb_type type, size_t length, const char *name, enum mdb_attr_flags flags);

bool mdb_attribute_free(mdb_attribute *attr);

bool mdb_attribute_comp(const mdb_attribute *lhs, const mdb_attribute *rhs);

mdb_attribute *mdb_attribute_cpy(const mdb_attribute *proto);