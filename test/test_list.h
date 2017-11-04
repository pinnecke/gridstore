//
// Created by Mahmoud Mohsen on 10/26/17.
//
#pragma once

#include <check.h>
#include <containers/list.h>

Suite *list_tsuit;
TCase *list_test_1;
TCase *list_test_2;
TCase *list_test_3;
TCase *list_test_4;
TCase *list_test_5;
TCase *list_test_6;
TCase *list_test_7;
TCase *list_test_8;
TCase *list_test_9;


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
        fail_unless (list_length(rat_list) == 2 , "list push failed");
        list_delete(rat_list);
    }
END_TEST


//START_TEST(test_list_new)
//    {
//        list_t * rat_list = list_new(sizeof (int));
//                fail_unless(list_is_empty(rat_list) , "list creation failed");
//        list_delete(rat_list);
//    }
//END_TEST


void init_list_test()
{
    list_tsuit = suite_create("list Test Suit");

    list_test_1 = tcase_create("test list creation");
    tcase_add_test(list_test_1, test_list_new);
    list_test_2 = tcase_create("test list push");
    tcase_add_test(list_test_2, test_list_push);

    suite_add_tcase(list_tsuit, list_test_1);
    suite_add_tcase(list_tsuit, list_test_2);
}

