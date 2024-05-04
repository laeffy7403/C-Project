#pragma once
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)
#define MAX 20

struct Depart {
    int day;
    int month;
    int year;
};

struct Time {
    int hour;
    int min;
    char period[3]; // AM/PM
};

typedef struct {
    int trainID;
    char departStation[20];
    char arrivalStation[20];
    struct Time departTime;
    struct Time arrivalTime;
    struct Depart departDate;
    int availableSeat;
}Train;

Train schedule;


/// ------------------- extra function ------------------///

bool isValidDateA(int day, int month, int year) {
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

int generateScheduleID() {
    srand(time(NULL));
    return rand() % 999 + 1;
}

int isValidTime(const char* timeStr) {
    int hour, min;
    char period[3];
    if (sscanf(timeStr, "%d:%d %2s", &hour, &min, period) != 3) {
        return 0; // Incorrect format
    }
    if (hour < 1 || hour > 12 || min < 0 || min > 59) {
        return 0; // Hour or minute out of range
    }
    if (strcmp(period, "AM") != 0 && strcmp(period, "PM") != 0) {
        return 0; // Invalid period
    }
    return 1; // Valid time format
} //check validation on time

void line() {
    printf("---------------------------------------------------------------------------------------------\n");
}

/// ----------------- main function -------------------///


void scheduleCreate() {
    FILE* ptr;
    int count = 0;

    ptr = fopen("scheduleTest.txt", "r");

    if (ptr == NULL) {
        printf("unable to open..\n");
        exit(-1);
    }

    while (fscanf(ptr, "%d | %s | %s | %d:%d %s | %d:%d %s | %02d-%02d-%04d | %d\n", &schedule.trainID, schedule.departStation, schedule.arrivalStation,
        &schedule.departTime.hour, &schedule.departTime.min, schedule.departTime.period,
        &schedule.arrivalTime.hour, &schedule.arrivalTime.min, schedule.arrivalTime.period,
        &schedule.departDate.day, &schedule.departDate.month, &schedule.departDate.year,
        &schedule.availableSeat) != EOF) {
        count++;
    };

    fclose(ptr);

    printf("Create record\n--------------------\n");


    int randomCode = generateScheduleID();
    schedule.trainID = randomCode;

    printf("TrainId :T%03d\n", schedule.trainID);

    printf("Enter depart station: ");
    scanf("%s", schedule.departStation);

    printf("Enter arrival station: ");
    scanf("%s", schedule.arrivalStation);

    char timeStr[20];

    do {
        printf("Enter depart time (hh:mm AM/PM): ");
        scanf("%s", timeStr);
    } while (!isValidTime(timeStr));
    sscanf(timeStr, "%d:%d %2s", &schedule.departTime.hour, &schedule.departTime.min, schedule.departTime.period);

    do {
        printf("Enter arrival time (hh:mm AM/PM): ");
        scanf("%s", timeStr);
    } while (!isValidTime(timeStr));
    sscanf(timeStr, "%d:%d %2s", &schedule.arrivalTime.hour, &schedule.arrivalTime.min, schedule.arrivalTime.period);


    while (true) {
        printf("Enter depart date (eg. dd-mm-yyyy): ");
        if (scanf(" %d-%d-%d", &schedule.departDate.day, &schedule.departDate.month, &schedule.departDate.year) != 3) {
            printf("Invalid input format. Please enter the date in dd-mm-yyyy format.\n");
            rewind(stdin); // Clear input buffer
            continue; // Prompt user again
        }

        // Validate depart date
        if (!isValidDateA(schedule.departDate.day, schedule.departDate.month, schedule.departDate.year)) {
            printf("Invalid depart date. Please enter a valid date.\n");
            continue; // Prompt user again
        }

        break; // Exit loop if a valid date is entered
    }

    printf("Enter available seats: ");
    scanf(" %d", &schedule.availableSeat);


    char a;
    FILE* Cptr;
    Cptr = fopen("scheduleTest.txt", "a");

    if (Cptr == NULL) {
        printf("staff.txt file unable to open\n");
        exit(-1);
    }

    fprintf(Cptr, "%03d | %s | %s | %d:%d %s | %d:%d %s | %02d-%02d-%04d | %d\n", schedule.trainID, schedule.departStation, schedule.arrivalStation,
        schedule.departTime.hour, schedule.departTime.min, schedule.departTime.period,
        schedule.arrivalTime.hour, schedule.arrivalTime.min, schedule.arrivalTime.period,
        schedule.departDate.day, schedule.departDate.month, schedule.departDate.year,
        schedule.availableSeat);

    printf("records added..\n");
    fclose(Cptr);
}

void scheduleRead() {
    int count = 0;
    FILE* Rptr;
    Rptr = fopen("scheduleTest.txt", "r");

    if (Rptr == NULL) {
        printf("staff.txt file unable to open");
        exit(-1);
    }
    line();
    printf("%-8s %-15s %-15s %-12s %-12s %-12s %s\n", "TrainID", "DepartStation", "ArrivalStation", "departTime", "ArrivalTime", "departTime", "availableSeat");

    line();

    while (fscanf(Rptr, "%d | %s | %s | %d:%d %s | %d:%d %s | %02d-%02d-%04d | %d\n", &schedule.trainID, schedule.departStation, schedule.arrivalStation,
        &schedule.departTime.hour, &schedule.departTime.min, schedule.departTime.period,
        &schedule.arrivalTime.hour, &schedule.arrivalTime.min, schedule.arrivalTime.period,
        &schedule.departDate.day, &schedule.departDate.month, &schedule.departDate.year,
        &schedule.availableSeat) != EOF) {
        count++;
        printf("%02d. T%03d | % -12s | % -12s | % .02d: % .02d %s | % .02d : % .02d %s | %02d-%02d-%04d | % d\n", count,
            schedule.trainID, schedule.departStation, schedule.arrivalStation,
            schedule.departTime.hour, schedule.departTime.min, schedule.departTime.period,
            schedule.arrivalTime.hour, schedule.arrivalTime.min, schedule.arrivalTime.period,
            schedule.departDate.day, schedule.departDate.month, schedule.departDate.year,
            schedule.availableSeat);
    };

    line();

    fclose(Rptr);
    printf("< %d schedule listed >\n\n", count);
}

void scheduleUpdate() {
    int inId;
    char found = 'X';
    int count = 0;
    Train new;

    FILE* ptr1, * ptr2;
    ptr1 = fopen("scheduleTest.txt", "r");
    ptr2 = fopen("scheduleTest.txt", "r");

    if (ptr1 == NULL || ptr2 == NULL) {
        printf("scheduleTest.txt file unable to open\n");
        exit(-1);
    }

    while (fscanf(ptr1, "%d | %s | %s | %d:%d %s | %d:%d %s | %d-%d-%d | %d\n", &schedule.trainID, schedule.departStation, schedule.arrivalStation,
        &schedule.departTime.hour, &schedule.departTime.min, schedule.departTime.period,
        &schedule.arrivalTime.hour, &schedule.arrivalTime.min, schedule.arrivalTime.period,
        &schedule.departDate.day, &schedule.departDate.month, &schedule.departDate.year,
        &schedule.availableSeat) != EOF) {
        count++;
    };

    fclose(ptr1);
    //if dont declare 'fclose(ptr1);' here the data or so called records inside the schedule file will loss..

    Train schedule[MAX];


    for (int i = 0; i < count; i++) {
        fscanf(ptr2, "%d | %s | %s | %d:%d %s | %d:%d %s | %d-%d-%d | %d\n", &schedule[i].trainID, schedule[i].departStation, schedule[i].arrivalStation,
            &schedule[i].departTime.hour, &schedule[i].departTime.min, schedule[i].departTime.period,
            &schedule[i].arrivalTime.hour, &schedule[i].arrivalTime.min, schedule[i].arrivalTime.period,
            &schedule[i].departDate.day, &schedule[i].departDate.month, &schedule[i].departDate.year,
            &schedule[i].availableSeat);

    }

    //fclose(ptr2);
    //line();

    printf("Enter Train Id to update (press '0' to cancel..) : T");
    scanf(" %d", &inId); rewind(stdin);
    //printf("_____________________________________________\n");
    for (int i = 0; i < count; i++) {
        if (inId == schedule[i].trainID) {
            //trash[i] = schedule[i];

            printf("Enter new details for Train %d:\n", inId);
            printf("Enter depart station: ");
            scanf(" %s", schedule[i].departStation);
            rewind(stdin);

            printf("Enter arrival station: ");
            scanf(" %s", schedule[i].arrivalStation);
            rewind(stdin);

            char timeStr[20];
            do {
                printf("Enter depart time (hh:mm AM/PM): ");
                scanf("%s", timeStr);
            } while (!isValidTime(timeStr));
            sscanf(timeStr, "%d:%d %2s", &schedule[i].departTime.hour, &schedule[i].departTime.min, schedule[i].departTime.period);

            do {
                printf("Enter arrival time (hh:mm AM/PM): ");
                scanf("%s", timeStr);
            } while (!isValidTime(timeStr));
            sscanf(timeStr, "%d:%d %2s", &schedule[i].arrivalTime.hour, &schedule[i].arrivalTime.min, schedule[i].arrivalTime.period);


            while (true) {
                printf("Enter depart date (eg. dd-mm-yyyy): ");
                if (scanf(" %d-%d-%d", &schedule[i].departDate.day, &schedule[i].departDate.month, &schedule[i].departDate.year) != 3) {
                    printf("Invalid input format. Please enter the date in dd-mm-yyyy format.\n");
                    rewind(stdin);
                    continue; // Prompt user again
                }

                // Validate depart date
                if (!isValidDateA(schedule[i].departDate.day, schedule[i].departDate.month, schedule[i].departDate.year)) {
                    printf("Invalid depart date. Please enter a valid date.\n");
                    continue; // Prompt user again
                }

                break; // Exit loop if a valid date is entered
            }


            printf("Enter available seats: ");
            scanf(" %d", &schedule[i].availableSeat);
            rewind(stdin);

            printf("\nRecord updated...\n");
            printf("======================\n");
            //line();
            printf("%-8s %-15s %-15s %-12s %-12s %s\n", "TrainID", "DepartStation", "ArrivalStation", "departTime", "ArrivalTime", "availableSeat");
            printf("%2d. T%03d | %-12s | %-12s | %02d:%02d %s | %02d:%02d %s | %02d-%02d-%04d | %d\n", i + 1,
                schedule[i].trainID, schedule[i].departStation, schedule[i].arrivalStation,
                schedule[i].departTime.hour, schedule[i].departTime.min, schedule[i].departTime.period,
                schedule[i].arrivalTime.hour, schedule[i].arrivalTime.min, schedule[i].arrivalTime.period,
                schedule[i].departDate.day, schedule[i].departDate.month, schedule[i].departDate.year,
                schedule[i].availableSeat);

            found = 'Y';
            break;
        }
    }

    line();

    if (found == 'X') {
        printf("No such train Id found : T%03d\n\n", inId);
    }

    FILE* ptr;
    ptr = fopen("scheduleTest.txt", "w");

    if (ptr == NULL) {
        printf("unable to open");
        exit(-1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(ptr, "%03d | %s | %s | %02d:%02d %s | %02d:%02d %s | %02d-%02d-%04d | %d\n",
            schedule[i].trainID, schedule[i].departStation, schedule[i].arrivalStation,
            schedule[i].departTime.hour, schedule[i].departTime.min, schedule[i].departTime.period,
            schedule[i].arrivalTime.hour, schedule[i].arrivalTime.min, schedule[i].arrivalTime.period,
            schedule[i].departDate.day, schedule[i].departDate.month, schedule[i].departDate.year,
            schedule[i].availableSeat);
    }

    fclose(ptr);
    fclose(ptr2);
}

void scheduleDelete() {
    int count = 0;
    int inId;
    char found = 'X';
    Train trash[MAX];
    Train schedule[MAX];

    FILE* ptr;
    ptr = fopen("scheduleTest.txt", "r");
    if (ptr == NULL) {
        printf("unable to open file..\n");
        exit(-1);
    }

    while (fscanf(ptr, "%d | %s | %s | %02d:%02d %s | %02d:%02d %s | %02d-%02d-%04d | %d\n",
        &schedule[count].trainID, schedule[count].departStation, schedule[count].arrivalStation,
        &schedule[count].departTime.hour, &schedule[count].departTime.min, schedule[count].departTime.period,
        &schedule[count].arrivalTime.hour, &schedule[count].arrivalTime.min, schedule[count].arrivalTime.period,
        &schedule[count].departDate.day, &schedule[count].departDate.month, &schedule[count].departDate.year,
        &schedule[count].availableSeat) != EOF) {
        count++;
    }

    fclose(ptr);

    printf("Enter Train Id to delete (press '0' to cancel..) : T");
    scanf(" %d", &inId);
    rewind(stdin);

    for (int i = 0; i < count; i++) {
        if (inId == schedule[i].trainID) {
            found = 'Y';

            printf("Record removed..\n");
            printf("=================\n");
            printf("%-8s %-15s %-15s %-12s %-12s %s\n", "TrainID", "DepartStation", "ArrivalStation", "departTime", "ArrivalTime", "availableSeat");
            line();
            printf("%2d. %d | %-12s | %-12s | %02d:%02d %s | %02d:%02d %s | %02d-%02d-%04d | %d\n",
                i + 1, schedule[i].trainID, schedule[i].departStation, schedule[i].arrivalStation,
                schedule[i].departTime.hour, schedule[i].departTime.min, schedule[i].departTime.period,
                schedule[i].arrivalTime.hour, schedule[i].arrivalTime.min, schedule[i].arrivalTime.period,
                schedule[i].departDate.day, schedule[i].departDate.month, schedule[i].departDate.year,
                schedule[i].availableSeat);

            trash[0] = schedule[i];

            for (int j = i; j < count - 1; j++) {
                schedule[j] = schedule[j + 1];
            }

            count--;
            break;
        }
    }
    line();

    if (found == 'X') {
        printf("No such train Id found : T%03d\n\n", inId);
    }

    FILE* ptr2;
    ptr2 = fopen("scheduleTest.txt", "w");
    if (ptr2 == NULL) {
        printf("unable to open");
        exit(-1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(ptr2, "%03d | %s | %s | %02d:%02d %s | %02d:%02d %s | %02d-%02d-%04d | %d\n",
            schedule[i].trainID, schedule[i].departStation, schedule[i].arrivalStation,
            schedule[i].departTime.hour, schedule[i].departTime.min, schedule[i].departTime.period,
            schedule[i].arrivalTime.hour, schedule[i].arrivalTime.min, schedule[i].arrivalTime.period,
            schedule[i].departDate.day, schedule[i].departDate.month, schedule[i].departDate.year,
            schedule[i].availableSeat);
    }

    fclose(ptr2);
}

void scheduleSearch() {
    int count = 0;
    int inId;

    FILE* Sptr1, * Sptr2;
    Sptr1 = fopen("scheduleTest.txt", "r");
    Sptr2 = fopen("scheduleTest.txt", "r");

    if (Sptr1 == NULL || Sptr2 == NULL) {
        printf("file unable to open..\n");
        exit(-1);
    }

    while (fscanf(Sptr1, "%d | %s | %s | %02d:%02d %s | %02d:%02d %s | %02d-%02d-%04d | %d\n",
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

    printf("Enter train Id to search (press '0' to cancel..) : T");
    scanf(" %d", &inId); rewind(stdin);

    line();

    printf("%-8s %-15s %-15s %-12s %-12s %-12s %s\n", "TrainID", "DepartStation", "ArrivalStation", "departTime", "ArrivalTime", "departDate", "availableSeat");
    line();

    for (int i = 0; i < count; i++) {
        if (inId == schedule[i].trainID) {
            printf("%2d. %03d | %-12s | %-12s | %02d:%02d %s | %02d:%02d %s | %02d-%02d-%04d |%d\n",
                i + 1, schedule[i].trainID, schedule[i].departStation, schedule[i].arrivalStation,
                schedule[i].departTime.hour, schedule[i].departTime.min, schedule[i].departTime.period,
                schedule[i].arrivalTime.hour, schedule[i].arrivalTime.min, schedule[i].arrivalTime.period,
                schedule[i].departDate.day, schedule[i].departDate.month, schedule[i].departDate.year,
                schedule[i].availableSeat);

            found = 1;
        }
    }
    line();

    if (!found) {
        printf("no records are found T%03d\n\n", inId);
    }

    fclose(Sptr2);
}

void scheduleMenu() {
    int select;

    printf("Schedule - Select module\n=====================\n'1' - Create\n'2' - Retrieve\n'3' - Update\n'4' - Delete\n'5' - Search\n'0' - Back to main menu\n===================\n>>");
    scanf(" %d", &select); rewind(stdin);

    if (select == 1) {
        system("cls");
        printf("continue?\n'1' - Proceed \n'0' - Back to schedule page\n>>");
        scanf(" %d", &select); rewind(stdin);
        if (select == 1) {
            scheduleCreate();
            scheduleMenu();
        }
        else if (select == 0) {
            system("cls");
            printf("Create schedule cancel..\n");
            scheduleMenu();
        }

    }
    else if (select == 2) {
        system("cls");
        scheduleRead();
        scheduleMenu();
    }
    else if (select == 3) {
        system("cls");
        scheduleRead();
        scheduleUpdate();
        scheduleMenu();

    }
    else if (select == 4) {
        system("cls");
        scheduleRead();
        scheduleDelete();
        scheduleMenu();

    }
    else if (select == 5) {
        system("cls");
        scheduleRead();
        scheduleSearch();
        scheduleMenu();

    }
    else if (select == 0) {
        system("cls");
        printf("logout from schedule page..\n");
        printf("Out..\n");
    }
    else {
        system("cls");
        scheduleMenu();
    }
}

void trainSchedule() {
    system("cls");
    scheduleMenu();

    //scheduleRead();
    //scheduleCreate();
    //scheduleUpdate();
    //scheduleDelete();
    //scheduleSearch();

}