#include <stdio.h>
#include <stdlib.h>

#include <math.h>

typedef struct node *Node;
struct node {
	float mon;
	int cou;
	int num;//人的编号 
}List[10000];

int compare(const void *a,const void *b)
{//mon按照降序,cou按照降序,个人编号升序 
	int k = 0;
	if(fabs(((const struct node *)a)->mon - ((const struct node *)b)->mon) > 1e-5)
		k=(((const struct node *)b)->mon - ((const struct node *)a)->mon > 0) ? 1 : -1;
	else if(((const struct node *)a)->cou!=((const struct node *)b)->cou)
		k=(((const struct node *)b)->cou - ((const struct node *)a)->cou > 0) ? 1 : -1;
	else if(((const struct node *)a)->num!=((const struct node *)b)->num)
		k=(((const struct node *)a)->num - ((const struct node *)b)->num > 0) ? 1 : -1;
	return k;
}

int main()
{
	int N,i;
	scanf("%d",&N);
	for(i=1;i<=N;i++) {
		List[i].cou=0;
		List[i].mon=0;
		List[i].num=i;
	}
	for(i=1;i<=N;i++) {
		int k,n,p;
		scanf("%d",&k);
		while(k--) {
			scanf("%d%d",&n,&p);
			List[n].cou++;
			List[n].mon+=p/100.0;
			List[i].mon-=p/100.0;
		}
	}
//	开始排序 
	qsort(List+1,N,sizeof(struct node),compare);
	for(i=1;i<=N;i++) {
		printf("%d %.2f\n",List[i].num,List[i].mon);
	}
	return 0;
}

// Data
// 10
// 3 2 22 10 58 8 125
// 5 1 345 3 211 5 233 7 13 8 101
// 1 7 8800
// 2 1 1000 2 1000
// 2 4 250 10 320
// 6 5 11 9 22 8 33 7 44 10 55 4 2
// 1 3 8800
// 2 1 23 2 123
// 1 8 250
// 4 2 121 4 516 7 112 9 10