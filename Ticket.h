#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Member.h"
#include "Schedule.h"
#pragma warning (disable : 4996)
#define MAX 100

struct Date {
	int day;
	int month;
	int year;
};

struct Info {
	int seatNum;
	char coach;
	int qty;
	double amount;
	char ticketStatus[20];
};

typedef struct {
	int bookID;
	int memberID;
	int trainID;
	struct Date bookDate;
	struct Date departDate;
	struct Info Memberinfo;
}Ticketing;

Ticketing ticket;


/// ------------------- extra function ------------------///

int generateTicketID() {
	srand(time(NULL));
	return rand() % 999 + 1;
}

void TicketBookLine() {
	printf("------------------------------------------------------------------------------------------\n");
}

bool isValidDate(int day, int month, int year) {
	// Check if year, month, and day are in valid ranges
	if (year < 1900 || year > 9999 || month < 1 || month > 12 || day < 1) {
		return false;
	}

	// Determine the number of days in the month
	int daysInMonth;
	switch (month) {
	case 2:
		// Check for leap year
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			daysInMonth = 29;
		}
		else {
			daysInMonth = 28;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		daysInMonth = 30;
		break;
	default:
		daysInMonth = 31;
	}

	// Check if the day is within the valid range for the month
	return day <= daysInMonth;
}// validate the date input correctly

/// ----------------- main function -------------------///


void ticketCreate() {
	int count = 0;
	int coutR = 0;
	FILE* Cptr;
	Cptr = fopen("ticketTest.txt", "r");

	if (Cptr == NULL) {
		printf("ticket.txt file unable to open\n");
		exit(-1);
	}

	while (fscanf(Cptr, "%d | %d | %d | %d-%d-%d | %c | %d | %d | %lf | %s\n", &ticket.bookID, &ticket.memberID, &ticket.trainID,
		&ticket.bookDate.day, &ticket.bookDate.month, &ticket.bookDate.year,
		&ticket.Memberinfo.coach, &ticket.Memberinfo.seatNum,
		&ticket.Memberinfo.qty, &ticket.Memberinfo.amount,
		ticket.Memberinfo.ticketStatus) != EOF) {

		coutR++;
	}

	fclose(Cptr);

	int randomCode = generateTicketID();
	ticket.bookID = randomCode;

	printf("bookId : B%03d\n", ticket.bookID);

	printf("memberID (M001)> M");
	scanf(" %d", &ticket.memberID); rewind(stdin);

	printf("trainID (T001)> T");
	scanf(" %d", &ticket.trainID); rewind(stdin);

	while (true) {
		printf("Enter book date (eg. dd-mm-yyyy): ");
		if (scanf(" %d-%d-%d", &ticket.bookDate.day, &ticket.bookDate.month, &ticket.bookDate.year) != 3) {
			printf("Invalid input format. Please enter the date in yyyy-mm-dd format.\n");
			rewind(stdin); // Clear input buffer
			continue; // Prompt user again
		}

		// Validate book date
		if (!isValidDate(ticket.bookDate.day, ticket.bookDate.month, ticket.bookDate.year)) {
			printf("Invalid book date. Please enter a valid date.\n");
			continue; // Prompt user again
		}

		break; // Exit loop if a valid date is entered
	}

	printf("enter coach (eg. A) >");
	scanf(" %c", &ticket.Memberinfo.coach); rewind(stdin);

	printf("enter seat num (eg. %c01)> ", toupper(ticket.Memberinfo.coach));
	scanf(" %d", &ticket.Memberinfo.seatNum); rewind(stdin);

	printf("enter qty >");
	scanf(" %d", &ticket.Memberinfo.qty); rewind(stdin);

	printf("enter amount  >");
	scanf(" %lf", &ticket.Memberinfo.amount); rewind(stdin);

	count++;

	if (count == 1) {
		strcpy(ticket.Memberinfo.ticketStatus, "Booked");
	}
	else {
		strcpy(ticket.Memberinfo.ticketStatus, "Processing");
	}

	FILE* ptr;
	ptr = fopen("ticketTest.txt", "a");

	if (ptr == NULL) {
		printf("ticket.txt file unable to open\n");
		exit(-1);
	}

	fprintf(ptr, "%.03d | %.03d | %.03d | %.02d-%.02d-%d | %c | %.02d | %d | %.2lf | %s\n",
		ticket.bookID, ticket.memberID, ticket.trainID,
		ticket.bookDate.day, ticket.bookDate.month, ticket.bookDate.year,
		ticket.Memberinfo.coach, ticket.Memberinfo.seatNum,
		ticket.Memberinfo.qty, ticket.Memberinfo.amount,
		ticket.Memberinfo.ticketStatus);

	printf("records added..\n\n");
	fclose(ptr);
}

