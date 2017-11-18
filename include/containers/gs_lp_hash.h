//
// Created by gurumurt on 11/17/17.
//

#ifndef GRIDSTORE_GS_LP_HASH_H
#define GRIDSTORE_GS_LP_HASH_H

#endif //GRIDSTORE_GS_LP_HASH_H

#pragma once

#include <gs.h>
#include <containers/vec.h>

typedef struct gs_hash_lp_t gs_hash_lp_t;

#define GS_HASH_BUCKET_CAP 10

// typedef struct gs_hash_it_t gs_hash_it_t;


__BEGIN_DECLS

GS_DECLARE(gs_status_t) gs_hash_create(gs_hash_t **hash, size_t num_buckets, gs_comp_func_t key_comp);

                        GS_DECLARE(gs_status_t) gs_hash_create_ex(gs_hash_t **hash, size_t num_buckets, hash_code_fn_t hash_func, gs_comp_func_t key_comp);

                        GS_DECLARE(gs_status_t) gs_hash_dispose(gs_hash_t *hash);

                        GS_DECLARE(gs_status_t) gs_hash_set(gs_hash_t *hash, void *key, size_t key_size, void *val, gs_comp_func_t key_comp);

                        GS_DECLARE(gs_status_t) gs_hash_set_ex(gs_hash_t *hash, void *keys, size_t key_size, void *vals, size_t num_elems, gs_comp_func_t key_comp);

                        GS_DECLARE(gs_status_t) gs_hash_unset_ex(gs_hash_t *hash, void *keys, size_t key_size, size_t num_elems);

                        GS_DECLARE(void *) gs_hash_get(const gs_hash_t *hash, void *key, size_t key_size);

                        GS_DECLARE(gs_status_t) gs_hash_get_ex(vec_t *result, const gs_hash_t *hash, void *keys, size_t key_size, size_t num_elems);

// GS_DECLARE(gs_status_t) gs_hash_open(gs_hash_it_t **it, const gs_hash_t *hash);

// GS_DECLARE(gs_status_t) gs_hash_next(gs_hash_it_t *it, const void **key, const void **value);

// GS_DECLARE(gs_status_t) gs_hash_close(gs_hash_it_t *it);

__END_DECLS