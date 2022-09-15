#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum m{
    QUICK, MERGE, HEAP, INSERTION, SHELL, SELECTION, BUBBLE, RADIX
};

/************************ Quick Sort ************************/
void quick_sort_recur(int *data, int start, int end){
    if(start >= end) return;

    int i, j, p;
    int pivot;
    int x;

    p = start;
    pivot = data[p];

    i = start;
    j = end;
    while(i <= j){
        while(data[i] < pivot) i++;
        while(data[j] > pivot) j--;

        if(i <= j){
            x = data[i];
            data[i] = data[j];
            data[j] = x;

            i++;
            j--;
        }
    }

    quick_sort_recur(data, start, j);
    quick_sort_recur(data, i, end);
}

void quick_sort(int *data, int len){
    quick_sort_recur(data, 0, len - 1);
}

/************************ Merge Sort ************************/
void merge_sort_recur(int *data, int start, int end){
    if(start >= end) return;

    int *out = (int *)malloc((end - start + 1) * sizeof(int));
    int mid;
    int i, j, o;
    
    mid = (start + end) / 2;
    merge_sort_recur(data, start, mid);
    merge_sort_recur(data, mid + 1, end);

    i = start;
    j = mid + 1;
    o = 0;
    while(i <= mid && j <= end){
        if(data[i] < data[j]){
            out[o++] = data[i++];
        }else{
            out[o++] = data[j++];
        }
    }
    while(i <= mid) out[o++] = data[i++];
    while(j <= end) out[o++] = data[j++];

    for(i = 0; i <= end - start; i++){
        data[start + i] = out[i];
    }

    free(out);
}

void merge_sort(int *data, int len){
    merge_sort_recur(data, 0, len - 1);
}

/************************ Heap Sort ************************/
void heap_sort(int *data, int len){
    int n = len;
    int i = n / 2;
    int x;
    int parent, child;

    while(1){
        if(i > 0){
            i--;
        }else{
            n--;
            if(n == 0) return;

            x = data[0];
            data[0] = data[n];
            data[n] = x;
        }

        parent = i;
        child = i * 2 + 1;
        while(child < n){
            if(child + 1 < n && data[child + 1] > data[child]){
                child++;
            }
            if(data[child] > data[parent]){
                x = data[parent];
                data[parent] = data[child];
                data[child] = x;
                parent = child;
                child = parent * 2 + 1;
            }else{
                break;
            }
        }
    }
}

/************************ Insertion Sort ************************/
void insertion_sort(int *data, int len){
    int i, j;
    int x;

    for(i = 1; i < len; i++){
        x = data[i];
        j = i;
        while(j - 1 >= 0 && x < data[j - 1]){
            data[j] = data[j - 1];
            j--;
        }
        data[j] = x;
    }
}

/************************ Shell Sort ************************/
void shell_sort(int *data, int len){
    int i, j;
    int x;
    int h;

    h = 1;
    while(h * 3 + 1 < len){
        h = h * 3 + 1;
    }

    do{
        h /= 3;

        for(i = h; i < len; i++){
            x = data[i];
            j = i;
            while(j - h >= 0 && x < data[j - h]){
                data[j] = data[j - h];
                j -= h;
            }
            data[j] = x;
        }
    }while(h > 1);
}

/************************ Selection Sort ************************/
void selection_sort(int *data, int len){
    int i, j;
    int x;
    int min;

    for(i = 0; i < len - 1; i++){
        min = i;
        for(j = i + 1; j < len; j++){
            if(data[j] < data[min]){
                min = j;
            }
        }
        x = data[i];
        data[i] = data[min];
        data[min] = x;
    }
}

/************************ Bubble Sort *******************************/
void bubble_sort(int *data, int len){
    int i, j;
    int x;

    for(i = 0; i < len - 1; i++){
        for(j = 0; j < len - i - 1; j++){
            if(data[j] > data[j + 1]){
                x = data[j];
                data[j] = data[j + 1];
                data[j + 1] = x;
            }
        }
    }
}

/************************ Radix Sort ************************/
void radix_sort(int *data, int len){
    int base = 10;
    int *tempdata = (int *)malloc(len * sizeof(int));
    int *count = (int *)malloc(base * sizeof(int));
    int max;
    int exp;
    int i;

    max = data[0];
    for(i = 1; i < len; i++){
        if(data[i] > max){
            max = data[i];
        }
    }

    exp = 1;
    while(max / exp > 0){
        for(i = 0; i < base; i++){
            count[i] = 0;
        }
        for(i = 0; i < len; i++){
            count[(data[i] / exp) % base]++;
        }
        for(i = 1; i < base; i++){
            count[i] += count[i - 1];
        }
        for(i = len - 1; i >= 0; i--){
            count[(data[i] / exp) % base]--;
            tempdata[count[(data[i] / exp) % base]] = data[i];
        }
        for(i = 0; i < len; i++){
            data[i] = tempdata[i];
        }

        exp *= base;
    }

    free(tempdata);
    free(count);
}

/************************ For Tests ************************/

int *rand_data(int len, int range){
    int *data = (int *)malloc(len * sizeof(int));
    int i;
    
    srand(time(NULL));
    for(i = 0; i < len; i++){
        data[i] = rand() % range;
    }

    return data;
}

void sort(int *data, int len, enum m method){
    switch(method){
    case QUICK:
        quick_sort(data, len);
        break;
    case MERGE:
        merge_sort(data, len);
        break;
    case HEAP:
        heap_sort(data, len);
        break;
    case INSERTION:
        insertion_sort(data, len);
        break;
    case SHELL:
        shell_sort(data, len);
        break;
    case SELECTION:
        selection_sort(data, len);
        break;
    case BUBBLE:
        bubble_sort(data, len);
        break;
    case RADIX:
        radix_sort(data, len);
        break;
    }
}

void print_data(int *data, int len){
    int i;
    for(i = 0; i < len; i++){
        printf("%d", data[i]);
        if(i != len - 1) printf(" ");
    }
    printf("\n");
}

int main(){
    int len = 1000000;
    int *data;
    time_t tm1, tm2;
    int i;

    for(i = 0; i < 10; i++){
        data = rand_data(len, len * 10);
    
        tm1 = clock();
        //sort(data, len, QUICK);
        tm2 = clock();
    
        printf("[Round %d] Time elapsed: %f s\n", i, (double)(tm2 - tm1) / CLOCKS_PER_SEC);
    
        free(data);
    }
}