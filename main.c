#include <stdio.h>
#include <stdlib.h>
#include "Ticket.h"
#include "Staff.h"
#include "Schedule.h"
#include "Member.h"
#pragma warning (disable : 4996)
#define PRICE 12.20

///-------Global Variable Declaration--------//
double currency = 2000;
int memberRegister = 1;
char password[15];
char recoveryPass[15];
//int staffId;
int id;

int countPass = 3;
int countPassRecovery = 3;
int lastWarning = 1;

int memberCountPass = 3;
int memberLastWarning = 1;
int memberCountPassRecovery = 3;

///-----------------------------------------//
///---------Function Declaration-----------//

void staffAccess();
void staffRecover();
void staffPage();
void staffAddTicketBooking();

void menu();
void memberPage(int id);
void memberPort(int id);

void memberAccess();
void memberRecover();
void memberNewRegister();


void memberTicketBooking(int id);
void memberAccUpdate(int id);
void memberView(int id);
void memberViewBooking(int id);
void memberViewProfile(int id);
void memberDeleteBooking(int id);

void trainSeatNumModify(int trainID, int numDeduct);

int codeGenerator() {
	srand(time(NULL));
	return rand() % 999 + 1;
}

void horizontal() {
	printf("-----------------------------------------------------------------------------\n");
}
///----------------------------------------//
///---------Main body-----------//

void main() {
	menu();
	//trainSchedule();
	//ticketBooking();
	//memberInfo();
	//staffInfo();
}

void menu() {
	int a;

	printf("Raymond Train Station\n==================\n'1' - Member\n'2' - Staff\n'0' - Leave\n>>");
	scanf(" %d", &a); rewind(stdin);

	if (a == 1) {
		if (memberLastWarning == 1) {
			memberPort(id);
		}
		else {
			printf("please kindly contact our admin for help..(60143997304)\n");
			menu();
		}
	}

	else if (a == 2) {
		if (lastWarning == 1) {
			staffAccess();
		}
		else {
			printf("you got blocked\n");
			menu();
		}
	}
	else if (a == 0) {
		printf("Train Ticketing System out..\nSee you next time..\n");
		exit(0);
	}
	else {
		//break
		system("cls");
		menu();

	}


//exit:
	//system("train ticketing system pause..\n\n");
	//return 0;
}

void memberPort(int id) {
	int tp;

	system("cls");

	if (memberRegister == 0) {
		printf("New records added\n");
		printf("Please select '2' to access the member page with following Id : M%03d..\n", id);

		memberRegister = 2;
	}
	else if (memberRegister != 1) {
		printf("You can only registered one account..\n");
	}

	printf("Member Portal\n====================\n'1' - New account register\n'2' - Already has account\n'0' - back to menu\n>>");
	scanf(" %d", &tp); rewind(stdin);

	if (tp == 1) {
		if (memberRegister == 1) {
			memberNewRegister();
			return 0;
		}
		else {
			//printf("You can only registered one account..\n");
			memberPort(id);
			return 0;
		}

	}
	else if (tp == 2) {
		memberAccess();
		return 0;
	}
	else {
		system("cls");
		menu();
		//return 0;
	}
}

void memberPage() {
	int select;

	printf("Select your option\n======================\n'1' - Display train schedule\n'2' - Ticket booking\n'3' - Update profile\n'4' - View status\n'0' - Logout\n>>");
	scanf(" %d", &select);

	if (select == 1) {
		system("cls");
		scheduleRead();
		memberPage();
		return 0;
	}
	else if (select == 3) {
		system("cls");
		memberAccUpdate(id);
		memberPage();
		return 0;
	}
	else if (select == 2) {
		system("cls");
		memberTicketBooking(id);
		memberPage();
		return 0;
	}
	else if (select == 4) {
		system("cls");
		memberView(id);
		memberPage();
		return 0;
	}
	else {
		//leave this function
		system("cls");
		printf("logout from member page..\n");
		menu();
		return 0;
		//break;
	}
}

