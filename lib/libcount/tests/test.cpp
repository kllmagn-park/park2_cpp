#include <iostream>
#include <gtest/gtest.h>

extern "C" {
    #include "./test.h"
}

#define TEST_CHAR_SERIES(series, symbols_0, symbols_1, symbols_2, symbols_3, symbols_4, symbols_5, symbols_6, symbols_7, count_num, len_num) \
            ASSERT_EQ(returned, 0); \
            EXPECT_EQ(series->cbits[0], symbols_0); \
            EXPECT_EQ(series->cbits[1], symbols_1); \
            EXPECT_EQ(series->cbits[2], symbols_2); \
            EXPECT_EQ(series->cbits[3], symbols_3); \
            EXPECT_EQ(series->cbits[4], symbols_4); \
            EXPECT_EQ(series->cbits[5], symbols_5); \
            EXPECT_EQ(series->cbits[6], symbols_6); \
            EXPECT_EQ(series->cbits[7], symbols_7); \
            EXPECT_EQ(series->freq, count_num); \
            EXPECT_EQ(series->length, len_num)

TEST(remove_series, test){
    char_series* series = new char_series;
    series->cbits[0] = 25;
    series->cbits[1] = 7;
    series->cbits[2] = 8;
    series->cbits[3] = 52;
    series->cbits[4] = 7582;
    series->cbits[5] = 7;
    series->cbits[6] = 2623;
    series->cbits[7] = 57;
    series->freq = 2;
    series->length = 157;


    int returned = remove_series(NULL);
    EXPECT_EQ(returned, -1);

    returned = remove_series(series);
    TEST_CHAR_SERIES(series,0,0,0,0,0,0,0,0,0,0);

    delete(series);
}


TEST(append_to_series, nan_return){
    unsigned int cbits[8];
    set_char('a', cbits);
    int returned = append_to_series(NULL, cbits,1);
    EXPECT_EQ(returned, -1);
}

TEST(append_to_series, correct_adding){
    char_series* series = new char_series;

    remove_series(series);

    // cbits[0]
    unsigned int cbits[8];
    set_char(1, cbits);
    int returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,0,0,0,0,0,0,0,1,0);

    set_char(1, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,0,0,0,0,0,0,0,2,0);

    // cbits[1]
    set_char(33, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,0,0,0,0,0,0,3,0);

    set_char(33, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,0,0,0,0,0,0,4,0);

    // cbits[2]
    set_char(65, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,0,0,0,0,0,5,0);

    set_char(65, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,0,0,0,0,0,6,0);

    // cbits[3]
    set_char(97, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,0,0,0,0,7,0);

    set_char(97, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,0,0,0,0,8,0);


    // cbits[4]
    set_char(129, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,2,0,0,0,9,0);

    set_char(129, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,2,0,0,0,10,0);


    // cbits[5]
    set_char(161, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,2,2,0,0,11,0);

    set_char(161, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,2,2,0,0,12,0);


    // cbits[6]
    set_char(193, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,2,2,2,0,13,0);

    set_char(193, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,2,2,2,0,14,0);


    // cbits[7]
    set_char(225, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,2,2,2,2,15,0);

    set_char(225, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,2,2,2,2,2,2,2,2,16,0);

    delete(series);
}

TEST(append_to_series, border_values){
    char_series* series = new char_series;

    remove_series(series);

    unsigned int max = 0x80000001;
    // cbits[0]
    unsigned int cbits[8];
    set_char(0, cbits);
    int returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,1,0,0,0,0,0,0,0,1,0);

    set_char(31, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,0,0,0,0,0,0,0,2,0);


    // cbits[1]
    set_char(32, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,1,0,0,0,0,0,0,3,0);

    set_char(63, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,0,0,0,0,0,0,4,0);


    // cbits[2]
    set_char(64, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,1,0,0,0,0,0,5,0);

    set_char(95, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,0,0,0,0,0,6,0);


    // cbits[3]
    set_char(96, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,1,0,0,0,0,7,0);

    set_char(127, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,max,0,0,0,0,8,0);


    // cbits[4]
    set_char(128, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,max,1,0,0,0,9,0);

    set_char(159, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,max,max,0,0,0,10,0);


    // cbits[5]
    set_char(160, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,max,max,1,0,0,11,0);

    set_char(191, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,max,max,max,0,0,12,0);


    // cbits[6]
    set_char(192, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,max,max,max,1,0,13,0);

    set_char(223, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,max,max,max,max,0,14,0);


    // cbits[7]
    set_char(224, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,max,max,max,max,1,15,0);

    set_char(255, cbits);
    returned = append_to_series(series, cbits,1);
    TEST_CHAR_SERIES(series,max,max,max,max,max,max,max,max,16,0);


    delete(series);
}


