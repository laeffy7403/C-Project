#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)
#define MAX_SIZE 20

typedef struct {
	int staffID;
	char staffName[30];
	char gender;
	char password[15];
	char passwordRecover[15];
	char position[30];
	char contactNum[12];
}Staff;

Staff staff;


/// ------------------- extra function ------------------///

int generateStaffID() {
	srand(time(NULL));
	return rand() % 999 + 1;
}

int isValidGenderStaff(char gender) {
	gender = toupper(gender);
	return gender == 'M' || gender == 'F';
}// validate to check gender 

void staffHorizontalLine() {
	printf("---------------------------------------------------------------------------------------------------------------\n");
}
/// ----------------- main function -------------------///


void staffCreate() {
	int count = 0;
	FILE* ptr, * ptrC;
	//ptr = fopen("c:\\PCD_Assign\\staff.dat", "ab");
	//ptrC = fopen("c:\\PCD_Assign\\staff.dat", "rb");
	ptr = fopen("staff.dat", "ab");
	ptrC = fopen("staff.dat", "rb");

	if (ptr == NULL || ptrC == NULL) {
		printf("member.dat file unable to open\n");
		exit(-1);
	}

	while (fread(&staff, sizeof(Staff), 1, ptrC)) {
		count++;
	}

	fclose(ptrC);

	int randomCode = generateStaffID();
	staff.staffID = randomCode;

	printf("Enter new staff name: ");
	scanf(" %29[^\n]", staff.staffName); rewind(stdin);

	int validInput = 0;

	while (!validInput) {
		printf("Enter staff gender (M/F): ");
		if (scanf(" %c", &staff.gender) != 1 || !isValidGenderStaff(staff.gender)) {
			printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n"); rewind(stdin);
		}
		else {
			validInput = 1; // Set flag to exit loop
		}
	}

	printf("Enter new password (15 lenght): ");
	scanf(" %s", staff.password); rewind(stdin);

	printf("Enter password recovery (15 lenght): ");
	scanf(" %s", staff.passwordRecover); rewind(stdin);

	printf("Assign position :");
	scanf(" %[^\n]", staff.position); rewind(stdin);

	printf("Enter contact number (+60): ");
	scanf(" %s", staff.contactNum); rewind(stdin);

	printf("Staff Id: S%03d\n", staff.staffID);

	fwrite(&staff, sizeof(Staff), 1, ptr);
	printf("New records successfully added.\n\n");

	fclose(ptr);
}

void staffRead() {
	int cntRec = 0;

	FILE* fptr;
	fptr = fopen("staff.dat", "rb");

	if (fptr == NULL) {
		printf("staff.dat file open error for display\n");
		exit(-1);
	}
	staffHorizontalLine();
	printf("StaffID |     Employees     |  Gender  |  Password  |  Password Recovery  |      Position      | Contact\n");
	staffHorizontalLine();
	while (fread(&staff, sizeof(Staff), 1, fptr)) {
		cntRec++;
		printf("%02d. S%03d |   %12s   | %5c    | %10s | %19s | %18s | %s\n", cntRec, staff.staffID,
			staff.staffName, staff.gender, staff.password, staff.passwordRecover, staff.position, staff.contactNum);
	}
	staffHorizontalLine();

	fclose(fptr);
	printf("< %d staff listed >\n\n", cntRec);
};

void staffUpdate() {
	Staff staff[20];
	int pCount = 0;
	int inId;

	FILE* fptr;
	fptr = fopen("staff.dat", "rb");
	if (fptr == NULL) {
		printf("staff.dat file open error for modify\n");
		exit(-1);
	}

	while (fread(&staff[pCount], sizeof(Staff), 1, fptr)) {
		pCount++;//record count ++
	}

	fclose(fptr);

	Staff userInput;
	char mod = 'Y';
	int modcnt = 0;

	int found = 0;

	printf("Enter staff ID to update (press '0' to cancel..) : S");
	scanf(" %d", &inId); rewind(stdin);

	//loop to check whether product code exist in the record against user input
	for (int i = 0; i < pCount; i++) {

		if (inId == staff[i].staffID) {
			found = 1;

			printf("Enter new staff name: ");
			scanf(" %29[^\n]", staff[i].staffName); rewind(stdin);

			int validInput = 0;

			while (!validInput) {
				printf("Enter staff gender (M/F): ");
				if (scanf(" %c", &staff[i].gender) != 1 || !isValidGenderStaff(staff[i].gender)) {
					printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n");
					rewind(stdin); // Clear input buffer
				}
				else {
					validInput = 1; // Set flag to exit loop
				}
			}

			printf("Enter new password (15 lenght): ");
			scanf(" %s", staff[i].password); rewind(stdin);

			printf("Enter password recovery (15 lenght): ");
			scanf(" %s", staff[i].passwordRecover); rewind(stdin);

			printf("Assign position :");
			scanf(" %[^\n]", staff[i].position); rewind(stdin);

			printf("Enter contact number (+60): ");
			scanf(" %s", staff[i].contactNum); rewind(stdin);

			modcnt++;
		}

	}
	if (!found) {
		printf("Staff ID S%03d not found\n\n", inId);
	}

	if (modcnt > 0) {
		FILE* fptr;
		fptr = fopen("staff.dat", "wb");
		if (fptr == NULL) {
			printf("member.dat file open error for modify\n");
			exit(-1);
		}

		fwrite(&staff, sizeof(Staff), pCount, fptr);

		fclose(fptr);
	}
	printf("\n< %d records updated >\n\n", modcnt);
}

