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

#include <check.h>
#include <schema.h>
#include "test_vector.h"
#include "utilities.h"
#include "test_list.h"
//#include "testhashset.h"
#include "test_utils.h"
#include "test_schema.h"
#include "test_attr.h"
#include "test_gshash.h"
#include "test_freelist.h"
#include "test_frag.h"
#include "test_tuplet.h"
#include "test_tuplet_field.h"
#include "test_tuple.h"
#include "test_dispatcher.h"
#include "test_event.h"
#include "test_gs_request.h"
#include "test_gs_response.h"

int fake_server2(void *data);
int fake_client(void *data);

int main(void)
{
    apr_initialize();

    init_vec_test();
    init_list_test();
//    init_hashset_test();  >> not implemented yet as of 16/11/2017
    init_utils_test();
    init_schema_test();
    init_attr_test();
    init_gs_hash_test();
    init_freelist_test();
    init_gs_hash_test();
    init_frag_test();
    init_tuplet_test();
    init_tuplet_field_test();
    init_tuple_test();
    init_dispatcher_test();
    init_event_test();
    thrd_t thread1;
    int thread1_num = thrd_create(&thread1, fake_server2, NULL);
    sleep(1);
    thrd_t thread2;
    int thread2_num = thrd_create(&thread2, fake_client, NULL);
    sleep(9);
    init_gs_request_test();
    init_gs_response_test();

    SRunner *sr = srunner_create(list_tsuit);
    srunner_add_suite(sr,vector_tsuit);
//    srunner_add_suite(sr,hashset_tsuit); >> not implemented yet as of 16/11/2017
    srunner_add_suite(sr, gs_hash_tsuit);
    srunner_add_suite(sr, utils_tsuit);
    srunner_add_suite(sr, schema_tsuit);
    srunner_add_suite(sr, attr_tsuit);
    srunner_add_suite(sr, freelist_tsuit);
    srunner_add_suite(sr, frag_tsuit);
    srunner_add_suite(sr, tuplet_tsuit);
    srunner_add_suite(sr, tuplet_field_tsuit);
    srunner_add_suite(sr, tuple_tsuit);
    srunner_add_suite(sr, dispatcher_tsuit);
    srunner_add_suite(sr, event_tsuit);
    srunner_add_suite(sr, gs_request_tsuit);
    srunner_add_suite(sr, gs_response_tsuit);
    int nf;
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    apr_terminate();
    thrd_exit(thread1_num);
    thrd_exit(thread2_num);

    return nf == 0 ? 0 : 1;
}

int fake_server2(void *data)
{
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;
    new_socket = 0;
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(7019);

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
        gs_request_create(&request, new_socket);
    }

    if (new_socket<0)
    {
        perror("accept failed");
        return 1;
    }
    return new_socket;
}

int fake_client(void *data)
{
//    system("curl -H 'Expect:' -F param1=hello  http://localhost:7017 &");
    system("curl   -F param1=hello  http://localhost:7019 &");
    return 0;
}
