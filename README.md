# Smart Hospital & Resource Allocation System

A menu driven patient intake, billing, and resource allocation system written in C. Registers patients, triages them by urgency, allocates beds in real time, generates itemized bills, and produces operational analytics  with data that persists across runs.

## Features

- Patient intake with full input validation (name, age, triage level, specialty, admission details)
- Real time bed allocation across four wards, with automatic fallback to outpatient status when a ward is full
- Six-part billing engine: consultation fees, emergency surcharges, ward costs, and age-based subsidy discounts
- Priority based patient sorting (critical cases first, stable on registration order)
- Reporting dashboard: urgency breakdowns, total revenue and discounts, per-ward occupancy, highest-paying patient
- Persistent storage  bed status survives a restart; every transaction is permanently logged

## Build & Run

```bash
gcc *.c -o hospital_system
./hospital_system
```

No external dependencies. Built and tested with GCC / Code::Blocks (MinGW).

## Menu

```
1. Register Patient
2. Display Sorted Patients
3. Generate Report
4. Display Bed status
5. Exit
```

## Data Persistence

| File | Purpose |
|---|---|
| `beds_status.txt` | Bed occupancy grid - loaded on startup, saved after each admission |
| `patient_records.txt` | Append only log of every billing transaction, across all runs |

## Wards & Specialties

| Ward | Daily Rate | Capacity |
|---|---|---|
| General | LKR 3,000 | 20 |
| Paediatric | LKR 6,000 | 10 |
| Surgical | LKR 12,000 | 10 |
| ICU | LKR 25,000 | 5 |

| Specialty | Consultation Fee | Daily Cap |
|---|---|---|
| General Practice (OPD) | LKR 1,500 | 30 |
| Paediatrics | LKR 2,500 | 20 |
| Cardiology | LKR 4,500 | 12 |
| Neurology | LKR 5,000 | 10 |

## Design Notes

Specialty, ward, and patient data are modeled as structs rather than parallel arrays. Billing calculations are implemented as pure functions, and priority sorting operates on an index array to preserve registration order. Full architecture and design rationale are documented in the project report.

## Author

T.S.P. Fernando - AS20250397
CSC 1012 - Introduction to Computer Programming
University of Sri Jayewardenepura
