# BAPESSS Ambulance Booking App

A console-based **ambulance booking and live tracking system** implemented in C, developed as part of the SPC AAT course at B.M.S College of Engineering. 
This project simulates a real-world emergency ambulance management system with booking, fare calculation, and live ETA countdown using multithreading. 

## Features

- Book an ambulance by entering patient name, pickup location, and hospital name. 
- Choose ambulance type: Normal or ICU, with different fare slabs.  
- Auto-generate a unique 10-digit booking ID for every request. 
- View saved booking details using the booking ID.   
- Live ambulance tracking with an ETA countdown running via a separate thread. 
- Simulated ambulance movement towards the patient using randomly generated coordinates. 

## Tech Stack

- Language: C  
- Concepts used:
  - Structures and pointers 
  - Random number generation for IDs and coordinates 
  - Console I/O for user interaction 
  - Multithreading with POSIX threads (`pthread`) 
  - Shared variables for ETA and tracking status 

## How It Works

- On launch, the app displays a menu:  
  1. Book Ambulance  
  2. View Booking Details  
  3. Track Ambulance (Live Location)  
  4. Exit  

- Booking flow:   
  - User enters patient name, pickup location, and hospital name.  
  - Pickup coordinates \((x, y)\) in the range 0–100 are generated randomly.  
  - User selects ambulance type (Normal / ICU), which decides the fare.  
  - A unique 10-digit booking ID is generated and stored in memory.  

- Tracking flow:  
  - User enters the booking ID to start tracking.  
  - Initial ETA is set based on ambulance type:
    - Normal: around 25–45 minutes (simulated)  
    - ICU: around 5–20 minutes (simulated)  
  - A tracking thread updates ambulance coordinates and prints a live ETA countdown on the same console line until arrival.  

## Compilation and Execution

Make sure `gcc` and `pthread` are installed. 

```bash
# Compile
gcc main.c -o bapesss_app -lpthread

# Run
./bapesss_app
Replace main.c with your actual source filename if it is different. [file:1]

Project Structure
text
.
├── main.c                           # Source code for BAPESSS app
├── SPC-AAT-Pavan-Niteesh-PN-2.pdf   # SPC AAT report
└── README.md                        # Project documentation
The report file includes the introduction, algorithm, flowchart, source code, results, and references for this project. [file:1]

Use Cases
Academic demonstration of:

Real-time system simulation in C. 

Practical usage of threads and shared variables. 

Menu-driven console applications. 

Suitable as a first-year B.E. CSE mini-project to learn system-level programming concepts. 

Authors:
DEVELOPERS-
Niteesh Avadhani – 1st Sem B.E, CSE, BMSCE 

Pavan K – 1st Sem B.E, CSE, BMSCE 

References
1) The C Programming Language – Kernighan & Ritchie 

2) POSIX Threads Programming Documentation 

3) GNU C Library Reference Manual [

4) GeeksforGeeks – C Programming and Multithreading concepts 

5) IEEE articles on real-time system simulation 
