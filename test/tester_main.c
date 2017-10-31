//
// Created by Mahmoud Mohsen on 10/26/17.
//
#include <check.h>
#include "test_vector.h"

int main(void)
{
    apr_initialize();
    init_vec_test();
    SRunner *sr = srunner_create(vector_tsuit);
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
//    vec_t *rat_vec = vec_new(sizeof (int),20);
//    int *source_data = malloc(3 * sizeof(int));
//    *source_data =4;
//    *(source_data + 1) =2;
//    *(source_data + 2) =3;
//    rat_vec->num_elements = 3;
//    rat_vec->data = source_data;
//    comp_t my_comp = &compare_ints;
////    printf("the result %d", my_comp(&a,&b));
//    vec_updatesort(rat_vec,my_comp);
//    printf("vd  =%d \n",rat_vec->is_sorted);
//    vec_free(rat_vec);
//
//    apr_terminate();
//    return 0;
//}