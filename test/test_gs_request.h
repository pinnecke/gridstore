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
#include <inet/gs_request.h>
#include <schema.h>
#include <field_type.h>
#include <stdio.h>

Suite *gs_request_tsuit;
TCase *gs_request_test_1;
TCase *gs_request_test_2;
TCase *gs_request_test_3;
TCase *gs_request_test_4;
TCase *gs_request_test_5;
TCase *gs_request_test_6;
TCase *gs_request_test_7;
TCase *gs_request_test_8;
TCase *gs_request_test_9;
gs_request_t *request;


START_TEST(test_gs_request_raw)
    {
        sleep(4);
        char *message_buffer;
        gs_request_raw(&message_buffer, request);
        fail_unless(message_buffer, "retrieve raw has failed");
    }
END_TEST

START_TEST(test_gs_request_has_field)
    {
        sleep(4);
        char key[] ="Content-Length";
        fail_unless(gs_request_has_field(request, key)
        , "request_has_field has failed");
    }
END_TEST

START_TEST(test_gs_request_field_by_name)
    {
        sleep(4);
        char key[] ="User-Agent";
        const char *field_value;
        fail_unless(gs_request_field_by_name(&field_value, request, key)
        , "request_has_field has failed");
        fail_unless(! strcmp(field_value,"curl/7.47.0"),"field by name has failed");
    }
END_TEST

START_TEST(test_gs_request_method)
    {
        sleep(4);
        gs_http_method_e method;
        fail_unless(gs_request_method(&method, request)
        , "request_has_field has failed");
        fail_unless(method == GS_POST,"request method has failed");
    }
END_TEST

START_TEST(test_gs_request_is_method)
    {
        sleep(4);
        gs_http_method_e method = GS_POST;
        fail_unless(gs_request_is_method(request, method)
        , "request is method has failed");
        gs_request_dispose(&request);
    }
END_TEST

START_TEST(test_gs_request_resource)
    {
        sleep(4);
        char *resource;
        fail_unless(gs_request_resource(&resource, request) == GS_SUCCESS
        , "request resource has failed");

        fail_unless(! strcmp(resource,"/")
        , "request resource has failed");

    }
END_TEST

START_TEST(test_gs_request_is_valid)
    {
        sleep(4);
        fail_unless(gs_request_is_valid(request)
        , "the request is not valid");
    }
END_TEST

START_TEST(test_gs_request_has_form)
    {
        sleep(4);
        char key[] ="param1";
        fail_unless( gs_request_has_form(request, key)
        , "the request has form has failed");

    }
END_TEST


void init_gs_request_test()
{
    gs_request_tsuit = suite_create("gs_request Test Suit");

    gs_request_test_2 = tcase_create("test gs_request get raw");
    tcase_add_test(gs_request_test_2, test_gs_request_raw);
    tcase_set_timeout(gs_request_test_2, 320);
    gs_request_test_3 = tcase_create("test gs_request has field");
    tcase_add_test(gs_request_test_3, test_gs_request_has_field);
    tcase_set_timeout(gs_request_test_3, 320);
    gs_request_test_4 = tcase_create("test gs_request field by name");
    tcase_add_test(gs_request_test_4, test_gs_request_field_by_name);
    tcase_set_timeout(gs_request_test_4, 320);
    gs_request_test_5 = tcase_create("test gs_request method");
    tcase_set_timeout(gs_request_test_5, 320);
    tcase_add_test(gs_request_test_5, test_gs_request_method);
    gs_request_test_6 = tcase_create("test gs_request is method");
    tcase_add_test(gs_request_test_6, test_gs_request_is_method);
    tcase_set_timeout(gs_request_test_6, 320);
    gs_request_test_7 = tcase_create("test gs_request resource");
    tcase_set_timeout(gs_request_test_7, 320);
    tcase_add_test(gs_request_test_7, test_gs_request_resource);
    gs_request_test_8 = tcase_create("test gs_request is valid");
    tcase_set_timeout(gs_request_test_8, 320);
    tcase_add_test(gs_request_test_8,  test_gs_request_is_valid);
    gs_request_test_9 = tcase_create("test gs_request has form");
    tcase_set_timeout(gs_request_test_9, 320);
    tcase_add_test(gs_request_test_9,  test_gs_request_has_form);

    suite_add_tcase(gs_request_tsuit, gs_request_test_1);
    suite_add_tcase(gs_request_tsuit, gs_request_test_2);
    suite_add_tcase(gs_request_tsuit, gs_request_test_3);
    suite_add_tcase(gs_request_tsuit, gs_request_test_4);
    suite_add_tcase(gs_request_tsuit, gs_request_test_5);
    suite_add_tcase(gs_request_tsuit, gs_request_test_6);
    suite_add_tcase(gs_request_tsuit, gs_request_test_7);
    suite_add_tcase(gs_request_tsuit, gs_request_test_8);
    suite_add_tcase(gs_request_tsuit, gs_request_test_9);
}

