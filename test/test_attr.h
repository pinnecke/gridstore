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
#include <attr.h>
#include <schema.h>
#include <field_type.h>
#include <stdio.h>

Suite *attr_tsuit;
TCase *attr_test_1;
TCase *attr_test_2;
TCase *attr_test_3;
TCase *attr_test_4;


START_TEST(test_attr_name)
{
    schema_t *rat_schema = schema_new("test_table");
    fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
    enum field_type ftype = FT_UINT32;
    attr_id_t attr_id = attr_create("age", ftype, sizeof(int32_t), rat_schema);
    const attr_t *age_attr = schema_attr_by_id(rat_schema, attr_id);
    fail_unless (!strcmp(attr_name(age_attr),"age"),"testing attribute name has failed");
    schema_delete(rat_schema);
}
END_TEST


START_TEST(test_attr_isstring)
    {
        schema_t *rat_schema = schema_new("test_table");
        fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_CHAR;
        attr_id_t attr_id = attr_create("name", ftype, sizeof(char), rat_schema);
        const attr_t *name_attr = schema_attr_by_id(rat_schema, attr_id);
        fail_unless (attr_isstring(name_attr),"testing attribute isstring has failed");
        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_attr_total_size)
    {
        schema_t *rat_schema = schema_new("test_table");
        fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_CHAR;
        attr_id_t attr_id = attr_create("name", ftype, sizeof(char), rat_schema);
        const attr_t *name_attr = schema_attr_by_id(rat_schema, attr_id);

        fail_unless (attr_total_size(name_attr) == sizeof(char), "testing total size has failed");

        schema_delete(rat_schema);
    }
END_TEST


START_TEST(test_attr_cpy)
    {
        schema_t *rat_schema = schema_new("test_table");
        fail_unless (! schema_num_attributes(rat_schema) ,"wrong number of schema attributes");
        enum field_type ftype = FT_CHAR;
        attr_id_t attr_id = attr_create("name", ftype, sizeof(char), rat_schema);
        const attr_t *name_attr = schema_attr_by_id(rat_schema, attr_id);
        schema_t *cpy_rat_schema = schema_new("test_table2");
        ftype = FT_UINT32;
        attr_create("age", ftype, sizeof(int32_t), cpy_rat_schema);
        fail_unless (schema_num_attributes(cpy_rat_schema) == 1,"testing copying attributes has failed");
        attr_cpy(name_attr, cpy_rat_schema);
        fail_unless (schema_num_attributes(cpy_rat_schema) == 2,"testing copying attributes has failed");

        schema_delete(rat_schema);
        schema_delete(cpy_rat_schema);
    }
END_TEST


void init_attr_test()
{
    attr_tsuit = suite_create("attr Test Suit");

    attr_test_1 = tcase_create("test attr name");
    tcase_add_test(attr_test_1, test_attr_name);
    attr_test_2 = tcase_create("test attr isstring");
    tcase_add_test(attr_test_2, test_attr_isstring);
    attr_test_3 = tcase_create("test attr attr_total_size");
    tcase_add_test(attr_test_3, test_attr_total_size);
    attr_test_4 = tcase_create("test attr_cpy");
    tcase_add_test(attr_test_4, test_attr_cpy);


    suite_add_tcase(attr_tsuit, attr_test_1);
    suite_add_tcase(attr_tsuit, attr_test_2);
    suite_add_tcase(attr_tsuit, attr_test_3);
    suite_add_tcase(attr_tsuit, attr_test_4);
}

