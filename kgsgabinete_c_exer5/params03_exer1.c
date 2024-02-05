//params03_exer1.c
//Exercise: Fill-in the blanks to make this program work like params03.c
#include<stdio.h>

void input(int *a, int n){ //should get user inputs for n integers
						// and store it in "array a in main"
	for(int i=0;i<n;i++) {
		printf("Enter an integer: ");
		scanf("%i",&a[i]);
	}

}

void output(int *a, int n){ //should print n integers from "array a in main"
	for(int i=0;i<n;i++) {
		printf("a[%i]==%i\n",i, a[i]);
	}	
}


int main(){
	int i, n=5;
	int a[n];
	
	//#1 do this in the input function
	//get user inputs for n integers and store it into array a

	
	input(a, n); // pass array variable a as parameter into input function
					
	
	
	//#2 do this in the output function
	//display the contents of array a

	
	output(a, n);// pass array variable a as parameter into output function
}
					