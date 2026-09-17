#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATIENTS 100
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4
#define MAX_BED_SLOTS 20

void displayMenu(void);
void registerPatient(void);
void displaySortedPatients(void);
void generateReport(void);
void displayBedStatus(void);
int assignBed(int wardID);

double calculateWaitTime(int patientsInLine, int avgTimePerPatient);
double calculateSurcharge(double baseFee, int triageLevel);
double calculateWardCost(int daysAdmitted, double bedRate);
double calculateGrossTotal(double baseFee, double surcharge, double wardCost);
double calculateDiscount(double grossTotal, int age);
double calculateFinalAmount(double grossTotal, double discount);
void formatCurrency(double amount, char* out);
void printBill(int i);

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

int main(){

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
        if (numPatients >= MAX_PATIENTS){
            printf("Hospital patient limit reached - cannot register.\n");
            return;
        }
        else{
        char name[50];
        int age;
        int triageLevel;
        int specId;
        int admittedFlag;
        int wardId;
        int daysAdmitted;
        int bedNum = 0;

        printf("Enter Patient name: ");
        scanf(" %49[^\n]", name);

        do{
            printf("Enter Patient age: ");
            scanf("%d", &age);
        }while (age < 0);

        do{
            printf("Enter Emergency Level: ");
            scanf("%d", &triageLevel);
        }while (triageLevel < 1 || triageLevel > 3);

        do{
            printf("Enter Specialty ID: ");
            scanf("%d", &specId);
        }while (specId < 1 || specId > 4);

        do{
            printf("Is Patient Admitted? (1=Yes, 0=No): ");
            scanf("%d", &admittedFlag);

            if (admittedFlag == 1){

                do{
                printf("Enter WardID: ");
                scanf("%d", &wardId);
                }while(wardId < 1 || wardId > 4);


                int assignedBed = assignBed(wardId-1);
                if (assignedBed == -1){
                    printf("Ward is full...Move to OPD instead.\n");
                    admittedFlag = 0;
                    wardId = 0;
                    daysAdmitted = 0;
                }
                else{
                    bedNum = assignedBed;
                    do{
                    printf("Enter Admitted days: ");
                    scanf("%d", &daysAdmitted);
                    }while(daysAdmitted <= 0);
                }

            }

            else{
              daysAdmitted = 0;
              wardId = 0; //There is no 0 ward.Just add to remove assigning garbage value.
            }
        }while(admittedFlag != 0 && admittedFlag != 1);



        double waitTime	= calculateWaitTime(specialtyQueueCount[specId - 1], doctorSpec[specId - 1].time);
        specialtyQueueCount[specId - 1]++;

        double baseFee = doctorSpec[specId - 1].baseFee;

        double surcharge = calculateSurcharge(baseFee, triageLevel);

        double bedRate = 0;
        if (wardId > 0) {
            bedRate = wardData[wardId - 1].bedRate;
        }

        double wardCost = calculateWardCost(daysAdmitted, bedRate);

        double grossTotal = calculateGrossTotal(baseFee, surcharge, wardCost);

        double discount = calculateDiscount(grossTotal, age);

        double finalAmount = calculateFinalAmount(grossTotal, discount);

        strcpy(patients[numPatients].name, name);
        patients[numPatients].age = age;
        patients[numPatients].triageLevel = triageLevel;
        patients[numPatients].specId = specId;
        patients[numPatients].admittedFlag = admittedFlag;
        patients[numPatients].wardId = wardId;
        patients[numPatients].daysAdmitted = daysAdmitted;
        patients[numPatients].bedNum = bedNum;
        patients[numPatients].waitTime = waitTime;
        patients[numPatients].baseFee = baseFee;
        patients[numPatients].surcharge = surcharge;
        patients[numPatients].wardCost = wardCost;
        patients[numPatients].grossTotal = grossTotal;
        patients[numPatients].discount = discount;
        patients[numPatients].finalAmount = finalAmount;

        numPatients++;
        printBill(numPatients - 1);

        }
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
        for (int w = 0; w < NUM_WARDS; w++)
        {
            printf("%s:\n", wardData[w].wardName);

            for (int s = 0; s < wardData[w].bedCap; s++)
            {
                if (bedOccupancy[w][s] == 0){
                    printf("  Bed %2d: Available\n", s+1);
                }else{
                    printf("  Bed %2d: Occupied\n", s+1);
                }
            }
        }
    }

