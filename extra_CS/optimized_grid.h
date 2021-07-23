#include <stdint.h>
#include <stdbool.h>

//should have run initGridLookup() before using girdLookup(m, n)
void initGridLookup(void);
uint64_t gridLookup(uint64_t m, uint64_t n);