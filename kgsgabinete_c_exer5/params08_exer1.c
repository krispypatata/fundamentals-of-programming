//params08_exer1.c
//Exercise: Fill-in the blanks to make this program work like params08.c
#include<stdio.h>

struct node_tag{
	char name[20];
	float grade;
};


void input(struct node_tag *r1){ //store values for r1

	printf("What is your name? ");
	scanf("%s",r1->name);
	
	printf("What is your GWA? ");
	scanf("%f",&r1->grade);
}

void output(struct node_tag r1){ //display values of fields of r1
	printf("Name: %s\n",r1.name);
	printf("GWA: %0.2f\n",r1.grade);
}


int main(){
	struct node_tag r1;
	
	//#1 do these lines in input function
	//printf("What is your name? ");
	//scanf("%s",r1.name);
	
	//printf("What is your GWA? ");
	//scanf("%f",&r1.grade);
	
	input(&r1);
	
	
	//#2 do this in output function
	//printf("Name: %s\n",r1.name);
	//printf("GWA: %0.2f\n",r1.grade);
	
	output(r1);
	
}