TEST(find_pos_by_length, nan_values){
    all_series *all = new all_series;
    all->bsize=10;
    all->size=0;
    all->arr = (char_series*)malloc(sizeof(char_series) * 10);

    EXPECT_EQ(find_pos_by_length(NULL, 1), -1);
    EXPECT_EQ(find_pos_by_length(all, 1), 0);

    free(all->arr);
    delete(all);
}

TEST(find_pos_by_length, correct_pos){
    all_series *all = new all_series;
    char_series array[10];
    unsigned int lengths[10] = {2,4,5,6,7,10,11,12,29,100};
    for(int i = 0; i < 10; i++) array[i].length = lengths[i];
    all->arr = array;
    all->size = 10;

    EXPECT_EQ(find_pos_by_length(all, 1), 0);
    EXPECT_EQ(find_pos_by_length(all, 2), 0);
    EXPECT_EQ(find_pos_by_length(all, 4), 1);
    EXPECT_EQ(find_pos_by_length(all, 8), 5);
    EXPECT_EQ(find_pos_by_length(all, 29), 8);
    EXPECT_EQ(find_pos_by_length(all, 100), 9);
    EXPECT_EQ(find_pos_by_length(all, 110), 10);

    delete(all);
}


TEST(init_all_series, wrong_values){
    all_series* all = new all_series;
    all->size = 500;
    all->bsize = 10;
    all->arr = (char_series*)malloc(sizeof(char_series) * 10);

    int result = init_all_series(NULL);
    EXPECT_EQ(result, -1);

    result = init_all_series(all);
    EXPECT_EQ(result, -1);

    free(all->arr);
    delete(all);
}

TEST(init_all_series, memory_alloc){
    all_series* all = new all_series;
    all->arr = NULL;
    all->bsize=0;
    all->size=0;

    int result = init_all_series(all);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(all->bsize, 10);
    if(all->arr == NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 211);

    all->size=9;
    result = init_all_series(all);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(all->bsize, 20);
    if(all->arr == NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 217);

    free(all->arr);
    delete(all);
}

TEST(handle_series, wrong_values){
    all_series* all = new all_series;
    all->size = 500;
    all->bsize = 10;
    all->arr = (char_series*)malloc(sizeof(char_series) * 10);

    unsigned int cbits[8];
    set_char(1, cbits);
    int result = handle_series(NULL, 1,cbits,1);
    EXPECT_EQ(result, -1);

    result = handle_series(all, 1,cbits,1);
    EXPECT_EQ(result, -1);

    free(all->arr);
    delete(all);
}

