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

int fake_client();
int fake_server();
int thread1_call_curl_with_post(void *data);

START_TEST(test_gs_request_create)
{
    gs_request_t *request;
    fail_unless(gs_request_create(&request, fake_client()) == GS_SUCCESS,
    "couldn't create a request");
    gs_request_dispose(&request);
}
END_TEST

START_TEST(test_gs_request_raw)
    {
        gs_request_t *request;
        fail_unless(gs_request_create(&request, fake_client()),
                            "couldn't create a request");
        char *message_buffer;
        gs_request_raw(&message_buffer, request);
        fail_unless(message_buffer, "retrieve raw has failed");
        gs_request_dispose(&request);
    }
END_TEST

START_TEST(test_gs_request_has_field)
    {
        gs_request_t *request;
        fail_unless(gs_request_create(&request, fake_client()),
                            "couldn't create a request");
        char key[] ="Content-Length";
        fail_unless(gs_request_has_field(request, key)
        , "request_has_field has failed");
        gs_request_dispose(&request);
    }
END_TEST

START_TEST(test_gs_request_field_by_name)
    {
        gs_request_t *request;
        fail_unless(gs_request_create(&request, fake_client()),
                            "couldn't create a request");
        char key[] ="Content-Length";
        const char *field_value;
        fail_unless(gs_request_field_by_name(&field_value, request, key)
        , "request_has_field has failed");
        fail_unless(! strcmp(field_value,"268"),"field by name has failed");
        gs_request_dispose(&request);
    }
END_TEST

// curl  -F param1=hello  http://localhost:7777

START_TEST(test_gs_request_method)
    {
        gs_request_t *request;
        fail_unless(gs_request_create(&request, fake_client()),
                            "couldn't create a request");
        gs_http_method_e method;
        fail_unless(gs_request_method(&method, request)
        , "request_has_field has failed");
        fail_unless(method == GS_POST,"request method has failed");
        gs_request_dispose(&request);
    }
END_TEST

// curl  -F param1=hello  http://localhost:7777

START_TEST(test_gs_request_is_method)
    {
        gs_request_t *request;
        fail_unless(gs_request_create(&request, fake_server()),
                            "couldn't create a request");
        gs_http_method_e method = GS_POST;
        fail_unless(gs_request_is_method(request, method)
        , "request is method has failed");
        gs_request_dispose(&request);
    }
END_TEST

// curl  -F param1=hello  http://localhost:7777

START_TEST(test_gs_request_resource)
    {
        gs_request_t *request;
        char *resource;
        fail_unless(gs_request_create(&request, fake_server()) == GS_SUCCESS,
                            "couldn't create a request");
        fail_unless(gs_request_resource(&resource, request) == GS_SUCCESS
        , "request resource has failed");

        fail_unless(! strcmp(resource,"/")
        , "request resource has failed");
        gs_request_dispose(&request);
    }
END_TEST

// curl  -F param1=hello  http://localhost:7777

START_TEST(test_gs_request_is_valid)
    {
        gs_request_t *request;

        int desc = fake_server();

        fail_unless(gs_request_create(&request, desc) == GS_SUCCESS,
                            "couldn't create a request");
        fail_unless(gs_request_is_valid(request)
        , "the request is not valid");
        gs_request_dispose(&request);
    }
END_TEST

// curl  -F param1=hello  http://localhost:7777

START_TEST(test_gs_request_has_form)
    {
        gs_request_t *request;

        int desc = fake_server();

        fail_unless(gs_request_create(&request, desc) == GS_SUCCESS,
                            "couldn't create a request");

        fail_unless( gs_request_has_form(request, key)
        , "the request has form has failed");
        gs_request_dispose(&request);
    }
END_TEST

// the code of this method is taken from here
// http://www.binarytides.com/socket-programming-c-linux-tutorial/

int fake_client()
{
    int socket_desc;
    struct sockaddr_in server;
    char *message;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr("216.58.206.4");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected\n");

    //Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }

    return socket_desc;
}

// the code of this method is taken from here
// http://www.binarytides.com/socket-programming-c-linux-tutorial/

int fake_server()
{
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;
    char *message;
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
    server.sin_port = htons(7777);

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

        //Reply to the client
        message = "Hello Client , I have received your connection. But I have to go now, bye\n";
        write(new_socket , message , strlen(message));
        if (new_socket)
            break;
    }

    if (new_socket<0)
    {
        perror("accept failed");
        return 1;
    }

    return new_socket;
}

int thread1_call_curl_with_post(void *data)
{
    sleep(1);
    system("curl --form param1=value1 --form param2=value2 http://localhost:7777");
    return EXIT_SUCCESS;
}

void init_gs_request_test()
{
    gs_request_tsuit = suite_create("gs_request Test Suit");

    gs_request_test_1 = tcase_create("test gs_request create");
    tcase_add_test(gs_request_test_1, test_gs_request_create);
    gs_request_test_2 = tcase_create("test gs_request get raw");
    tcase_add_test(gs_request_test_2, test_gs_request_raw);
    gs_request_test_3 = tcase_create("test gs_request has field");
    tcase_add_test(gs_request_test_3, test_gs_request_has_field);
    gs_request_test_4 = tcase_create("test gs_request field by name");
    tcase_add_test(gs_request_test_4, test_gs_request_field_by_name);
    gs_request_test_5 = tcase_create("test gs_request method");
    tcase_add_test(gs_request_test_5, test_gs_request_method);
    gs_request_test_6 = tcase_create("test gs_request is method");
    tcase_add_test(gs_request_test_6, test_gs_request_is_method);
    tcase_set_timeout(gs_request_test_7, 320);
    gs_request_test_7 = tcase_create("test gs_request resource");
    tcase_add_test(gs_request_test_7, test_gs_request_resource);
    gs_request_test_8 = tcase_create("test gs_request is valid");
    tcase_set_timeout(gs_request_test_8, 320);
    tcase_add_test(gs_request_test_8,  test_gs_request_is_valid);
    gs_request_test_9 = tcase_create("test gs_request is valid");
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