void ticketRead() {
	int count = 0;
	FILE* Rptr;
	Rptr = fopen("ticketTest.txt", "r");

	if (Rptr == NULL) {
		printf("ticket.txt file unable to open\n");
		exit(-1);
	}

	TicketBookLine();
	printf("- BookId | MemberId | TrainId | Book date | Couch | Seat | Qty | Amount(RM) | - Status\n");
	TicketBookLine();

	while (fscanf(Rptr, "%d | %d | %d | %d-%d-%d | %c | %d | %d | %lf | %s\n", &ticket.bookID, &ticket.memberID, &ticket.trainID,
		&ticket.bookDate.day, &ticket.bookDate.month, &ticket.bookDate.year,
		&ticket.Memberinfo.coach, &ticket.Memberinfo.seatNum,
		&ticket.Memberinfo.qty, &ticket.Memberinfo.amount,
		ticket.Memberinfo.ticketStatus) != EOF) {

		count++;

		printf("%02d. B%.03d   |  M%.03d    |  T%.03d   | %.02d-%.02d-%.04d |  %c   |  %.02d   |  %d  |    %.02lf   | - %s\n",
			count,
			ticket.bookID, ticket.memberID, ticket.trainID,
			ticket.bookDate.day, ticket.bookDate.month, ticket.bookDate.year,
			toupper(ticket.Memberinfo.coach), ticket.Memberinfo.seatNum,
			ticket.Memberinfo.qty, ticket.Memberinfo.amount,
			ticket.Memberinfo.ticketStatus);
	}

	TicketBookLine();

	fclose(Rptr);

	printf("< %d booking record listed >\n\n", count);
}

