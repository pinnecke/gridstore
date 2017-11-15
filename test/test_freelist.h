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
#include <containers/freelist.h>

Suite *freelist_tsuit;
TCase *freelist_test_1;
TCase *freelist_test_2;

void init_int (void *data);
void inc_int (void *data);

START_TEST(test_freelist_bind)
    {
        freelist_t rat_free_list;
        freelist_create(&rat_free_list, sizeof(int), 10, init_int, inc_int);
        int *available_indices = malloc(10 * sizeof (int));
        freelist_bind(available_indices, &rat_free_list, 10);
        fail_unless(available_indices[9] == 9, "list binding has failed");
        freelist_dispose(&rat_free_list);
        free(available_indices);
    }
END_TEST

START_TEST(test_freelist_pushback)
    {
        freelist_t rat_free_list;
        freelist_create(&rat_free_list, sizeof(int), 10, init_int, inc_int);
        int *available_indices = malloc(10 * sizeof(int));
        freelist_bind(available_indices, &rat_free_list, 10);

        int *sent_back_indices = malloc(3 * sizeof(int));

        sent_back_indices[0] = 7;
        sent_back_indices[1] = 5;
        sent_back_indices[2] = 1;

        freelist_pushback(&rat_free_list, 3, sent_back_indices);
        int available_index = 5;

        freelist_bind(&available_index, &rat_free_list, 1);
        fail_unless(available_index == 1 , "list pushback has failed");
        freelist_bind(&available_index, &rat_free_list, 1);
        fail_unless(available_index == 5 , "list pushback has failed");
        freelist_bind(&available_index, &rat_free_list, 1);
        fail_unless(available_index == 7 , "list pushback has failed");

        freelist_dispose(&rat_free_list);
        free(sent_back_indices);
        free(available_indices);
    }
END_TEST


void init_int(void *data)
{
        *(int *)data = 0;
}

void inc_int(void *data)
{
    *(int *)data += 1;
}

void init_freelist_test()
{
    freelist_tsuit = suite_create("freelist Test Suit");

    freelist_test_1 = tcase_create("test freelist creation");
    tcase_add_test(freelist_test_1, test_freelist_bind);
    freelist_test_2 = tcase_create("test freelist push");
    tcase_add_test(freelist_test_2, test_freelist_pushback);
    suite_add_tcase(freelist_tsuit, freelist_test_1);
    suite_add_tcase(freelist_tsuit, freelist_test_2);
}

