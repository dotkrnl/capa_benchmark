/*
 * main.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: hczhu
 */

#include <iostream>
#include <math.h>
#include "determinant.h"

using namespace std;

int main() {
   int n, i, j;
   int matrix[10][10];
   cout << "Enter the size of the matrix:\n";
   cin >> n;
   cout << "Enter the elements of the matrix:\n";
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         cin >> matrix[i][j];
   cout<<"The entered matrix is:"<<endl;
   for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++)
         cout << matrix[i][j] <<" ";
         cout<<endl;
   }
   cout<<"Determinant of the matrix is "<< determinant(matrix, n);
   return 0;
}

