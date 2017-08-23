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

// ---------------------------------------------------------------------------------------------------------------------
// I N C L U D E S
// ---------------------------------------------------------------------------------------------------------------------

#include <indexes/hindexes/bsearch_hindex.h>

// ---------------------------------------------------------------------------------------------------------------------
// D A T A T Y P E S
// ---------------------------------------------------------------------------------------------------------------------

typedef struct entry_t {
    tuple_id_interval_t interval;
    vector_t *grids;
} entry_t;

// ---------------------------------------------------------------------------------------------------------------------
// M A C R O S
// ---------------------------------------------------------------------------------------------------------------------

#define require_besearch_hindex_tag(index)                                                                             \
    require((index->tag == HT_BINARY_SEARCH), BADTAG);

#define require_instanceof_this(index)                                                                                 \
    { require_nonnull(index); require_nonnull(index->extra); require_besearch_hindex_tag(index); }

// ---------------------------------------------------------------------------------------------------------------------
// H E L P E R   P R O T O T Y P E S
// ---------------------------------------------------------------------------------------------------------------------

static inline void this_add(struct hindex_t *self, const tuple_id_interval_t *key, const struct grid_t *grid);
static inline void this_remove_interval(struct hindex_t *self, const tuple_id_interval_t *key);
static inline void this_remove_intersec(struct hindex_t *self, tuple_id_t tid);
static inline bool this_contains(const struct hindex_t *self, tuple_id_t tid);
static inline hindex_result_t *this_query_open(const struct hindex_t *self, const tuple_id_t *tid_begin,
                                const tuple_id_t *tid_end);
static inline const struct grid_t *this_query_read(const struct hindex_t *self, hindex_result_t *result_set);
static inline void this_query_close(hindex_result_t *result_set);
static inline void this_free(struct hindex_t *self);

// ---------------------------------------------------------------------------------------------------------------------
// I N T E R F A C E  I M P L E M E N T A T I O N
// ---------------------------------------------------------------------------------------------------------------------

hindex_t *besearch_hindex_create(size_t approx_num_horizontal_partitions)
{
    hindex_t *result = require_good_malloc(sizeof(hindex_t));
    *result = (hindex_t) {
        .tag = HT_BINARY_SEARCH,

        ._add = this_add,
        ._remove_interval = this_remove_interval,
        ._remove_intersec = this_remove_intersec,
        ._contains = this_contains,
        ._query_open = this_query_open,
        ._query_read = this_query_read,
        ._query_close = this_query_close,
        ._free = this_free,

        .extra = vector_create(sizeof(entry_t), approx_num_horizontal_partitions)
    };

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------
// H E L P E R   I M P L E M E N T A T I O N
// ---------------------------------------------------------------------------------------------------------------------

static inline int comp_by_start(const void *lhs, const void *rhs)
{
    const tuple_id_interval_t *a = lhs;
    const tuple_id_interval_t *b = rhs;
    return (b->begin - a->begin);
}

static inline int comp_intervals(const void *needle, const void *data)
{
    const tuple_id_interval_t *a = needle;
    const tuple_id_interval_t *b = data;
    if (a->begin < b->begin) {
        return -1;
    } else if (a->begin > b->begin) {
        return 1;
    } else {
        return (b->end - a->end);
    }
}

static inline void this_add(struct hindex_t *self, const tuple_id_interval_t *key, const struct grid_t *grid)
{
    require_instanceof_this(self);
    require_non_null(key);
    require_non_null(grid);

    vector_t *vec = self->extra;
    entry_t *result = vector_bsearch(vec, key, comp_by_start, comp_intervals);
    if (result) {
        vector_add(result->grids, 1, &grid);
    } else {
        entry_t entry = {
                .interval = *key,
                .grids = vector_create(sizeof(struct grid_t *), 16)
        };
        vector_add(entry.grids, 1, &grid);
        vector_add(vec, 1, &entry);
    }
}

static inline void this_remove_interval(struct hindex_t *self, const tuple_id_interval_t *key)
{
    panic(NOTIMPLEMENTED, to_string(this_remove_interval))
}

static inline void this_remove_intersec(struct hindex_t *self, tuple_id_t tid)
{
    panic(NOTIMPLEMENTED, to_string(this_remove_intersec))
}

static inline bool this_contains(const struct hindex_t *self, tuple_id_t tid)
{
    require_instanceof_this(self);
    // TODO:...
    panic(NOTIMPLEMENTED, to_string(this_contains))
    return false;
}

static inline hindex_result_t *this_query_open(const struct hindex_t *self, const tuple_id_t *tid_begin,
                                 const tuple_id_t *tid_end)
{
    require_instanceof_this(self);
    // TODO:...
    panic(NOTIMPLEMENTED, to_string(hindex_result_t))
    return NULL;
}

static inline const struct grid_t *this_query_read(const struct hindex_t *self, hindex_result_t *result_set)
{
    require_instanceof_this(self);
    require_instanceof_this(result_set);
    // TODO:...
    panic(NOTIMPLEMENTED, to_string(this_query_read))
    return NULL;
}

static inline void this_query_close(hindex_result_t *result_set)
{
    require_instanceof_this(result_set);
    // TODO:...
    panic(NOTIMPLEMENTED, to_string(this_query_close))
}

static inline void this_free(struct hindex_t *self)
{
    require_instanceof_this(self);
    // TODO:...
    panic(NOTIMPLEMENTED, to_string(this_free))

}