#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_BUYER 7
int stock[5];
pthread_mutex_t mutex;

struct buyer {
	int index_buyer;
	int buyer_need;
	int bought;
}buyer_param[MAX_BUYER];

void * load_stock(void * arg) {
	pthread_mutex_lock(&mutex);
	printf("> loader online\n");
	int i = rand() % 5 + 0;
	printf("> loader choise %d = %d\n", i, stock[i]);
	stock[i] += 100;
	printf("> stock %d = %d\n", i, stock[i]);
	sleep(2);
	pthread_mutex_unlock(&mutex);
	return 0;
}

void * buy_product(void * arg) {
	pthread_mutex_lock(&mutex);
	struct buyer b_param = *(struct buyer *) arg;
	int i = rand() % 5 + 0;
	if(stock[i] >= buyer_param[b_param.index_buyer].buyer_need) {
		stock[i] -= buyer_param[b_param.index_buyer].buyer_need;
		buyer_param[b_param.index_buyer].bought = buyer_param[b_param.index_buyer].buyer_need;
		buyer_param[b_param.index_buyer].buyer_need = 0;
		printf("> %d bought = %d\n", b_param.index_buyer, buyer_param[b_param.index_buyer].bought);
		sleep(1);
		pthread_mutex_unlock(&mutex);
		return 0;
	} else {
		buyer_param[b_param.index_buyer].bought = stock[i];
		buyer_param[b_param.index_buyer].buyer_need -= stock[i];
		stock[i] = 0;
		printf("> %d bought = %d\n", b_param.index_buyer, buyer_param[b_param.index_buyer].bought);
		sleep(1);
		pthread_mutex_unlock(&mutex);
		return 0;
	}
}

int main() {
	srand(time(NULL));
	for(int i = 0; i <= 5; ++i) {
		stock[i] = rand() % 1000 + 1000;
		printf("stock %d product = %d\n", i, stock[i]);
	}
	int need_to_buy = 0;
	for(int i = 0; i < MAX_BUYER; ++i) {
		buyer_param[i].index_buyer = i;
		buyer_param[i].buyer_need = rand() % 1000 + 600;
		buyer_param[i].bought = 0;
		need_to_buy += buyer_param[i].buyer_need;
		printf("buyer № %d need = %d\n", i, buyer_param[i].buyer_need);
	}
	printf("-> need_to_buy = %d\n", need_to_buy);
	do {
		pthread_t thread_loader;
		if (pthread_mutex_init(&mutex, NULL) != 0) {
			perror("pthread_mutex_init() error");
			return 1;
		}
		if (pthread_create(&thread_loader, NULL, &load_stock, NULL) != 0) {
			perror("pthread_create() error");
			return 1;
		}
		pthread_t thread_buyer[MAX_BUYER];
		for(int i = 0; i < MAX_BUYER; ++i) {
			if (pthread_create(&thread_buyer[i], NULL, &buy_product, &buyer_param[i].index_buyer) != 0) {
				perror("pthread_create() error");
				return 1;
			}
		}
		if (pthread_join(thread_loader, NULL) != 0) {
			perror("pthread_join() error");
			return 1;
		}
		for(int i = 0; i < MAX_BUYER; ++i) {
			if (pthread_join(thread_buyer[i], NULL) != 0) {
				perror("pthread_join() error");
				return 1;
			}
		}
		int left_to_buy = 0;
		for(int i = 0; i < MAX_BUYER; ++i) {
			left_to_buy += buyer_param[i].bought;
		}
		need_to_buy -= left_to_buy;
		printf("-> need_to_buy = %d\n", need_to_buy);
	} while(need_to_buy > 0);
	return 0;
}
