#ifndef _FRAC_KNAPSACK_H_
#define _FRAC_KNAPSACK_H_

#include <stdio.h>
#include <stdlib.h>

struct knapsack_item{
	char name[100];
	double weight;
	double profit;
	double selected;
};

void input_items(struct knapsack_item *items, int item_count);
double fractional_knapsack(double capacity, struct knapsack_item *items, int item_count);
void print_result(struct knapsack_item *items, int item_count, double max_profit);



