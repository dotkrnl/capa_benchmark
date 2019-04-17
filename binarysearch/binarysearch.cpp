/*
 * binarysearch.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: hczhu
 */

#include "binarysearch.h"

/* Iterative solution */
int binary_search(int list[], int length, int to_be_found){

    int p = 0;
    int r = length - 1;
    int q = (r + p) / 2;
    int counter = 0;

    while (p <= r)
    {
        counter++;
        if (list[q] == to_be_found)
            return q;
        else
        {
            if (list[q] < to_be_found)
            {
                p = q + 1;
                q = (r + p) / 2;
            }
            else
            {
                r = q - 1;
                q = (r + p) / 2;
            }
        }
    }
    return -1;
}

/* Recursive solution */
int recursive_binary_search(int list[], int to_be_found, int p, int r){

    if (p > r)
        return -1;
    else
    {
        int q = (p + r) / 2;
        if (list[q] == to_be_found)
            return q;
        else
        {
            if (list[q] < to_be_found)
                return recursive_binary_search(list, to_be_found, q + 1, r);

            else
                return recursive_binary_search(list, to_be_found, p, q - 1);
        }
    }
}



