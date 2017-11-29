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
TCase *gs_hash_test_10;
TCase *gs_hash_test_11;
TCase *gs_hash_test_12;
TCase *gs_hash_test_13;
TCase *gs_hash_test_14;
TCase *gs_hash_test_15;

int compare_chars(const void *lhs ,const void *rhs);

START_TEST(test_gs_hash_new)
{
    gs_hash_t *gs_hash;                             // <------- MUST be a pointer to "gs_hash_t" ;)
    gs_hash_create(&gs_hash,10, compare_ints);
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

        fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                    "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

        fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                                  "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

                fail_unless(equal_strings,
                            "couldn't retrive the correct value");
        gs_hash_dispose(gs_hash);
    }
END_TEST


START_TEST(test_gs_hash_set_get_ex)
    {
        gs_hash_t *gs_hash;
        gs_hash_create(&gs_hash, 10, compare_ints);
        int *keys = malloc(4 * sizeof(int));
        int *vals = malloc(4 * sizeof(int));
        keys[0] = 0; keys[1] = 1; keys[2] = 2; keys[3] = 3;
        vals[0] = 8; vals[1] = 1; vals[2] = 2; vals[3] = 3;

        gs_hash_set_ex(gs_hash, keys, sizeof(int), vals, 4,compare_ints);

                fail_unless(vals[0] != *(int *) gs_hash_get(gs_hash, keys + sizeof(int) , sizeof(int)),
                            "couldn't retrive the correct value");

        free(keys);
        free(vals);
//        gs_hash_dispose(gs_hash);
    }
END_TEST



START_TEST(test_gs_hash_set_get_hash_code_identity_size_t)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_identity_size_t,compare_ints);
        size_t key1 = 5;
        int val1 = 20;
        gs_hash_set(gs_hash, &key1, sizeof(size_t), &val1,compare_ints);
        fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(size_t)),
                            "couldn't retrive the correct value");
    gs_hash_dispose(gs_hash);
    }
END_TEST


START_TEST(test_gs_hash_set_get_hash_code_additive)
    {

        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_additive,compare_ints);
        int key1 = 5;
        int val1 = 20;
        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

                fail_unless(equal_strings,
                            "couldn't retrive the correct value");
        gs_hash_dispose(gs_hash);

    }
END_TEST


START_TEST(test_gs_hash_set_get_hash_code_xor)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_xor,compare_ints);
        int key1 = 5;
        int val1 = 20;
        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

                fail_unless(equal_strings,
                            "couldn't retrive the correct value");
//        gs_hash_dispose(gs_hash); >> causes signal 6 abort
    }
END_TEST



START_TEST(test_gs_hash_set_get_hash_code_rot)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_rot,compare_ints);
        int key1 = 5;
        int val1 = 20;
        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

                fail_unless(equal_strings,
                            "couldn't retrive the correct value");
        gs_hash_dispose(gs_hash);
    }
END_TEST


START_TEST(test_gs_hash_set_get_hash_code_bernstein)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_bernstein,compare_ints);
        int key1 = 5;
        int val1 = 20;
        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

                fail_unless(equal_strings,
                            "couldn't retrive the correct value");
        gs_hash_dispose(gs_hash);
    }
END_TEST


START_TEST(test_gs_hash_set_get_hash_code_bernstein2)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_bernstein2,compare_ints);

        int key1 = 5;
        int val1 = 20;

        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

        fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

        fail_unless(equal_strings,
                            "couldn't retrive the correct value");
//        gs_hash_dispose(gs_hash);
    }
END_TEST


START_TEST(test_gs_hash_set_get_hash_code_sax)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_sax,compare_ints);

        int key1 = 5;
        int val1 = 20;

        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

        fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

        fail_unless(equal_strings,
                            "couldn't retrive the correct value");
//        gs_hash_dispose(gs_hash);
    }
END_TEST


START_TEST(test_gs_hash_set_get_hash_code_fnv)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_fnv, compare_ints);

        int key1 = 5;
        int val1 = 20;

        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

                fail_unless(equal_strings,
                            "couldn't retrive the correct value");
//        gs_hash_dispose(gs_hash);
    }
END_TEST



START_TEST(test_gs_hash_set_get_hash_code_oat)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_oat, compare_ints);

        int key1 = 5;
        int val1 = 20;

        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

                fail_unless(equal_strings,
                            "couldn't retrive the correct value");
//        gs_hash_dispose(gs_hash);
    }
END_TEST


START_TEST(test_gs_hash_set_get_hash_code_jsw)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_jsw, compare_ints);

        int key1 = 5;
        int val1 = 20;

        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

                fail_unless(equal_strings,
                            "couldn't retrive the correct value");
//        gs_hash_dispose(gs_hash);
    }
END_TEST


