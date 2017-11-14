//
// Created by Mahmoud Mohsen on 10/26/17.
//
#pragma once

#include <check.h>
#include <schema.h>
#include <attr.h>
#include <field_type.h>
#include <stdio.h>

Suite *schema_tsuit;
TCase *schema_test_1;
TCase *schema_test_2;
TCase *schema_test_3;
TCase *schema_test_4;
TCase *schema_test_5;
TCase *schema_test_6;
TCase *schema_test_7;
TCase *schema_test_8;
TCase *schema_test_9;


START_TEST(test_schema_new)
{
    schema_t *rat_schema = schema_new("test_table");
    schema_delete(rat_schema);
    fail_unless (true ,"schema creation has failed");
}
END_TEST



START_TEST(test_schema_num_attributes)
    {
        schema_t *rat_schema = schema_new("test_table");

        fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);

        fail_unless ( schema_num_attributes(rat_schema) == 2 ,"wrong number of schema attributes");

        schema_delete(rat_schema);
    }
END_TEST



START_TEST(test_schema_attributes)
    {
        schema_t *rat_schema = schema_new("test_table");
        fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        const attr_id_t * attributes_id = schema_attributes(rat_schema);
        fail_unless ( *(int *) attributes_id + 1 == 1 ,"schema attributes has failed");
        fail_unless ( *(int *) attributes_id  == 0 ,"schema attributes has failed");

        schema_delete(rat_schema);
    }
END_TEST



START_TEST(test_schema_subset)
    {
        schema_t *rat_schema = schema_new("test_table");
                fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        attr_create("length", ftype, sizeof(int32_t), rat_schema);
        attr_create("Id", ftype, sizeof(int32_t), rat_schema);
        const attr_id_t* attributes_id = schema_attributes(rat_schema);
        attr_id_t* projected_attributes_id = malloc( sizeof(attributes_id) * 3 );
        *projected_attributes_id = *attributes_id;
        *(projected_attributes_id + 1) = *attributes_id + 2;
        *(projected_attributes_id + 2) = *attributes_id + 3;
        schema_t *rat_subschema = schema_subset(rat_schema, projected_attributes_id, 3);
        fail_unless ( schema_num_attributes(rat_subschema) == 3 ,"subschema has failed");
        fail_unless ( strcmp(schema_attr_by_id(rat_subschema, 0)->name, "age" ) == 0 ,"subschema has failed");
        fail_unless ( strcmp(schema_attr_by_id(rat_subschema, 1)->name, "length" ) == 0 ,"subschema has failed");
        fail_unless ( strcmp(schema_attr_by_id(rat_subschema, 2)->name, "Id" ) == 0 ,"subschema has failed");


        free((attr_id_t*)projected_attributes_id);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_schema_attr_by_name)
    {
        schema_t *rat_schema = schema_new("test_table");
        fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        attr_create("length", ftype, sizeof(int32_t), rat_schema);
        attr_create("Id", ftype, sizeof(int32_t), rat_schema);
        const attr_id_t* attributes_id = schema_attributes(rat_schema);
        attr_id_t* projected_attributes_id = malloc( sizeof(attributes_id) * 3 );
        *projected_attributes_id = schema_attr_by_name(rat_schema,"age") ->id;
        fail_unless ( *(attr_id_t*) projected_attributes_id == 0 ,"getting attributes by name failed");
        *(projected_attributes_id + 1) = schema_attr_by_name(rat_schema,"length") ->id;
        *(projected_attributes_id + 2) = schema_attr_by_name(rat_schema,"Id") ->id;

        fail_unless ( *(attr_id_t*) (projected_attributes_id + 1) == 2 ,"getting attributes by name failed");
        fail_unless ( *(attr_id_t*) (projected_attributes_id + 2) == 3 ,"getting attributes by name failed");

        free((attr_id_t*)projected_attributes_id);
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_schema_attr_by_id)
    {
        schema_t *rat_schema = schema_new("test_table");
                fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        attr_create("length", ftype, sizeof(int32_t), rat_schema);
        attr_create("Id", ftype, sizeof(int32_t), rat_schema);
        const attr_id_t* attributes_id = schema_attributes(rat_schema);
        attr_id_t* projected_attributes_id = malloc( sizeof(attributes_id) * 3 );
        *projected_attributes_id = schema_attr_by_id(rat_schema,
                                                     schema_attr_by_name(rat_schema,"age") ->id)->id;


        fail_unless ( *(attr_id_t*) projected_attributes_id == 0 ,"getting attributes by name failed");

        *(projected_attributes_id + 1) = schema_attr_by_id(rat_schema,
                                                          schema_attr_by_name(rat_schema,"length") ->id)->id;

        *(projected_attributes_id + 2) = schema_attr_by_id(rat_schema,
                                                          schema_attr_by_name(rat_schema,"Id") ->id)->id;

        fail_unless ( *(attr_id_t*) (projected_attributes_id + 1) == 2 ,"getting attributes by name failed");
        fail_unless ( *(attr_id_t*) (projected_attributes_id + 2) == 3 ,"getting attributes by name failed");

        free((attr_id_t*)projected_attributes_id);

        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_schema_attr_by_size_by_id)
    {
        schema_t *rat_schema = schema_new("test_table");
                fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        attr_create("length", ftype, sizeof(int32_t), rat_schema);
        attr_create("Id", ftype, sizeof(int32_t), rat_schema);
        const attr_id_t* attributes_id = schema_attributes(rat_schema);
        attr_id_t* projected_attributes_id = malloc( sizeof(attributes_id) * 3 );
        *projected_attributes_id = schema_attr_by_id(rat_schema,
                                                     schema_attr_by_name(rat_schema,"age") ->id)->id;


        fail_unless (schema_attr_type(rat_schema, *projected_attributes_id) == FT_UINT32 ,"getting attributes by name failed");

      free((attr_id_t*)projected_attributes_id);

        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_schema_print)
    {
        schema_t *rat_schema = schema_new("test_table");
        fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), rat_schema);
        attr_create("salary", ftype, sizeof(int32_t), rat_schema);
        attr_create("length", ftype, sizeof(int32_t), rat_schema);
        attr_create("Id", ftype, sizeof(int32_t), rat_schema);
        char *path_to_outputfile = "/home/pegasus/gridstore_test/printed_schema.txt";
        FILE *file_writer = fopen(path_to_outputfile,"w+");
        schema_print(file_writer,rat_schema);
        fclose(file_writer);

        FILE *file_reader = fopen(path_to_outputfile,"r");

        fseek (file_reader, 0, SEEK_END);

        fail_unless (ftell(file_reader),"printing the schema has failed (Emptyfile)");

        fclose(file_reader);

        schema_delete(rat_schema);
    }
