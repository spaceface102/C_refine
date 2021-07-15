#include <stdio.h>

#define DO_SOMETHING(x)\
printf("First time: %d\n", x);\
printf("Once more!  %d\n", x)

int main(void)
{
    int stu = 1;
    
    DO_SOMETHING(stu++);
    printf("Final value of stu: %d\n", stu);
    getc(stdin);
}