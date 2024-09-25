#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>

// declaration of struct(s)
struct adminStructure {
	char adminID[50];
	char adminPW[50];
	char adminName[50];
};

struct tutorStructure {
	char name[50];
	char tutorID[10];
	char tutorBack[10];
	char title[50];
	char password[50];
};
struct studentStructure {
	char TPNum[50];
	char TPBack[10];
	char name[50];
	char gender[50];
	char password[50];
};
struct sessionStructure {
	char code[50];
	char title[50];
	char day[50];
	char time[50];
	char location[50];
	char tutorID[50];
	char tutorName[50];
};

struct enrolStructure {
	char code[50];
	char title[50];
	char day[50];
	char time[50];
	char location[50];
	char tutorID[50];
	char tutorName[50];
	char studenttp[50];
	char studentname[50];
} ;


void getInput(char str[50]){ // Get user input
	fflush(stdin);
	fgets(str, 50, stdin);
	str[strlen(str)-1] = 0;
}

void getGender(char gender[10]){ // Get gender detail input by user
	int genderOpt = 0;
	do {
		printf("Your gender: (1.Female | 2.Male | 3.N/A)\n");
		printf("Your choice: ");
		if(scanf("%d",&genderOpt)==1){
			switch (genderOpt) {
				case 1:
					strcpy(gender, "Female");
					break;
				case 2:
					strcpy(gender, "Male");
					break;
				case 3:
					strcpy(gender, "N/A");
					break;
				default:
					printf("Invalid Input. Please Enter Again\n");
					genderOpt = 0;
					break;
			}
		}
		else {
			printf("Invalid input. Please enter a valid integer.\n\n");
			// Clear the input buffer
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	} while (genderOpt==0);
}

void passwordAllocation(char password[50]){ // generating new password
	int hasLetter = 0, hasNumber = 0;
	do {
		printf("Enter a password: ");
		printf("(password has to be at least 8 characters long and consists of both numbers and letters)\n");
		printf("Your password: ");
		getInput(password);
		
		if (strlen(password)<8) {
			printf("Password must be at least 8 characters long. Please try again.\n");
		}
		else{
			for (int i = 0; i < strlen(password); i++) {
				if (isalpha(password[i])) {
					hasLetter = 1;
				}
				if (isdigit(password[i])) {
					hasNumber = 1;
				}
			}
		}
		if (!hasLetter || !hasNumber) {
			printf("Password must contain both letters and numbers. Please try again.\n");
			hasLetter = 0;
			hasNumber = 0;
		}
	} while (strlen(password)<8 ||!hasLetter ||!hasNumber);
	if(hasLetter && hasNumber){
		printf("Password accepted.\n");
	}
	else{
		printf("Error generating password.\n");
	}
}

bool validInputPattern(char *pattern, char input[50]){
	regex_t regex; //regular expression
	int reti = regcomp(&regex, pattern, REG_EXTENDED);
	if(reti){ //return value of regcomp
		printf("Could not compile regex\n");
	}
	
	reti = regexec(&regex, input, 0, NULL, 0);
	if(!reti){
		regfree(&regex); //free the compiled regex
		return true;
	}
	else{
		printf("Invalid format of input. Please enter again.\n\n");
		regfree(&regex); //free the compiled regex
		return false;
	}
	
}

FILE* openFile(const char* filename, const char* mode) {
	FILE* fptr = fopen(filename, mode);
	if (fptr == NULL) {
		printf("Unable to open file");
		exit(1);
	}
	return fptr;
}

bool toProceed(char proceed[10]){
	getInput(proceed);
	if(strcmp(proceed, "yes")==0||strcmp(proceed, "Yes")==0||strcmp(proceed, "Y")==0||strcmp(proceed, "y")==0){
		return true;
	}
	else if(strcmp(proceed, "no")==0||strcmp(proceed, "No")==0||strcmp(proceed, "N")==0||strcmp(proceed, "n")==0){
		return false;
	}
	else{
		printf("Invalid Input.\n\n");
		return  false;
	}
}

void loadDefaultAdmin(void){
	FILE *admin_fptr = openFile("admin.txt", "w+");
	fprintf(admin_fptr, "%s|%s|%s|\n","Name","AdminID","Password");
	fprintf(admin_fptr, "%s|%s|%s|\n","Admin","A01","1234");
	fclose(admin_fptr);
}

void loadDefaulTutor(void){
	FILE *tutor_fptr = openFile("tutor.txt", "w+");
	fprintf(tutor_fptr, "%s|%s|%s|%s|\n","TutorName","TutorID","SessionTitle","Password");
	fprintf(tutor_fptr, "%s|%s|%s|%s|\n","Albert","T01","Python Programming","albert1234");
	fprintf(tutor_fptr, "%s|%s|%s|%s|\n","Amad","T02","Java Programming","amad1234");
	fprintf(tutor_fptr, "%s|%s|%s|%s|\n","Steve","T03","C Programming","steve1234");
	fprintf(tutor_fptr, "%s|%s|%s|%s|\n","Andrew","T04","Web Development","andrew123");
	fprintf(tutor_fptr, "%s|%s|%s|%s|\n","Au Kit","T05","C Sharp Programming","aukit1234");
	fprintf(tutor_fptr, "%s|%s|%s|%s|\n","Sam","T06","C++ Programming","sam12345");
	fclose(tutor_fptr);
}

void loadDefaultSession(void){
	FILE *session_fptr = openFile("session.txt", "w+");
	fprintf(session_fptr, "%s|%s|%s|%s|%s|%s|%s|\n","Session Code","Session Title","Day","Start Time","Location","Tutor Code","Tutor Name");
	fprintf(session_fptr, "%s|%s|%s|%s|%s|%s|%s|\n","PYP101","Python Programming","Saturday","0900am","C-01-01","T01","Albert");
	fprintf(session_fptr, "%s|%s|%s|%s|%s|%s|%s|\n","JAV102","Java Programming","Sunday","0900am","C-01-02","T02","Amad");
	fprintf(session_fptr, "%s|%s|%s|%s|%s|%s|%s|\n","CPL103","C Programming","Saturday","0200pm","C-01-03","T03","Steve");
	fprintf(session_fptr, "%s|%s|%s|%s|%s|%s|%s|\n","WEB104","Web Development","Sunday","0200pm","C-01-04","T04","Andrew");
	fprintf(session_fptr, "%s|%s|%s|%s|%s|%s|%s|\n","CSP105","C Sharp Programming","Monday","0700pm","C-01-05","T05","Au Kit");
	fprintf(session_fptr, "%s|%s|%s|%s|%s|%s|%s|\n","ABC106","ABC Programming","Wednesdyay","0500pm","C-02-03","T06","Apple");
	fclose(session_fptr);
}


int userLogin(char userType[10], char inputID[50]) {
	struct tutorStructure tut;
	struct studentStructure stud;
	struct adminStructure adm;
	int flag = 0, askingCount = 0, loginSuccess = 0;
	char inputPW[50], fileName[20], askforID[50];
	
	// Set the appropriate file name based on the user type
	if (strcmp(userType, "tutor") == 0) {
		strcpy(fileName, "tutor.txt");
		strcpy(askforID, "Tutor ID(TXX): ");
	}
	else if (strcmp(userType, "student") == 0) {
		strcpy(fileName, "student.txt");
		strcpy(askforID, "TP Number(TPXXXXXX): ");
	}
	else if (strcmp(userType, "admin") == 0) {
		strcpy(fileName, "admin.txt");
		strcpy(askforID, "Admin ID: ");
	}
	
	do {
		printf("%s", askforID);
		getInput(inputID);
		for (int i = 0; i < strlen(inputID); i++) {
			inputID[i] = toupper(inputID[i]);
		}
		printf("Password: ");
		getInput(inputPW);
		
		FILE *fptr = openFile(fileName, "r");
		
		char content[100];
		fgets(content, sizeof(content), fptr); //discard the first content of text file
		while (fgets(content, sizeof(content), fptr) != NULL) {
			if (strcmp(userType, "tutor") == 0) {
				sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|", tut.name, tut.tutorID, tut.title, tut.password);
				if (strcmp(inputID, tut.tutorID) == 0) {
					if (strcmp(inputPW, tut.password) == 0) {
						flag = 1; //password match
						break;
					} else {
						flag = 2; //wrong password
					}
				}
			} else if (strcmp(userType, "student") == 0) {
				sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|",stud.name,stud.TPNum,stud.gender,stud.password);
				if (strcmp(inputID, stud.TPNum) == 0) {
					if (strcmp(inputPW, stud.password) == 0) {
						flag = 1; //password match
						break;
					} else {
						flag = 2; //wrong password
					}
				}
			} else if (strcmp(userType, "admin") == 0) {
				sscanf(content, "%[^|]|%[^|]|%[^|]|", adm.adminName, adm.adminID, adm.adminPW);
				if (strcmp(inputID, adm.adminID) == 0) {
					if (strcmp(inputPW, adm.adminPW) == 0) {
						flag = 1; //password match
						break;
					} else {
						flag = 2; //wrong password
					}
				}
			}
		}
		
		if (askingCount >= 2) { //exit the loop when user enters wrongly too many times
			printf("Too many attempts at a time. Please try again later.\n\n");
			break;
		}
		
		switch (flag) {
			case 0:
				printf("\nUser does not exist! Please try again.\n");
				askingCount++;
				break;
			case 1:
				printf("\nSuccessfully logged in...\n");
				printf("Welcome, %s!\n\n", (strcmp(userType, "tutor") == 0) ? tut.name : (strcmp(userType, "student") == 0) ? stud.name : adm.adminName);
				loginSuccess = 1;
				break;
			case 2:
				printf("\nWrong password... Please try again.\n\n");
				askingCount++;
				break;
			default:
				printf("Error!");
				break;
		}
		fclose(fptr);
	} while (flag == 2 || flag == 0);
	return loginSuccess;
}

void registration(char userType[10]) {
	if (strcmp(userType, "tutor") == 0) {
		struct tutorStructure tut;
		printf("Please enter the details below:\n");
		printf("Tutor name: ");
		getInput(tut.name);
		printf("Tutor title: ");
		getInput(tut.title);
		passwordAllocation(tut.password); // Allocate password

		// Allocate Tutor ID
		FILE *fptr = openFile("tutor.txt", "r");
		char content[100];
		fgets(content, sizeof(content), fptr); // discard the first line of the file
		int tutorNum = 0;
		while (fgets(content, sizeof(content), fptr) != NULL) {
			tutorNum++;
		} fclose(fptr);
		
		printf("Tutor ID will be auto-generated...\n");
		strcpy(tut.tutorID, "T");
		sprintf(tut.tutorBack, "%02d", tutorNum + 1);
		strcat(tut.tutorID, tut.tutorBack);
		printf("Your Tutor ID is: %s\n", tut.tutorID);
		
		fptr = openFile("tutor.txt", "a");
		fprintf(fptr, "%s|%s|%s|%s|\n", tut.name, tut.tutorID, tut.title, tut.password); // save into tutor.txt
		fclose(fptr);
		
		printf("Tutor registration completed successfully!\n");
	}
	else if (strcmp(userType, "student") == 0) {
		struct studentStructure stud;
		char fileTP[50], fileName[50], filePW[50];
		char *TPpattern = "^TP[0-9]{6}$";
		int repeat = 0;
		
		printf("Please enter the details below:\n");
		do {
			do {
				printf("Your TP Number (TPXXXXXX): ");
				getInput(stud.TPNum);
				for (int i = 0; i < strlen(stud.TPNum); i++) {
					stud.TPNum[i] = toupper(stud.TPNum[i]); //make TP uppercase
				}
			} while (!validInputPattern(TPpattern, stud.TPNum)); // check if input TP Number follows the correct format
			
			// Validation - check if user is already registered
			FILE *fptr = openFile("student.txt", "r");
			char content[100];
			fgets(content, sizeof(content), fptr); // discard the first line of the file
			while (fgets(content, sizeof(content), fptr) != NULL) {
				sscanf(content, "%[^|]|%[^|]|%[^|]|", fileName, fileTP, filePW);
				if (strcmp(stud.TPNum, fileTP) == 0) {
					printf("%s is already a registered student. Please enter again.\n\n", stud.TPNum);
					repeat = 1;
					break;
				} else {
					repeat = 0;
				}
			}
			fclose(fptr);
		} while (repeat != 0);
		
		printf("Your name: ");
		getInput(stud.name);
		getGender(stud.gender);
		passwordAllocation(stud.password); // allocate password
		
		// Save into student.txt
		FILE *fptr = openFile("student.txt", "a");
		
		fprintf(fptr, "%s|%s|%s|%s|\n", stud.name, stud.TPNum, stud.gender, stud.password);
		fclose(fptr);
		
		printf("Student registration completed successfully!\n");
	}
	else {
		printf("Registration failed.\n");
	}
}


void tutorViewSession(char inputID[10]){
	struct studentStructure stud;
	struct sessionStructure sess;

	FILE *session_fptr = openFile("session.txt", "r");
	FILE *studentEnrolled_fptr = openFile("enrolledStudent.txt", "r");
	
	char content[100], code[20];
	int flag = 0, i = 0;
	fgets(content,sizeof(content),session_fptr); //discard the first content of text file
	while (fgets(content,sizeof(content),session_fptr)!=NULL){
		sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", sess.code, sess.title, sess.day, sess.time, sess.location, sess.tutorID, sess.tutorName);
		if(strcmp(inputID, sess.tutorID)==0){
			printf("\nSearching.....\n");
			printf("Programming session for tutor %s is found.\n",inputID);
			printf("-----------------------------------------------------------------------------------------------------------------------\n");
			printf("%-15s%-15s%-20s%-25s%-15s%-15s%-15s\n","Tutor ID","Name","Session Code", "Session Title", "Day", "Start Time", "Location");
			printf("-----------------------------------------------------------------------------------------------------------------------\n");
			printf("%-15s%-15s%-20s%-25s%-15s%-15s%-15s\n", sess.tutorID, sess.tutorName, sess.code, sess.title, sess.day, sess.time, sess.location);
			printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
			strcpy(code, sess.code);
			flag = 1;
		}
	}
	printf("\nStudent(s) under the programming session %s.\n",code);
	printf("---------------------------------------\n");
	printf("%-4s%-15s%-20s\n","No","TP Number","Student Name");
	printf("---------------------------------------\n");
	char content1[200];
	fgets(content1,sizeof(content1),studentEnrolled_fptr); //discard the first content of text file
	while (fgets(content1,sizeof(content1),studentEnrolled_fptr)!=NULL){
		sscanf(content1, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", sess.code, sess.title, sess.day, sess.time, sess.location, sess.tutorID, sess.tutorName, stud.TPNum, stud.name);
		if(strcmp(inputID, sess.tutorID)==0){
			i++;
			printf("%-4d%-15s%-20s\n",i , stud.TPNum, stud.name);
			flag = 1;
		}
	}printf("---------------------------------------\n");
	printf("Total number of students: %d\n\n",i);
	
	if(flag==0){
		printf("Searching.....\n");
		printf("No session was found for tutor %s\n",inputID);
	}
	
	fclose(studentEnrolled_fptr);
	fclose(session_fptr);
}

void studentViewSession(char inputID[10]){
	struct studentStructure stud;
	struct sessionStructure sess;
	
	FILE *studentEnrolled_fptr= openFile("enrolledStudent.txt", "r");
	
	char content[100];
	int flag = 0;
	printf("\nSearching.....\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%-15s%-15s%-20s%-25s%-15s%-15s%-15s\n","Tutor ID","Tutor Name","Session Code", "Session Title", "Day", "Start Time", "Location");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");

	fgets(content,sizeof(content),studentEnrolled_fptr); //discard the first content of text file
	while (fgets(content,sizeof(content),studentEnrolled_fptr)!=NULL){
		sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", sess.code, sess.title, sess.day, sess.time, sess.location, sess.tutorID, sess.tutorName, stud.TPNum, stud.name);
		if(strcmp(inputID, stud.TPNum)==0){
			printf("%-15s%-15s%-20s%-25s%-15s%-15s%-15s\n", sess.tutorID, sess.tutorName, sess.code, sess.title, sess.day, sess.time, sess.location);
			flag = 1;
		}
	}printf("-----------------------------------------------------------------------------------------------------------------------\n");
	if(flag==1){
		printf("Programming session for student %s is found.\n",inputID);
	}
	if(flag==0){
		printf("No programming session was found for student %s.\n\n",inputID);
	}
	fclose(studentEnrolled_fptr);
}


bool enrolTutor(char inputID[10], char inputName[20]){
	// inner function in addNewSession and modify
	struct tutorStructure tut;
	char fTutor[10], fName[20];
	int flag = 0;
	
	do {
		printf("Tutor ID(TXX): ");
		getInput(inputID);
		//validation - check if tutor exist and already registered
		FILE *tutor_fptr = openFile("tutor.txt", "r");
		FILE *session_fptr = openFile("session.txt", "r");

		char content[100];
		bool tutorExist = true;
		fgets(content, sizeof(content), tutor_fptr); //discard the first content of text file
		while (fgets(content, sizeof(content), tutor_fptr)!=NULL){
			sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|", tut.name, tut.tutorID, tut.title, tut.password);
			if (strcmp(inputID, tut.tutorID) != 0){
				tutorExist = false;
			}
			else{
				tutorExist = true;
				strcpy(inputName, tut.name);
				break;
			}
		}
		if(!tutorExist){
			int choice;
			printf("Tutor %s does not exist.\n",inputID);
			printf("1. Enter again\n");
			printf("2. Register a new tutor\n");
			printf("Your choice: ");
			scanf("%d",&choice);
			printf("\n");
			if(choice==1){
				flag = 1;
			}
			else{
				registration("tutor");
				printf("New tutor(s) has been added into the system successfully.\n");
				printf("Please enter your new registered tutor ID.\n");
				flag = 1;
			}
		}
		else{ //if tutor exist, check if tutor already registered
			char content1[150];
			fgets(content1, sizeof(content1), session_fptr); //discard the first content of text file
			while (fgets(content1, sizeof(content1), session_fptr)!=NULL)
			{
				sscanf(content1, "%*[^|]|%*[^|]|%*[^|]|%*[^|]|%*[^|]|%[^|]|%[^|]|", fTutor, fName);
				if (strcmp(inputID, fTutor) == 0){
					int choice;
					printf("Tutor %s is already a registered tutor in the system.\n",fTutor);
					printf("1. Enter again\n");
					printf("2. Register a new tutor\n");
					printf("Your choice: ");
					scanf("%d",&choice);
					printf("\n");
					if(choice==1){
						flag = 1;
					}
					else{
						registration("tutor");
						printf("\n---------- New tutor(s) has been added into the system successfully ----------\n");
						printf("Please enter your new registered tutor ID.\n");
						flag = 1;
					}
					break;
				}
				else{
					flag = 0;
				}
			}
		}
	} while (flag != 0);
	if(flag==0){
		strcpy(inputName, tut.name);
	}
	return true;
}

void sessionList(void){		// inner function to display list of student (addNewSession in admin interface, enrolStudent)
	struct sessionStructure sess;
	FILE *fptr = openFile("session.txt", "r");
	
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("%-20s%-30s%-15s%-15s%-15s%-15s%-15s\n","Session Code","Session Title","Day","Start Time","Location","Tutor Code","Tutor Name");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	
	char content[100];
	fgets(content,sizeof(content),fptr); //discard the first content of text file
	while (fgets(content,sizeof(content),fptr)!=NULL)
	{
		sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", sess.code, sess.title, sess.day, sess.time, sess.location, sess.tutorID, sess.tutorName);
		printf("%-20s%-30s%-15s%-15s%-15s%-15s%-15s\n", sess.code, sess.title, sess.day, sess.time, sess.location, sess.tutorID, sess.tutorName);
	}
	fclose(fptr);
	printf("-------------------------------------------------------------------------------------------------------------------------\n\n");
}

void addNewSession(char inputCode[10], char inputSession[30]){
	struct sessionStructure sess;
	char fCode[10], fTitle[30], fDay[20], fTime[10], fLocation[10], fTutor[10], fName[30];
	int flag = 0;
	printf("Please enter the details below: \n");
	do {
		printf("Session Code: ");
		getInput(inputCode);
		//validation - check if session already existed
		FILE *session_fptr = openFile("session.txt", "r");
		
		char content[150];
		fgets(content, sizeof(content), session_fptr); //discard the first content of text file
		while (fgets(content, sizeof(content), session_fptr)!=NULL){
			sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", fCode, fTitle, fDay, fTime, fLocation, fTutor, fName);
			if (strcmp(inputCode, fCode) == 0){
				printf("%s is already existed in the system. Please enter again.\n\n",fCode);
				flag = 1;
				break;
			}
			else{
				flag = 0;
			}
		}
		fclose(session_fptr);
	} while (flag != 0);
	
	printf("Title of Session: ");
	getInput(inputSession);
	printf("Day(Monday-Sunday): ");
	getInput(sess.day);
	printf("Start Time(1200am/pm): ");
	getInput(sess.time);
	printf("Location: ");
	getInput(sess.location);
	
	// validation - check if tutor ID exist (tutor.txt) and check if tutor ID already registered in session (session.txt)
	if(enrolTutor(sess.tutorID, sess.tutorName)){
		//save into session.txt
		FILE *session_fptr = openFile("session.txt", "a");
		fprintf(session_fptr, "%s|%s|%s|%s|%s|%s|%s|\n",inputCode,inputSession,sess.day,sess.time,sess.location,sess.tutorID,sess.tutorName);
		fclose(session_fptr);
	}
}

void sessionAndParticipantList(void){	//display list of session and participating student
	struct enrolStructure enrol;
	FILE *fptr = openFile("enrolledStudent.txt", "r");
	
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("%-20s%-15s%-20s%-30s%-15s%-15s%-15s%-15s%-15s\n","Student Name","TP Number","Session Code","Session Title","Day","Start Time","Location","Tutor Code","Tutor Name");
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	char content[100];
	fgets(content,sizeof(content),fptr); //discard the first content of text file
	while (fgets(content,sizeof(content),fptr)!=NULL)
	{
		sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", enrol.code, enrol.title, enrol.day, enrol.time, enrol.location, enrol.tutorID, enrol.tutorName, enrol.studenttp, enrol.studentname);
		printf("%-20s%-15s%-20s%-30s%-15s%-15s%-15s%-15s%-15s\n", enrol.studentname, enrol.studenttp, enrol.code, enrol.title, enrol.day, enrol.time, enrol.location, enrol.tutorID, enrol.tutorName);
	}
	fclose(fptr);
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

int searchTP(char inputTP[10]){	// inner function for enrolStudent at admin interface
	struct studentStructure stud;
	int studentFlag = 0;
	do {
		FILE *studentFile = openFile("student.txt", "r");
		char content[110];
		fgets(content, sizeof(content), studentFile); // Discard the first line in the file
		while (fgets(content, sizeof(content), studentFile) != NULL) {
			sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|", stud.name, stud.TPNum, stud.gender, stud.password);
			if (strcmp(inputTP, stud.TPNum) == 0) {
				printf("Student %s is found.\n\n", inputTP);
				studentFlag = 1;
				break;
			} else {
				studentFlag = 0;
			}
		}
		
		if (studentFlag == 0) {
			printf("Student %s is not found. Please try again.\n\n", inputTP);
			break;
			fclose(studentFile);
		} else {
			fclose(studentFile);
		}
	} while (studentFlag == 0);
	return studentFlag; // 1
}

void enrolStudent(char inputTP[10]) {
	// Enrols a student into a session.
	struct studentStructure stud;
	struct sessionStructure sess;
	struct enrolStructure  enrol;
	char inputCode[20];
	int sessionFlag = 0, enrolFlag = 0;
	bool exitLoop = false;
	
	// Ask for session code that students want to enrol
	do{
			sessionList();
			printf("Please enter the session code that the student wants to join: ");
			getInput(inputCode);
			printf("Searching......\n");
			
			FILE *sessionFile = openFile("session.txt", "r");
			char sessionContent[200];
			fgets(sessionContent, sizeof(sessionContent), sessionFile); // Discard the first line in the file
			
			while (fgets(sessionContent, sizeof(sessionContent), sessionFile) != NULL) {
				sscanf(sessionContent, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", sess.code, sess.title, sess.day, sess.time, sess.location, sess.tutorID, sess.tutorName);
				if (strcmp(inputCode, sess.code) == 0) {
					printf("Session code %s is found.\n\n", inputCode);
					sessionFlag = 1;
					break;
				}
			}
			
			fclose(sessionFile);
			
		if (sessionFlag ==0){
			printf("Session code %s is not found. Please try again.\n\n", inputCode);
			return;
		}
		
		// Check if student is already enrolled in the session
		FILE *enrolFile = openFile("enrolledStudent.txt", "r");
		char enrolContent[200];
		fgets(enrolContent, sizeof(enrolContent), enrolFile); // Discard the first line in the file
		
		while (fgets(enrolContent, sizeof(enrolContent), enrolFile) != NULL) {
			sscanf(enrolContent, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", enrol.code, enrol.title, enrol.day,enrol.time, enrol.location, enrol.tutorID, enrol.tutorName,enrol.studenttp, enrol.studentname);
			if (strcmp(inputCode, enrol.code) == 0 && strcmp(inputTP, enrol.studenttp) == 0) {
				printf("Student %s has already enrolled in Programming Café session %s.\n", inputTP, inputCode);
				fclose(enrolFile);
				int choice;
				printf("1. Enter again\n");
				printf("2. Back\n");
				printf("Your choice: ");
				scanf("%d",&choice);
				printf("\n");
				if(choice==1){
					enrolFlag = 0; // Restart the loop to ask for session code again
					continue;
				} else{
					enrolFlag = 1;
					exitLoop = true;
					break;
				}
			} else {
				enrolFlag = 1;
			}
		}
		fclose(enrolFile);
	} while(enrolFlag == 0);
	
	if (exitLoop) {
		return;
	} else{
		char proceed[10] = "yes";
		printf("Confirm to enrol %s in %s [%s]?\n[Yes/No]: ", inputTP, sess.title, sess.code);
		if(toProceed(proceed)){
			// Save student enrolment info
			FILE *studentFile = openFile("student.txt", "r");
			char content[110];
			fgets(content, sizeof(content), studentFile); // Discard the first line in the file
			while (fgets(content, sizeof(content), studentFile) != NULL) {
				sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|", stud.name, stud.TPNum, stud.gender, stud.password);
				if (strcmp(inputTP, stud.TPNum) == 0) {
					FILE *enrolFileAppend = openFile("enrolledStudent.txt", "a");
					fprintf(enrolFileAppend, "%s|%s|%s|%s|%s|%s|%s|%s|%s|\n", sess.code, sess.title, sess.day, sess.time, sess.location, sess.tutorID, sess.tutorName, stud.TPNum, stud.name);
					printf("Student %s has enrolled in session %s successfully!\n\n", inputTP, inputCode);
					fclose(enrolFileAppend);
				}
			}
		} else{
			printf("\n");
			return;
		}
	}
}

void tutorList(char inputID[10]){
	struct tutorStructure tut;
	FILE *inputFile = fopen("tutor.txt", "r");
	printf("------------------------------------------------\n");
	printf("%-15s%-15s%-15s\n","Tutor ID","Name","Title");
	printf("------------------------------------------------\n");
	
	char content[100];
	fgets(content,sizeof(content),inputFile); //discard the first content of text file
	while (fgets(content,sizeof(content),inputFile)!=NULL){
		sscanf(content, "%[^|]|%[^|]|%[^|]|%*[^|]|", tut.name, tut.tutorID, tut.title);
		if(strcmp(inputID, tut.tutorID)==0){
			printf("%-15s%-15s%-25s\n", tut.tutorID, tut.name, tut.title);
		}
	}
	printf("------------------------------------------------\n\n");
	fclose(inputFile);
}

void modifyTitle(char inputID[50]){
	struct tutorStructure tut;
	bool keywordFound = false;
	FILE *inputFile = openFile("tutor.txt", "r");
	FILE *tempFile  = openFile("temp.txt", "w+");
	char content[100], proceed[10]="no";
	while (fgets(content, sizeof(content), inputFile) != NULL) {
		sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|", tut.name, tut.tutorID, tut.title, tut.password);
		// Check if the line contains the keyword
		if (strcmp(tut.tutorID, inputID)==0) {
			keywordFound = true;
			printf("Current Title: %-20s\n", tut.title);
			printf("Do you want to change your current title?\n[Yes/No]: ");
			if(toProceed(proceed)){
				printf("Please enter your new title: ");
				getInput(tut.title);
				fprintf(tempFile, "%s|%s|%s|%s|\n", tut.name, tut.tutorID, tut.title, tut.password);
				printf("The content has been modified successfully!\n");
				continue;
			}
		} fputs(content, tempFile); // Write the other line to the temporary file
	}
	fclose(inputFile);
	fclose(tempFile);
	// Rename the temporary file to replace the original input file and remove it
	rename("temp.txt", "tutor.txt");
	remove("temp.txt");
	
	if(keywordFound){
		tutorList(inputID);
	} else{
		printf("Keyword not found.\n");
	} printf("\n");
}

void modifyPassword(char fileName[20], char inputID[50]){
	struct studentStructure stud;
	bool keywordFound = false;
	FILE *inputFile = openFile(fileName, "r");
	FILE *tempFile  = openFile("temp.txt", "w+");
	char content[200], proceed[10]="no";
	while (fgets(content, sizeof(content), inputFile) != NULL) {
		sscanf(content, "%[^|]|%[^|]|%[^|]|%[^|]|", stud.name, stud.TPNum, stud.gender, stud.password);
		// Check if the line contains the keyword
		if (strcmp(stud.TPNum, inputID)==0) {
			keywordFound = true;
			printf("Current Password: %-20s\n", stud.password);
			printf("Do you want to change the current password?\n[Yes/No]: ");
			if(toProceed(proceed)){
				passwordAllocation(stud.password);
				fprintf(tempFile, "%s|%s|%s|%s|\n", stud.name, stud.TPNum, stud.gender, stud.password);
				printf("The content has been modified successfully!\n");
				continue;
			}
		} fputs(content, tempFile); // Write the other line to the temporary file
		
	}
	fclose(inputFile);
	fclose(tempFile);
	// Rename the temporary file to replace the original input file and remove it
	rename("temp.txt", fileName);
	remove("temp.txt");
	
	if(!keywordFound){
		printf("Keyword not found.\n");
	} printf("\n");
}

void modifySession(void){
	//struct studentStructure stud[50];
	struct sessionStructure sess[50];
	struct enrolStructure enrol[50];
	bool exitInnerLoop = false, sessionFound = false;
	int numSessions = 0, numEnrols = 0;
	FILE *tempFile  = openFile("temp.txt", "w+");
	//open session.txt
	FILE* sessionFile = openFile("session.txt", "r");
	char sessionContent[100];
	while (fgets(sessionContent, sizeof(sessionContent), sessionFile)!=NULL) {
		sscanf(sessionContent, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", sess[numSessions].code, sess[numSessions].title, sess[numSessions].day, sess[numSessions].time, sess[numSessions].location, sess[numSessions].tutorID, sess[numSessions].tutorName);
		numSessions++;
	}
	fclose(sessionFile);
	
	//open enrolledStudent.txt
	FILE* enrolFile = openFile("enrolledStudent.txt", "r");
	char enrolContent[100];
	while (fgets(enrolContent, sizeof(enrolContent), enrolFile)!=NULL) {
		sscanf(enrolContent, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", enrol[numEnrols].code, enrol[numEnrols].title, enrol[numEnrols].day, enrol[numEnrols].time, enrol[numEnrols].location, enrol[numEnrols].tutorID, enrol[numEnrols].tutorName, enrol[numEnrols].studenttp, enrol[numEnrols].studentname);
		numEnrols++;
	}
	fclose(enrolFile);
	do{
		printf("----------------------------------------------------------------------------------------------------------------\n");
		printf("%-4s%-20s%-30s%-15s%-15s%-15s%-15s\n","No","Session Code","Session Title","Day","Start Time","Location","Tutor Code");
		printf("----------------------------------------------------------------------------------------------------------------\n");
		for (int i=1; i<numSessions; i++) {
			printf("%-4d%-20s%-30s%-15s%-15s%-15s%-15s\n", i, sess[i].code, sess[i].title, sess[i].day, sess[i].time, sess[i].location, sess[i].tutorID);
		}
		printf("----------------------------------------------------------------------------------------------------------------\n");
		
		int n = 0;
		//ask user to choose the correct content to modify
		printf("Please choose the content that you wish to modify.\n");
		printf("Your choice: ");
		scanf("%d",&n);
		if(n>numSessions||n<1){
			printf("Invalid Input.\n");
			exitInnerLoop = true;
			return;
		}
		// Ask user to enter corrected information
		printf("Please enter the details for %s [%s].\n",sess[n].title, sess[n].code);
		printf("Day(Monday-Sunday): ");
		getInput(sess[n].day);
		printf("Start Time: ");
		getInput(sess[n].time);
		printf("Location: ");
		getInput(sess[n].location);
		for (int i=1; i<numSessions; i++) {
			fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|\n", sess[i].code, sess[i].title, sess[i].day, sess[i].time, sess[i].location, sess[i].tutorID, sess[i].tutorName);
			sessionFound = true;
		}
		fclose(tempFile);
		remove("session.txt");
		rename("temp.txt", "session.txt");
		/*
		for (int i=1; i<numEnrols; i++) {
			if(strcmp(enrol[i].code, sess[n].code)==0){
				fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%s|%s|\n", enrol[n].code, enrol[n].title, sess[n].day, sess[n].time, sess[n].location, enrol[i].tutorID, enrol[i].tutorName, enrol[i].studenttp, enrol[i].studentname);
				continue;
			}
			fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%s|%s|\n", enrol[i].code, enrol[i].title, enrol[i].day, enrol[i].time, enrol[i].location, enrol[i].tutorID, enrol[i].tutorName, enrol[i].studenttp, enrol[i].studentname);
			enrolFound = true;
		}
		fclose(tempFile);
		remove("enrolledStudent.txt");
		rename("temp.txt", "enrolledStudent.txt");
		*/
		printf("The content has been modified successfully!\n\n");
		//display the latest list
		printf("----------------------------------------------------------------------------------------------------------------\n");
		printf("%-4s%-20s%-30s%-15s%-15s%-15s%-15s\n","No","Session Code","Session Title","Day","Start Time","Location","Tutor Code");
		printf("----------------------------------------------------------------------------------------------------------------\n");
		for (int i=1; i<numSessions; i++) {
			printf("%-4d%-20s%-30s%-15s%-15s%-15s%-15s\n", i, sess[i].code, sess[i].title, sess[i].day, sess[i].time, sess[i].location, sess[i].tutorID);
		}
		printf("----------------------------------------------------------------------------------------------------------------\n");
		return;
		printf("\n");
	} while(!exitInnerLoop);
}


void modifyOrDeleteSession(void){
	//struct studentStructure stud[50];
	struct sessionStructure sess[50];
	struct tutorStructure tut[50];
	bool exitInnerLoop = false, sessionFound = false;
	int numSessions = 0, numTutors = 0;
	FILE *tempFile  = openFile("temp.txt", "w+");
	//open session.txt
	FILE* sessionFile = openFile("session.txt", "r");
	char sessionContent[100];
	while (fgets(sessionContent, sizeof(sessionContent), sessionFile)!=NULL) {
		sscanf(sessionContent, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|", sess[numSessions].code, sess[numSessions].title, sess[numSessions].day, sess[numSessions].time, sess[numSessions].location, sess[numSessions].tutorID, sess[numSessions].tutorName);
		numSessions++;
	}
	fclose(sessionFile);
	//open tutor.txt
	FILE* tutorFile = openFile("tutor.txt", "r");
	char tutorContent[100];
	while (fgets(tutorContent, sizeof(tutorContent), tutorFile)!=NULL) {
		sscanf(tutorContent, "%[^|]|%[^|]|%*[^|]|%*[^|]|", tut[numTutors].name, tut[numTutors].tutorID);
		numTutors++;
	}
	fclose(tutorFile);
	do{
		
		printf("----------------------------------------------------------------------------------------------------------------\n");
		printf("%-4s%-20s%-30s%-15s%-15s%-15s%-15s\n","No","Session Code","Session Title","Day","Start Time","Location","Tutor Code");
		printf("----------------------------------------------------------------------------------------------------------------\n");
		for (int i=1; i<numSessions; i++) {
			printf("%-4d%-20s%-30s%-15s%-15s%-15s%-15s\n", i, sess[i].code, sess[i].title, sess[i].day, sess[i].time, sess[i].location, sess[i].tutorID);
		}
		printf("----------------------------------------------------------------------------------------------------------------\n");
		
		int n = 0;
		//ask user to choose the correct content to modify
		printf("Please choose the content that you wish to modify.\n");
		printf("Your choice: ");
		scanf("%d",&n);
		if(n>numSessions||n<1){
			printf("Invalid Input.\n");
			exitInnerLoop = true;
			return;
		}

		//ask user whether to modify or delete the content
		int choice = 0;
		printf("Do you want to modify or delete the content?\n");
		printf("1. Modify\n");
		printf("2. Delete\n");
		printf("3. Back\n");
		printf("Your choice: ");
		if (scanf("%d", &choice) == 1) {
			switch (choice) {
				case 1:
					// Ask user to enter corrected information
					printf("Please enter the details for %s [%s].\n",sess[n].title, sess[n].code);
					printf("Day(Monday-Sunday): ");
					getInput(sess[n].day);
					printf("Start Time: ");
					getInput(sess[n].time);
					printf("Location: ");
					getInput(sess[n].location);
					for (int i=1; i<numSessions; i++) {
						fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|\n", sess[i].code, sess[i].title, sess[i].day, sess[i].time, sess[i].location, sess[i].tutorID, sess[i].tutorName);
						sessionFound = true;
					}
					printf("The content has been modified successfully!\n\n");
					fclose(tempFile);
					// Rename the temporary file to replace the original input file and remove it
					rename("temp.txt", "session.txt");
					remove("temp.txt");
					//display the latest list
					printf("----------------------------------------------------------------------------------------------------------------\n");
					printf("%-4s%-20s%-30s%-15s%-15s%-15s%-15s\n","No","Session Code","Session Title","Day","Start Time","Location","Tutor Code");
					printf("----------------------------------------------------------------------------------------------------------------\n");
					for (int i=1; i<numSessions; i++) {
						printf("%-4d%-20s%-30s%-15s%-15s%-15s%-15s\n", i, sess[i].code, sess[i].title, sess[i].day, sess[i].time, sess[i].location, sess[i].tutorID);
					}
					printf("----------------------------------------------------------------------------------------------------------------\n");
					return;
				case 2:
					printf("\nAre you sure you want to delete the content above?\n[Yes/No]: ");
					char proceed[10]="no";
					if(toProceed(proceed)){
						numSessions--;
						for (int i=1; i<numSessions; i++) {
							if(strcmp(sess[i].code, sess[n].code)==0){
								sess[i] = sess[i+1];
								sessionFound = true;
							} else{
								fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|\n", sess[i].code, sess[i].title, sess[i].day, sess[i].time, sess[i].location, sess[i].tutorID, sess[i].tutorName);
							}
						}
												
						printf("The content has been removed successfully!\n\n");
						fclose(tempFile);
						if(sessionFound){
							rename("temp.txt", "session.txt");
							remove("temp.txt");
						}
					}
					break;
				case 3:
					printf("\n");
					exitInnerLoop = true;
					continue;
				default:
					printf("You have entered an invalid choice. Please try again.\n");
					continue;;
			}
		}
		else {
			printf("Invalid input. Please enter a valid integer.\n\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		} printf("\n");
		
	} while(!exitInnerLoop);
}
