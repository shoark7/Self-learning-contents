#ifndef _COIN_CHANGE_H_
#define _COIN_CHANGE_H_

#include <stdio.h>
#include <stdlib.h>

struct coin_item{
	int value;
	int selected;
};

void input_items(struct coin_item *items, int item_count);
int get_change(int change_total, struct coin_item *items, int item_count);
void print_result(struct coin_item *items, int item_count, int remained);

#endif
