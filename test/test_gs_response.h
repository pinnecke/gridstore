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
#include <inet/response.h>
#include <schema.h>
#include <field_type.h>
#include <stdio.h>

Suite *gs_response_tsuit;
TCase *gs_response_test_1;
TCase *gs_response_test_2;
TCase *gs_response_test_3;
TCase *gs_response_test_4;
TCase *gs_response_test_5;
TCase *gs_response_test_6;
TCase *gs_response_test_7;
TCase *gs_response_test_8;
TCase *gs_response_test_9;


START_TEST(test_gs_response_create)
{
    response_t response;
    response_create(&response);
    fail_unless(true,
    "couldn't create a response");
    response_dispose(&response);
}
END_TEST

START_TEST(test_gs_response_set)
    {
        response_t response;
        response_create(&response);
        fail_unless(true,
                "couldn't create a response");
        char key[] = "Content-Length";
        char val[] = "100";
        response_field_set(&response, key, val);
        fail_unless(true,
                    "couldn't set a field response");
        response_dispose(&response);
    }
END_TEST

START_TEST(test_gs_response_get)
    {
        response_t response;
        response_create(&response);
                fail_unless(true,
                            "couldn't create a response");

        response_field_set(&response, "Content-Length", "40");
        fail_unless(true,
                        "couldn't set a field response");
        const char *field_Val = response_field_get(&response, "Content-Length");
        fail_unless(!strncmp(field_Val,"40",2),
                    "response field get has failed");
        response_dispose(&response);
    }
END_TEST

START_TEST(test_gs_response_body_set_get)
    {
        response_t response;
        response_create(&response);
        fail_unless(true,
                   "couldn't create a response");
        char body[] ="blablalbla";
        response_body_set(&response, body);
        fail_unless(!strcmp(body, response_body_get(&response)),
        "body set and get has failed");
        response_dispose(&response);
    }
END_TEST

START_TEST(test_gs_response_type_set_get)
    {
        response_t response;
        response_create(&response);
        fail_unless(true,
                        "couldn't create a response");
        response_content_type_set(&response, MIME_CONTENT_TYPE_TEXT_PLAIN);
        response_end(&response, HTTP_STATUS_CODE_400_BAD_REQUEST);
        fail_unless(! strcmp(MIME_CONTENT_TYPE_TEXT_PLAIN, response_body_get(&response)),
                            "body set and get has failed");
        response_dispose(&response);
    }
END_TEST

START_TEST(test_gs_response_end)
    {
        response_t response;
        response_create(&response);
        fail_unless(true,
                        "couldn't create a response");
        response_end(&response,HTTP_STATUS_CODE_100_CONTINUE);
        fail_unless(true,
                            "couldn't modify the response end a response");
        response_dispose(&response);
    }
END_TEST

START_TEST(test_gs_response_format_fields)
    {
        response_t response;
        response_create(&response);
        fail_unless(true,
                        "couldn't create a response");
        response_content_type_set(&response, MIME_CONTENT_TYPE_TEXT_PLAIN);
        const char *formated_field = response_format_fields(&response);
        fail_unless(! strcmp(formated_field, "Content-Type: text/plain"),
        "string format field has failed");
        response_dispose(&response);
    }
END_TEST

START_TEST(test_gs_response_pack)
    {
        response_t response;
        response_create(&response);
        fail_unless(true,
                        "couldn't create a response");
        response_content_type_set(&response, MIME_CONTENT_TYPE_TEXT_PLAIN);
        const char *res_pack = response_pack(&response);
        fail_unless(res_pack != NULL,
        "failed to retrieve the response pack");
        response_dispose(&response);
    }
END_TEST

void init_gs_response_test()
{
    gs_response_tsuit = suite_create("gs_response Test Suit");

    gs_response_test_1 = tcase_create("test gs_response create");
    tcase_add_test(gs_response_test_1, test_gs_response_create);
    gs_response_test_2 = tcase_create("test gs_response set");
    tcase_add_test(gs_response_test_2, test_gs_response_set);
    gs_response_test_3 = tcase_create("test gs_response get");
    tcase_add_test(gs_response_test_3, test_gs_response_get);
    gs_response_test_4 = tcase_create("test gs_response get");
    tcase_add_test(gs_response_test_4, test_gs_response_body_set_get);
    gs_response_test_5 = tcase_create("test gs_response get");
    tcase_add_test(gs_response_test_5, test_gs_response_type_set_get);
    gs_response_test_6 = tcase_create("test gs_response get");
    tcase_add_test(gs_response_test_6, test_gs_response_end);
    gs_response_test_7 = tcase_create("test gs_response get");
    tcase_add_test(gs_response_test_7, test_gs_response_format_fields);
    gs_response_test_8 = tcase_create("test gs_response get");
    tcase_add_test(gs_response_test_8, test_gs_response_pack);

    suite_add_tcase(gs_response_tsuit, gs_response_test_1);
    suite_add_tcase(gs_response_tsuit, gs_response_test_2);
    suite_add_tcase(gs_response_tsuit, gs_response_test_3);
    suite_add_tcase(gs_response_tsuit, gs_response_test_4);
    suite_add_tcase(gs_response_tsuit, gs_response_test_5);
    suite_add_tcase(gs_response_tsuit, gs_response_test_6);
    suite_add_tcase(gs_response_tsuit, gs_response_test_7);
    suite_add_tcase(gs_response_tsuit, gs_response_test_8);
}

