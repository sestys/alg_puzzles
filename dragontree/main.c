#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void printMatrix(int* matrix, int c, int r){
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			printf("%i ", matrix[c *i +j]);
		}
		printf("\n");
	}
	printf("\n");
}

void getBranches(int* matrix, int* branches, int r, int c){
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c-1; j++){
			if(j == 0){
				branches[i * c] = matrix[i*c];
			} else if( matrix[i*c+j]+branches[i*c+j-1] > matrix[i*c+j]){
				branches[i*c+j] = matrix[i*c+j] + branches[i*c+j-1];
			} else {
				branches[i*c+j] = matrix[i*c+j];
			}
		}
	}
}

void sort3ints(int* a){
	int tmp;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2 - i; j++){
			if(a[j] > a[j+1]){
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
}

void findMax(int* matrix, int* branches, int* maxSum, int r, int c){
	int b[3];
	int msum;
	getBranches(matrix, branches, r, c);
	for(int i = 1; i < c; i++){
		for(int offset = 0; offset < r-2; offset++){
			b[0] = branches[offset*c+i-1];
			b[1] = branches[(offset+1)*c+i-1];
			b[2] = branches[(offset+2)*c+i-1];
			msum = matrix[offset*c+i] + matrix[(offset+1)*c+i] + matrix[(offset+2)*c+i]+
		branches[offset*c+i-1] + branches[(offset+1)*c+i-1] + branches[(offset+2)*c+i-1];
			sort3ints(b);
			if(msum > *maxSum){
				*maxSum = msum;
			}
			for(int j = offset+3; j < r; j++){
				msum += matrix[j*c+i];
				if(b[0] < branches[j*c+i-1]){
					msum = msum - b[0] + branches[j*c+i-1];
					b[0] = branches[j*c+i-1];
					sort3ints(b);
				}
				if(msum > *maxSum){
					*maxSum = msum;
				}
			}
		}
	}
}
	



int main(void){
	int r, c, l, maxSum;
	scanf("%i %i\n", &r, &c);
	int *branches, *m1, *m2, *m3, *m4;
	m1 = (int *)malloc(r*c*sizeof(int));
	m2 = (int *)malloc(r*c*sizeof(int));
	m3 = (int *)malloc(r*c*sizeof(int));
	m4 = (int *)malloc(r*c*sizeof(int));
	branches = (int *)malloc(r*c*sizeof(int));

	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			scanf("%i", &l);
			m1[i * c + j] = l;
			m2[r*(c-1-j)+ i] = l;
			m3[c*(r-1-i)+ c-1-j] = l;
			m4[r* j + r - 1 - i] = l;
		}
	}
	maxSum = INT_MIN;
	findMax(m1, branches, &maxSum,r,c);
	findMax(m2, branches, &maxSum,c,r);
	findMax(m3, branches, &maxSum,r,c);
	findMax(m4, branches, &maxSum,c,r);
	printf("%i\n", maxSum);
	free(m1);
	free(m2);
	free(m3);
	free(m4);
	free(branches);
}