void staffDelete() {
	Staff staff[20];
	int pCount = 0;

	FILE* fptr;
	fptr = fopen("staff.dat", "rb");
	if (fptr == NULL) {
		printf("Error opening staff.dat file for delete\n");
		exit(EXIT_FAILURE);
	}


	while (fread(&staff[pCount], sizeof(Staff), 1, fptr)) {
		pCount++;
	}

	fclose(fptr);

	int staffIdToDelete;
	int found = 0;

	printf("Enter staff ID to delete (press '0' to cancel..) : S");
	scanf(" %d", &staffIdToDelete);
	rewind(stdin);

	// Loop to search for the member with the specified ID
	for (int i = 0; i < pCount; i++) {
		if (staffIdToDelete == staff[i].staffID) {
			found = 1;
			// Shift the array elements to overwrite the deleted member
			for (int j = i; j < pCount - 1; j++) {
				staff[j] = staff[j + 1];
			}
			pCount--; // Decrement record count
			printf("Staff ID S%03d deleted successfully.\n", staffIdToDelete);
			break;
		}
	}

	if (!found) {
		printf("Staff ID S%03d not found.\n", staffIdToDelete);
	}
	else {

		fptr = fopen("staff.dat", "wb");
		if (fptr == NULL) {
			printf("Error opening staff.dat file for delete\n");
			exit(EXIT_FAILURE);
		}

		fwrite(&staff, sizeof(Staff), pCount, fptr);
		fclose(fptr);
	}
}

void staffSearch() {
	Staff staff[20]; // Declare Member array
	int count = 0;
	int inId;
	FILE* fptr;
	fptr = fopen("staff.dat", "rb");

	if (fptr == NULL) {
		printf("staff.dat file open error for display\n");
		exit(-1);
	}

	while (fread(&staff[count], sizeof(Staff), 1, fptr)) {
		count++;
	}

	fclose(fptr);

	printf("Enter staff ID to search (press '0' to cancel..) : S");
	scanf("%d", &inId);
	rewind(stdin);

	printf("StaffID |     Username     |  Gender  |  Password  |  Password Recovery  |      Position      | Contact\n");

	staffHorizontalLine();

	for (int i = 0; i < count; i++) {
		if (inId == staff[i].staffID) {
			printf("%02d. B%03d |   %12s   | %5c    | %10s | %19s | %s | %s \n", i + 1, staff[i].staffID,
				staff[i].staffName, staff[i].gender, staff[i].password, staff[i].passwordRecover, staff[i].position, staff[i].contactNum);
			// Assuming only one member can have the same ID, so we break after finding the member
			break;
		}
	}
	staffHorizontalLine();
}

void staffMenu() {
	int select;

	printf("Staff Info - Select module\n===================\n'1' - Create\n'2' - Retrieve\n'3' - Update\n'4' - Delete\n'5' - Search\n'0' - Back to main menu\n===================\n>>");
	scanf(" %d", &select); rewind(stdin);

	if (select == 1) {
		system("cls");
		printf("continue?\n'1' - Proceed\n'0' - Back to staff menu\n>>");
		scanf("%d", &select);
		if (select == 1) {
			system("cls");
			staffCreate();
			staffMenu();
		}
		else {
			system("cls");
			printf("Create staff cancel..\n");
			staffMenu();
		}
	}
	else if (select == 2) {
		system("cls");
		staffRead();
		staffMenu();

	}
	else if (select == 3) {
		system("cls");
		staffRead();
		staffUpdate();
		staffMenu();
	}
	else if (select == 4) {
		system("cls");
		staffRead();
		staffDelete();
		staffMenu();
	}
	else if (select == 5) {
		system("cls");
		staffRead();
		staffSearch();
		staffMenu();
	}
	else if (select == 0) {
		system("cls");
		printf("logout from member page..\n");
		printf("Out..\n");
	}
	else {
		system("cls");
		staffMenu();
	}
}


void staffInfo() {
	staffMenu();
	//staffCreate();
	//staffRead();
	//staffUpdate();
	//staffDelete();
	//staffRead();
	//staffSearch();
}