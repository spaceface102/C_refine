#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "optimized_grid.h"

uint64_t gridPaths(uint64_t m, uint64_t n)
{
    if (m == 1 || n == 1)
        return 1;
    return gridPaths(m - 1, n) + gridPaths(m, n - 1);
}

uint64_t gridPaths_optimized(uint64_t m, uint64_t n)
{
/* VERSION 1 OPTIMIZED */
    if (m == 1 || n == 1)
        return 1;
    if (m == n)
        return 2*gridPaths(m - 1, n);
    return gridPaths(m - 1, n) + gridPaths(m, n - 1);
}

//n number of objects, m is max number of
//objects per each part in a partion.
//m should be <= n
uint64_t partition(uint64_t n, uint64_t m)
{
    //no object to partion or each part can have no objects
    if (n == 0 || m == 0) 
        return 0;
    //each part can only have one object.
    if (m == 1)
        return 1;
    return 1 + partition(m, m - 1);
}
//EOF

//max m and n is 100
uint64_t noInit_gridDynamic(uint64_t m, uint64_t n)
{   //not as good for concurrent applications since
    //there is a possibility that multiple threads
    //might try to modify at the same time.
    static uint64_t LOOKUP[200][200]; //automatically filled with zeros
    //160, 161 reaches the max (161, 161 overflows)
    /* VERSION 3 OPTIMIZED_Easier to use than V2 */
    if (LOOKUP[m][n])   //already input in lookup table
        return LOOKUP[m][n];
    else //didn't find it in look up table.
    {
        if (m == 1 || n == 1) //base case
            LOOKUP[m][n] = LOOKUP[n][m] = 1;
        else if (m == n)
            //2* since gridPaths(m - 1, n) is eq.
            //to gridPaths(m, n - 1) since m eq. n
            LOOKUP[m][n] = 2*noInit_gridDynamic(m - 1, n);
        else //not a perfect square
            //grid 2, 3 eq. to grid 3, 2 just different orientation
            //this is the general idea:
            LOOKUP[m][n] = LOOKUP[n][m] = 
            noInit_gridDynamic(m - 1, n) + noInit_gridDynamic(m, n - 1);
    }
    return LOOKUP[m][n]; //return for the bigger else block
}

int main(int argc, char* argv[])
{
    uint64_t row = 12, col = 12;

    if (argc > 2)
        row = atoi(argv[1]), col = atoi(argv[2]);


    //printf("For a grid(%lu, %lu) = %lu paths\n",
    //row, col, gridPaths_optimized(row, col));
    printf("For a grid(%lu, %lu) = %lu paths\n",
    row, col, noInit_gridDynamic(row, col));
    return 0;
}