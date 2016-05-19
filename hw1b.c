#include <stdio.h>
#include <string.h>

int toString(unsigned int x);
int count;
 
int main(void){
    char userinput[1];
    do {
        printf("n - display the total number of courses\n");
        printf("d - list all courses from a particular department\n");
        printf("l - list all courses with a particular letter grade\n");
        printf("c - list all courses with at least a specified number of credits in decimal form\n");
        printf("g - compute the GPA of all the courses with letter grades\n");
        printf("q - quit the program\n");
        printf("Enter letter choice --> ");
        scanf("%s", userinput);
        if(userinput[0] == '\n') {
            scanf("%s", userinput);
        } 
        else if(userinput[0]=='n' || userinput[0]=='N') {
            count = 0;
            FILE* infile = fopen("courseInts.txt","r");
            unsigned int decimalnum;
            while (!feof(infile)) {
                fscanf(infile, "%u\n", &decimalnum);
                count++;
            }
            printf("The total number of courses: %d\n", count);
            fclose(infile);
        }
        else if (userinput[0]=='d' ||userinput[0]=='D') {
            FILE* infile = fopen("courseInts.txt","r");
            unsigned int departmentNumber;
            printf("Enter the department number: ");
            scanf("%u",&departmentNumber);
            departmentNumber = departmentNumber<<19;
            unsigned int marker = 1023; 
            marker = marker << 19;
            unsigned int decimalnum;
            while(!feof(infile)){
                fscanf(infile, "%u\n", &decimalnum);
                if((decimalnum & marker) == departmentNumber) {
                    toString(decimalnum);
                }
            }
            fclose(infile);
        }
        else if(userinput[0]=='l' || userinput[0]=='L') {
            FILE* infile = fopen("courseInts.txt","r");
            char grade[2];
            printf("Enter the letter grade: ");
            scanf("%s", grade);
            char grades[] = {'A','B','C','D','F','I','S','U','\0'};
            unsigned int encoding;
            for(unsigned int i =0; i < 8; i++){
                if(grade[0]==grades[i]){
                    encoding = i;
                }
            }
            encoding = encoding << 6;
            unsigned int marker = 448;
            unsigned int decimalnum;
            while(!feof(infile)){
                fscanf(infile, "%u\n", &decimalnum);
                if((decimalnum & marker) == encoding) {
                    toString(decimalnum);
                }
            }
            fclose(infile);
        }
        else if(userinput[0]=='c' || userinput[0]=='C') {
            FILE* infile = fopen("courseInts.txt","r");
            float  credits;
            printf("Enter the minimum number of credits: ");
            scanf("%f",&credits);
            unsigned int rep = (unsigned int) (credits*2);
            unsigned int marker = 15;
            unsigned int decimalnum;
            while(!feof(infile)){
                fscanf(infile,"%u\n",&decimalnum);
                if((decimalnum&marker)>=rep) {
                    toString(decimalnum);
                }
            }
            fclose(infile);
        }
        else if(userinput[0]=='g' || userinput[0]=='G') {
            unsigned int grade = 0;
            unsigned int credit = 0;
            int sumcredits=0;
            float points;
            float sumpoints;
            unsigned int symbol;
            unsigned int creditmarker = 15;
            unsigned int grademarker = 448;
            unsigned int symbolmarker = 48;
            FILE* infile = fopen("courseInts.txt","r");
            unsigned int decimalnum = 0;
            while(!feof(infile)){
                fscanf(infile,"%u\n", &decimalnum);
                credit = decimalnum & creditmarker;
                sumcredits+=credit;
                grade = decimalnum & grademarker;
                grade = grade>>6;
                symbol = decimalnum& symbolmarker;
                symbol = symbol>>4;
                if(grade == 0 && symbol !=1)
                    points = 4.0;
                if(grade == 0 && symbol == 1)
                    points = 3.7;
                if(grade == 1 && symbol == 0)
                    points = 3.3;
                if(grade == 1 && symbol == 2)
                    points = 3.0;
                if(grade == 1 && symbol == 1)
                    points = 2.7;
                if(grade == 2 && symbol == 0)
                    points = 2.3;
                if(grade == 2 && symbol == 2)
                    points = 2.0;
                if(grade == 2 && symbol == 1)
                    points = 1.7;
                if(grade == 3 && symbol == 0)
                    points = 1.3;
                if(grade == 3 && symbol == 2)
                    points = 1.0;
                if(grade == 3 && symbol == 1)
                    points = 0.7;
                sumpoints = sumpoints + (points*credit);
            }
            float gpa = sumpoints/sumcredits;
            printf("GPA is: %f\n", gpa);
        }
        else if(userinput[0]=='q' || userinput[0]=='Q') {
            printf("Goodbye\n");
            return 0;
        }
    } while(userinput[0]!= 'q');
    return 0;
}

int toString(unsigned int num){
    unsigned int one = 1;
    int credit2;
    
    if((one & num) == 1)
        credit2 = 5;
    else
        credit2 = 0;
    unsigned int fourteen = 14;
    unsigned int credit = num & fourteen;
    
    credit = credit >> 1;
    int credit1 = credit;
    unsigned int fourtyeight = 48;
    unsigned int symbol = num & fourtyeight;
    symbol = symbol >> 4;
    char gradedesignation;
    
    if (symbol== 0)
        gradedesignation='+';
    if (symbol==1)
        gradedesignation='-';
    else
        gradedesignation='/';

    unsigned int fourfortyeight = 448;
    unsigned int grade = fourfortyeight & num;
    
    grade = grade>>6;
    
    char grades[] = {'A','B','C','D','F','I','S','U','\0'};
    char gr = grades[grade];
    unsigned int fivehundredgrand = 523776;
    unsigned int coursenum = fivehundredgrand & num;
    
    coursenum = coursenum >> 9;
    
    int creditnum = coursenum;
    unsigned int fivehundredmillion = 536346624;
    unsigned int depnum = fivehundredmillion & num;
    
    depnum = depnum >> 19;
    
    int dnum = depnum;
    unsigned int seventh = 3758096384;
    unsigned int division = seventh&num;
    
    division = division >> 29;
    
    char divisions[] = {'S','U','D','N','E','H','Y','A','\0'};
    char letter2 = divisions[division];
    char divisions2[] = {'A','B','E','E','M','P','P','S','\0'};
    char letter1 = divisions2[division];
    printf("%c%c.%03d.%03d%c%c%d.%d\n",letter1, letter2, dnum, creditnum, gr, gradedesignation, credit1, credit2);
    
    return 0;
}

