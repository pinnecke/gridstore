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
#include <frag.h>
#include <check.h>
#include <schema.h>
#include <attr.h>
#include <field_type.h>
#include <stdio.h>
#include <tuplet.h>

Suite *frag_tsuit;
TCase *frag_test_1;
TCase *frag_test_2;
TCase *frag_test_3;
TCase *frag_test_4;
TCase *frag_test_5;
TCase *frag_test_6;
TCase *frag_test_7;
TCase *frag_test_8;
TCase *frag_test_9;
TCase *frag_test_10;
TCase *frag_test_11;
TCase *frag_test_12;


START_TEST(test_frag_new_vsm)
{
    schema_t *rat_schema = schema_new("test_table");
    enum field_type ftype = FT_UINT32;
    attr_create("age", ftype, sizeof(int32_t), rat_schema);
    attr_create("salary", ftype, sizeof(int32_t), rat_schema);
    frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
    frag_delete(rat_frag);
    schema_delete(rat_schema);
}
END_TEST


START_TEST(test_frag_insert_vsm)
{
    schema_t *rat_schema = schema_new("test_table");
    enum field_type ftype = FT_UINT32;
    attr_create("age", ftype, sizeof(int32_t), rat_schema);
    attr_create("salary", ftype, sizeof(int32_t), rat_schema);
    frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
    tuplet_t out;
    frag_insert(&out, rat_frag, 4);
    const char *path_to_file ="/home/pegasus/gridstore_test/fragment.txt";
    FILE *output_file = fopen(path_to_file, "w");
    frag_print(output_file, rat_frag, 0, 4);
    fclose(output_file);

    FILE *file_reader = fopen(path_to_file,"r");
    fseek (file_reader, 0, SEEK_END);
    fail_unless (ftell(file_reader),"printing the fragment has failed (Emptyfile)");
    fclose(file_reader);

    frag_delete(rat_frag);
    schema_delete(rat_schema);
}
END_TEST


START_TEST(test_frag_num_of_attributes_vsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        fail_unless(frag_num_of_attributes(rat_frag) == 2, "returned wrong number of atttributes");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_frag_num_of_tuplets_vsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 6);
        fail_unless(frag_num_of_tuplets(rat_frag) == 6, "returned wrong number of tuplets");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_frag_schema_vsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);

        fail_unless(frag_schema(rat_frag)->attr->num_elements == rat_schema->attr->num_elements, "wrong returned value of frag schema");

        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_frag_field_type_vsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_DSM_VM);
        const attr_id_t* attributes_id = schema_attributes(rat_schema);

        fail_unless(frag_field_type(rat_frag, *attributes_id) == FT_UINT32, "wrong returned value of "
                "the type of the attribute");

        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_frag_new_nsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_NSM_VM);
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_frag_insert_nsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_NSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 4);
        const char *path_to_file ="/home/pegasus/gridstore_test/fragment.txt";
        FILE *output_file = fopen(path_to_file, "w");
        frag_print(output_file, rat_frag, 0, 4);
        fclose(output_file);

        FILE *file_reader = fopen(path_to_file,"r");
        fseek (file_reader, 0, SEEK_END);
                fail_unless (ftell(file_reader),"printing the fragment has failed (Emptyfile)");
        fclose(file_reader);

        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_frag_num_of_attributes_nsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_NSM_VM);
        fail_unless(frag_num_of_attributes(rat_frag) == 2, "returned wrong number of atttributes");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_frag_num_of_tuplets_nsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_NSM_VM);
        tuplet_t out;
        frag_insert(&out, rat_frag, 6);
        fail_unless(frag_num_of_tuplets(rat_frag) == 6, "returned wrong number of tuplets");
        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_frag_schema_nsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_NSM_VM);
        fail_unless(frag_schema(rat_frag)->attr->num_elements == rat_schema->attr->num_elements, "wrong returned value of"
                " frag schema");

        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_frag_field_type_nsm)
    {
        schema_t *rat_schema = schema_new("test_table");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        frag_t *rat_frag = frag_new(rat_schema, 10,  FIT_HOST_NSM_VM);
        const attr_id_t* attributes_id = schema_attributes(rat_schema);
        fail_unless(frag_field_type(rat_frag, *attributes_id) == FT_UINT32, "wrong returned value of "
        "the type of the attribute");

        frag_delete(rat_frag);
        schema_delete(rat_schema);
    }
END_TEST


void init_frag_test()
{
    frag_tsuit = suite_create("frag Test Suit");

    frag_test_1 = tcase_create("test frag creation");
    tcase_add_test(frag_test_1, test_frag_new_vsm);
    frag_test_2 = tcase_create("test frag insertion");
    tcase_add_test(frag_test_2, test_frag_insert_vsm);
    frag_test_3 = tcase_create("test frag num of attributes");
    tcase_add_test(frag_test_3, test_frag_num_of_attributes_vsm);
    frag_test_4 = tcase_create("test frag num of tuplets");
    tcase_add_test(frag_test_4, test_frag_num_of_tuplets_vsm);
    frag_test_5 = tcase_create("test frag schema");
    tcase_add_test(frag_test_5, test_frag_schema_vsm);
    frag_test_6 = tcase_create("test frag the types of schema attributes");
    tcase_add_test(frag_test_6, test_frag_field_type_vsm);
    frag_test_7 = tcase_create("test frag creation");
    tcase_add_test(frag_test_7, test_frag_new_nsm);
    frag_test_8 = tcase_create("test frag insertion");
    tcase_add_test(frag_test_8, test_frag_insert_nsm);
    frag_test_9 = tcase_create("test frag num of attributes");
    tcase_add_test(frag_test_9, test_frag_num_of_attributes_nsm);
    frag_test_10 = tcase_create("test frag num of tuplets");
    tcase_add_test(frag_test_10, test_frag_num_of_tuplets_nsm);
    frag_test_11 = tcase_create("test frag schema");
    tcase_add_test(frag_test_11, test_frag_schema_nsm);
    frag_test_12 = tcase_create("test frag the types of schema attributes");
    tcase_add_test(frag_test_12, test_frag_field_type_nsm);



    suite_add_tcase(frag_tsuit, frag_test_1);
    suite_add_tcase(frag_tsuit, frag_test_2);
    suite_add_tcase(frag_tsuit, frag_test_3);
    suite_add_tcase(frag_tsuit, frag_test_4);
    suite_add_tcase(frag_tsuit, frag_test_5);
    suite_add_tcase(frag_tsuit, frag_test_6);
    suite_add_tcase(frag_tsuit, frag_test_7);
    suite_add_tcase(frag_tsuit, frag_test_8);
    suite_add_tcase(frag_tsuit, frag_test_9);
    suite_add_tcase(frag_tsuit, frag_test_10);
    suite_add_tcase(frag_tsuit, frag_test_11);
    suite_add_tcase(frag_tsuit, frag_test_12);

}

