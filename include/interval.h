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

#include <stdinc.h>
#include <tuple.h>

// ---------------------------------------------------------------------------------------------------------------------
// D A T A   T Y P E S
// ---------------------------------------------------------------------------------------------------------------------

typedef struct interval_t {
    size_t begin;
    size_t end;
} interval_t;

typedef struct tuple_id_interval_t {
    tuple_id_t begin;
    tuple_id_t end;
} tuple_id_interval_t;

// ---------------------------------------------------------------------------------------------------------------------
// M A C R O S
// ---------------------------------------------------------------------------------------------------------------------

#define gs_interval_get_span(interval)                                   \
    ({                                                                   \
        (interval->end - interval->begin);                               \
    })

#define GS_INTERVAL_CONTAINS(interval, elem)                             \
    ({                                                                   \
        (elem >= interval->begin && elem < interval->end);               \
    })

#define gs_interval_equals(a, b)                                         \
    ({                                                                   \
        (a->begin == b->begin && a->end == b->end);                      \
    })

// ---------------------------------------------------------------------------------------------------------------------
// I N L I N E   F U N C T I O N S
// ---------------------------------------------------------------------------------------------------------------------

static inline int gs_interval_tuple_id_comp_by_lower_bound(const void *lhs, const void *rhs)
{
    const tuple_id_interval_t *a = lhs;
    const tuple_id_interval_t *b = rhs;
    return (a->begin < b->begin ? - 1 : (a->begin > b->begin ? + 1 : 0));
}