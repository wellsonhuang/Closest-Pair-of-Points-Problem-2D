//
//  main.c
//  演算法-程式作業1
//
//  Created by 黃瑋宸 on 2022/3/12.
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#define N 1000000
struct node
{
    int x, y;
}node;

struct node n[N];
struct node temp[N];

int compareX(const void* a, const void* b)
{
    struct node *ac=(struct node*)a;
    struct node *bd=(struct node*)b;
    return ac->x - bd->x;
}

int compareY(const void* a, const void* b)
{
    struct node *ac = (struct node*)a;
    struct node *bd = (struct node*)b;
    return ac->y - bd->y;
}

double minDistance(double left , double right){
    return (left < right )? left: right;
}


double distance(struct node n1 ,struct node n2)
{
    return sqrt( (n1.x - n2.x)*(n1.x - n2.x) +
                 (n1.y - n2.y)*(n1.y - n2.y)
               );
}


double closestPair(struct node n[],int size,int threshold){
    double d;
    if(size<=threshold){
        double min = FLT_MAX;
        for(int i=0;i<size;i++){
            for(int j =i+1;j<size;j++){
                if(distance(n[i],n[j])<min)
                    min=distance(n[i],n[j]);
            }
        }
        return min;
    }
    
    int mid =size/2;
    int midPoint = n[mid].x;
    d = minDistance(closestPair(n,mid,threshold), closestPair(n+mid,size-mid,threshold));
    
    int counter=0;
    for(int i=0;i < size ; i++){
        if(abs(n[i].x - midPoint) < d){
            temp[counter] = n[i];
            counter++;
        }
    }
    
    qsort(n,counter,sizeof(node),compareY);
   
    for(int i=0;i < counter;i++)
        for(int j=i+1 ; j < counter && (n[j].y - n[i].y) < d ;++j)
            if( distance(temp[i] , temp[j]) < d)
                d = distance(temp[i] , temp[j]);
    return d;
}


int randint(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    long end = RAND_MAX / n;
    assert (end > 0L);
    end *= n;
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}

void sampling(int numbers){

for(int j =0;j<numbers;j++){
    int min1 = -10000;
    int max1 = 10000;
    n[j].x=rand()%(max1 - min1 + 1) + min1;
    n[j].y=rand()%(max1 - min1 + 1) + min1;
}
    
qsort(n, numbers,sizeof(node),compareX);
    
}


int main(){
    srand((int)time(NULL));
    double record[1000];
    double mintime=10;
    int place = 0;
    
    int min = 2;
    int max = 1000000;
    int numbers=0;
    numbers = rand()%(max - min + 1) + min;
    
    clock_t start, end;
    double cpu_time_used;
    
    
    for(int i=2;i<=5;i++){
        
    start = clock();
    int threshold=i;
    sampling(numbers);
    double dis = closestPair(n,numbers,threshold);
        printf("%f",dis);
    end = clock();
        
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   
    record[i-2]=cpu_time_used;
        if (record[i-2] < mintime){
            mintime = record[i-2];
            place = threshold;
            }

    }
    
    printf("n=%d\n",numbers);
    printf("threshold 應設為 %d, 時間為 %f \n",place,mintime);
    return 0 ;
}