void memberView(int id) {
	int view;
	printf("User profile\n===============\n'1' - View profile\n'2' - View booking\n'3' - Remove booking\n'0' - Leave\n>>");
	scanf(" %d", &view); rewind(stdin);

	if (view == 1) {
		system("cls");
		memberViewProfile(id);
		memberView(id);
		//return 0;
	}
	else if (view == 2) {
		system("cls");
		memberViewBooking(id);
		memberView(id);
		//return 0;
	}
	else if (view == 3) {
		system("cls");
		memberDeleteBooking(id);
		memberView(id);
		//return 0;
	}
	else {
		// leave this function
		system("cls");
		memberPage();
		return 0;
		//break;
		//return 0;
	}
}

///------ Staff related module -------//

void staffRecover() {
	int count = 0;
	Staff staff[10];
	//char password[15];
	char recoveryPassStaff[15];
	//int staffId;

	FILE* fptr;
	fptr = fopen("staff.dat", "rb");

	if (fptr == NULL) {
		printf("staff.dat file open error for display\n");
		exit(-1);
	}

	while (fread(&staff, sizeof(Staff), 1, fptr)) {
		count++;
	}

	printf("please enter recovery password to unfreeze : ");
	scanf(" %s", recoveryPassStaff); rewind(stdin);

	for (int i = 0; i < count; i++) {
		if (countPassRecovery != 0) {
			if (strcmp(recoveryPassStaff, staff[i].passwordRecover) == 0) {
				printf("Your account got unfreeze please try login again\n");
				lastWarning = 1;
				countPass = 3;
				//countPassRecovery = 3;
				staffAccess();
				break;
			}
			else {
				printf("wrong recover password please re-enter - %d times left\n", countPassRecovery);
				countPassRecovery--;
				staffRecover();

			}
		}
		else {
			//menu();

			printf("kindly contact our admin for help..(+60143997403)\n");
			menu();
			break;
		}
	}
	fclose(fptr);
}

void staffAccess() {
	Staff staff[20];
	int count = 0;
	char passStaff[15];
	int staffId = 0;
	//int countPass = 3; 
	//int lastWarning = 3; 

	FILE* fptr;
	fptr = fopen("staff.dat", "rb");

	if (fptr == NULL) {
		printf("staff.dat file open error for display\n");
		exit(-1);
	}

	while (fread(&staff[count], sizeof(Staff), 1, fptr)) {
		count++;
	}

	fclose(fptr); // Close the file after reading

	system("cls");

	while (countPass > 0) {
		printf("Enter staff Id :S");
		scanf("%d", &staffId);
		rewind(stdin);
		if (staffId == 0) {
			system("cls");
			menu();
		}
		else {

			printf("Enter staff password : ");
			scanf("%s", passStaff);
			rewind(stdin);

			int found = 0;
			system("cls");
			for (int i = 0; i < count; i++) {
				if (strcmp(passStaff, staff[i].password) == 0 && staffId == staff[i].staffID) {
					printf("Welcome back admin!\n---------------\n");
					printf("Staff Id : S%03d\nUsername : %s\nPosition : %s\n", staff[i].staffID, staff[i].staffName, staff[i].position);
					staffPage();
					found = 1;
					break;
				}
			}

			if (!found) {
				printf("wrong password or id please re-enter - %d times left\n", countPass - 1);
				countPass--;
			}
			else {
				break; // Exit the loop if login is successful
			}
		}
	}

	if (countPass == 0) {
		char tp;
		lastWarning--;

		printf("\nYour account is frozen due to an invalid password entered streak 3 times..\n");
		printf("To recover your account press 'R' or 'O'ut (take note you will never access to staff page..) : ");
		scanf(" %c", &tp);

		if (tp == 'R' || tp == 'r') {

			staffRecover();
		}
		else {
			system("cls");
			menu();
			// Handle other actions if needed
		}
	}
}

void staffPage() {
	int a;

	printf("\nEnter option\n=====================\n'1' - Staff\n'2' - Booking\n'3' - Schedule\n'4' - Member\n'0' - Back to main menu\n=====================\n>>");
	scanf(" %d", &a); rewind(stdin);
	if (a == 1) {
		system("cls");
		staffInfo();
		staffPage();
		return 0;
	}
	else if (a == 2) {
		system("cls");
		ticketBooking();
		staffPage();
		return 0;
	}
	else if (a == 3) {
		system("cls");
		trainSchedule();
		staffPage();
		return 0;
	}
	else if (a == 4) {
		system("cls");
		memberInfo();
		staffPage();
		return 0;
	}
	else if (a == 0) {
		system("cls");
		printf("logout from staff page..\n");
		menu();
	}
	else {
		system("cls");
		staffPage();
	}
}

