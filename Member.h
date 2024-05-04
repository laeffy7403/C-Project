#pragma once
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

typedef struct {
	int memberID;
	char memberName[30];
	char password[20];
	char passwordRecover[20];
	char gender;
	char IC[13];
	char contactNum[13];
}Member;

Member member;

/// ------------------- extra function ------------------///

int generateMemberID() {
	srand(time(NULL));
	return rand() % 999 + 1;
}

int isValidGenderMember(char gender) {
	gender = toupper(gender);
	return gender == 'M' || gender == 'F';
} // validate to check gender 

void memberHorizontalLine() {
	printf("-----------------------------------------------------------------------------------------------------\n");
}

/// ----------------- main function -------------------///


void memberCreate() {
	int count = 0;
	FILE* ptr, * ptrC;
	ptr = fopen("member.dat", "ab");

	if (ptr == NULL) {
		printf("member.dat file unable to open\n");
		exit(-1);
	}

	//member.memberID = count + 1;
	int randomCode = generateMemberID();
	member.memberID = randomCode;

	printf("Enter new name: ");
	scanf(" %29[^\n]", member.memberName); rewind(stdin);

	int validInput = 0;

	while (!validInput) {
		printf("Enter member gender (M/F): ");
		if (scanf(" %c", &member.gender) != 1 || !isValidGenderMember(member.gender)) {
			printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n");
			rewind(stdin); // Clear input buffer
		}
		else {
			validInput = 1; // Set flag to exit loop
		}
	}

	printf("Enter new password (10 lenght): ");
	scanf(" %s", member.password); rewind(stdin);

	printf("Enter password recovery (10 lenght): ");
	scanf(" %s", member.passwordRecover); rewind(stdin);

	printf("Enter identity number (IC eg.yymmddxxxxxx): ");
	scanf(" %s", member.IC); rewind(stdin);

	printf("Enter contact number (+60): ");
	scanf(" %s", member.contactNum); rewind(stdin);

	printf("Your member Id: M%03d\n", member.memberID);

	fwrite(&member, sizeof(Member), 1, ptr);
	printf("New records successfully added.\n\n");

	fclose(ptr);
}

void memberRead() {
	//Member member;
	int cntRec = 0;

	FILE* fptr;
	fptr = fopen("member.dat", "rb");

	if (fptr == NULL) {
		printf("member.dat file open error for display\n");
		exit(-1);
	}
	memberHorizontalLine();
	printf("MemberID |     Username     |  Gender  |  Password  |  Password Recovery  |      IC      | Contact\n");
	memberHorizontalLine();
	while (fread(&member, sizeof(Member), 1, fptr)) {
		cntRec++;
		printf("%02d. M%03d |   %12s   | %5c    | %10s | %19s | %s | %s\n", cntRec, member.memberID,
			member.memberName, member.gender, member.password, member.passwordRecover, member.IC, member.contactNum);
	}
	memberHorizontalLine();

	fclose(fptr);
	printf("< %d members listed >\n\n", cntRec);
}

void memberUpdate() {
	Member member[20];
	int pCount = 0;
	int inId;

	FILE* fptr;
	//fopen("c:\\PCD_Assign\\member.dat", "rb");
	fptr = fopen("member.dat", "rb");
	if (fptr == NULL) {
		printf("member.dat file open error for modify\n");
		exit(-1);
	}

	//read all records from file & store into array "p"
	while (fread(&member[pCount], sizeof(Member), 1, fptr)) {
		pCount++;//record count ++
	}

	fclose(fptr);

	Member userInput;
	char mod = 'Y';
	int modcnt = 0;

	//do {
	int found = 0;

	printf("Enter member ID to update (press '0' to cancel..) : M");
	scanf(" %d", &inId); rewind(stdin);

	//if (userInput.memberID != 0) {
	for (int i = 0; i < pCount; i++) {

		//if there's matching product code...
		if (inId == member[i].memberID) {
			found = 1;

			printf("Enter new name: ");
			scanf(" %29[^\n]", member[i].memberName); rewind(stdin);

			int validInput = 0;

			while (!validInput) {
				printf("Enter member gender (M/F): ");
				if (scanf(" %c", &member[i].gender) != 1 || !isValidGenderMember(member[i].gender)) {
					printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n"); rewind(stdin);
				}
				else {
					validInput = 1; // Set flag to exit loop
				}
			}

			printf("Enter new password (10 lenght): ");
			scanf(" %s", member[i].password); rewind(stdin);

			printf("Enter password recovery (10 lenght): ");
			scanf(" %s", member[i].passwordRecover); rewind(stdin);

			printf("Enter identity number (IC eg.yymmddxxxxxx): ");
			scanf(" %s", member[i].IC); rewind(stdin);

			printf("Enter contact number (+60): ");
			scanf(" %s", member[i].contactNum); rewind(stdin);

			modcnt++;
		}

	}
	if (!found) {
		printf("Member ID M%03d not found\n\n", inId);
	}

	if (modcnt > 0) {
		FILE* fptr;
		fptr = fopen("member.dat", "wb");
		if (fptr == NULL) {
			printf("member.dat file open error for modify\n");
			exit(-1);
		}

		fwrite(&member, sizeof(Member), pCount, fptr);

		fclose(fptr);
	}
	printf("\n< %d records updated >\n\n", modcnt);
}

