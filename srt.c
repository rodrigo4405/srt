#include <string.h>
#include <stdlib.h>
#include <stdio.h>


const int SAMPLE_SIZE_LIMIT = 6;

int g_sample_size(char *sample_file);
void read_nums(char *sample_file, int *nums, int size);
void print_sorted(int *sample, int size);

void sort_bubble(int *sample, int size);
void sort_select(int *sample, int size);

typedef struct {
    int number;
    int index;
} elem;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("./csrt <sample> <opt>\n");
        return -1;
    }

    char *sample = argv[1];

    char opt = argv[2][0];

    int sample_size = g_sample_size(sample);
    
    printf("Sample size: %i\n", sample_size);
    int nums[sample_size];
    read_nums(sample, nums, sample_size);
    
    switch (opt) {
        case 'b':
            sort_bubble(nums, sample_size);
            break;
        case 's':
            sort_select(nums, sample_size);
            break;
        default:
            printf("No sort selected.\n");
            break;
    }

    print_sorted(nums, sample_size);
}

int g_sample_size(char *sample_file) {
    char count[SAMPLE_SIZE_LIMIT + 1];
    FILE *sample = fopen(sample_file, "r");

    if (!sample) {
        return -90;
    }

    char c;
    for (int i = 0; i < SAMPLE_SIZE_LIMIT + 1; i++) {
        fread(&c, sizeof(char), 1, sample);

        if (c == '\n') {
            count[i] = '\0';
            break;
        }

        count[i] = c;
    }

    fclose(sample);
    return atoi(count);
}

void read_nums(char* sample_file, int *nums, int size) {
    FILE *sample = fopen(sample_file, "r");

    if (!sample) {
        exit(2313);
    }

    //find start
    char c;
    for (int i = 0; i < SAMPLE_SIZE_LIMIT; i++) {
        fread(&c, sizeof(char), 1, sample);
        if (c == '\n') {
            break;
        }
    }

    for (int k = 0; k < size; k++) {
        char num[SAMPLE_SIZE_LIMIT + 1];
        char l;
        for (int u = 0; u < 10; u++) {
            fread(&l, sizeof(char), 1, sample);
            if (l == ',' || feof(sample)) {
                num[u] = '\0';
                break;
            }
            num[u] = l;
        }
        nums[k] = atoi(num);
    }
}

void print_sorted(int *sample, int size) {
    FILE *otp = fopen("sorted.txt", "w");

    if (!otp) {
        exit(100);
    }

    for (int i = 0; i < size; i++) {
        fprintf(otp, "%i\n", sample[i]);
    }

    fclose(otp);
}

int check(int *sample, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (sample[i] > sample[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void sort_bubble(int *sample, int size) {
    int p = 0;
    int tmp;
    while (!check(sample, size)) {
        for (int i = 0; i < size - 1; i++) {
            if (sample[i] < sample[i + 1]) {
                continue;
            }

            tmp = sample[i];
            sample[i] = sample[i + 1];
            sample[i + 1] = tmp; 
        }
    }
}

void sort_select(int *sample, int size) {
    elem btt;
    btt.index = 0;
    btt.number = sample[0];
    int tmp;

    int i;
    int s = 1;
    while (!check(sample, size)) {
        for (i = s; i < size - 1; i++) {
            if (sample[i] < btt.number) {
                tmp = sample[i];
                sample[i] = btt.number;
                btt.number = tmp;
                btt.index = i;
                s++;
            }
        }    
    }
}