///------------------------------------//
///------ Member related module -------//

void memberRecover() {
	Member member[20]; // Declare Member array
	int count = 0;
	FILE* fptr;
	fptr = fopen("member.dat", "rb");

	if (fptr == NULL) {
		printf("member.dat file open error for display\n");
		exit(-1);
	}

	while (fread(&member, sizeof(Member), 1, fptr)) {
		count++;
	}

	printf("please enter recovery password to unfreeze : ");
	scanf(" %s", recoveryPass); rewind(stdin);

	for (int i = 0; i < count; i++) {
		if (memberCountPassRecovery != 0) {
			if (strcmp(recoveryPass, member[i].passwordRecover) == 0) {
				printf("Your account got unfreeze please try login again\n");
				memberLastWarning = 1;
				memberCountPass = 3;
				memberAccess();
				//countPassRecovery = 3;
				break;
			}
			else {
				printf("wrong recover password please re-enter - %d times left\n", memberCountPassRecovery);
				memberCountPassRecovery--;
				memberRecover();

			}
		}
		else {
			system("cls");
			printf("kindly contact our admin for help(+60143997403)\n");
			menu();
			break;
		}
	}


	fclose(fptr);
}

void memberAccess() {
	system("cls");
	Member member[20];
	int count = 0;
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

	int success = 0;
	while (memberCountPass > 0) {
		printf("Enter member id (Enter '0' to cancel..): M");
		scanf(" %d", &id); rewind(stdin);
		if (id == 0) {

			memberPort(id);
			return 0;
		}
		else {
			// Check if the entered ID exists in the member array
			int idExists = 0;
			for (int i = 0; i < count; i++) {
				if (id == member[i].memberID) {
					idExists = 1;
					break;
				}
			}

			if (!idExists) {
				printf("No such account exists. Please try again.\n");
				continue; // Restart the loop to allow for re-entry of ID
			}

			printf("Enter member password : ");
			scanf(" %s", password);
			rewind(stdin);

			system("cls");

			for (int i = 0; i < count; i++) {
				if (strcmp(password, member[i].password) == 0 && id == member[i].memberID) {
					printf("Welcome back %s!\n---------------\n", member[i].memberName);
					printf("Member Id : M%03d\nUsername : %s\nIdentity num : %s\nPhone num : %s\n\n", member[i].memberID, member[i].memberName, member[i].IC, member[i].contactNum);
					memberPage(id);
					success = 1;
					break;
				}
			}

			if (success) {
				break;
			}
			else {
				printf("Wrong password or member ID. %d attempts left.\n", memberCountPass - 1);
				memberCountPass--;
			}
		}
	}

	if (!success) {
		printf("Your account is frozen due to invalid password entered streak 3 times.\n");
		char tp;
		printf("To recover your account, press 'R' or 'O' to exit: ");
		scanf(" %c", &tp);

		if (tp == 'R' || tp == 'r') {
			memberRecover();
		}
		else {
			// Handle exit option
		}
	}
}

