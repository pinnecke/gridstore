//
// Created by Mahmoud Mohsen on 10/26/17.
//
#include <check.h>
#include "test_vector.h"
#include "test_list.h"
int main(void)
{
    apr_initialize();
    init_vec_test();
    init_list_test();
    SRunner *sr = srunner_create(list_tsuit);
    srunner_add_suite(sr,vector_tsuit);
    int nf;

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);
    apr_terminate();
    return nf == 0 ? 0 : 1;
}

//
//int main(void){
//    apr_initialize();
//    vec_t *rat_vec_src = vec_new(sizeof (int), 4);
//
//    int *source_data = malloc(4 * sizeof(int));
//    *source_data = 500;
//    *(source_data + 1) = 3;
//    *(source_data + 2) = 4;
//    *(source_data + 3) = 6;
////    printf("source + 2 = %d\n",*(source_data ));
//    vec_set(rat_vec_src, 0, 4, source_data);
//
//    int (*compare_ints_ptr)(const void*,const void*) = &compare_ints;
//    int (*equal_ints_ptr)(const void*,const void*) = &equal_ints;
//    int needle = 4;
//    int *search_results = (int *) vec_bsearch(rat_vec_src, &needle, compare_ints_ptr, equal_ints_ptr);
//
//    printf("search result = %d\n",*(search_results));
//
//    free(source_data);
//    vec_free(rat_vec_src);
//    apr_terminate();
//    return 0;
//}