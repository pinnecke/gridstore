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
#include <utils.h>

Suite *utils_tsuit;
TCase *utils_test_1;

START_TEST(test_utils_basic)
{
    fail_unless(strtoint("5") == 5,"string to int fails");
    fail_unless(strtoint("5") != 6,"string to int fails");
    fail_unless(strtoint("100000") == 100000,"string to int fails");
}

END_TEST


void init_utils_test()
{
    utils_tsuit = suite_create("utils Test Suit");

    utils_test_1 = tcase_create("test utils creation");
    tcase_add_test(utils_test_1, test_utils_basic);

    suite_add_tcase(utils_tsuit, utils_test_1);
}

