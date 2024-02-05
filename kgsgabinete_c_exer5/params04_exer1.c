//params04_exer1.c
//Exercise: Fill-in the blanks to make this program work like params04.c

#include<stdio.h>
#include<malloc.h> //for malloc function
#include<stdlib.h> //for exit function

void input( int *a , int n){ //should get user inputs for n integers
						// and store it in the dynamic "array a in main"

	for(int i=0;i<n;i++) {
		printf("Enter an integer: ");
		scanf("%i",&a[i]);
	}

}

void output(int *a, int n){ //should print n integers from "array a in main"
	for(int i=0;i<n;i++) {
		printf("a[%i]==%i\n",i,a[i]);
	}
}

int main(){
	int i, n=5;
	//int a[n];
	
	//dynamic allocation using a pointer "int *a"
	//"int *a" will store the starting address of the contiguously
	//allocated space for  n integers i.e. size n*sizeof(int)
	//making "int *a" a dynamically allocated array of n integers
	int *a = (int *)malloc(n*sizeof(int));
	if (a==NULL){
		printf("insufficient allocation error\n");
		exit(1);
	}

	//#1 get user inputs for n integers and store it into array a

	input(a, n); // pass the dynamic array variable a 
				   //  as parameter to the input function
	
	
	//#2 display the contents of array a

	output(a, n);// pass the dynamic array variable a 
				   //   as parameter to the output function
	
	
	//dynamic de-allocation
	if (a!=NULL){
		free(a);  //frees or allows other programs to use the memory
				  // initially assigned to "int *a"
	}
}
