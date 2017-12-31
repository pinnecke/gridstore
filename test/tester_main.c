// Copyright (C) 2017 Marcus Pinnecke
//
// This program is free software: you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation, either user_port 3 of the License, or
// (at your option) any later user_port.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see <http://www.gnu.org/licenses/>.

#include <check.h>
#include <schema.h>
#include "test_vector.h"
#include "utilities.h"
#include "test_list.h"
//#include "testhashset.h"
#include "test_utils.h"
#include "test_schema.h"
#include "test_attr.h"
#include "test_gshash.h"
#include "test_freelist.h"
#include "test_frag.h"
#include "test_tuplet.h"
#include "test_tuplet_field.h"
#include "test_tuple.h"
#include "test_dispatcher.h"
#include "test_event.h"
#include "test_gs_request.h"
int main(void)
{
    apr_initialize();

    init_vec_test();
    init_list_test();
//    init_hashset_test();  >> not implemented yet as of 16/11/2017
    init_utils_test();
    init_schema_test();
    init_attr_test();
    init_gs_hash_test();
    init_freelist_test();
    init_gs_hash_test();
    init_frag_test();
    init_tuplet_test();
    init_tuplet_field_test();
    init_tuple_test();
//    init_dispatcher_test();
    init_event_test();
    init_gs_request_test();

    SRunner *sr = srunner_create(list_tsuit);
    srunner_add_suite(sr,vector_tsuit);
//    srunner_add_suite(sr,hashset_tsuit); >> not implemented yet as of 16/11/2017
//    srunner_add_suite(sr, gs_hash_tsuit);
//    srunner_add_suite(sr, utils_tsuit);
//    srunner_add_suite(sr, schema_tsuit);
//    srunner_add_suite(sr, attr_tsuit);
//    srunner_add_suite(sr, freelist_tsuit);
//    srunner_add_suite(sr, frag_tsuit);
//    srunner_add_suite(sr, tuplet_tsuit);
//    srunner_add_suite(sr, tuplet_field_tsuit);
//    srunner_add_suite(sr, tuple_tsuit);
//    srunner_add_suite(sr, dispatcher_tsuit);
//    srunner_add_suite(sr, event_tsuit);
    srunner_add_suite(sr, gs_request_tsuit);

    int nf;
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    apr_terminate();

    return nf == 0 ? 0 : 1;
}
//
////////
//int main(void){
//
//    apr_initialize();
//
//    schema_t *schema = schema_new("My Grid Table");
//    attr_create_uint64("A", schema); // attribute id 0
//    attr_create_uint32("B", schema); // attribute id 1
//    attr_create_uint16("C", schema); // attribute id 2
//    attr_create_uint16("D", schema); // attribute id 3
//
//    table_t *table = table_new(schema, 16);
//    printf("\n \n hi I'm here \n \n");
//
//    tuple_t rat_tuple;
//    tuple_open(&rat_tuple, table, 0);
//            fail_unless(rat_tuple.table == table, "tuple open has failed");
////        fail_unless(rat_tuple.table == table, "tuple open has failed");
//    table_delete(table);
//    schema_delete(schema);
//
//    apr_terminate();
//
//    return 0;
//}