void ticketUpdate() {
	int inId;
	char found = 'X';
	int count = 0;
	Ticketing update;

	FILE* ptr1, * ptr2;
	ptr1 = fopen("ticketTest.txt", "r");
	ptr2 = fopen("ticketTest.txt", "r");

	if (ptr1 == NULL || ptr2 == NULL) {
		printf("staff.txt file unable to open\n");
		exit(-1);
	}

	while (fscanf(ptr1, "%d | %d | %d | %d-%d-%d | %c | %d | %d | %lf | %s\n", &ticket.bookID, &ticket.memberID, &ticket.trainID,
		&ticket.bookDate.day, &ticket.bookDate.month, &ticket.bookDate.year,
		&ticket.Memberinfo.coach, &ticket.Memberinfo.seatNum,
		&ticket.Memberinfo.qty, &ticket.Memberinfo.amount,
		ticket.Memberinfo.ticketStatus) != EOF) {

		count++;
	}

	fclose(ptr1);

	Ticketing ticket[MAX];
	TicketBookLine();
	printf("- BookId | MemberId | TrainId | Book date | Couch | Seat | Qty | Amount(RM) | - Status\n");
	TicketBookLine();

	for (int i = 0; i < count; i++) {
		fscanf(ptr2, "%d | %d | %d | %d-%d-%d | %c | %d | %d | %lf | %s\n", &ticket[i].bookID, &ticket[i].memberID, &ticket[i].trainID,
			&ticket[i].bookDate.day, &ticket[i].bookDate.month, &ticket[i].bookDate.year,
			&ticket[i].Memberinfo.coach, &ticket[i].Memberinfo.seatNum,
			&ticket[i].Memberinfo.qty, &ticket[i].Memberinfo.amount,
			ticket[i].Memberinfo.ticketStatus);

		printf("%02d. B%.03d  |  M%.03d    |  T%.03d   | %.02d-%.02d-%.04d |  %c   |  %.02d   |  %d  |    %.02lf   | - %s\n",
			i + 1,
			ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
			ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
			toupper(ticket[i].Memberinfo.coach), ticket[i].Memberinfo.seatNum,
			ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
			ticket[i].Memberinfo.ticketStatus);
	}

	TicketBookLine();

	printf("Enter Book Id to update (press '0' to cancel..) : B");
	scanf(" %d", &inId); rewind(stdin);

	for (int i = 0; i < count; i++) {
		if (inId == ticket[i].bookID) {

			int cout = 0;

			//printf("enter new bookID (B001)> B");
			//scanf(" %d", &ticket[i].bookID); rewind(stdin);

			printf("enter new memberID (M001)> M");
			scanf(" %d", &ticket[i].memberID); rewind(stdin);

			printf("enter new trainID (T001)> T");
			scanf(" %d", &ticket[i].trainID); rewind(stdin);

			while (true) {
				printf("Enter new book date (eg. dd-mm-yyyy): ");
				if (scanf(" %d-%d-%d", &ticket[i].bookDate.day, &ticket[i].bookDate.month, &ticket[i].bookDate.year) != 3) {
					printf("Invalid input format. Please enter the date in dd-mm-yyyy format.\n");
					rewind(stdin); // Clear input buffer
					continue; // Prompt user again
				}

				// Validate book date
				if (!isValidDate(ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year)) {
					printf("Invalid book date. Please enter a valid date.\n");
					continue; // Prompt user again
				}

				break; // Exit loop if a valid date is entered
			}

			printf("enter new coach (eg. A) >");
			scanf(" %c", &ticket[i].Memberinfo.coach); rewind(stdin);

			printf("enter new seat num (eg. %c01)> ", toupper(ticket[i].Memberinfo.coach));
			scanf(" %d", &ticket[i].Memberinfo.seatNum); rewind(stdin);

			printf("enter qty >");
			scanf(" %d", &ticket[i].Memberinfo.qty); rewind(stdin);

			printf("enter new amount  >");
			scanf(" %lf", &ticket[i].Memberinfo.amount); rewind(stdin);

			cout++;

			if (cout == 1) {
				strcpy(ticket[i].Memberinfo.ticketStatus, "Booked");
			}
			else {
				strcpy(ticket[i].Memberinfo.ticketStatus, "Processing");
			}

			printf("\nRecord updated..\n");
			printf("====================\n");
			printf("BookId | MemberId | TrainId | Book date | Depart date | Couch | Seat | Qty | Amount(RM) | - Status\n");
			TicketBookLine();
			printf("%d. B%.03d  |  M%.03d    |  T%.03d   | %.02d-%.02d-%.04d |  %c   |  %.02d   |  %d  |    %.02lf   | - %s\n",
				count, ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
				ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
				toupper(ticket[i].Memberinfo.coach), ticket[i].Memberinfo.seatNum,
				ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
				ticket[i].Memberinfo.ticketStatus);
			TicketBookLine();
			found = 'Y';
			break; // Exit loop after finding the train
		}
	}
	if (found == 'X') {
		printf("No such train Id found : T%03d\n\n", inId);
	}

	FILE* ptr;
	ptr = fopen("ticketTest.txt", "w");

	if (ptr == NULL) {
		printf("unable to open");
		exit(-1);
	}

	for (int i = 0; i < count; i++) {
		fprintf(ptr, "%.03d | %.03d | %.03d | %.02d-%.02d-%d | %c | %.02d | %d | %.2lf | %s\n",
			ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
			ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
			ticket[i].Memberinfo.coach, ticket[i].Memberinfo.seatNum,
			ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
			ticket[i].Memberinfo.ticketStatus);
	}

	fclose(ptr);
	fclose(ptr2);
}