void memberAccUpdate(int id) {
	Member member[20];
	int pCount = 0;

	FILE* fptr;
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
	int found = 0;
	int a;

	printf("continue?\n'1' - Yes\n'2' - Back to menu\n>>");
	scanf(" %d", &a); rewind(stdin);

	if (a == 1) {
		for (int i = 0; i < pCount; i++) {

			if (id == member[i].memberID) {
				found = 1;

				printf("Enter new name: ");
				scanf(" %29[^\n]", member[i].memberName); rewind(stdin);

				printf("Enter contact number (+60): ");
				scanf(" %s", member[i].contactNum); rewind(stdin);
				modcnt++;
			}

		}
	}
	else {
		system("cls");
		printf("update cancel..\n");
		memberPage();
	}
	if (!found) {
		printf("There's no such product code : %d\n\n", id);
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
	printf("\n< %d records modified >\n\n", modcnt);
}

void memberTicketBooking(int id) {
	int count = 0;
	int inId;

	FILE* Sptr1, * Sptr2;
	Sptr1 = fopen("scheduleTest.txt", "r");
	Sptr2 = fopen("scheduleTest.txt", "r");

	if (Sptr1 == NULL || Sptr2 == NULL) {
		printf("file unable to open..\n");
		exit(-1);
	}

	while (fscanf(Sptr1, "%d | %s | %s | %02d:%02d %s | %02d:%02d %s | %02d-%02d-%04d |%d\n",
		&schedule.trainID, schedule.departStation, schedule.arrivalStation,
		&schedule.departTime.hour, &schedule.departTime.min, schedule.departTime.period,
		&schedule.arrivalTime.hour, &schedule.arrivalTime.min, schedule.arrivalTime.period,
		&schedule.departDate.day, &schedule.departDate.month, &schedule.departDate.year,
		&schedule.availableSeat) != EOF) {
		count++;
	}

	fclose(Sptr1);
	Train schedule[MAX];

	for (int i = 0; i < count; i++) {
		fscanf(Sptr2, "%d | %s | %s | %02d:%02d %s | %02d:%02d %s | %02d-%02d-%04d |%d\n",
			&schedule[i].trainID, schedule[i].departStation, schedule[i].arrivalStation,
			&schedule[i].departTime.hour, &schedule[i].departTime.min, schedule[i].departTime.period,
			&schedule[i].arrivalTime.hour, &schedule[i].arrivalTime.min, schedule[i].arrivalTime.period,
			&schedule[i].departDate.day, &schedule[i].departDate.month, &schedule[i].departDate.year,
			&schedule[i].availableSeat);
	}

	int found = 0;

	system("cls");

	scheduleRead();

	printf("Enter train ID to make booking (Enter '0' to cancel)>T");
	scanf(" %d", &inId); rewind(stdin);

	printf("Train ID entered: %d\n", inId);

	int temp = id;

	line();

	for (int i = 0; i < count; i++) {
		if (inId == schedule[i].trainID) {
			if (schedule[i].availableSeat > 0) {

				printf("Booking make from M%03d\nDepart station : %s - %02d:%02d %s\nArrival station : %s - %02d:%02d %s\nDepart date : %02d-%02d-%04d\nTrain ID : T%03d\n", temp,
					schedule[i].departStation, schedule[i].departTime.hour, schedule[i].departTime.min, schedule[i].departTime.period,
					schedule[i].arrivalStation, schedule[i].arrivalTime.hour, schedule[i].arrivalTime.min, schedule[i].arrivalTime.period,
					schedule[i].departDate.day, schedule[i].departDate.month, schedule[i].departDate.year,
					schedule[i].trainID);

				found = 1;
				if (found == 1) {
					while (true) {
						printf("Enter book date (eg. dd-mm-yyyy): ");
						if (scanf(" %d-%d-%d", &ticket.bookDate.day, &ticket.bookDate.month, &ticket.bookDate.year) != 3) {
							printf("Invalid input format. Please enter the date in dd-mm-yyyy format.\n");
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

					if (ticket.Memberinfo.qty > schedule[i].availableSeat) {

						printf("seat is not enough %d seat left..\n", schedule[i].availableSeat);
						memberPage();
						/// if the train seat not enough.. the system will brinig user back to the memberpage
					}
					else {
						system("cls");
						ticket.Memberinfo.amount = ticket.Memberinfo.qty * PRICE;

						char payment;

						printf("Your total amount will be Rm %.02lf\nEnter 'P'roceed to make payment > ", ticket.Memberinfo.amount);
						scanf(" %c", &payment); rewind(stdin);

						if (payment == 'P' || payment == 'p') {
							if (ticket.Memberinfo.amount <= currency) {
								currency = currency - ticket.Memberinfo.amount;
								printf("payment successful\ncurrency remaining %.2lf\n", currency);
								count = 0;
								count++;
							}
							else {
								printf("payment decline - not enought currency\n");
								memberPage();
								return 0;
							}
						}
						else {
							printf("payment decline\n");
							memberPage();
							return 0;
						}

						if (count == 1) {
							strcpy(ticket.Memberinfo.ticketStatus, "Booked");
						}
						else {
							strcpy(ticket.Memberinfo.ticketStatus, "Processing");
						}
					}
				}
				else {
					printf("order cancel..\n\n");
				}
			}
			else {
				printf("the booking is pax..\n\n");
				memberPage();
				return 0;
			}
		}
	}
	int qtyDeduct = 0;
	qtyDeduct = ticket.Memberinfo.qty;
	int trainID = inId;

	if (!found) {
		printf("no records are found T%.03d\n", inId);
		memberPage();
		return 0;

		/// if record not found just escape to memberPage 
		/// I am so stupid enough that not doing this in the first place :skull emote:
	}

	FILE* ptr;
	ptr = fopen("ticketTest.txt", "a");
	if (ptr == NULL) {
		printf("unable to open file\n");
		exit(-1);
	}

	int bookingID = codeGenerator();

	fprintf(ptr, "%.03d | %.03d | %.03d | %.02d-%.02d-%d | %c | %.02d | %d | %.2lf | %s\n",
		bookingID, temp, inId,
		ticket.bookDate.day, ticket.bookDate.month, ticket.bookDate.year,
		ticket.Memberinfo.coach, ticket.Memberinfo.seatNum,
		ticket.Memberinfo.qty, ticket.Memberinfo.amount,
		ticket.Memberinfo.ticketStatus);

	printf("records added..\n");

	//fclose(ptr);
	//fclose(Sptr2);

	trainSeatNumModify(trainID, qtyDeduct);

	fclose(ptr);
	fclose(Sptr2);
}

void memberViewBooking(int id) {
	int count = 0;

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

	printf("- BookId | MemberId | TrainId | Book date | Couch | Seat | Qty | Amount(RM) | - Status\n");

	horizontal();

	int countB = 0;

	for (int i = 0; i < count; i++) {
		if (id == ticket[i].memberID) {
			countB++;
			printf("%02d. B%.03d  |  M%.03d    |  T%.03d   | %.02d-%.02d-%.04d |  %c   |  %.02d   |  %d  |    %.02lf   | - %s\n",
				countB, ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
				ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
				toupper(ticket[i].Memberinfo.coach), ticket[i].Memberinfo.seatNum,
				ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
				ticket[i].Memberinfo.ticketStatus);

			found = 1;
		}
	}

	if (!found) {
		//printf("no records are found '%d'", inId);
	}

	fclose(Sptr2);
}

void memberViewProfile(int id) {
	Member member[20]; // Declare Member array
	int count = 0;

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

	for (int i = 0; i < count; i++) {
		if (id == member[i].memberID) {
			printf("MemberID   : B%03d\nUsername  : %12s\nGender   : %12c\nIC number : %12s\nContact number : %12s\nCurrency :%.2lf\n\n", member[i].memberID,
				member[i].memberName, member[i].gender, member[i].IC, member[i].contactNum, currency);
			//only one member can have the same ID, so we break after finding the member
			break;
		}
	}
}

void memberNewRegister() {
	int count = 0;
	FILE* ptr, * ptrC;
	ptr = fopen("member.dat", "ab");

	if (ptr == NULL) {
		printf("member.dat file unable to open\n");
		exit(-1);
	}

	int randomCode = generateMemberID();
	member.memberID = randomCode;

	printf("Enter new name: ");
	scanf(" %29[^\n]", member.memberName); rewind(stdin);

	int validInput = 0;

	while (!validInput) {
		printf("Enter member gender (M/F): ");
		if (scanf(" %c", &member.gender) != 1 || !isValidGenderMember(member.gender)) {
			printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n");
			rewind(stdin);
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

	memberRegister--;

	fclose(ptr);

	memberPort(member.memberID);
}

void trainSeatNumModify(int trainID, int numDeduct) {
	FILE* Sptr;
	Sptr = fopen("scheduleTest.txt", "r+");
	if (Sptr == NULL) {
		printf("Unable to open schedule file.\n");
		exit(-1);
	}

	Train keep[MAX];
	int count = 0;

	while (fscanf(Sptr, "%d | %s | %s | %d:%d %s | %d:%d %s | %d-%d-%d | %d\n", &keep[count].trainID, keep[count].departStation, keep[count].arrivalStation,
		&keep[count].departTime.hour, &keep[count].departTime.min, keep[count].departTime.period,
		&keep[count].arrivalTime.hour, &keep[count].arrivalTime.min, keep[count].arrivalTime.period,
		&keep[count].departDate.day, &keep[count].departDate.month, &keep[count].departDate.year,
		&keep[count].availableSeat) != EOF) {
		count++;
	};

	// Update available seat count for the specified train ID
	for (int i = 0; i < count; i++) {
		if (trainID == keep[i].trainID) {
			keep[i].availableSeat -= numDeduct;
			break; // Exit loop after updating the seat count
		}
	}

	// Rewind to the beginning of the file
	rewind(Sptr);

	for (int i = 0; i < count; i++) {
		fprintf(Sptr, "%03d | %s | %s | %d:%d %s | %d:%d %s | %d-%d-%d |%d\n", keep[i].trainID, keep[i].departStation, keep[i].arrivalStation,
			keep[i].departTime.hour, keep[i].departTime.min, keep[i].departTime.period,
			keep[i].arrivalTime.hour, keep[i].arrivalTime.min, keep[i].arrivalTime.period,
			keep[i].departDate.day, keep[i].departDate.month, keep[i].departDate.year,
			keep[i].availableSeat);
	}

	fclose(Sptr);
}

void memberDeleteBooking(int id) {
	int count = 0;
	int inId;
	char found = 'X';
	Ticketing ticket[MAX];

	FILE* ptr;
	ptr = fopen("ticketTest.txt", "r+"); // Open file for reading and writing

	if (ptr == NULL) {
		printf("unable to open file..\n");
		exit(-1);
	}

	// Read ticket records from file
	while (fscanf(ptr, "%d | %d | %d | %d-%d-%d | %c | %d | %d | %lf | %s\n",
		&ticket[count].bookID, &ticket[count].memberID, &ticket[count].trainID,
		&ticket[count].bookDate.day, &ticket[count].bookDate.month, &ticket[count].bookDate.year,
		&ticket[count].Memberinfo.coach, &ticket[count].Memberinfo.seatNum,
		&ticket[count].Memberinfo.qty, &ticket[count].Memberinfo.amount,
		ticket[count].Memberinfo.ticketStatus) != EOF) {
		count++;
	}

	// Close the file after reading
	fclose(ptr);

	memberViewBooking(id);

	printf("Enter booking Id to delete(press '0' to cancel..) : B");
	scanf("%d", &inId);
	rewind(stdin);

	// Search for the booking ID to delete
	for (int i = 0; i < count; i++) {
		if (inId == ticket[i].bookID) {
			found = 'Y';
			printf("\nBooking canceled..\n");
			printf("_____________________________________________\n");
			printf("- BookId | MemberId | TrainId | Book date | Couch | Seat | Qty | Amount(RM) | - Status\n");
			printf("%d. B%.03d  |  M%.03d    |  T%.03d   | %.02d-%.02d-%.04d |  %c   |  %.02d   |  %d  |    %.02lf   | - %s\n",
				i + 1, ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
				ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
				toupper(ticket[i].Memberinfo.coach), ticket[i].Memberinfo.seatNum,
				ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
				ticket[i].Memberinfo.ticketStatus);

			// Shift remaining elements to fill the gap
			for (int j = i; j < count - 1; j++) {
				ticket[j] = ticket[j + 1];
			}

			count--;
			break; // Exit loop after deleting the record
		}
	}

	if (found == 'X') {
		printf("No such booking ID found: %d\n\n", inId);
	}

	// Reopen file in write mode to overwrite existing content
	ptr = fopen("ticketTest.txt", "w");

	if (ptr == NULL) {
		printf("unable to open");
		exit(-1);
	}

	// Write remaining ticket records to the file
	for (int i = 0; i < count; i++) {
		fprintf(ptr, "%.03d | %.03d | %.03d | %.02d-%.02d-%d | %c | %.02d | %d | %.2lf | %s\n",
			ticket[i].bookID, ticket[i].memberID, ticket[i].trainID,
			ticket[i].bookDate.day, ticket[i].bookDate.month, ticket[i].bookDate.year,
			ticket[i].Memberinfo.coach, ticket[i].Memberinfo.seatNum,
			ticket[i].Memberinfo.qty, ticket[i].Memberinfo.amount,
			ticket[i].Memberinfo.ticketStatus);
	}

	// Close the file after writing
	fclose(ptr);
}



///------------------------------------//