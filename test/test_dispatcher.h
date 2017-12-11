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
#include <gs_dispatcher.h>
#include <gs_event.h>
#include <stdio.h>
#include <unistd.h>
#include <c11threads.h>

Suite *dispatcher_tsuit;
TCase *dispatcher_test_1;
TCase *dispatcher_test_2;
TCase *dispatcher_test_3;
TCase *dispatcher_test_4;
TCase *dispatcher_test_5;


gs_event_t *gs_event;
gs_event_t *gs_waited_event;


bool publish_success = false;


gs_status_t thread1_handle_events(const gs_event_t *event)
{
//    printf("\n hello \n");
    publish_success = true;
    return GS_SUCCESS;
}


int thread1_publish_shutdown(void *dispatcher)
{
    sleep(3);
    gs_dispatcher_publish(dispatcher, gs_event);
    gs_dispatcher_shutdown(dispatcher);
    return EXIT_SUCCESS;
}


int thread3_waitfor_command(void *dispatcher)
{
    sleep(2);
    gs_dispatcher_waitfor(dispatcher,gs_event);
    gs_dispatcher_publish(dispatcher, gs_event);
    gs_dispatcher_shutdown(dispatcher);

    return EXIT_SUCCESS;
}


START_TEST(test_dispatcher_creation)
{
    gs_dispatcher_t *rat_dispatcher;
    fail_unless(gs_dispatcher_create(&rat_dispatcher) == GS_SUCCESS, "couldn't create a dispatcher");
}
END_TEST


START_TEST(test_dispatcher_publish)
    {
        gs_dispatcher_t *dispatcher;
        fail_unless(gs_dispatcher_create(&dispatcher) == GS_SUCCESS, "couldn't create a dispatcher");
        thrd_t thread1;
        gs_event = gs_event_new(GS_SIG_TEST, GS_OBJECT_TYPE_NONE, NULL,
                                GS_OBJECT_TYPE_DISPATCHER, dispatcher, NULL, NULL);
        int thread1_num = thrd_create(&thread1, thread1_publish_shutdown, dispatcher);
        GS_CONNECT(GS_SIG_TEST, thread1_handle_events);
        gs_dispatcher_start(dispatcher);
        fail_unless(publish_success, "publish has failed");
//        fail_unless(gs_dispatcher_dispose(&dispatcher) == GS_SUCCESS, "couldn't dispose a dispatcher");
        thrd_exit(thread1_num);
    }
END_TEST




void init_dispatcher_test()
{
    dispatcher_tsuit = suite_create("dispatcher Test Suit");

    dispatcher_test_1 = tcase_create("test dispatcher creation");
    tcase_add_test(dispatcher_test_1, test_dispatcher_creation);
    dispatcher_test_4 = tcase_create("test dispatcher_publish");
    tcase_set_timeout(dispatcher_test_4,320);
    tcase_add_test(dispatcher_test_4, test_dispatcher_publish);

    suite_add_tcase(dispatcher_tsuit, dispatcher_test_1);
    suite_add_tcase(dispatcher_tsuit, dispatcher_test_4);
}

