#include "coinchange.h"

int compare_coin_item_value(const void *value1, const void *value2)
{
	struct coin_item *item1 = (struct coin_item*)value1;
	struct coin_item *item2 = (struct coin_item*)value2;

	return (item->value < item2->value) ?  1 :
		   (item->value > item2->value) ? -1 : 0;
}

int get_change_count(int target_change, int coin_value)
{
	int count = 0;

	if(target_change >= coin_value){
		count = target_change/coin_value;
	}

	return count;
}

int get_change(int change_total, struct coin_item *items, int item_count)
{
	int current_change = change_total;
	int i;

	// 동전 금액이 큰 순서대로 정렬한다.
	qsort(items, item_count, sizeof(struct coin_item), compare_coin_item_value);

	// 동전 정보를 출력한다.
	// 어떻게 정렬이 이루어졌는지 알 수 있게 된다.
	printf("정렬 결과\n\t값\n");
	for(i = 0; i < item_count; i++){
		printf("%d\t%d\n", i, items[i].value);
	}

	/*
	 	탐욕 알고리즘의 구현 부분으로 가장 중요하다.

		먼저 for문을 사용하여 부분 해를 도출한다.  
		여기서 부분 해를 도출하는 부분이 바로 

		int count = get_change_count(current_change, items[i].value);
		이 부분이 되겠다. 여기서는 현재 남은 거스름돈 current_change와  
		현재 동전의 금액 items[i].value를 이용하여 부분 해를 계산한다.  
		부분 해를 계산하는 부분은 함수 get_change_count()를 호출했기 때문이다.  
		이렇게 구한 동전의 개수 count를 items[i].selected에 저장한다.

		그리고 다음 줄에서 남은 거스름돈을 다시 계산한다.
		왜냐하면, 현재 선택된 동전 금액items[i].value를 count개만큼 거슬러 주었기 때문이다.  
		이러한 방식으로 모든 동전의 종류에 대해서 계산을 수행한다. 
		특별히 여기서 i번째 동전의 개수를 구한 값을 items[i]의 멤버변수인 selected에 저장한다는 점에 주의하라.  
		왜냐면 items는 포인터로 전달되어 입출력 파라미터의 역할을 하기 때문이다.

		참고로 배열 연산자는 왜 들어갔을까?
		그 이유는 main함수에서 malloc을 통해 items를 관리하기 때문이다.  

	 */
	for(i = 0; i < item_count; i++){
		int count = get_change_count(current_change, items[i].value);
		items[i].selected = count;
		current_change = current_change - count * items[i].value;
	}

	return current_change;
}

void input_items(struct coin_items *items, int item_count)
{
	int i;

	for(i = 0; i < item_count; i++){
		printf("%d 번째 동전의 단위를 입력해 주세요 (예, 100)\n", i + 1);
		scanf("%d", &items[i].value);
		items[i].selected = 0;
	}
}

void print_result(struct coin_items *items, int remained)
{
	int i;

	printf("(동전)\t(동전 개수)\n");
	for(i = 0; i < item_count; i++){
		printf("%d\t%d\n", items[i].value, items[i].selected);
	}

	printf("남은 거스름돈: %d\n", remained);
}



