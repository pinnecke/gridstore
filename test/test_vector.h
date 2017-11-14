//
// Created by Mahmoud Mohsen on 10/26/17.
//
#pragma once

#include <check.h>
#include <containers/vec.h>

Suite *vector_tsuit;
TCase *vector_test_1;
TCase *vector_test_2;
TCase *vector_test_3;
TCase *vector_test_4;
TCase *vector_test_5;
TCase *vector_test_6;
TCase *vector_test_7;
TCase *vector_test_8;
TCase *vector_test_9;
TCase *vector_test_10;
TCase *vector_test_11;
TCase *vector_test_12;
TCase *vector_test_13;
TCase *vector_test_14;
TCase *vector_test_15;
TCase *vector_test_16;
TCase *vector_test_17;
TCase *vector_test_18;
TCase *vector_test_19;
TCase *vector_test_20;
TCase *vector_test_21;
TCase *vector_test_22;
TCase *vector_test_23;

TCase *vector_test_50;

int compare_ints (const void *lhs ,const void *rhs);
int equal_ints (const void *lhs ,const void *rhs);
bool check_bigger_than_something(void *something, void *begin, void *end);
bool pred (void *capture, void *it);
bool for_each_check_bigger_capture(void *capture, void *begin, void *end);

START_TEST(test_vec_creation)
{
    vec_t * rat_vec = vec_new(sizeof (int),20);
    fail_unless((int) rat_vec->element_capacity == 20, "vector creation failed");
    vec_free(rat_vec);
}
END_TEST

START_TEST(test_vec_resize)
    {
        vec_t * rat_vec = vec_new(sizeof (int),20);
        fail_unless((int) rat_vec->element_capacity == 20, "vector creation failed");
        vec_resize(rat_vec,15);
        fail_unless((int) rat_vec->num_elements == 15, "vector resize failed");
        vec_free(rat_vec);
    }
END_TEST


START_TEST(test_vec_reserve)
    {
        vec_t * rat_vec = vec_new(sizeof (int),20);
        fail_unless( vec_reserve(rat_vec,150), "vector reserve & auto resize enabled");

//        if uncommenting this lines produce an error, it means the code does what it suppose to do
//        rat_vec->flags =zero_memory;
//        fail_unless(! vec_reserve(rat_vec,150), "vector reserve with zero memory, num of elements is small");

        vec_resize(rat_vec,500);
        rat_vec->flags =zero_memory;
        fail_unless(vec_reserve(rat_vec,150), "vector reserve & auto resize disabled & num of elements is big");
        vec_free(rat_vec);
    }
END_TEST



START_TEST(test_vec_length)
    {
        vec_t * rat_vec = vec_new(sizeof (int),20);
        vec_resize(rat_vec,500);
        fail_unless( vec_length(rat_vec)== 500, "vector length gave a wrong value after reserve");
        vec_free(rat_vec);
    }
END_TEST

