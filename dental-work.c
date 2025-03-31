/*

2.	(Dental Appointment System) Create dentist appointment system. Each record holds the following:
•	client id no
•	name
•	telephone number
•	appointment date
•	procedure (i.e. filling, cleaning etc.), payment type (i.e. cash, credit)
•	card number (i.e. debit card no., credit card no.). Initialize all values in the structure to appropriate default values.
The system will have file with appointment details and should be able to perform the following:
- Add an Appointment Record
- Edit an Appointment Record
- Delete an Appointment Record
- Display Appointment Records
- search records
- main

all files must be binary
and a text file to see whats there

The system must:
- be menu-driven and continue to perform tasks until the user chooses the option to exit the system.
- make use of a modularity, structure and binary files.

structs
function - 5

*/

// Libraries to link
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define nameLen 50
#define dateLen 30
#define procedureLen 20
#define APPOINTMENTS "appointments.txt"
char PROCEDURE_MAP[5][20] = {"", "Cleaning", "Tooth Filling", "Oral Examination", "Tooth Extraction"};
char PAYMENT_MAP[4][20] = {"", "Cash", "Credit Card", "Debit Card"};

// TODO: procedure map DONE
// TODO: payment type map PENDING
// UUID IS IMMUTABLE!

typedef struct Appointment
{
    long uuid;
    double clientId;
    char firstName[nameLen];
    char lastName[nameLen];
    char apptDate[dateLen];
    char procedureType[procedureLen];
    char paymentType[20];
    char cardNumber[16];
} Appointment;

// function protos
int addAppointment();
int editAppointment();
int deleteAppointment();
void displayAppointments();
void searchRecords();
int menu();

int addAppointment()
{

    // START UUID GENERATION | libuuid isnt working for me - B.S
    srand(time(NULL));
    long uuid = rand();

    FILE *writePtr;

    if ((writePtr = fopen(APPOINTMENTS, "ab+")) == NULL)
    {
        printf("Error opening appointments file.");
    }

    struct Appointment appt;
    int procedureType, paymentMethod;

    appt.uuid = uuid;

    printf("Enter the client's ID: ");
    scanf("%ld", &appt.clientId);

    printf("Enter the date for the appointment\nDD/MM/YYYY: ");
    scanf("%s", &appt.apptDate);

    printf("Enter the first and last name of the client\n> ");
    scanf("%s %s", appt.firstName, appt.lastName);

    printf("Select the procedure the client has selected:\n");
    printf("1. Cleaning\n");
    printf("2. Tooth filling\n");
    printf("3. Oral examination\n");
    printf("4. Tooth extraction\n");
    printf("> ");
    scanf("%d", &procedureType);
    strcpy(appt.procedureType, PROCEDURE_MAP[procedureType]);

    printf("Enter payment type\n1. Cash\n2. Credit Card\n3. Debit Card\n> ");
    scanf("%d", &paymentMethod);
    strcpy(appt.paymentType, PAYMENT_MAP[paymentMethod]);
    if (paymentMethod != 1)
    {
        long long cardNumber;
        printf("Enter card number: ");
        scanf("%ld", &appt.cardNumber);
    }

    fwrite(&appt, sizeof(struct Appointment), 1, writePtr);
    printf("Saved!, Unique ID generated = %d", uuid);

    fclose(writePtr);
}

int editAppointment()
{
    long uuid;
    int editOp;
    struct Appointment appt;

    printf("Enter the uuid for the appointment created: ");
    scanf("%ld", &uuid);

    FILE *fptr;
    if ((fptr = fopen(APPOINTMENTS, "rb+")) == NULL)
    {
        printf("Error opening appointments master file.");
    }

    // printf("[Search Records]: Initialized with robots = True\n");
    // printf("[Search Records]: Searching databank with key = uuid (%d)\n", uuid);

    while (fread(&appt, sizeof(struct Appointment), 1, fptr))
    {
        if (appt.uuid == uuid)
        {
            fclose(fptr);
        }
    }
    printf("Enter what you would like to edit\n");
    printf("1. Client ID            | %ld\n", appt.clientId);
    printf("2. Client First Name    | %s\n", appt.firstName);
    printf("3. Client Last Name     | %s\n", appt.lastName);
    printf("4. Appointment Date     | %s\n", appt.apptDate);
    printf("5. Procedure Type       | %s\n", appt.procedureType);
    printf("6. Payment Type         | %s\n", appt.paymentType);

    if (strcmp(appt.paymentType, "Cash") != 0)
    {
        printf("7. Card number          | %lf\n", appt.cardNumber);
    }
    printf("> ");
    scanf("%d", &editOp);

    switch (editOp)
    {
    case 1:
        printf("Enter the edited client ID: ");
        scanf("%ld", &appt.clientId);
        break;
    case 2:
        printf("Enter the edited first name: ");
        scanf("%s", appt.firstName);
        break;
    case 3:
        printf("Enter the edited last name: ");
        scanf("%s", appt.lastName);
        break;
    case 4:
        printf("Enter the edited appointment date (DD/MM/YYYY): ");
        scanf("%s", appt.apptDate);
        break;
    case 5:
        printf("Select the edited procedure type:\n");
        printf("1. Cleaning\n2. Tooth Filling\n3. Oral Examination\n4. Tooth Extraction\n> ");
        int procedureType;
        scanf("%d", &procedureType);
        strcpy(appt.procedureType, PROCEDURE_MAP[procedureType]);
        break;
    case 6:
        printf("Select the edited payment type:\n");
        printf("1. Cash\n2. Credit Card\n3. Debit Card\n> ");
        int paymentMethod;
        scanf("%d", &paymentMethod);
        strcpy(appt.paymentType, PAYMENT_MAP[paymentMethod]);
        if (paymentMethod != 1)
        {
            printf("Enter the edited card number: ");
            scanf("%s", appt.cardNumber);
        }
        break;
    case 7:
        if (strcmp(appt.paymentType, "Cash") != 0)
        {
            printf("Enter the edited card number: ");
            scanf("%s", appt.cardNumber);
        }
        else
        {
            printf("Card number is not applicable for cash payments.\n");
        }
        break;
    default:
        printf("Invalid option selected.\n");
        break;
    }

    FILE *ePtr;

    if ((ePtr = fopen(APPOINTMENTS, "rb+")) == NULL)
    {
        printf("Error opening file");
        return -1;
    }
    else
    {
        fseek(ePtr, -sizeof(struct Appointment), SEEK_CUR);
        fwrite(&appt, sizeof(struct Appointment), 1, ePtr);
        printf("Appointment edited successfully!");
    }
}

