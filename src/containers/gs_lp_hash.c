//
// Created by gurumurt on 11/17/17.
//

#include <containers/gs_lp_hash.h>
#include <emmintrin.h>
#include <smmintrin.h>

typedef struct gs_hash_func_t {
    const void         *capture;
    hash_code_fn_t      hash_code;
} gs_hash_func_t;

typedef struct hash_bucket_t {
    bool                *in_use;
    const void          *key;
    const void          *value;
    size_t              num_of_entries;
} hash_bucket_t;

typedef struct gs_hash_lp_t {
    hash_bucket_t       *buckets;
    size_t               num_buckets;
    hash_code_fn_t       hash_func;
} gs_hash_lp_t;

#define GET_HASH_CODE(key, key_size)                                \
    (hash->hash_func(NULL, key_size, key) % hash->num_buckets)

static inline void setup_hash_buckets(hash_bucket_t *buckets, size_t num_buckets, gs_comp_func_t key_comp);
static inline void cleanup_hash_buckets(hash_bucket_t *buckets, size_t num_buckets);
static inline void hash_bucket_init(hash_bucket_t *bucket, gs_comp_func_t key_comp);
static inline void hash_bucket_set(hash_bucket_t *bucket, void *key, void *value, gs_comp_func_t key_comp);
static inline void hash_bucket_unset(hash_bucket_t *bucket, void *key);
static inline const void *hash_bucket_get(hash_bucket_t *bucket, void *key);
static inline void hash_bucket_cleanup(hash_bucket_t *bucket);
static inline void hash_bucket_entry_init(hash_bucket_entry_t *entry, gs_comp_func_t key_comp);
static inline int entry_comp_by_key(const void *a, const void *b);

static inline void size_t_init(void *data);
static inline void size_t_inc(void *data);


//creating Linear probing hash table
GS_DECLARE(gs_status_t) gs_hash_create(gs_hash_lp_t **hash, size_t num_buckets, gs_comp_func_t key_comp)
{
    return gs_hash_create_ex(hash, num_buckets, hash_code_jen, key_comp);
}

GS_DECLARE(gs_status_t) gs_hash_create_ex(gs_hash_lp_t **hash, size_t num_buckets,size_t num_of_entries, hash_code_fn_t hash_func, gs_comp_func_t key_comp)
{
    gs_hash_lp_t *result   =   (gs_hash_lp_t *)malloc(sizeof(gs_hash_lp_t));
    result->buckets     = (hash_bucket_t *)malloc(num_buckets*sizeof(hash_bucket_t));
    result->hash_func   = hash_func;
    result->num_buckets = num_buckets;
    setup_hash_buckets(result->buckets, result->num_buckets, key_comp, num_of_entries);
    *hash = result;
    return GS_SUCCESS;
}

static inline void setup_hash_buckets(hash_bucket_t *buckets, size_t num_buckets, gs_comp_func_t key_comp,size_t num_of_entries)
{
    for(int i=0;i<num_buckets;i++){
        buckets[i].num_of_entries = num_of_entries;
        buckets[i].in_use = (bool *)malloc(num_of_entries*sizeof(bool));
        buckets[i].key = (int *)calloc(num_of_entries,num_of_entries*sizeof(int));
        buckets[i].value = (int *)alloc(num_of_entries,num_of_entries*sizeof(int));
    }
}

//setting Linear probing hash table with key and value pair
GS_DECLARE(gs_status_t) gs_hash_set(gs_hash_lp_t *hash, void *key, size_t key_size, void *val, gs_comp_func_t key_comp)
{
return gs_hash_set_ex(hash, key, key_size, val, 1, key_comp);
}

GS_DECLARE(gs_status_t) gs_hash_set_ex(gs_hash_lp_t *hash, void *keys, size_t key_size, void *vals, size_t num_elems,
gs_comp_func_t key_comp)
{
GS_REQUIRE_NONNULL(hash);
GS_REQUIRE_NONNULL(keys);
GS_REQUIRE_NONNULL(vals);

while (num_elems--) {
void *key = keys++;
void *val = vals++;
size_t bucket_idx = GET_HASH_CODE(key, key_size);
hash_bucket_set(bucket_idx, key, val, key_comp);
}

return GS_SUCCESS;
}

static inline void hash_bucket_set(hash_bucket_t *bucket, void *key, void *value, gs_comp_func_t key_comp)
{
    for(int i=0;i<(bucket->num_of_entries)/4;i++){
        __m128i keysInsert = _mm_loadu_si128(key);
        __m128i avail = _mm_loadu_si128(bucket->key);

        if(_mm_test_all_zeros(avail,0)){
            _mm_storeu_si128(avail->key,keysInsert);
        }
    }
}


