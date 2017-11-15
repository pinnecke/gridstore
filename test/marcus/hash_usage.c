#include <stdio.h>
#include <containers/gs_hash.h>

int compare_ints(const void *lhs ,const void *rhs);

int main(void) {

    apr_initialize();
    gs_hash_t *gs_hash;                             // <------- MUST be a pointer to "gs_hash_t" ;)
    gs_hash_create(&gs_hash,10, compare_ints);
//    gs_hash_dispose(gs_hash);
    return 0;
}

int compare_ints(const void *lhs ,const void *rhs)
{
    return *(int *) lhs >= *(int *)rhs ;
}