//
// Created by Mahmoud Mohsen on 10/26/17.
//
#include <check.h>
#include <schema.h>
#include "test_vector.h"
#include "test_list.h"
#include "testhashset.h"
#include "test_utils.h"
#include "test_schema.h"
// #include "test_freelist.h"
#include "test_gshash.h"
int main(void)
{
    apr_initialize();
    init_vec_test();
    init_list_test();
    init_hashset_test();
    init_utils_test();
    init_schema_test();
    //  init_freelist_test();
    init_gs_hash_test();
    SRunner *sr = srunner_create(list_tsuit);
    srunner_add_suite(sr,vector_tsuit);
    srunner_add_suite(sr,hashset_tsuit);
   // srunner_add_suite(sr,gs_hash_tsuit);
    srunner_add_suite(sr,utils_tsuit);
    srunner_add_suite(sr,schema_tsuit);
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
//    schema_t *rat_schema = schema_new("test_table");
//    enum field_type ftype = FT_UINT32;
//    attr_create("age", ftype, sizeof(int32_t), rat_schema);
//    attr_create("salary", ftype, sizeof(int32_t), rat_schema);
//    attr_create("length", ftype, sizeof(int32_t), rat_schema);
//    attr_create("Id", ftype, sizeof(int32_t), rat_schema);
//    const attr_id_t* attributes_id = schema_attributes(rat_schema);
//    attr_id_t* projected_attributes_id = malloc( sizeof(attributes_id) * 3 );
//    *projected_attributes_id = *attributes_id;
//    *(projected_attributes_id + 1) = *attributes_id + 2;
//    *(projected_attributes_id + 2) = *attributes_id + 3;
//    printf("\nthe number of elements with in the schema = %d \n",(int) rat_schema->attr->num_elements) ;
//    schema_t *rat_subschema = schema_subset(rat_schema, projected_attributes_id, 3);
//    printf("\n %s \n",schema_attr_by_id(rat_subschema, 1)->name);
//    free((attr_id_t*)projected_attributes_id);
//    schema_delete(rat_schema);
//    apr_terminate();
//    return 0;
//}