END_TEST

//
//START_TEST(test_schema_push)
//    {
//        schema_t * rat_schema = schema_new(sizeof (int));
//        int data = 4;
//        schema_push(rat_schema, &data);
//        int add_data = 5;
//        schema_push(rat_schema, &add_data);
//        fail_unless(! schema_is_empty(rat_schema) , "schema push failed");
//        fail_unless ( *(int *) schema_begin(rat_schema) == data, "schema push failed"  );
//        fail_unless (schema_length(rat_schema) == 2 , "schema push failed");
//        schema_delete(rat_schema);
//    }
//END_TEST
//
//
//START_TEST(test_schema_remove)
//    {
//
//        schema_t * rat_schema = schema_new(sizeof (int));
//    }
//END_TEST


void init_schema_test()
{
    schema_tsuit = suite_create("schema Test Suit");

    schema_test_1 = tcase_create("test schema creation");
    tcase_add_test(schema_test_1, test_schema_new);
    schema_test_2 = tcase_create("test schema num of attributes");
    tcase_add_test(schema_test_2, test_schema_num_attributes);
    schema_test_3 = tcase_create("test schema attributes");
    tcase_add_test(schema_test_3, test_schema_attributes);
    schema_test_4 = tcase_create("test schema subset");
    tcase_add_test(schema_test_4, test_schema_subset);
    schema_test_5 = tcase_create("test schema get attribute by name");
    tcase_add_test(schema_test_5, test_schema_attr_by_name);
    schema_test_6 = tcase_create("test schema get attribute by id");
    tcase_add_test(schema_test_6, test_schema_attr_by_id);
    schema_test_7 = tcase_create("test schema get attribute size by id");
    tcase_add_test(schema_test_7, test_schema_attr_by_size_by_id);
    schema_test_8 = tcase_create("test schema print to file");
    tcase_add_test(schema_test_8, test_schema_print);


    suite_add_tcase(schema_tsuit, schema_test_1);
    suite_add_tcase(schema_tsuit, schema_test_2);
    suite_add_tcase(schema_tsuit, schema_test_3);
    suite_add_tcase(schema_tsuit, schema_test_4);
    suite_add_tcase(schema_tsuit, schema_test_5);
    suite_add_tcase(schema_tsuit, schema_test_6);
    suite_add_tcase(schema_tsuit, schema_test_7);
    suite_add_tcase(schema_tsuit, schema_test_8);

}

