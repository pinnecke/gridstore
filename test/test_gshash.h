//
// Created by Mahmoud Mohsen on 10/26/17.
//

#pragma once

#include <check.h>
#include <containers/gs_hash.h>

Suite *gs_hash_tsuit;
TCase *gs_hash_test_1;
TCase *gs_hash_test_2;
TCase *gs_hash_test_3;
TCase *gs_hash_test_4;
TCase *gs_hash_test_5;
TCase *gs_hash_test_6;
TCase *gs_hash_test_7;
TCase *gs_hash_test_8;
TCase *gs_hash_test_9;


int compare_ints(const void *lhs ,const void *rhs);

START_TEST(test_gs_hash_new)
{
    gs_hash_t m_gs_hash;
    gs_hash_t *gs_pointer = &gs_hash_t;
    gs_hash_t *gs_double_pointer = &gs_pointer;
    gs_comp_func_t key_comp = &compare_ints;
    gs_hash_create(gs_double_pointer,10, key_comp);
}
END_TEST

//
//START_TEST(test_gs_hash_push)
//    {
//        gs_hash_t * rat_gs_hash = gs_hash_new(sizeof (int));
//        int data = 4;
//        gs_hash_push(rat_gs_hash, &data);
//        int add_data = 5;
//        gs_hash_push(rat_gs_hash, &add_data);
//        fail_unless(! gs_hash_is_empty(rat_gs_hash) , "gs_hash push failed");
//        fail_unless ( *(int *) gs_hash_begin(rat_gs_hash) == data, "gs_hash push failed"  );
//        fail_unless (gs_hash_length(rat_gs_hash) == 2 , "gs_hash push failed");
//        gs_hash_delete(rat_gs_hash);
//    }
//END_TEST
//
//
//START_TEST(test_gs_hash_remove)
//    {
//
//        gs_hash_t * rat_gs_hash = gs_hash_new(sizeof (int));
//        int data = 4;
//        gs_hash_remove(&data);
//
//        gs_hash_push(rat_gs_hash, &data);
//        int add_data = 5;
//        gs_hash_push(rat_gs_hash, &add_data);
//                fail_unless(! gs_hash_is_empty(rat_gs_hash) , "gs_hash push failed");
//                fail_unless ( *(int *) gs_hash_begin(rat_gs_hash) == data, "gs_hash push failed"  );
//                fail_unless (gs_hash_length(rat_gs_hash) == 2 , "gs_hash push failed");
//        gs_hash_delete(rat_gs_hash);
//    }
//END_TEST
//

int compare_ints(const void *lhs ,const void *rhs)
{
    return *(int *) lhs >= *(int *)rhs ;
}

void init_gs_hash_test()
{
    gs_hash_tsuit = suite_create("gs_hash Test Suit");

    gs_hash_test_1 = tcase_create("test gs_hash creation");
    tcase_add_test(gs_hash_test_1, test_gs_hash_new);
//    gs_hash_test_2 = tcase_create("test gs_hash push");
//    tcase_add_test(gs_hash_test_2, test_gs_hash_push);
//    gs_hash_test_3 = tcase_create("test gs_hash remove");
//    tcase_add_test(gs_hash_test_3, test_gs_hash_remove);

    suite_add_tcase(gs_hash_tsuit, gs_hash_test_1);
//    suite_add_tcase(gs_hash_tsuit, gs_hash_test_2);
//    suite_add_tcase(gs_hash_tsuit, gs_hash_test_3);
}

