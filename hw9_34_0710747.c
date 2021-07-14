#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int FIFO(int frames, int *reference) 
{
	int faults = 0;
	int page[frames];
	for (int i = 0; i < frames; i++) {
		page[i] = -1;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < frames; j++) {
			if (page[j] < 0) {
				page[j] = reference[i];
				faults++;
				break;
			}
			if (page[j] == reference[i]) {
				break;
			}
			if (j == frames - 1) {
				for (int k = 0; k < frames - 1; k++) {
					page[k] = page[k + 1];
				}
				page[j] = reference[i];
				faults++;
			}
		}
	}

	return faults;
}

int LRU(int frames, int *reference)
{
	int faults = 0;
        int page[frames];
	int count[10] = {0};
	int key = 0;
        for (int i = 0; i < frames; i++) {
                page[i] = -1;
        }
        for (int i = 0; i < 10; i++) {
                for (int j = 0; j < frames; j++) {
                        if (page[j] < 0) {
                                page[j] = reference[i];
				count[reference[i]]++;
                                faults++;
                                break;
                        }
                        if (page[j] == reference[i]) {
				count[reference[i]]++;
                                break;
                        }
			if (j == frames - 1) {
				for (int k = 0; k < frames - 1; k++) {
					if (count[page[k]] > count[page[k + 1]]) {
						key = k + 1;
					}
				}
				for (int k = key; k < frames - 1; k++) {
					page[k] = page[k + 1];
				}
				page[j] = reference[i];
				count[reference[i]]++;
				key = 0;
				faults++;
			}			
		}
	}

	return faults;
}

int main(int argv, char *argc[])
{
	srand(time(NULL));
	int frames = atoi(argc[1]);
	if (frames > 7 || frames < 1) {
		printf("the range is 1~7\n");
		return 1;
	}
	int reference[10];
	int n, m;
	printf("Reference string: ");
	for (int i = 0; i < 10; i++) {
		reference[i] = rand() % 10;
		printf("%d ", reference[i]);
	}
	printf("\n");
	n = FIFO(frames, reference);
	m = LRU(frames, reference);
	printf("page faults under FIFO algorithm: %d\n", n);
	printf("page faults under LRU algorithm: %d\n", m);

	return 0;
}
