//
// Created by Mahmoud Mohsen on 10/26/17.
//
#pragma once

#include <check.h>
#include <containers/hashset.h>

Suite *hashset_tsuit;
TCase *hashset_test_1;
TCase *hashset_test_2;
TCase *hashset_test_3;
TCase *hashset_test_4;
TCase *hashset_test_5;
TCase *hashset_test_6;
TCase *hashset_test_7;
TCase *hashset_test_8;
TCase *hashset_test_9;


START_TEST(test_hashset_create)
    {
        hashset_t  rat_hashset ;
        hashset_create(&rat_hashset,sizeof(int),10);
        hashset_dispose(&rat_hashset);
    }
END_TEST



//
//START_TEST(test_hashset_push)
//    {
//
//    }
//END_TEST


//START_TEST(test_hashset_remove)
//    {
//
//
//    }
//END_TEST
//

void init_hashset_test()
{
    hashset_tsuit = suite_create("hashset Test Suit");

    hashset_test_1 = tcase_create("test hashset creation");
    tcase_add_test(hashset_test_1, test_hashset_create);
//    hashset_test_2 = tcase_create("test hashset push");
//    tcase_add_test(hashset_test_2, test_hashset_push);
//    hashset_test_3 = tcase_create("test hashset remove");
//    tcase_add_test(hashset_test_3, test_hashset_remove);

    suite_add_tcase(hashset_tsuit, hashset_test_1);
//    suite_add_tcase(hashset_tsuit, hashset_test_2);
//    suite_add_tcase(hashset_tsuit, hashset_test_3);
}

