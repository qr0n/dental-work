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

// TODO: procedure map
// TODO: payment type map

typedef struct Appointment
{
    double uuid;
    double clientId;
    char firstName[nameLen];
    char lastName[nameLen];
    char apptDate[dateLen];
    char procedureType[procedureLen];
    char paymentType[10];
    char cardNumber[16];
};

// function protos
int addAppointment();
int editAppointment();
int deleteAppointment(double unique_id);
void displayAppointments();
struct Appointment searchRecords(int robots);
int menu();

int addAppointment()
{

    // START UUID GENERATION | libuuid isnt working for me - B.S
    srand(time(NULL));
    int uuid = rand();

    FILE *writePtr;

    if ((writePtr = fopen(APPOINTMENTS, "ab+")) == NULL)
    {
        printf("Error opening appointments file.");
    }

    struct Appointment appt;
    int procedureType;

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

    fwrite(&appt, sizeof(struct Appointment), 1, writePtr);
    printf("Saved!, Unique ID generated = %d", uuid);

    fclose(writePtr);
}

int editAppointment()
{
    int uuid;
    printf("Enter the uuid for the appointment created: ");
    scanf("%d", &uuid);
    printf("Searching databank for appointment #%d\n", uuid);
    searchRecords(uuid);
}

int deleteAppointment(double unique_id)
{
    // return a confirmation prompt
}

// for menu design use system from stdlib.h to clear the terminal

void displayAppointments()
{
    // print all of them
}

struct Appointment searchRecords(int robots)
{
    struct Appointment appt;

    // prompt the user which of the unique things they have
    // eg, name, id, etc
    FILE *fptr;
    if ((fptr = fopen(APPOINTMENTS, "rb+")) == NULL)
    {
        printf("Error opening appointments master file.");
        return appt; // empty function returned on error.
    }

    if (robots != 0)
    {
        printf("[Search Records]: Initialized with robots = True\n");
        printf("[Search Records]: Searching databank with key = uuid (%d)\n", robots);

        while (fread(&appt, sizeof(struct Appointment), 1, fptr))
        {
            if (appt.uuid == robots)
            {
                fclose(fptr);
                return appt;
            }
        }
    }

    fclose(fptr);
    printf("[Search Records]: No record found.\n");
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
        addAppointment();
        break;

    case 2:
        editAppointment();
        break;

    case 3:
        // deleteAppointment();
        break;

    case 4:
        searchRecords(0); // robots is disabled
        break;

    case 5:
        displayAppointments();
        break;

    default:
        break;
    }
    // this does the switching
}