//
// Created by Mahmoud Mohsen on 10/26/17.
//
#pragma once

#include <check.h>
#include <utils.h>

Suite *utils_tsuit;
TCase *utils_test_1;
TCase *utils_test_2;
TCase *utils_test_3;
TCase *utils_test_4;
TCase *utils_test_5;
TCase *utils_test_6;
TCase *utils_test_7;
TCase *utils_test_8;
TCase *utils_test_9;


START_TEST(test_utils_basic)
{
    fail_unless(strtoint("5") == 5,"string to int fails");
    fail_unless(strtoint("5") != 6,"string to int fails");
    fail_unless(strtoint("100000") == 100000,"string to int fails");
    fail_unless(strtoint("-1") == -1,"string to int fails");
}

END_TEST




void init_utils_test()
{
    utils_tsuit = suite_create("utils Test Suit");

    utils_test_1 = tcase_create("test utils creation");
    tcase_add_test(utils_test_1, test_utils_basic);

    suite_add_tcase(utils_tsuit, utils_test_1);
}

