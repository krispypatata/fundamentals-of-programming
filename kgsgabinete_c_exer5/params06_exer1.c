//params06_exer1.c
//Exercise: Fill-in the blanks to make this program work like params06.c

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>


//try these alternative formal parameters
//void input(int a[2][3], int n){ //int a[2][3] DOESN'T decay to int *a

void input(int **a , int m, int n){ 
	//should get user inputs for m*n integers
	// and store it in the dynamic 2D array, a, in main
	// #1 get user inputs for m*n integers and store it into 
	// dynamic 2D array "a"
	int i, j;
	for(i=0;i<m;i++) {
		printf("\nEnter %i integers for row %i\n", n,i+1);
		for(j=0;j<n;j++) {
			printf("Enter an integer: ");
			scanf("%i",&a[i][j]);
		}		
	}
	
}

void output(int **a , int m, int n){ 
	//should print m*n integers from the 2D dynamic array, a, in main
	//#2 display the contents of the dynamic 2D array "a"
	int i, j;
	for(i=0;i<m;i++) {
		for(j=0;j<n;j++) {
			printf("%3i ",a[i][j]);
		}		
		printf("\n");
	}	
}

void chkalloc(void *p){ //checks if pointer is NULL, usually used after malloc
	if (p==NULL){
		printf("insufficient allocation error\n");
		exit(1);
	}
}

int main(){
	int i, j, m=2, n=3;

	//dynamic allocation using a pointer to a pointer
	//int **a will be an array of pointers
	//each a[i] will be an array of integers
	
	int **a = (int **)malloc(m*sizeof(int *)); // allocate m pointers
	chkalloc(a);
	for(i=0;i<m;i++){
		a[i] = (int *)malloc(n*sizeof(int)); // allocate n integers
		chkalloc(a[i]);						 // for each of the m pointers 
	}

	

	input(a, m, n); //pass the dynamic 2D array to input function

	output(a, m, n);//pass the dynamic 2D array to input function
	
	//dynamic de-allocation
	for(i=0;i<m;i++)
		if (a[i]!=NULL) free(a[i]);
	if (a!=NULL) free(a);

}
					