//Functions with return values
int assignBed(int wardId)
{
    for (int s = 0; s < wardData[wardId].bedCap; s++){
        if(bedOccupancy[wardId][s] == 0){
            bedOccupancy[wardId][s] = 1;
            return s + 1;
        }
    }
    return -1; //nothing was free. Therefore return -1(no -1 bed)
}

double calculateWaitTime(int patientsInLine, int avgTimePerPatient)
{
    return patientsInLine * avgTimePerPatient;
}

double calculateSurcharge(double baseFee, int triageLevel)
{
    if (triageLevel == 3){
        return baseFee * 0.5;
    }else if (triageLevel == 2){
        return baseFee * 0.2;
    }
    return 0;
}

double calculateWardCost(int daysAdmitted, double bedRate)
{
    return daysAdmitted * bedRate;
}

double calculateGrossTotal(double baseFee, double surcharge, double wardCost)
{
    return baseFee + surcharge + wardCost;
}

double calculateDiscount(double grossTotal, int age)
{
    if (age < 5 || age > 65){
        return grossTotal * 0.15;
    }
    return 0;
}

double calculateFinalAmount(double grossTotal, double discount)
{
    return grossTotal - discount;
}

void formatCurrency(double amount, char* out)
{
    char raw[30];
    sprintf(raw, "%.2f", amount);

    int decimalPos = strlen(raw) - 3;

    int outIndex = 0;
    for (int i = 0; i < decimalPos; i++) {
        out[outIndex++] = raw[i];
        int digitsRemaining = decimalPos - 1 - i;
        if (digitsRemaining > 0 && digitsRemaining % 3 == 0) {
            out[outIndex++] = ',';
        }
    }
    strcpy(out + outIndex, raw + decimalPos);
}

void printBill(int i)
{
    const char* triageLabel[3] = {"Normal", "Urgent", "Critical"};

    printf("====================================================\n");
    printf(" SMART HOSPITAL ADMISSION & BILL\n");
    printf("----------------------------------------------------------------------------------------\n");

    printf("Patient ID    : PAT-%d\n", 1000 + i + 1);
    printf("Patient Name  : %s\n", patients[i].name);

    if (patients[i].discount > 0) {
        printf("Age           : %d Years (15%% Subsidy Eligible)\n", patients[i].age);
    } else {
        printf("Age           : %d Years\n", patients[i].age);
    }

    printf("Specialty     : %s\n", doctorSpec[patients[i].specId - 1].specialtyName);

    if (patients[i].wardId > 0) {
        printf("Assigned Ward : %s (Bed #%02d)\n",
               wardData[patients[i].wardId - 1].wardName, patients[i].bedNum);
    } else {
        printf("Assigned Ward : Outpatient (OPD)\n");
    }

    printf("Urgency Level : Level %d (%s)\n", patients[i].triageLevel, triageLabel[patients[i].triageLevel - 1]);

    char buf[30];

    printf("----------------------------------------------------------------------------------------\n");

    formatCurrency(patients[i].baseFee, buf);
    printf("Base Consultation Fee : LKR %s\n", buf);

    formatCurrency(patients[i].surcharge, buf);
    if (patients[i].triageLevel == 3) {
        printf("Emergency Surcharge   : LKR %s (50%%)\n", buf);
    } else if (patients[i].triageLevel == 2) {
        printf("Emergency Surcharge   : LKR %s (20%%)\n", buf);
    } else {
        printf("Emergency Surcharge   : LKR %s\n", buf);
    }

    formatCurrency(patients[i].wardCost, buf);
    if (patients[i].daysAdmitted > 0) {
        printf("Ward Stay Cost (%d Days) : LKR %s\n", patients[i].daysAdmitted, buf);
    } else {
        printf("Ward Stay Cost         : LKR %s\n", buf);
    }

    printf("----------------------------------------------------------------------------------------\n");

    formatCurrency(patients[i].grossTotal, buf);
    printf("Gross Total Bill      : LKR %s\n", buf);

    formatCurrency(patients[i].discount, buf);
    if (patients[i].discount > 0) {
        printf("Age Subsidy Discount  : LKR -%s (15%%)\n", buf);
    } else {
        printf("Age Subsidy Discount  : LKR -%s\n", buf);
    }

    printf("----------------------------------------------------------------------------------------\n");

    formatCurrency(patients[i].finalAmount, buf);
    printf("Final Payable Amount  : LKR %s\n", buf);

    printf("Estimated Waiting Time : %.2f mins", patients[i].waitTime);
    if (patients[i].waitTime == 0) {
        printf(" (Immediate Attention)");
    }
    printf("\n");

    printf("====================================================\n");
}
