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
#include <tuplet.h>
#include <tuplet_field.h>


Suite *tuplet_field_tsuit;
TCase *tuplet_field_test_1;
TCase *tuplet_field_test_2;
TCase *tuplet_field_test_3;
TCase *tuplet_field_test_4;
TCase *tuplet_field_test_5;


START_TEST(test_tuplet_field_update)
    {
        tuplet_field_t rat_tuplet_field;
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 2);
        tuplet_t rat_tuplet;
        tuplet_open(&rat_tuplet, rat_frag, 0);
        tuplet_field_open(&rat_tuplet_field, &rat_tuplet);
        int first_tuplet[] = {85, 1500};
        int second_tuplet[] = {95 ,1800};
        tuplet_field_update(&rat_tuplet_field, first_tuplet);
        const int *data = tuplet_field_read(&rat_tuplet_field);
        fail_unless(data[0] == first_tuplet[0], "tuplet field update has failed");
        fail_unless(data[1] == first_tuplet[1], "tuplet field update has failed");
        fail_unless(tuplet_field_next(&rat_tuplet_field, true));
        tuplet_field_update(&rat_tuplet_field, second_tuplet);
        data = tuplet_field_read(&rat_tuplet_field);
        fail_unless(data[0] == second_tuplet[0], "tuplet field update has failed");
        fail_unless(data[1] == second_tuplet[1], "tuplet field update has failed");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_tuplet_field_write)
    {
        tuplet_field_t rat_tuplet_field;
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 2);
        tuplet_t rat_tuplet;
        tuplet_open(&rat_tuplet, rat_frag, 0);
        tuplet_field_open(&rat_tuplet_field, &rat_tuplet);
        int first_tuplet[] = {85, 1500};
        int second_tuplet[] = {95 ,1800};
        bool next = tuplet_field_write(&rat_tuplet_field, first_tuplet, true);
        tuplet_field_update(&rat_tuplet_field, second_tuplet);
        const int *data = tuplet_field_read(&rat_tuplet_field);
        fail_unless(next, "tuplet field write has failed");
        fail_unless(data[0] == second_tuplet[0], "tuplet field write has failed");
        fail_unless(data[1] == second_tuplet[1], "tuplet field write has failed");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_tuplet_field_size)
    {
        tuplet_field_t rat_tuplet_field;
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 2);

        tuplet_t rat_tuplet;
        tuplet_open(&rat_tuplet, rat_frag, 0);
        tuplet_field_open(&rat_tuplet_field, &rat_tuplet);

        fail_unless(tuplet_field_size(&rat_tuplet_field) == (4 * 2 * sizeof(int32_t)), "tuplet field size has"
                "failed");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_tuplet_get_type)
    {
        tuplet_field_t rat_tuplet_field;
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 2);
        tuplet_t rat_tuplet;
        tuplet_open(&rat_tuplet, rat_frag, 0);
        tuplet_field_open(&rat_tuplet_field, &rat_tuplet);
        fail_unless(tuplet_field_get_type(&rat_tuplet_field) == FT_UINT32, "tuplet type size has"
                "failed");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_tuplet_field_str)
    {
        tuplet_field_t rat_tuplet_field;
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 2);
        tuplet_t rat_tuplet;
        tuplet_open(&rat_tuplet, rat_frag, 0);
        tuplet_field_open(&rat_tuplet_field, &rat_tuplet);
        int first_tuplet[] = {85, 1500};
        tuplet_field_update(&rat_tuplet_field, first_tuplet);
        fail_unless(! strcmp(tuplet_field_str(&rat_tuplet_field),"85"), "tuplet field str failed");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


// usage is not known yet.
//START_TEST(test_tuplet_field_printlen)
//    {
//        tuplet_field_t rat_tuplet_field;
//        schema_t *rat_schema = schema_new("test_table");
//        enum field_type ftype = FT_UINT32;
//        attr_create("age", ftype, sizeof(int32_t), rat_schema);
//        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
//        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
//        tuplet_t out;
//        frag_insert(&out, rat_frag, 2);
//        tuplet_t rat_tuplet;
//        tuplet_open(&rat_tuplet, rat_frag, 0);
//        tuplet_field_open(&rat_tuplet_field, &rat_tuplet);
//        printf("\n\n what should be returned is %d \n\n",(int) tuplet_field_printlen(&rat_tuplet_field));
////        fail_unless(tuplet_field_size(&rat_tuplet_field) == (4 * 2 * sizeof(int32_t)), "tuplet field size has"
////                "failed");
//        frag_delete(rat_frag);
//        schema_delete(rat_schema);
//    }
//END_TEST

// not implemented yet
//START_TEST(test_tuplet_set_null)
//    {
//        tuplet_field_t rat_tuplet_field;
//        schema_t *rat_schema = schema_new("test_table");
//        enum field_type ftype = FT_UINT32;
//        attr_create("age", ftype, sizeof(int32_t), rat_schema);
//        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
//        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
//        tuplet_t out;
//        frag_insert(&out, rat_frag, 2);
//        tuplet_t rat_tuplet;
//        tuplet_open(&rat_tuplet, rat_frag, 0);
//        tuplet_field_open(&rat_tuplet_field, &rat_tuplet);
//
//                fail_unless(tuplet_field_size(&rat_tuplet_field) == (4 * 2 * sizeof(int32_t)), "tuplet field size has"
//                "failed");
//        frag_delete(rat_frag);
//        schema_delete(rat_schema);
//    }
//END_TEST


void init_tuplet_field_test()
{
    tuplet_field_tsuit = suite_create("Tuplet Field Suit");

    tuplet_field_test_1 = tcase_create("test tuplet field update");
    tcase_add_test(tuplet_field_test_1, test_tuplet_field_update);
    tuplet_field_test_2 = tcase_create("test tuplet field write");
    tcase_add_test(tuplet_field_test_2, test_tuplet_field_write);
    tuplet_field_test_3 = tcase_create("test tuplet field size");
    tcase_add_test(tuplet_field_test_3, test_tuplet_field_size);
    tuplet_field_test_4 = tcase_create("test tuplet field get type");
    tcase_add_test(tuplet_field_test_4, test_tuplet_get_type);
    tuplet_field_test_5 = tcase_create("test tuplet field str");
    tcase_add_test(tuplet_field_test_5, test_tuplet_field_str);

    suite_add_tcase(tuplet_field_tsuit, tuplet_field_test_1);
    suite_add_tcase(tuplet_field_tsuit, tuplet_field_test_2);
    suite_add_tcase(tuplet_field_tsuit, tuplet_field_test_3);
    suite_add_tcase(tuplet_field_tsuit, tuplet_field_test_4);
    suite_add_tcase(tuplet_field_tsuit, tuplet_field_test_5);
}