// makes a copy of the old appointments file, while copying it ignores the uuid to delete, removing it
int deleteAppointment()
{
    double unique_id;

    printf("Enter the UUID of the appointment you'd like to delete: ");
    scanf("%ld", &unique_id);
    FILE *readPtr, *writePtr;
    struct Appointment appt;
    int found = 0;

    // Open the original file in read mode
    if ((readPtr = fopen(APPOINTMENTS, "rb")) == NULL)
    {
        printf("Error opening appointments file.\n");
        return -1;
    }

    // Open a temporary file in write mode
    if ((writePtr = fopen("temp_appointments.txt", "wb")) == NULL)
    {
        printf("Error creating temporary file.\n");
        fclose(readPtr);
        return -1;
    }

    // Read each record and copy to the temporary file if it doesn't match the unique_id
    while (fread(&appt, sizeof(struct Appointment), 1, readPtr))
    {
        if (appt.uuid == unique_id)
        {
            found = 1; // Mark that the record to delete was found
            continue;  // Skip writing this record to the temporary file
        }
        fwrite(&appt, sizeof(struct Appointment), 1, writePtr);
    }

    fclose(readPtr);
    fclose(writePtr);

    // Replace the original file with the temporary file
    remove(APPOINTMENTS);
    rename("temp_appointments.txt", APPOINTMENTS);

    if (found)
    {
        printf("Appointment with UUID %lf deleted successfully.\n", unique_id);
    }
    else
    {
        printf("Appointment with UUID %lf not found.\n", unique_id);
    }

    return found ? 0 : -1;
}

// for menu design use system from stdlib.h to clear the terminal
void displayAppointments()
{
    FILE *readPtr;
    struct Appointment appt;
    int recordCount = 0;

    // Open the file in read mode
    if ((readPtr = fopen(APPOINTMENTS, "rb")) == NULL)
    {
        printf("Error opening appointments file or no appointments found.\n");
        return;
    }

    printf("Displaying all appointments:\n");
    printf("============================================================\n");

    // Read and display each record
    while (fread(&appt, sizeof(struct Appointment), 1, readPtr))
    {
        recordCount++;
        printf("Record #%d:\n", recordCount);
        printf("UUID: %ld\n", appt.uuid);
        printf("Client ID: %ld\n", (long)appt.clientId);
        printf("Name: %s %s\n", appt.firstName, appt.lastName);
        printf("Appointment Date: %s\n", appt.apptDate);
        printf("Procedure: %s\n", appt.procedureType);
        printf("Payment Type: %s\n", appt.paymentType);
        if (strcmp(appt.paymentType, "Cash") != 0)
        {
            printf("Card Number: %s\n", appt.cardNumber);
        }
        printf("------------------------------------------------------------\n");
    }

    // Check if no records were found
    if (recordCount == 0)
    {
        printf("No appointments found.\n");
    }

    // Close the file
    fclose(readPtr);
}

void searchRecords()
{
    int searchType;
    printf("Enter how you would like to search");
    printf("1. Name (First and Last required)\n2. Date (DD/MM/YYYY)\n3. Client ID\n> ");
    scanf("%d", &searchType);

    switch (searchType)
    {
    case 0:
        /* code */
        break;

    default:
        break;
    }
}

int menu()
{
    int menuType;
    printf("Hello, welcome to the dental appointment system\n");
    // printf("----------------------------------------------");
    // printf("███████████████████████████████████████████████\n");
    printf("=================================================\n");
    printf("\n\n");
    printf("Please select one of the following menu options or enter -1 to quit:\n");
    printf("1. Add an appointment\n");
    printf("2. Edit an appointment\n");
    printf("3. Delete an appointment\n");
    printf("4. Search for an appointment\n");
    printf("5. Display all appointments\n");
    printf("> ");
    scanf("%d", &menuType);

    return menuType;
}

int main()
{
    int menuType = menu();
    switch (menuType)
    {

    case -1:
        return 0;

    case 1:
        system("cls");
        addAppointment();
        break;

    case 2:
        system("cls");
        editAppointment();
        break;

    case 3:
        system("cls");
        deleteAppointment();
        break;

    case 4:
        system("cls");
        searchRecords(0); // robots is disabled
        break;

    case 5:
        system("cls");
        displayAppointments();
        break;

    default:
        break;
    }
    // this does the switching
    main();
}