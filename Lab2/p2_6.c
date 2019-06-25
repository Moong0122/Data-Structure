#include <stdio.h>
#include <stdlib.h>

#define NUM_HW 3
#define NUM_EXAMS 2
#define MAX_ENROLL 5

typedef struct{
	char name[31];
	int progs[NUM_HW];
	int exams[NUM_EXAMS];
	int progAvg;
	double examAvg;
	double numGrade;
	char Grade;
} studentT;

typedef struct{
	studentT *students[MAX_ENROLL];
	int numEnrolled;
} courseT;


studentT *GetStudentData(){
	studentT *tmp;
	int gr;
	int i,sum_progs,sum_exam = 0;
	tmp = (studentT*)malloc(sizeof(studentT));
	
	printf("input your name: ");
	scanf("%s",tmp->name);

	for(i=0;i<NUM_HW;i++){
		printf("input program score [%d]: \n",i+1);
		scanf("%d",&tmp->progs[i]);
		sum_progs += tmp->progs[i];
	}

	for(i=0;i<NUM_EXAMS;i++){
		printf("input exams score [%d]: \n",i+1);
		scanf("%d",&tmp->exams[i]);
		sum_exam += tmp->exams[i];
	}
	tmp->progAvg = sum_progs / NUM_HW;
	tmp->examAvg = sum_exam / NUM_EXAMS;
	tmp->numGrade = (tmp->progAvg + tmp->examAvg) / 2;

	if(tmp->numGrade>=90.0){
		tmp->Grade = 'A';
	}else if(tmp->numGrade>=80.0){
		tmp->Grade = 'B';
	}else
		tmp->Grade = 'C';

	printf("=====================\n");
	sum_exam = 0;
	sum_progs = 0;

	return tmp;
}

void PrintStudentData(studentT *x){
	printf("your name: ");
	printf("%s\n",x->name);

	printf("programs score: ");
	for(int i= 0;i<NUM_HW;i++)
		printf("%d ",x->progs[i]);
	printf("\n");

	printf("exams score: ");
	for(int i= 0;i<NUM_EXAMS;i++)
		printf("%d ",x->exams[i]);
	printf("\n");

	printf("program average score: ");
	printf("%d\n",x->progAvg);

	printf("exam average score: ");
	printf("%5.1f\n",x->examAvg);

	printf("number Grade: ");
	printf("%5.1f\n",x->numGrade);

	printf("Grade: ");
	printf("%c\n",x->Grade);
	printf("=====================\n");
}

int main(){
	courseT *cs2019A;
	int i;
	cs2019A = (courseT*)malloc(sizeof(courseT));
	cs2019A->numEnrolled = 0;

	for(i=0;i<MAX_ENROLL;i++){
		cs2019A->students[i] = GetStudentData();
		cs2019A->numEnrolled++;
	}
	for(i=0; i< cs2019A->numEnrolled;i++)
		PrintStudentData(cs2019A->students[i]);

	return 0;
}