void memberDelete() {
	Member member[20];
	int pCount = 0;

	FILE* fptr;
	fptr = fopen("member.dat", "rb");
	if (fptr == NULL) {
		printf("Error opening member.dat file for delete\n");
		exit(EXIT_FAILURE);
	}

	while (fread(&member[pCount], sizeof(Member), 1, fptr) == 1) {
		pCount++;
	}

	fclose(fptr);

	int memberIdToDelete;
	int found = 0;

	printf("Enter member ID to delete (press '0' to cancel..) : M");
	scanf("%d", &memberIdToDelete);
	rewind(stdin);

	// Loop to search for the member with the specified ID
	for (int i = 0; i < pCount; i++) {
		if (memberIdToDelete == member[i].memberID) {
			found = 1;
			// Shift the array elements to overwrite the deleted member
			for (int j = i; j < pCount - 1; j++) {
				member[j] = member[j + 1];
			}
			pCount--; // Decrement record count
			printf("Member with ID M%d deleted successfully.\n", memberIdToDelete);
			break;
		}
	}

	if (!found) {
		printf("Member with ID %d not found.\n", memberIdToDelete);
	}
	else {

		fptr = fopen("member.dat", "wb");
		if (fptr == NULL) {
			printf("Error opening member.dat file for delete\n");
			exit(EXIT_FAILURE);
		}

		fwrite(&member, sizeof(Member), pCount, fptr);
		fclose(fptr);
	}
}

void memberSearch() {
	Member member[20];
	int count = 0;
	int inId;
	FILE* fptr;
	fptr = fopen("member.dat", "rb");

	if (fptr == NULL) {
		printf("member.dat file open error for display\n");
		exit(-1);
	}

	while (fread(&member[count], sizeof(Member), 1, fptr)) {
		count++;
	}

	fclose(fptr);

	printf("Enter member ID to search (press '0' to cancel..) : M");
	scanf("%d", &inId);
	rewind(stdin);

	printf("MemberID |     Username     |  Gender  |  Password  |  Password Recovery  |      IC      | Contact\n");
	memberHorizontalLine();
	for (int i = 0; i < count; i++) {
		if (inId == member[i].memberID) {
			printf("%02d. B%03d |   %12s   | %5c    | %10s | %19s | %s | %s\n", i + 1, member[i].memberID,
				member[i].memberName, member[i].gender, member[i].password, member[i].passwordRecover, member[i].IC, member[i].contactNum);
			// Assuming only one member can have the same ID, so we break after finding the member
			break;
		}
	}
	memberHorizontalLine();
}

void memberMenu() {
	int select;

	printf("Member Info - Select module\n===================\n'1' - Create\n'2' - Retrieve\n'3' - Update\n'4' - Delete\n'5' - Search\n'0' - Back to main menu\n===================\n>>");
	scanf(" %d", &select); rewind(stdin);

	if (select == 1) {
		system("cls");
		printf("continue?\n'1' - Proceed\n'0' - Back to member menu\n>>");
		scanf("%d", &select);
		if (select == 1) {
			system("cls");
			memberCreate();
			memberMenu();
		}
		else {
			system("cls");
			printf("Create member cancel..\n");
			memberMenu();
		}
	}
	else if (select == 2) {
		system("cls");
		memberRead();
		memberMenu();

	}
	else if (select == 3) {
		system("cls");
		memberRead();
		memberUpdate();
		memberMenu();
	}
	else if (select == 4) {
		system("cls");
		memberRead();
		memberDelete();
		memberMenu();
	}
	else if (select == 5) {
		system("cls");
		memberRead();
		memberSearch();
		memberMenu();
	}
	else if (select == 0) {
		system("cls");
		printf("logout from member page..\n");
		printf("Out..\n");
	}
	else {
		system("cls");
		memberMenu();
	}
}

void memberInfo() {
	memberMenu();
}