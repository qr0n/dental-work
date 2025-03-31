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
    char cardNumber[20]; // Increased size and changed to char array
} Appointment;

// function protos
int addAppointment();
int editAppointment();
int deleteAppointment();
void displayAppointments();
void searchRecordsInterface();
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
    scanf("%s", appt.apptDate); // Remove &

    printf("Enter the first and last name of the client\n> ");
    scanf("%s %s", appt.firstName, appt.lastName); // Remove &

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
        printf("Enter card number: ");
        scanf("%s", appt.cardNumber); // Changed to %s
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

int deleteAppointment()
{
    long uuid;
    struct Appointment appt;
    int found = 0;

    printf("Enter the UUID of the appointment to delete: ");
    scanf("%ld", &uuid);

    FILE *fptr, *tempFile;

    if ((fptr = fopen(APPOINTMENTS, "rb")) == NULL)
    {
        printf("Error opening appointments file.\n");
        return 1;
    }

    if ((tempFile = fopen("temp.dat", "wb")) == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(fptr);
        return 1;
    }

    while (fread(&appt, sizeof(struct Appointment), 1, fptr))
    {
        if (appt.uuid == uuid)
        {
            found = 1;
            printf("Appointment with UUID %ld deleted successfully.\n", uuid);
        }
        else
        {
            fwrite(&appt, sizeof(struct Appointment), 1, tempFile);
        }
    }

    fclose(fptr);
    fclose(tempFile);

    if (!found)
    {
        printf("Appointment not found.\n");
        remove("temp.dat");
    }
    else
    {
        remove(APPOINTMENTS);
        rename("temp.dat", APPOINTMENTS);
    }

    return 0;
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

void searchRecordsInterface()
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
    int searchType;
    char firstName[15], lastName[15], date[15];
    double idnum;

    printf("Enter how you would like to search\n");
    printf("1. Name (First and Last required)\n2. Date (DD/MM/YYYY)\n3. Client ID\n> ");
    scanf("%d", &searchType);

    switch (searchType)
    {
    case 1:
        printf("Enter your First name\n> ");
        scanf("%s", firstName); // Remove &
        printf("Enter your Last name\n> ");
        scanf("%s", lastName); // Remove & and add newline

        int found = 0;
        while (fread(&appt, sizeof(struct Appointment), 1, readPtr))
        {
            if (strcmp(firstName, appt.firstName) == 0 && strcmp(lastName, appt.lastName) == 0)
            {
                found = 1;
                printf("\nAppointment found:\n");
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
        }
        if (!found)
        {
            printf("\nNo appointments found for %s %s\n", firstName, lastName);
        }
        break;

    case 2:
        printf("Enter the date of appointment\n");
        scanf("%s", date);

        rewind(readPtr);
        while (fread(&appt, sizeof(struct Appointment), 1, readPtr) == 1)
        {
            if (strcmp(appt.apptDate, date) == 0)
            {
                printf(" %-16s %-11s %-17s %-16s %-16s %.2f %-16s %-16ld\n", appt.firstName, appt.lastName, appt.cardNumber, appt.apptDate, appt.paymentType, appt.clientId, appt.procedureType, appt.uuid);
            }
        }
        break;

    case 3:
        printf("Enter ID number\n");
        scanf("%lf", &idnum);

        rewind(readPtr);
        while (fread(&appt, sizeof(struct Appointment), 1, readPtr) == 1)
        {
            if (appt.clientId == idnum)
            {
                printf(" %-16s %-11s %-17s %-16s %-16s %.2f %-16s %-16ld\n", appt.firstName, appt.lastName, appt.cardNumber, appt.apptDate, appt.paymentType, appt.clientId, appt.procedureType, appt.uuid);
                return; // Exit after finding the record
            }
        }
        printf("Account %.2f does not exist.\n", idnum);
        break;

    default:
        printf("INVALID OPTION\n");
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
    while (1)
    {
        system("cls");
        int menuType = menu();

        if (menuType == -1)
        {
            printf("\nGoodbye!\n");
            return 0;
        }

        system("cls");
        switch (menuType)
        {
        case 1:
            addAppointment();
            break;
        case 2:
            editAppointment();
            break;
        case 3:
            deleteAppointment();
            break;
        case 4:
            searchRecordsInterface();
            break;
        case 5:
            displayAppointments();
            break;
        default:
            printf("Invalid option selected!\n");
            break;
        }
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
}