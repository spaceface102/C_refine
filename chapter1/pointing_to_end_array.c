#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct an_array{
	int size;
	void (*make_array)(struct an_array *);
	void (*free_array)(struct an_array *);
	struct an_array *next;
	struct an_array *prev;
	int *array;
} an_array;


void make_array_func(an_array *data);
void free_array_func(an_array *data);
void init_an_array(an_array *data);

int main(void)
{
	/* DEMONSTRATE NEGAITVE INDEX
	int x[5] = {1, 2, 3, 4, 5};
	int *y = &x[4]; //eq to saying y = x+4
	printf("%d %d\n", x[1], y[-3]);
	return 0; */

	an_array x;
	init_an_array(&x);
	x.make_array(&x);
	for(int i = 0; i < x.size; x.array[i++] = 0xfeedbeef);
	x.free_array(&x);
}


void make_array(an_array *data)
{
	if (!data->size)
	{
		printf("What size should this array be? ");
		scanf("%d", &data->size);
	}
	else
	{
		printf("You already allocated memory for this array!\n");
		return;
	}

	if (data->size > 0)
	{
		data->array = (int *)malloc(sizeof(int)*data->size);
		if (data->array == NULL)
			printf("Oh oh, I think we are out of memory:/\n");
	}
	else
		printf("Invalid size!");
}


void free_array(an_array *data)
{
	if (data->array == NULL)
		printf("Please make sure to first allocate memory to array!\n");
	else
	{
		free(data->array);
		data->array = NULL;
	}
}	

void init_an_array(an_array *data)
{
	data->size = 0;
	data->make_array = make_array;
	data->free_array = free_array;
	data->next = NULL;
	data->prev = NULL;
	data->array = NULL;
}
