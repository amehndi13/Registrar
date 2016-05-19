/* Homework 1a, 600.120 Spring 2015
 * JHED: amehndi1
 * Name: Anuj Mehndiratta
 * Date: February 8th, 2016
 *  */

#include <stdio.h>
#include <string.h>

#define LENGTH 16

int main(int argc, char* argv[])
{
	if (argc < 2) {  //user forgot to give us a filename at command line
		printf("Usage: ./a.out filename\n");
		return 1; //exit program
	}

	FILE* infile = fopen(argv[1], "r");
	FILE* outfile = fopen("courseInts.txt", "w");

	char course[LENGTH];
	unsigned int coursenum;

    while (fscanf(infile, "%s", course) != EOF) {

    
    //	strncpy(course, argv[1], LENGTH);  // copy to course string
    	course[LENGTH-1] = '\0';   // make sure last character is null
    	printf("%s  ", course);  // echo input
		char divisions[] = {'S', 'U', 'D', 'N', 'E', 'H', 'Y', 'A', '\0'};
		char grades[] = {'A', 'B', 'C', 'D', 'F', 'I', 'S', 'U', '\0'};
		char grade = course[10];
		int division=0;
		char x = course[1];
		for (int i = 0; i <= 7; i++) {
			if (x == divisions[i]) {
				division = i;
			}
		}
		coursenum = division;
		coursenum = coursenum<<29;

		int grade_bit = 0;
		for (int i = 0; i <= 7; i++) {
			if (grade ==  grades[i]) {
				grade_bit = i;
			}
		}
	
		int department_digit_one = course[3]-'0';
		int department_digit_two = course[4]-'0';
		int department_digit_three = course[5]-'0';
		int departmentnum = department_digit_one*100 + department_digit_two*10 + department_digit_three;
		departmentnum = departmentnum<<19;
		coursenum = coursenum|departmentnum;
		int course_digit_one = course[7]-'0';
		int course_digit_two = course[8]-'0';
		int course_digit_three = course[9]-'0';
		int course_num = course_digit_one*100 + course_digit_two*10 + course_digit_three;
		course_num = course_num<<9;
		coursenum = coursenum|course_num;
		int credits = course[12]-'0';
		int credit_decimal = course[14]-'0';
		if (credit_decimal == 0) {
			credit_decimal = 0;
		} else {
			credit_decimal = 1;
		}	
		grade_bit = grade_bit<<6;
		coursenum = coursenum|grade_bit;
		int grade_denomination = 0;
		if (course[11] == '/')	{
			grade_denomination = 2;
			//printf("Division: %d\nDepartment: %d%d%d\nCourse: %d%d%d\nGrade: %d\nCredits: %d %d\n",
			//	 division, department_digit_one, department_digit_two, department_digit_three, course_digit_one, 
			//	 course_digit_two, course_digit_three, grade_bit, credits, credit_decimal);
		}
		else if (course[11] == '+') {
			grade_denomination = 0;
			//printf("Division: %d\nDepartment: %d%d%d\nCourse: %d%d%d\nGrade: %d %d\nCredits: %d %d\n",
			//	 division, department_digit_one, department_digit_two, department_digit_three, course_digit_one,
			//	 course_digit_two, course_digit_three, grade_bit, grade_denomination, credits, credit_decimal);
		}	
		else if (course[11] == '-') {
			grade_denomination = 1;
			//printf("Division: %d\nDepartment: %d%d%d\nCourse: %d%d%d\nGrade: %d %d\nCredits: %d %d\n",
			//	 division, department_digit_one, department_digit_two, department_digit_three, course_digit_one, 
			//	 course_digit_two, course_digit_three, grade_bit, grade_denomination, credits, credit_decimal);
		}
		grade_denomination = grade_denomination<<4;
		coursenum = coursenum|grade_denomination;
		credits = credits<<1;
		coursenum = coursenum|credits;
		coursenum = coursenum|credit_decimal;		
		printf("%u  ", coursenum);
		fprintf(outfile, "%u  ", coursenum);
		unsigned int temp = coursenum;
		char binaryString[33] = {'\0'};
		for (int i = 0; i < 32; i++) {
			if (temp%2==1) {
				binaryString[31-i] = '1';
			} else {
				binaryString[31 - i] = '0';
			}	
			temp = temp>>1;
		}
	
		printf("%s\n", binaryString);	
	}
	fclose(outfile);
	fclose(infile);
		
	return 0;

}
