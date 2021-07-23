#include "optimized_grid.h"

#define ROWS 100UL
#define COLS 100UL

static uint64_t LOOKUP[ROWS][COLS]; //auto set to 0
static bool INIT_LOOKUP = false;

static uint64_t Lookup_Init_FillNonTrivial(uint64_t m, uint64_t n);


//once initGridLookup is finished, this is ready
//for concurency, no writing just reading!
//should have run initGridLookup() before hand
uint64_t gridLookup(uint64_t m, uint64_t n)
{
    return LOOKUP[m][n];
}

void initGridLookup(void)
{
    if (!INIT_LOOKUP) //make sure not init more than once.
    {
        for (uint64_t i = 0; i < ROWS; i++)
            LOOKUP[i][1] = 1;
        for (uint64_t i = 0; i < COLS; i++)
            LOOKUP[1][i] = 1;
        
        Lookup_Init_FillNonTrivial(ROWS, COLS);
        INIT_LOOKUP = true;
    }
}

static uint64_t Lookup_Init_FillNonTrivial(uint64_t m, uint64_t n)
{
/* VERSION 2 OPTIMIZED */
    if (LOOKUP[m][n])   //already input in lookup table
        return LOOKUP[m][n];
    else //didn't find it in look up table.
    {
        if (m == n)
            //2* since gridPaths(m - 1, n) is eq. 
            //to gridPaths(m, n - 1) since m eq. n
            LOOKUP[m][n] = 2*Lookup_Init_FillNonTrivial(m - 1, n);
        else //not a perfect square
        {
            LOOKUP[m][n] = Lookup_Init_FillNonTrivial(m - 1, n)
                           + Lookup_Init_FillNonTrivial(m, n - 1);
            //grid 2, 3 eq. to grid 3, 2 just different orientation
            //this is the general idea:
            LOOKUP[n][m] = LOOKUP[m][n];
        }
    }
    return LOOKUP[m][n]; //return for the bigger else block
}