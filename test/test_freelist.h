//
// Created by Mahmoud Mohsen on 10/26/17.
//
#pragma once

#include <check.h>
#include <containers/freelist.h>

Suite *freelist_tsuit;
TCase *freelist_test_1;
TCase *freelist_test_2;
TCase *freelist_test_3;
TCase *freelist_test_4;
TCase *freelist_test_5;
TCase *freelist_test_6;
TCase *freelist_test_7;
TCase *freelist_test_8;
TCase *freelist_test_9;


START_TEST(test_freelist_create)
    {

    }
END_TEST



//
//START_TEST(test_freelist_push)
//    {
//
//    }
//END_TEST


//START_TEST(test_freelist_remove)
//    {
//
//
//    }
//END_TEST
//

void init_freelist_test()
{
    freelist_tsuit = suite_create("freelist Test Suit");

    freelist_test_1 = tcase_create("test freelist creation");
    tcase_add_test(freelist_test_1, test_freelist_create);
//    freelist_test_2 = tcase_create("test freelist push");
//    tcase_add_test(freelist_test_2, test_freelist_push);
//    freelist_test_3 = tcase_create("test freelist remove");
//    tcase_add_test(freelist_test_3, test_freelist_remove);

    suite_add_tcase(freelist_tsuit, freelist_test_1);
//    suite_add_tcase(freelist_tsuit, freelist_test_2);
//    suite_add_tcase(freelist_tsuit, freelist_test_3);
}