void ticketDelete() {
	int count = 0;
	int inId;
	char found = 'X';
	Ticketing trash[MAX];
	//Train schedule[10];

	FILE* ptr1, * ptr2;
	ptr1 = fopen("ticketTest.txt", "r");
	ptr2 = fopen("ticketTest.txt", "r");
	if (ptr1 == NULL || ptr2 == NULL) {
		printf("unable to open file..\n");
		exit(-1);
	}

	while (fscanf(ptr1, "%d | %d | %d | %d-%d-%d | %c | %d | %d | %lf | %s\n", &ticket.bookID, &ticket.memberID, &ticket.trainID,
		&ticket.bookDate.day, &ticket.bookDate.month, &ticket.bookDate.year,
		&ticket.Memberinfo.coach, &ticket.Memberinfo.seatNum,
		&ticket.Memberinfo.qty, &ticket.Memberinfo.amount,
		ticket.Memberinfo.ticketStatus) != EOF) {

		count++;
	}

	fclose(ptr1);

	Ticketing ticket[MAX];

	printf("- BookId | MemberId | TrainId | Book date | Couch | Seat | Qty | Amount(RM) | - Status\n");

	TicketBookLine();

	for (int i = 0; i < count; i++) {
		fscanf(ptr2, "%d | %d | %d | %d-%d-%d | %c | %d | %d | %lf | %s\n",
			&ticket[i].bookID, &ticket[i].memberID, &ticket[i].trainID,
			&ticket[i].bookDate.day, &ticket[i].bookDate.month, &ticket[i].bookDate.year,
			&ticket[i].Memberinfo.coach, &ticket[i].Memberinfo.seatNum,
			&ticket[i].Memberinfo.qty, &ticket[i].Memberinfo.amount,
			ticket[i].Memberinfo.ticketStatus);

		printf("%02d. B%.03d  |  M%.03d    |  T%.03d   | %.02d-%.02d-%.04d |  %c   |  %.02d   |  %d  |    %.02lf   | - %s\n",
			i + 1,
			ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
			ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
			toupper(ticket[i].Memberinfo.coach), ticket[i].Memberinfo.seatNum,
			ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
			ticket[i].Memberinfo.ticketStatus);
	}

	TicketBookLine();

	printf("Enter booking Id to delete (press '0' to cancel..) : B");
	scanf(" %d", &inId); rewind(stdin);
	//printf("_____________________________________________\n");

	for (int i = 0; i < count; i++) {
		if (inId == ticket[i].bookID) {
			found = 'Y';

			printf("\nRecord removed..\n");
			//printf("_____________________________________________\n");
			printf("- BookId | MemberId | TrainId | Book date | Depart date | Couch | Seat | Qty | Amount(RM) | - Status\n");
			TicketBookLine();
			printf("%d. B%.03d  |  M%.03d    |  T%.03d   | %.02d-%.02d-%.04d |  %c   |  %.02d   |  %d  |    %.02lf   | - %s\n",
				i + 1, ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
				ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
				toupper(ticket[i].Memberinfo.coach), ticket[i].Memberinfo.seatNum,
				ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
				ticket[i].Memberinfo.ticketStatus);

			trash[0] = ticket[i];

			for (int j = i; j < count; j++) {
				ticket[j] = ticket[j + 1];
			}

			count--;
			break;
		}
	}
	if (found == 'X') {
		printf("No such train Id found : T%03d\n\n", inId);
	}

	FILE* ptr;
	ptr = fopen("ticketTest.txt", "w");

	if (ptr == NULL) {
		printf("unable to open");
		exit(-1);
	}

	for (int i = 0; i < count; i++) {
		fprintf(ptr, "%.03d | %.03d | %.03d | %.02d-%.02d-%d | %c | %.02d | %d | %.2lf | %s\n",
			ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
			ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
			ticket[i].Memberinfo.coach, ticket[i].Memberinfo.seatNum,
			ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
			ticket[i].Memberinfo.ticketStatus);
	}
	fclose(ptr);
	fclose(ptr2);
}