START_TEST(test_vec_memset)
    {
        vec_t * rat_vec = vec_new(sizeof (int),3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;
        vec_memset(rat_vec, 0, 3, source_data);

        int *p = rat_vec->data;
        fail_unless( (*p ==1) && (*(p+1) == 2) && (*(p+2) == 3) , "vector data gave a wrong value after vector mem set");
        free(source_data);
        vec_free(rat_vec);
    }
END_TEST

START_TEST(test_vec_updatesort)
    {
        vec_t * rat_vec = vec_new(sizeof (int), 3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data = 1;
        *(source_data + 1) = 2;
        *(source_data + 2) = 3;
        vec_set(rat_vec, 0, 3, source_data);
        fail_unless(vec_updatesort(rat_vec, compare_ints), "vector update sort has failed");
        *source_data = 4;
        vec_set(rat_vec, 0, 3, source_data);
        fail_unless(!vec_updatesort(rat_vec, compare_ints), "vector update sort has failed");

        free(source_data);
        vec_free(rat_vec);
    }
END_TEST



START_TEST(test_vec_cpy_deep)
    {
        vec_t *rat_vec = vec_new(sizeof (int),3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;

        vec_memset(rat_vec, 0, 3, source_data);
        vec_t *deep_cloned_vec = vec_cpy_deep(rat_vec);
        int *source_ptr = rat_vec->data;
        int *copied_ptr = deep_cloned_vec->data;
        fail_unless( (*source_ptr == *copied_ptr) &&
                     (*(source_ptr + 1) == *(copied_ptr + 1)) &&
                     (*(source_ptr + 2) == *(copied_ptr + 2) )
                             , "deep copying the two vectors failed");
        free(source_data);
        vec_free(rat_vec);
    }
END_TEST


START_TEST(test_vec_cpy_shallow)
    {
        vec_t *rat_vec_src = vec_new(sizeof (int),3);
        vec_t *rat_vec_dist = vec_new(sizeof (int),3);

        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;

        int *dist_data = malloc(3 * sizeof(int));
        *dist_data = 4;
        *(dist_data + 1) = 5;
        *(dist_data + 2) = 6;

        vec_memset(rat_vec_src, 0, 3, source_data);
        vec_memset(rat_vec_dist, 0, 3, dist_data);

        vec_cpy_shallow(rat_vec_dist, rat_vec_src);

        int *source_ptr = rat_vec_src->data;
        int *copied_ptr = rat_vec_dist->data;

                fail_unless( (*source_ptr == *copied_ptr) &&
                             (*(source_ptr + 1) == *(copied_ptr + 1)) &&
                             (*(source_ptr + 2) == *(copied_ptr + 2) )
        , "shallow copying the two vectors failed");

        free(source_data);
        free(dist_data);

        vec_free(rat_vec_src);
    }
END_TEST

START_TEST(test_vec_at)
    {
        vec_t * rat_vec = vec_new(sizeof (int),3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;
        rat_vec->num_elements = 3;
        rat_vec->data =source_data;
        fail_unless( (*(int *)vec_at(rat_vec,0) ==1) &&
                             (*(int *)vec_at(rat_vec,1) == 2) &&
                             (*(int *)vec_at(rat_vec,2) == 3)
        , "vector at gave wrong value");
        vec_free(rat_vec);

    }
END_TEST

START_TEST(test_vec_peek)
    {
        vec_t * rat_vec = vec_new(sizeof (int),3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;
        rat_vec->num_elements = 3;
        rat_vec->data =source_data;
        fail_unless(  (*(int *)vec_peek(rat_vec) == 3), "vector peek has failed");
        vec_free(rat_vec);
    }
END_TEST

START_TEST(test_vec_begin)
    {
        vec_t * rat_vec = vec_new(sizeof (int),3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;
        rat_vec->num_elements = 3;
        rat_vec->data =source_data;
                fail_unless(  (*(int *)vec_begin(rat_vec) == 1), "vector begin has failed");
        vec_free(rat_vec);
    }
END_TEST

START_TEST(test_vec_end)
    {
        vec_t * rat_vec = vec_new(sizeof (int),3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;
        rat_vec->num_elements = 3;

        rat_vec->data =source_data;
                fail_unless(  (*(int *)vec_end(rat_vec) == 3), "vector end has failed");
        vec_free(rat_vec);

    }
END_TEST

START_TEST(test_vec_pop_unsafe)
    {
        vec_t * rat_vec = vec_new(sizeof (int),3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;
        rat_vec->num_elements = 3;
        rat_vec->data =source_data;

        fail_unless( *(int *) vec_pop_unsafe(rat_vec) == 3 &&
                     (*(int *)vec_peek_unsafe(rat_vec) == 2  &&
                     rat_vec->num_elements == 2  ), "vector pop unsafe has failed");
        vec_free(rat_vec);
    }
END_TEST

START_TEST(test_vec_set)
    {
        vec_t * rat_vec = vec_new(sizeof (int),3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;
        vec_set(rat_vec,0,3,source_data);
        int *p = rat_vec->data;
                fail_unless( (*p ==1) && (*(p+1) == 2) && (*(p+2) == 3) , "vector data gave a wrong value after vector set");
        free(source_data);
        vec_free(rat_vec);
    }
END_TEST


START_TEST(test_vec_pushback)
    {
        vec_t * rat_vec = vec_new(sizeof (int),3);
        int *source_data = malloc(3 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;
        *(source_data + 2) =3;

        int *more_data = malloc(3 * sizeof(int));
        *more_data = 5;
        *(more_data + 1) = 6;
        *(more_data + 2) = 7;

        vec_set(rat_vec,0,3,source_data);
        vec_pushback(rat_vec,3,more_data);

        int *p = rat_vec->data;
                fail_unless( (*(p+3) ==5) && (*(p+4) == 6) && (*(p+5) == 7) , "vector data gave a wrong value after vector set");
        free(source_data);
        free(more_data);
        vec_free(rat_vec);
    }
END_TEST


START_TEST(test_vec_add_all)
    {
        vec_t *rat_vec_src = vec_new(sizeof (int),2);
        vec_t *rat_vec_dist = vec_new(sizeof (int),2);

        int *source_data = malloc(2 * sizeof(int));
        *source_data =1;
        *(source_data + 1) =2;


        int *dist_data = malloc(2 * sizeof(int));
        *(dist_data ) = 5;
        *(dist_data + 1) = 6;

        vec_set(rat_vec_src, 0, 2 ,source_data);
        vec_set(rat_vec_dist, 0, 2 ,dist_data);
        vec_add_all(rat_vec_dist, rat_vec_src);

        int *copied_ptr = rat_vec_dist->data;
                fail_unless(  (*copied_ptr) == 5 &&
                             (6 == *(copied_ptr + 1)) &&
                             ( 1 == *(copied_ptr + 2) )  &&
                             ( 2 == *(copied_ptr + 3) )
        , "vector add all has failed");

        free(source_data);
        free(dist_data);

        vec_free(rat_vec_src);
    }
END_TEST


START_TEST(test_vec_comp)
    {
        vec_t *rat_vec_src = vec_new(sizeof (int),2);
        vec_t *rat_vec_dist = vec_new(sizeof (int),2);

        int *source_data = malloc(2 * sizeof(int));
        *source_data = 1;
        *(source_data + 1) = 2;


        int *dist_data = malloc(2 * sizeof(int));
        *(dist_data ) = 5;
        *(dist_data + 1) = 6;

        vec_set(rat_vec_src, 0, 2 ,source_data);
        vec_set(rat_vec_dist, 0, 2 ,dist_data);
        comp_t my_comp = &compare_ints;
        fail_unless(vec_comp(rat_vec_dist,rat_vec_src,my_comp), "vector compare has failed");

        free(source_data);
        free(dist_data);

        vec_free(rat_vec_src);
    }
END_TEST

START_TEST(test_vec_swap)
    {
        vec_t *rat_vec_src = vec_new(sizeof (int),2);
        vec_t *rat_vec_dist = vec_new(sizeof (int),2);

        int *source_data = malloc(2 * sizeof(int));
        *source_data = 1;
        *(source_data + 1) = 2;

        int *dist_data = malloc(2 * sizeof(int));
        *(dist_data) = 5;
        *(dist_data + 1) = 6;

        vec_set(rat_vec_src, 0, 2 , source_data);
        vec_set(rat_vec_dist, 0, 2 , dist_data);
        vec_swap(rat_vec_src, rat_vec_dist);
        bool success_condition =( *((int *) rat_vec_dist->data) == *(source_data)
                                && *((int *)rat_vec_dist->data + 1) == *(source_data + 1)
                                && *((int *)rat_vec_src->data) == *(dist_data)
                                && *((int *)rat_vec_src->data + 1) == *(dist_data + 1)
                                );

        fail_unless(success_condition, "vector swapping has failed");

        free(source_data);
        free(dist_data);

        vec_free(rat_vec_src);
    }
END_TEST


START_TEST(test_vec_count)
    {
        vec_t *rat_vec_src = vec_new(sizeof (int), 2);

        int *source_data = malloc(2 * sizeof(int));
        *source_data = 1;
        *(source_data + 1) = 2;

        vec_set(rat_vec_src, 0, 2, source_data);
        bool (*pred_ptr)(void *capture, void *it) = &pred;
        int capture = 10;
        int how_many = vec_count(rat_vec_src,&capture,pred_ptr);
        bool success_condition = (how_many == 2);
        fail_unless(success_condition, "vector counting has failed");

        free(source_data);
        vec_free(rat_vec_src);
    }
END_TEST



START_TEST(test_vec_contains)
    {
        vec_t *rat_vec_src = vec_new(sizeof (int), 2);

        int *source_data = malloc(2 * sizeof(int));
        *source_data = 1;
        *(source_data + 1) = 2;

        vec_set(rat_vec_src, 0, 2, source_data);
        int element_contained = 1;
        int element_isnt_contained = 10;

        bool success_condition = vec_contains(rat_vec_src, &element_contained);
        success_condition &= !vec_contains(rat_vec_src, &element_isnt_contained);
        fail_unless(success_condition, "vector counting has failed");

        free(source_data);
        vec_free(rat_vec_src);
    }
END_TEST


START_TEST(test_vec_foreach)
    {
        vec_t *rat_vec_src = vec_new(sizeof (int), 2);

        bool (*foreach_pred_ptr)(void *capture, void *begin, void *end) = &for_each_check_bigger_capture;

        int *source_data = malloc(2 * sizeof(int));
        *source_data = 1;
        *(source_data + 1) = 2;

        vec_set(rat_vec_src, 0, 2, source_data);
        int capture_value = 5 ;

        vec_foreach(rat_vec_src,&capture_value, foreach_pred_ptr);
        bool success_condition = !vec_foreach(rat_vec_src,&capture_value, foreach_pred_ptr);

        fail_unless(success_condition, "vector test vector for each has failed");

        free(source_data);
        vec_free(rat_vec_src);
    }
END_TEST

START_TEST(test_vec_sort)
    {
        vec_t *rat_vec_src = vec_new(sizeof (int), 2);


        int *source_data = malloc(2 * sizeof(int));
        *source_data = 500;
        *(source_data + 1) = 2;

        vec_set(rat_vec_src, 0, 2, source_data);
        int (*compare_ints_ptr)(const void*,const void*) = &compare_ints;
        vec_sort(rat_vec_src,compare_ints_ptr);

        bool success_condition = *(int *)rat_vec_src->data == 2 ;
        fail_unless(success_condition, "vector sort has failed");

        free(source_data);
        vec_free(rat_vec_src);
    }
END_TEST


START_TEST(test_vec_bisearch)
    {
        vec_t *rat_vec_src = vec_new(sizeof (int), 4);

        int *source_data = malloc(4 * sizeof(int));
        *source_data = 500;
        *(source_data + 1) = 3;
        *(source_data + 2) = 4;
        *(source_data + 3) = 6;
        vec_set(rat_vec_src, 0, 4, source_data);
        int (*compare_ints_ptr)(const void*,const void*) = &compare_ints;
        int (*equal_ints_ptr)(const void*,const void*) = &equal_ints;
        int needle = 4;

        int *search_results = (int *) vec_bsearch(rat_vec_src, &needle, compare_ints_ptr, equal_ints_ptr);

        printf("\n search result = %d \n", * search_results);
        bool success_condition = *search_results == 4 ;
        fail_unless(success_condition, "vector bi search has failed");
        free(source_data);
        vec_free(rat_vec_src);
    }
END_TEST


bool for_each_check_bigger_capture(void *capture, void *begin, void *end)
{
    while (begin != end)
        {
            begin += sizeof(int);
            if (*(int *)begin > *(int *)capture)
            {
                continue;
            }
            return false;
        }
    return true;
}

bool pred(void *capture, void *it)
{
    return( *(int *)capture > *(int *)it);
}

int compare_ints(const void *lhs ,const void *rhs){

    if (*(int *)lhs == *(int *)rhs)
    {
        return 0;
    }else if (*(int *) lhs > *(int *)rhs){
        return 1;
    }
    return -1;
}

int equal_ints(const void *lhs ,const void *rhs){
    return *(int *) lhs == *(int *)rhs ;
}
void init_vec_test()
{
    vector_tsuit = suite_create("Vector Test Suit");

    vector_test_1 = tcase_create("test vector creation");
    tcase_add_test(vector_test_1, test_vec_creation);
    vector_test_2 = tcase_create("test vector creation");
    tcase_add_test(vector_test_2, test_vec_resize);
    vector_test_3 = tcase_create("test vector reserve");
    tcase_add_test(vector_test_3, test_vec_reserve);
    vector_test_4 = tcase_create("test vector length");
    tcase_add_test(vector_test_4, test_vec_length);
    vector_test_5 = tcase_create("test vector deep copy");
    tcase_add_test(vector_test_5, test_vec_cpy_deep);
    vector_test_6 = tcase_create("test vector shallow copy");
    tcase_add_test(vector_test_6, test_vec_cpy_shallow);
    vector_test_7 = tcase_create("test vector at");
    tcase_add_test(vector_test_7, test_vec_at);
    vector_test_8 = tcase_create("test vector peek");
    tcase_add_test(vector_test_8, test_vec_peek);
    vector_test_9 = tcase_create("test vector begin");
    tcase_add_test(vector_test_9, test_vec_begin);
    vector_test_10 = tcase_create("test vector end");
    tcase_add_test(vector_test_10, test_vec_end);
    vector_test_11 = tcase_create("test pop_unsafe");
    tcase_add_test(vector_test_11, test_vec_pop_unsafe);
    vector_test_12 = tcase_create("test vector set");
    tcase_add_test(vector_test_12, test_vec_set);
    vector_test_13 = tcase_create("test vector pushback");
    tcase_add_test(vector_test_13, test_vec_pushback);
    vector_test_14 = tcase_create("test vector add all");
    tcase_add_test(vector_test_14, test_vec_add_all);
    vector_test_15 = tcase_create("test vector compare");
    tcase_add_test(vector_test_15, test_vec_comp);
    vector_test_16 = tcase_create("test vector swap");
    tcase_add_test(vector_test_16, test_vec_swap);
    vector_test_17 = tcase_create("test vector count");
    tcase_add_test(vector_test_17, test_vec_count);
    vector_test_18 = tcase_create("test vector contains");
    tcase_add_test(vector_test_18, test_vec_contains);
//    vector_test_19 = tcase_create("test vector mem used");
//    tcase_add_test(vector_test_19, test_vec_memused);
    vector_test_20 = tcase_create("test vector foreach");
    tcase_add_test(vector_test_20, test_vec_foreach);
    vector_test_21 = tcase_create("test vector sort");
    tcase_add_test(vector_test_21, test_vec_sort);
    vector_test_22 = tcase_create("test vector bi search");
    tcase_add_test(vector_test_22, test_vec_bisearch);
    vector_test_23 = tcase_create("test vector update sort");
    tcase_add_test(vector_test_23, test_vec_updatesort);


    vector_test_50 = tcase_create("test vector memset");
    tcase_add_test(vector_test_50, test_vec_memset);

    suite_add_tcase(vector_tsuit, vector_test_1);
    suite_add_tcase(vector_tsuit, vector_test_2);
    suite_add_tcase(vector_tsuit, vector_test_3);
    suite_add_tcase(vector_tsuit, vector_test_4);
    suite_add_tcase(vector_tsuit, vector_test_5);
    suite_add_tcase(vector_tsuit, vector_test_6);
    suite_add_tcase(vector_tsuit, vector_test_7);
    suite_add_tcase(vector_tsuit, vector_test_8);
    suite_add_tcase(vector_tsuit, vector_test_9);
    suite_add_tcase(vector_tsuit, vector_test_10);
    suite_add_tcase(vector_tsuit, vector_test_11);
    suite_add_tcase(vector_tsuit, vector_test_12);
    suite_add_tcase(vector_tsuit, vector_test_13);
    suite_add_tcase(vector_tsuit, vector_test_14);
    suite_add_tcase(vector_tsuit, vector_test_15);
    suite_add_tcase(vector_tsuit, vector_test_16);
    suite_add_tcase(vector_tsuit, vector_test_17);
    suite_add_tcase(vector_tsuit, vector_test_18);
//    suite_add_tcase(vector_tsuit, vector_test_19);
    suite_add_tcase(vector_tsuit, vector_test_20);
    suite_add_tcase(vector_tsuit, vector_test_21);
    suite_add_tcase(vector_tsuit, vector_test_22);
    suite_add_tcase(vector_tsuit, vector_test_23);
    suite_add_tcase(vector_tsuit, vector_test_50);
}

