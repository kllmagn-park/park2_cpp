#include <iostream>
#include <gtest/gtest.h>

extern "C" {
#include "test.h"
}

TEST(most_frequent, adding_values){
    char* result = most_frequent(NULL, 0);
    if(result != NULL) ADD_FAILURE_AT("static/tests/test.cpp", 28);

    char tst_string[] = "bbaacqbbaaacfffqqsaaqcy";
    result = most_frequent(tst_string, sizeof(tst_string));

    EXPECT_STREQ(result, "most frequent series: 'a' x 2   (5 times)\n");
    free(result);


    char tst_string_2[] = "\0\0\0\0\0\0\0";
    result = most_frequent(tst_string_2, sizeof(tst_string_2));

    EXPECT_STREQ(result, "most frequent series: '\\0' x 8   (1 times)\n");
    free(result);
}


