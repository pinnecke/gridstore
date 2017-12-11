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
#include <gs_event.h>
#include <gs_event.h>
#include <stdio.h>
#include <unistd.h>
#include <c11threads.h>
#include <gs_shell.h>
#include <inet/gs_server.h>
#include <gs_gridstore.h>


Suite *event_tsuit;
TCase *event_test_1;
TCase *event_test_2;
TCase *event_test_3;
TCase *event_test_4;
TCase *event_test_5;
TCase *event_test_6;
TCase *event_test_7;
TCase *event_test_8;
TCase *event_test_9;


START_TEST(test_event_creation)
{
    gs_event_t *rat_event = gs_event_new(GS_SIG_SHUTDOWN, GS_OBJECT_TYPE_NONE, NULL,
                                         GS_OBJECT_TYPE_DISPATCHER, NULL, NULL, NULL);
    fail_unless(rat_event, "couldn't create a event");
}
END_TEST


START_TEST(test_event_free)
    {
        gs_event_t *rat_event = gs_event_new(GS_SIG_SHUTDOWN, GS_OBJECT_TYPE_NONE, NULL,
                                             GS_OBJECT_TYPE_DISPATCHER, NULL, NULL, NULL);
        gs_event_free(rat_event);
        rat_event = NULL;
        fail_unless(!rat_event, "couldn't free an event");
    }
END_TEST


START_TEST(test_event_heartbeat_new)
    {
        gs_dispatcher_t *dispatcher;
        gs_dispatcher_create(&dispatcher);
        gs_event_t *rat_event = gs_event_heartbeat_new(dispatcher);
        fail_unless(rat_event, "couldn't create a heart beat event");
        fail_unless(gs_event_get_signal(rat_event) == GS_SIG_HEARTBEAT,
                    "couldn't create a heart beat event");

    }
END_TEST


START_TEST(test_event_shell_shutdown)
    {
        gs_dispatcher_t *dispatcher;
        gs_shell_t *shell;
        gs_dispatcher_create(&dispatcher);
        gs_shell_create(&shell, dispatcher);
        gs_event_t *rat_event = gs_event_shell_shutdown(dispatcher, shell);
        fail_unless(rat_event, "couldn't create shell_shutdown");
        fail_unless(gs_event_get_signal(rat_event) == GS_SIG_SHUTDOWN,
                    "got the wrong signal with shell shutdown");
        gs_shell_dispose(&shell);
    }
END_TEST


START_TEST(test_event_server_shutdown)
    {
        gs_dispatcher_t *dispatcher;
        gs_dispatcher_create(&dispatcher);
        gs_server_t *server;
        gs_server_create(&server, 35497, dispatcher);
        gs_event_t *rat_event = gs_event_server_shutdown(dispatcher, server);
        fail_unless(rat_event, "couldn't create server shutdown");
        fail_unless(gs_event_get_signal(rat_event) == GS_SIG_SHUTDOWN,
                    "got the wrong signal with the server shutting down");

        gs_server_dispose(&server);
    }
END_TEST


START_TEST(test_event_gridstore_shutdown)
    {
        gs_dispatcher_t *dispatcher;
        gs_dispatcher_create(&dispatcher);
        gs_gridstore_t *gridstore;
        gs_gridstore_create(&gridstore);
        gs_event_t *rat_event = gs_event_gridstore_shutdown(dispatcher, gridstore);
        fail_unless(rat_event, "couldn't create gridstore shutdown");
        fail_unless(gs_event_get_signal(rat_event) == GS_SIG_SHUTDOWN,
                            "got the wrong signal with the gridstore shutting down");
    }
END_TEST


START_TEST(test_event_gridstore_test)
    {
        gs_gridstore_t *gridstore;
        gs_gridstore_create(&gridstore);
        gs_event_t *rat_event = gs_event_gridstore_test(gridstore);
        fail_unless(rat_event, "couldn't create gridstore test");
        fail_unless(gs_event_get_signal(rat_event) == GS_SIG_TEST,
                            "got the wrong signal with gridstore test");
    }
END_TEST


START_TEST(test_event_gridstore_invoke)
    {
        gs_event_t *rat_event = gs_event_gridstore_invoke();
        fail_unless(rat_event, "couldn't get a gridstore invoke");
        fail_unless(gs_event_get_signal(rat_event) == GS_SIG_INVOKE,
                            "got the wrong signal with gridstore invoke");
    }
END_TEST


void init_event_test()
{
    event_tsuit = suite_create("event Test Suit");

    event_test_1 = tcase_create("test event creation");
    tcase_add_test(event_test_1, test_event_creation);
    event_test_2 = tcase_create("test event free");
    tcase_add_test(event_test_2, test_event_free);
    event_test_3 = tcase_create("test event_heart beat");
    tcase_add_test(event_test_3, test_event_heartbeat_new);
    event_test_4 = tcase_create("test event_heart beat");
    tcase_add_test(event_test_4, test_event_heartbeat_new);
    event_test_5 = tcase_create("test event shell shutdown");
    tcase_add_test(event_test_5, test_event_shell_shutdown);
    event_test_6 = tcase_create("test event server shutdown");
    tcase_add_test(event_test_6, test_event_server_shutdown);
    event_test_7 = tcase_create("test event gridstore shutdown");
    tcase_add_test(event_test_7, test_event_gridstore_shutdown);
    event_test_8 = tcase_create("test event gridstore test");
    tcase_add_test(event_test_8, test_event_gridstore_test);
    event_test_9 = tcase_create("test event gridstore invoke");
    tcase_add_test(event_test_9, test_event_gridstore_invoke);

    suite_add_tcase(event_tsuit, event_test_1);
    suite_add_tcase(event_tsuit, event_test_2);
    suite_add_tcase(event_tsuit, event_test_3);
    suite_add_tcase(event_tsuit, event_test_4);
    suite_add_tcase(event_tsuit, event_test_5);
    suite_add_tcase(event_tsuit, event_test_6);
    suite_add_tcase(event_tsuit, event_test_7);
    suite_add_tcase(event_tsuit, event_test_8);
    suite_add_tcase(event_tsuit, event_test_9);
}

