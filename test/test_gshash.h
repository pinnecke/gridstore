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
#include <containers/gs_hash.h>
#include <hash.h>

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


int compare_ints2(const void *lhs ,const void *rhs);

START_TEST(test_gs_hash_new)
{
    gs_hash_t *gs_hash;                             // <------- MUST be a pointer to "gs_hash_t" ;)
    gs_hash_create(&gs_hash,10, compare_ints2);
    fail_unless(true, "couldn't reach this part due to hash creation error");
//    gs_hash_dispose(gs_hash);
}
END_TEST


START_TEST(test_gs_hash_new_ex)
    {
        gs_hash_t *gs_pointer;
        gs_hash_create_ex(&gs_pointer,10,hash_code_fnv,compare_ints);
        fail_unless(true, "couldn't reach this part due to hash creation error");
//        gs_hash_dispose(gs_pointer);
    }
END_TEST


START_TEST(test_gs_hash_set_get)
    {

        gs_hash_t *gs_hash;
        gs_hash_create(&gs_hash, 10, compare_ints);
        int key1 = 5;
        int val1 = 20;
      gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

//        fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
//                    "couldn't reach this part due to hash creation error");

    }
END_TEST


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

int compare_ints2(const void *lhs ,const void *rhs){

    if (*(int *)lhs == *(int *)rhs)
    {
        return 0;
    }else if (*(int *) lhs > *(int *)rhs){
        return 1;
    }
    return -1;
}

void init_gs_hash_test()
{
    gs_hash_tsuit = suite_create("gs_hash Test Suit");

    gs_hash_test_1 = tcase_create("test gs_hash creation");
    tcase_add_test(gs_hash_test_1, test_gs_hash_new);
    gs_hash_test_2 = tcase_create("test gs_hash ex creation");
    tcase_add_test(gs_hash_test_2, test_gs_hash_new_ex);
    gs_hash_test_3 = tcase_create("test gs_hash get & set");
    tcase_add_test(gs_hash_test_3, test_gs_hash_set_get);


//    gs_hash_test_2 = tcase_create("test gs_hash push");
//    tcase_add_test(gs_hash_test_2, test_gs_hash_push);
//    gs_hash_test_3 = tcase_create("test gs_hash remove");
//    tcase_add_test(gs_hash_test_3, test_gs_hash_remove);
//
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_1);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_2);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_3);
}

