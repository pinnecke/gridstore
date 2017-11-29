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


Suite *tuplet_tsuit;
TCase *tuplet_test_1;
TCase *tuplet_test_2;
TCase *tuplet_test_3;
TCase *tuplet_test_4;


bool next_tuplet(struct tuplet_t *);


START_TEST(test_tuplet_field_type)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 6);
        tuplet_t rat_tuplet;
        tuplet_open(&rat_tuplet, rat_frag, 0);

        fail_unless(tuplet_field_type(&rat_tuplet, 0) == FT_UINT32, "tuplet_field_type has failed");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST



START_TEST(test_tuplet_next)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 6);
        tuplet_t rat_tuplet;
        tuplet_open(&rat_tuplet, rat_frag, 0);
        fail_unless(tuplet_next(&rat_tuplet), "tuplet_next has failed");
        tuplet_open(&rat_tuplet, rat_frag, 4);
        fail_unless(tuplet_next(&rat_tuplet), "tuplet_next has failed");
        tuplet_open(&rat_tuplet, rat_frag, 5);
        fail_unless(! tuplet_next(&rat_tuplet), "tuplet_next has failed");
        tuplet_rewind(&rat_tuplet);
        fail_unless(tuplet_next(&rat_tuplet), "tuplet_next has failed");

        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_tuplet_size)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 6);
        tuplet_t rat_tuplet;
        tuplet_open(&rat_tuplet, rat_frag, 0);

        fail_unless(tuplet_size(&rat_tuplet) == (sizeof(int32_t) * 2 * 4), "tuplet_size has failed");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_size_by_schema)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 6);
        tuplet_t rat_tuplet;
        tuplet_open(&rat_tuplet, rat_frag, 0);
        fail_unless(tuplet_size(&rat_tuplet) == tuplet_size_by_schema(rat_tuplet.fragment->schema), "tuplet schema"
                "size has failed");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST

// tuplet set null isn't yet implemented
//START_TEST(test_tuplet_set_null)
//    {
//        schema_t *rat_schema = schema_new("test_table");
//        enum field_type ftype = FT_UINT32;
//        attr_create("age", ftype, sizeof(int32_t), rat_schema);
//        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
//        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
//        tuplet_t out;
//        frag_insert(&out, rat_frag, 6);
//        tuplet_t rat_tuplet;
//        tuplet_open(&rat_tuplet, rat_frag, 0);
//        tuplet_set_null(&rat_tuplet);
//        printf("\n \n \n  Heeeeeeeeeeeeeeeeeeere  \n \n \n");
//
//        fail_unless(tuplet_is_null(&rat_tuplet), "tuplet is null has failed");
//        frag_delete(rat_frag);
//        schema_delete(rat_schema);
//    }
//END_TEST

bool next_tuplet(struct tuplet_t * tuplet)
{

    return true;
}

void init_tuplet_test()
{
    tuplet_tsuit = suite_create("tuplet test suit");

    tuplet_test_1 = tcase_create("test tuplet field type");
    tcase_add_test(tuplet_test_1, test_tuplet_field_type) ;
    tuplet_test_2 = tcase_create("test tuplet next");
    tcase_add_test(tuplet_test_2, test_tuplet_next) ;
    tuplet_test_3 = tcase_create("test tuplet size");
    tcase_add_test(tuplet_test_3, test_tuplet_size) ;
    tuplet_test_4 = tcase_create("test tuplet size by schema");
    tcase_add_test(tuplet_test_4, test_size_by_schema) ;

    suite_add_tcase(tuplet_tsuit, tuplet_test_1);
    suite_add_tcase(tuplet_tsuit, tuplet_test_2);
    suite_add_tcase(tuplet_tsuit, tuplet_test_3);
    suite_add_tcase(tuplet_tsuit, tuplet_test_4);
}
