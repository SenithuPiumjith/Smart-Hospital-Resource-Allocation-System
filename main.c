#include <stdio.h>
#include <stdlib.h>
#define MAX_PATIENTS 100
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4
#define MAX_BED_SLOTS 20

void displayMenu(void);
void registerPatient(void);
void displaySortedPatients(void);
void generateReport(void);
void displayBedStatus(void);

struct doctorSpecRow
{
    int specialtyId;
    const char* specialtyName;
    double baseFee;
    int time;
    int dailyCap;
};

struct wardsDataRow
{
    int wardId;
    const char* wardName;
    double bedRate;
    int bedCap;
};
const struct doctorSpecRow doctorSpec[NUM_SPECIALTIES] = {
    {1, "OPD", 1500, 15, 30},
    {2, "Paediatrics", 2500, 20, 20},
    {3, "Cardiology", 4500, 30, 12},
    {4, "Neurology", 5000, 30, 10}
    };

const struct wardsDataRow wardData[NUM_WARDS] ={
    {1, "General", 3000, 20},
    {2, "Paediatrics", 6000, 10},
    {3, "Surgical", 12000, 10},
    {4, "ICU", 25000, 5}
    };

int bedOccupancy[NUM_WARDS][MAX_BED_SLOTS] = {0};

struct patientRecords
{
    char name[50];
    int age;
    int triageLevel;
    int specId;
    int admittedFlag;
    int wardId;
    int daysAdmitted;
    int bedNum;
    double waitTime;
    double baseFee;
    double surcharge;
    double wardCost;
    double grossTotal;
    double discount;
    double finalAmount;
  };
struct patientRecords patients[MAX_PATIENTS];

int numPatients = 0;

int specialtyQueueCount[NUM_SPECIALTIES] = {0};

int main()
{

    //menu loop
    int choice;

    do{
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerPatient();
            break;
        case 2:
            displaySortedPatients();
            break;
        case 3:
            generateReport();
            break;
        case 4:
            displayBedStatus();
            break;
        case 5:
            printf("Saving and exiting...\n");
            break;
        default:
            printf("Invalid choice, try again.\n");
        }
    }while (choice != 5);


    return 0;
}

void displayMenu(void)
    {
        printf("1. Register Patient\n");
        printf("2. Display Sorted Patients\n");
        printf("3. Generate Report\n");
        printf("4. Display Bed status\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
    }

void registerPatient(void)
    {
        printf("register patient not implemented yet\n");
    }

void displaySortedPatients(void)
    {
        printf("display sorted patients not implemented yet\n");
    }

void generateReport(void)
    {
        printf("generate report not implemented yet\n");
    }

void displayBedStatus(void)
    {
        printf("display bed status not implemented yet\n");
    }
