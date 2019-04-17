/*
 * main.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: hczhu
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "binarysearch.h"

using namespace std;


int main()
{
    int list_length = 30;
    int item_to_find = 150;
    int list[list_length];
    int temp_int = 0;
    srand(time(NULL));
    /* Generates a random non decreasing sequence (list) of size list_length */
    for (int i = 0; i < list_length; i++)
    {
        temp_int = rand() % 30 + temp_int;
        list[i] = temp_int;
        std::cout << i << ":" << temp_int << std::endl;
    }
    std::cout << "Result from iterative procedure: " << binary_search(list, list_length, item_to_find) << std::endl;
    std::cout << "Result from recursive procedure: " << recursive_binary_search(list, item_to_find, 0, list_length - 1) << std::endl;

    return 0;
}

