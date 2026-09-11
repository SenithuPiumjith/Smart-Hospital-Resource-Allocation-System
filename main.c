#include <stdio.h>
#include <stdlib.h>
#define MAX_PATIENTS 100
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4
#define MAX_BED_SLOTS 20

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
    {2, "Paediatric", 6000, 10},
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


    return 0;
}