TEST(handle_series, adding_values){

    all_series* all = new all_series;
    all->arr = NULL;

    unsigned int cbits[8];
    set_char(0, cbits);
    int returned = handle_series(all, 4,cbits,1);
    EXPECT_EQ(returned, 0);
    EXPECT_EQ(all->bsize, 10);
    EXPECT_EQ(all->size, 1);
    TEST_CHAR_SERIES((&all->arr[0]),1,0,0,0,0,0,0,0,1,4);

    set_char(1, cbits);
    returned = handle_series(all, 4,cbits,1);
    EXPECT_EQ(returned, 0);
    EXPECT_EQ(all->bsize, 10);
    EXPECT_EQ(all->size, 1);
    TEST_CHAR_SERIES((&all->arr[0]),3,0,0,0,0,0,0,0,2,4);

    set_char(0, cbits);
    returned = handle_series(all, 2,cbits,1);
    EXPECT_EQ(returned, 0);
    EXPECT_EQ(all->bsize, 10);
    EXPECT_EQ(all->size, 2);
    TEST_CHAR_SERIES((&all->arr[0]),1,0,0,0,0,0,0,0,1,2);

    returned = handle_series(all, 6,cbits,1);
    EXPECT_EQ(returned, 0);
    EXPECT_EQ(all->bsize, 10);
    EXPECT_EQ(all->size, 3);
    TEST_CHAR_SERIES((&all->arr[2]),1,0,0,0,0,0,0,0,1,6);

    returned = handle_series(all, 5,cbits,1);
    EXPECT_EQ(returned, 0);
    EXPECT_EQ(all->bsize, 10);
    EXPECT_EQ(all->size, 4);

    set_char(2, cbits);
    handle_series(all, 2,cbits,1);
    handle_series(all, 4,cbits,1);
    handle_series(all, 5,cbits,1);
    handle_series(all, 6,cbits,1);

    EXPECT_EQ(all->bsize, 10);
    EXPECT_EQ(all->size, 4);

    TEST_CHAR_SERIES((&all->arr[0]),5,0,0,0,0,0,0,0,2,2);
    TEST_CHAR_SERIES((&all->arr[1]),7,0,0,0,0,0,0,0,3,4);
    TEST_CHAR_SERIES((&all->arr[2]),5,0,0,0,0,0,0,0,2,5);
    TEST_CHAR_SERIES((&all->arr[3]),5,0,0,0,0,0,0,0,2,6);

    free(all->arr);
    delete(all);
}


TEST(get_all, wrong_values){
    all_series* result = get_all(NULL, 2);
    if(result != NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 360);

    char tst_string[] = "abcd";
    result = get_all(tst_string, -3);
    if(result != NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 363);
}

TEST(get_all, adding_values){
    char tst_string[] = "abbcccccdddqqqef";
    all_series* result = get_all(tst_string, sizeof(tst_string));
    if(result == NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 370);

    EXPECT_EQ(result->bsize, 10);
    EXPECT_EQ(result->size, 3);
    int returned = 0;

    TEST_CHAR_SERIES((&result->arr[0]),0,0,0,0x00000004,0,0,0,0,1,2);
    TEST_CHAR_SERIES((&result->arr[1]),0,0,0,0x00020010,0,0,0,0,2,3);
    TEST_CHAR_SERIES((&result->arr[2]),0,0,0,0x00000008,0,0,0,0,1,5);

    free_all(result);
}

TEST(get_all, zero_string){
    char tst_string[] = "\0\0\0\0\0\0\0";
    all_series* result = get_all(tst_string, sizeof(tst_string));
    if(result == NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 370);

    EXPECT_EQ(result->bsize, 10);
    EXPECT_EQ(result->size, 1);
    int returned = 0;

    TEST_CHAR_SERIES((&result->arr[0]),1,0,0,0,0,0,0,0,1,sizeof(tst_string));

    free_all(result);
}

TEST(get_char, test){
    char result = get_char(NULL);
    EXPECT_EQ(result, 0);

    unsigned int cbits[8];
    set_char('w', cbits);
    char_series* series = new char_series;
    remove_series(series);
    append_to_series(series, cbits,1);

    result = get_char(series);
    EXPECT_EQ(result, 'w');

    set_char('W', cbits);
    remove_series(series);
    append_to_series(series, cbits,1);

    result = get_char(series);
    EXPECT_EQ(result, 'W');

    delete(series);
}


TEST(mfrcs, test){
    all_series* all = get_all(NULL, 0);
    char_series* result = mfrcs(all);
    if(result != NULL) ADD_FAILURE_AT("shared/tests/test.cpp", 12);

    char tst_string[] = "abbcccccdddqqqef";
    all = get_all(tst_string, sizeof(tst_string));

    result = mfrcs(all);
    EXPECT_EQ(result->freq, 2);
    EXPECT_EQ(result->length, 3);
    EXPECT_EQ(get_char(result), 'd');

    free(all->arr);
    free(all);
}