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

#pragma once

#include <check.h>
#include <stdio.h>
#include <grid.h>
#include <tuplet_field.h>
#include <tuple_field.h>
#include <tuple.h>

Suite *tuple_tsuit;
TCase *tuple_test_1;
TCase *tuple_test_2;
TCase *tuple_test_3;
TCase *tuple_test_4;


START_TEST(test_tuple_open)
    {

        schema_t *schema = schema_new("My Grid Table");
        attr_create_uint64("A", schema); // attribute id 0
        attr_create_uint32("B", schema); // attribute id 1
        attr_create_uint16("C", schema); // attribute id 2
        attr_create_uint16("D", schema); // attribute id 3

        table_t *table = table_new(schema, 16);
        printf("\n \n hi I'm here \n \n");

        tuple_t rat_tuple;
        tuple_open(&rat_tuple, table, 0);
        fail_unless(rat_tuple.table == table, "tuple open has failed");
//        fail_unless(rat_tuple.table == table, "tuple open has failed");
        table_delete(table);
        schema_delete(schema);
    }
END_TEST

void init_tuple_test()
{
    tuple_tsuit = suite_create("tuple test suit");

    tuple_test_1 = tcase_create("test tuple open");
    tcase_add_test(tuple_test_1, test_tuple_open);
//    tuple_test_2 = tcase_create("test tuple next");
//    tcase_add_test(tuple_test_2, test_tuple_next) ;
//    tuple_test_3 = tcase_create("test tuple size");
//    tcase_add_test(tuple_test_3, test_tuple_size) ;
//    tuple_test_4 = tcase_create("test tuple size by schema");
//    tcase_add_test(tuple_test_4, test_size_by_schema) ;

    suite_add_tcase(tuple_tsuit, tuple_test_1);
//    suite_add_tcase(tuple_tsuit, tuple_test_2);
//    suite_add_tcase(tuple_tsuit, tuple_test_3);
//    suite_add_tcase(tuple_tsuit, tuple_test_4);
}