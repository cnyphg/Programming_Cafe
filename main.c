#include "function.h"

void admin(void){
	struct sessionStructure sess;
	bool exitLoop = false;
	char inputid[10], inputtp[10];
	
	printf("Please Login to Continue: \n");
	if(userLogin("admin", inputid) == 1) {
		do {
			int choice;
			printf("Please select an option:\n");
			printf("1. New Tutor(s) Registration\n");
			printf("2. New Student(s) Registration\n");
			printf("3. Session Enrolment for Student(s)\n");
			printf("4. Programming Café Session(s) and Enrolled Student(s)\n");
			printf("5. Add New Programming Café session(s)\n");
			printf("6. Modify Programming Café Session(s)\n");
			printf("7. Back\n\n");
			printf("Your choice: ");
			if (scanf("%d", &choice) == 1) {
				
				switch (choice) {
					case 1:
						printf("----------------------------------------\n");
						printf("         Tutor Registration Page        \n");
						printf("----------------------------------------\n");
						do {
							registration("tutor");
							//whether continue to register next tutor
							char proceed[10] = "yes";
							printf("\nDo you want to register another tutor?\n[Yes/No]: ");
							if(!toProceed(proceed)){
								printf("\n");
								break;
							}printf("\n");
						} while (true);
						break;
					case 2:
						printf("----------------------------------------\n");
						printf("       Student Registration Page       \n");
						printf("----------------------------------------\n");
						do {
							registration("student");
							char proceed[10] = "yes";
							printf("\nDo you want to register another student?\n[Yes/No]: ");//whether continue to register next student
							if(!toProceed(proceed)){
								printf("\n");
								break;
							}printf("\n");
						} while (true);
						break;
					case 3:
						printf("\nPlease enter the following details for student enrolment: \n");
						printf("Student's TP Number(TPXXXXXX): ");
						getInput(inputtp);
						for (int i = 0; i < strlen(inputtp); i++) {
							inputtp[i] = toupper(inputtp[i]);
						}
						printf("Searching......\n");

						if(searchTP(inputtp)==1){
							enrolStudent(inputtp);
						}
						break;
					case 4:
						printf("\n                                    Programming Café Session and Participating Students\n");
						sessionAndParticipantList();
						break;
					case 5:
						printf("------------------------------------------------\n");
						printf("       Add New Programming Café session(s)      \n");
						printf("------------------------------------------------\n");
						do{
							addNewSession(sess.title,sess.code);
							printf("New programming session %s [%s] has been successfully added.\n", sess.title, sess.code);
							sessionList();
							char proceed[10] = "yes";
							printf("\nDo you want to register another session?\n[Yes/No]: ");//whether continue to enter next new session
							if(!toProceed(proceed)){
								printf("\n");
								break;
							}
						} while(true);
						break;

					case 6:
						modifySession();
						break;
					case 7:
						exitLoop = true;
						break;
					default:
						printf("You have entered an invalid choice. Please try again.\n");
						break;
				}
			} else {
				printf("Invalid input. Please enter a valid integer.\n\n");
				// Clear the input buffer
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
			}
		}while (!exitLoop);
	}
}

void tutor(void){
	bool exitLoop = false;
	char inputid[10];
	printf("Please Login to Continue: \n");
	if(userLogin("tutor", inputid) == 1) {
		do {
			int choice;
			printf("Please select an option:\n");
			printf("1. View your list of session(s)\n");
			printf("2. Change title\n");
			printf("3. Change password\n");
			printf("4. Back\n\n");
			printf("Your choice: ");
			if (scanf("%d", &choice) == 1) {
				switch (choice) {
					case 1:
						tutorViewSession(inputid);
						break;
					case 2:
						modifyTitle(inputid);
						break;
					case 3:
						modifyPassword("tutor.txt", inputid);
						break;
					case 4:
						exitLoop = true;
						break;
					default:
						printf("You have entered an invalid choice. Please try again.\n");
						break;
				}
			} else {
				printf("Invalid input. Please enter a valid integer.\n\n");
				// Clear the input buffer
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
			}
		}while (!exitLoop);
	}
}

void student(void){
	bool exitLoop = false;
	char inputtp[10];
	printf("Please Login to Continue: \n");
	if(userLogin("student", inputtp) == 1) {
		do {
			int choice;
			printf("Please select an option:\n");
			printf("1. View your list of session(s)\n");
			printf("2. Enrol into programming café session\n");
			printf("3. Change password\n");
			printf("4. Back\n\n");
			printf("Your choice: ");
			if (scanf("%d", &choice) == 1) {
				switch (choice) {
					case 1:
						studentViewSession(inputtp);
						break;
					case 2:
						enrolStudent(inputtp);
						break;
					case 3:
						modifyPassword("student.txt", inputtp);
						break;
					case 4:
						exitLoop = true;
						break;
					default:
						printf("You have entered an invalid choice. Please try again.\n");
						break;
				}
			} else {
				printf("Invalid input. Please enter a valid integer.\n\n");
				// Clear the input buffer
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
			}
		}while (!exitLoop);
	}
}

void mainMenu(void){
	bool exitLoop = false;
	do {
		int choice;
		printf("----------------------------------------\n");
		printf("       Welcome to Programming Café      \n");
		printf("----------------------------------------\n");
		printf("Please select an user: \n");
		printf("1. Admin\n2. Tutor\n3. Student\n4. Exit the system\n\nYour choice: ");
		if (scanf("%d", &choice) == 1) {
			printf("\n");
			
			switch (choice) {
				case 1:
					admin();
					break;
				case 2:
					tutor();
					break;
				case 3:
					student();
					break;
				case 4:
					exitLoop = true;
					break;
				default:
					printf("You have entered an invalid choice. Please try again\n\n");
					break;
			}
		}
		else {
			printf("Invalid input. Please enter a valid integer.\n\n");
			// Clear the input buffer
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	} while (!exitLoop);
}


int main(void){
	loadDefaultAdmin();
	loadDefaulTutor();
	loadDefaultSession();
	mainMenu();
	return 0;
}
