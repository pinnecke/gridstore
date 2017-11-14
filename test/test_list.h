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
#include <containers/list.h>

Suite *list_tsuit;
TCase *list_test_1;
TCase *list_test_2;
TCase *list_test_3;


START_TEST(test_list_new)
{
    list_t * rat_list = list_new(sizeof (int));
    fail_unless(list_is_empty(rat_list) , "list creation failed");
    list_delete(rat_list);
}
END_TEST


START_TEST(test_list_push)
    {
        list_t * rat_list = list_new(sizeof (int));
        int data = 4;
        list_push(rat_list, &data);
        int add_data = 5;
        list_push(rat_list, &add_data);
        fail_unless(! list_is_empty(rat_list) , "list push failed");
        fail_unless ( *(int *) list_begin(rat_list) == data, "list push failed"  );
        fail_unless ( *(int *) list_next(list_begin(rat_list)) == add_data, "list push failed"  );
        fail_unless (list_length(rat_list) == 2 , "list push failed");
        list_delete(rat_list);
    }
END_TEST


START_TEST(test_list_remove)
    {
        list_t * rat_list = list_new(sizeof (int));
        int data = 4;
        list_push(rat_list, &data);
        int add_data = 5;
        list_push(rat_list, &add_data);
        fail_unless(list_length(rat_list) == 2 , "list remove has failed");
        list_remove(list_next(list_begin(rat_list)));
        fail_unless (list_length(rat_list) == 1 ,"list remove has failed");
        list_remove(list_begin(rat_list));
        fail_unless (list_is_empty(rat_list), "list push failed");
        list_delete(rat_list);
    }
END_TEST


void init_list_test()
{
    list_tsuit = suite_create("list Test Suit");

    list_test_1 = tcase_create("test list creation");
    tcase_add_test(list_test_1, test_list_new);
    list_test_2 = tcase_create("test list push");
    tcase_add_test(list_test_2, test_list_push);
    list_test_3 = tcase_create("test list remove");
    tcase_add_test(list_test_3, test_list_remove);

    suite_add_tcase(list_tsuit, list_test_1);
    suite_add_tcase(list_tsuit, list_test_2);
    suite_add_tcase(list_tsuit, list_test_3);
}