START_TEST(test_gs_hash_set_get_hash_code_elf)
    {
        gs_hash_t *gs_hash;
        gs_hash_create_ex(&gs_hash, 10, hash_code_elf, compare_ints);

        int key1 = 5;
        int val1 = 20;

        gs_hash_set(gs_hash, &key1, sizeof(int), &val1,compare_ints);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(int)),
                            "couldn't retrive the correct value");

        char *key2 = "name";

        gs_hash_set(gs_hash, key2, 5 * sizeof(char), &val1, compare_chars);

                fail_unless(20 == *(int *) gs_hash_get(gs_hash, key2, 5 * sizeof(char)),
                            "couldn't retrive the correct value");

        char *key3 = "string key";
        char *string_value = "string value";

        gs_hash_set(gs_hash, key3, strlen(key3), string_value, compare_chars);

        bool equal_strings = !strcmp("string value",
                                     gs_hash_get(gs_hash, key3, strlen(key3)));

                fail_unless(equal_strings,
                            "couldn't retrive the correct value");
//        gs_hash_dispose(gs_hash);
    }
END_TEST


/*
 * hash_code_perfect_size_t is not yet implemented as of 16/11/2017
 */

//START_TEST(test_gs_hash_set_get_hash_code_perfect_size_t)
//    {
//        gs_hash_t *gs_hash;
//        gs_hash_create_ex(&gs_hash, 10, hash_code_perfect_size_t,compare_ints);
//        int key1 = 5;
//        int val1 = 20;
//        gs_hash_set(gs_hash, &key1, sizeof(size_t), &val1,compare_ints);
//
//                fail_unless(20 == *(int *) gs_hash_get(gs_hash, &key1, sizeof(size_t)),
//                            "couldn't retrive the correct value");
//
//        gs_hash_dispose(gs_hash);
//    }
//END_TEST


int compare_chars(const void *lhs ,const void *rhs){
    return strcmp(lhs, rhs);
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
    gs_hash_test_4 = tcase_create("test gs_hash get hash_code_identity_size_t\n"
                                          "     ");
    tcase_add_test(gs_hash_test_4, test_gs_hash_set_get_hash_code_identity_size_t);
    gs_hash_test_5 = tcase_create("test gs_hash get hash_code_additive\n"
                                          "     ");
    tcase_add_test(gs_hash_test_5, test_gs_hash_set_get_hash_code_additive);

    gs_hash_test_6 = tcase_create("test gs_hash get hash_code_xor\n"
                                          "     ");
    tcase_add_test(gs_hash_test_6, test_gs_hash_set_get_hash_code_xor);

    gs_hash_test_7 = tcase_create("test gs_hash get hash_code_rot\n"
                                          "     ");
    tcase_add_test(gs_hash_test_7, test_gs_hash_set_get_hash_code_rot);

    gs_hash_test_8 = tcase_create("test gs_hash get hash_code_bernstein\n"
                                          "     ");
    tcase_add_test(gs_hash_test_8, test_gs_hash_set_get_hash_code_bernstein);
    gs_hash_test_9 = tcase_create("test gs_hash get hash_code_bernstein2\n"
                                          "     ");
    tcase_add_test(gs_hash_test_9, test_gs_hash_set_get_hash_code_bernstein2);

    gs_hash_test_10 = tcase_create("test gs_hash get hash_code_sax\n"
                                          "     ");
    tcase_add_test(gs_hash_test_10, test_gs_hash_set_get_hash_code_sax);
    gs_hash_test_11 = tcase_create("test gs_hash get hash_code_fnv\n"
                                           "     ");
    tcase_add_test(gs_hash_test_11, test_gs_hash_set_get_hash_code_fnv);
    gs_hash_test_12 = tcase_create("test gs_hash get hash_code_oat\n"
                                           "     ");
    tcase_add_test(gs_hash_test_12, test_gs_hash_set_get_hash_code_oat);
    gs_hash_test_13 = tcase_create("test gs_hash get hash_code_jsw\n"
                                           "     ");
    tcase_add_test(gs_hash_test_13, test_gs_hash_set_get_hash_code_jsw);
    gs_hash_test_14 = tcase_create("test gs_hash get hash_code_elf\n"
                                           "     ");
    tcase_add_test(gs_hash_test_14, test_gs_hash_set_get_hash_code_elf);

    gs_hash_test_15 = tcase_create("test gs_hash get ex\n"
                                           "     ");
    tcase_add_test(gs_hash_test_15, test_gs_hash_set_get_ex);

    suite_add_tcase(gs_hash_tsuit, gs_hash_test_1);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_2);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_3);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_4);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_5);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_6);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_7);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_8);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_9);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_10);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_11);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_12);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_13);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_14);
    suite_add_tcase(gs_hash_tsuit, gs_hash_test_15);
}