void ticketSearch() {
	int count = 0;
	int inId;

	FILE* Sptr1, * Sptr2;
	Sptr1 = fopen("ticketTest.txt", "r");
	Sptr2 = fopen("ticketTest.txt", "r");

	if (Sptr1 == NULL || Sptr2 == NULL) {
		printf("file unable to open..\n");
		exit(-1);
	}

	while (fscanf(Sptr1, "%d | %d | %d | %d-%d-%d | %c | %d | %d | %lf | %s\n", &ticket.bookID, &ticket.memberID, &ticket.trainID,
		&ticket.bookDate.day, &ticket.bookDate.month, &ticket.bookDate.year,
		&ticket.Memberinfo.coach, &ticket.Memberinfo.seatNum,
		&ticket.Memberinfo.qty, &ticket.Memberinfo.amount,
		ticket.Memberinfo.ticketStatus) != EOF) {

		count++;
	}

	fclose(Sptr1);

	Ticketing ticket[MAX];

	for (int i = 0; i < count; i++) {
		fscanf(Sptr2, "%d | %d | %d | %d-%d-%d | %c | %d | %d | %lf | %s\n", &ticket[i].bookID, &ticket[i].memberID, &ticket[i].trainID,
			&ticket[i].bookDate.day, &ticket[i].bookDate.month, &ticket[i].bookDate.year,
			&ticket[i].Memberinfo.coach, &ticket[i].Memberinfo.seatNum,
			&ticket[i].Memberinfo.qty, &ticket[i].Memberinfo.amount,
			ticket[i].Memberinfo.ticketStatus);
	}

	int found = 0;

	printf("enter booking Id (press '0' to cancel..) : B");
	scanf(" %d", &inId); rewind(stdin);

	printf("- BookId | MemberId | TrainId | Book date | Couch | Seat | Qty | Amount(RM) | - Status\n");
	TicketBookLine();
	for (int i = 0; i < count; i++) {
		if (inId == ticket[i].bookID) {
			printf("%d. B%.03d  |  M%.03d    |  T%.03d   | %.02d-%.02d-%.04d |  %c   |  %.02d   |  %d  |    %.02lf   | - %s\n",
				i + 1, ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
				ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
				toupper(ticket[i].Memberinfo.coach), ticket[i].Memberinfo.seatNum,
				ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
				ticket[i].Memberinfo.ticketStatus);

			found = 1;
		}
	}

	TicketBookLine();

	if (!found) {
		printf("no records are found T%03d\n\n", inId);
	}

	fclose(Sptr2);
}

void ticketMenu() {
	int select;

	printf("Ticket booking - Select module\n=====================\n'1' - Create\n'2' - Retrieve\n'3' - Update\n'4' - Delete\n'5' - Search\n'0' - Back to main menu\n===================\n>>");
	scanf(" %d", &select); rewind(stdin);

	if (select == 1) {
		system("cls");
		printf("continue?\n'1' - Proceed\n'0' - Back to ticket menu\n>>");
		scanf("%d", &select);
		if (select == 1) {
			system("cls");
			memberRead();
			scheduleRead();
			ticketCreate();
			ticketMenu();
		}
		else {
			system("cls");
			printf("Create ticket cancel..\n");
			ticketMenu();
		}
	}
	else if (select == 2) {
		system("cls");
		ticketRead();
		//TicketBookLine();
		ticketMenu();

	}
	else if (select == 3) {
		system("cls");
		memberRead();
		scheduleRead();
		ticketUpdate();
		//TicketBookLine();
		ticketMenu();
	}
	else if (select == 4) {
		system("cls");
		ticketDelete();
		//TicketBookLine();
		ticketMenu();
	}
	else if (select == 5) {
		system("cls");
		ticketRead();
		ticketSearch();
		//TicketBookLine();
		ticketMenu();
	}
	else if (select == 0) {
		system("cls");
		printf("logout from ticket page..\n");
		printf("Out..\n");
	}
	else {
		system("cls");
		ticketMenu();
	}
}

void ticketBooking() {
	ticketMenu();

	//ticketCreate();
	//ticketRead();
	//ticketUpdate();
	//ticketDelete();
	//ticketSearch();

}