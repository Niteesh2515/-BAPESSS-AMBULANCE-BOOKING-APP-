#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int x;
    int y;
} Location;

/* ---------- GLOBAL VARIABLES ---------- */
int bookingExists = 0;
int trackingActive = 0;
int typeChoice;
int fare;

int currentETA;                 // shared countdown ETA

long long bookingId;

char patientName[50], pickup[100], hospital[100];
char ambulanceType[20];

Location ambulancePos, pickupPos;

/* ---------- BOOKING ID ---------- */
long long generateBookingId() {
    long long id = (rand() % 9) + 1;
    for (int i = 1; i < 10; i++)
        id = id * 10 + (rand() % 10);
    return id;
}

/* ---------- TRACKING THREAD (INLINE COUNTDOWN) ---------- */
void* trackAmbulance(void* arg) {

    while (trackingActive && currentETA > 0) {

        if (ambulancePos.x < pickupPos.x) ambulancePos.x++;
        if (ambulancePos.y < pickupPos.y) ambulancePos.y++;

        /* 🔹 UPDATE SAME LINE */
        printf("\r[ETA COUNTDOWN] ETA: %d mins   ", currentETA);
        fflush(stdout);

        if (typeChoice == 1)
            usleep(2500000);   // Normal → 2.5 sec
        else
            sleep(5);          // ICU → 5 sec

        currentETA--;
    }

    printf("\r[ETA COUNTDOWN] STATUS: Ambulance has ARRIVED!   \n");
    trackingActive = 0;
    return NULL;
}

/* ---------- MAIN ---------- */
int main() {
    int choice;
    long long enteredId;
    pthread_t trackingThread;

    srand(time(NULL));

    while (1) {

        printf("\n=== BAPESSS Ambulance Booking App ===\n");
        printf("1. Book Ambulance\n");
        printf("2. View Booking Details\n");
        printf("3. Track Ambulance (Live Location)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        /* ---------- BOOK ---------- */
        if (choice == 1) {
            printf("\nEnter patient name: ");
            fgets(patientName, sizeof(patientName), stdin);
            patientName[strcspn(patientName, "\n")] = 0;

            printf("Enter pickup location: ");
            fgets(pickup, sizeof(pickup), stdin);

            pickupPos.x = rand() % 101;
            pickupPos.y = rand() % 101;

            printf("Enter hospital name: ");
            fgets(hospital, sizeof(hospital), stdin);

            printf("\nSelect ambulance type:\n");
            printf("1. Normal (Rs.1000)\n");
            printf("2. ICU    (Rs.2000)\n");
            printf("Enter choice: ");
            scanf("%d", &typeChoice);
            getchar();

            if (typeChoice == 1) {
                fare = 1000;
                strcpy(ambulanceType, "Normal");
            } else {
                fare = 2000;
                strcpy(ambulanceType, "ICU");
            }

            ambulancePos = pickupPos;

            bookingId = generateBookingId();
            bookingExists = 1;

            printf("\n--- BOOKING CONFIRMED ---\n");
            printf("Booking ID   : %lld\n", bookingId);
            printf("Pickup Coord : (%d, %d)\n",
                   pickupPos.x, pickupPos.y);
        }

        /* ---------- VIEW ---------- */
        else if (choice == 2) {
            if (!bookingExists) {
                printf("\nNo booking found.\n");
            } else {
                printf("\nEnter Booking ID: ");
                scanf("%lld", &enteredId);

                if (enteredId == bookingId) {
                    printf("\n--- BOOKING DETAILS ---\n");
                    printf("Patient Name   : %s\n", patientName);
                    printf("Pickup Address : %s", pickup);
                    printf("Hospital Name  : %s", hospital);
                    printf("Ambulance Type : %s\n", ambulanceType);
                    printf("Fare           : Rs.%d\n", fare);
                }
            }
        }

        /* ---------- TRACK (OPTION 1) ---------- */
        else if (choice == 3) {
            if (!bookingExists || trackingActive) {
                printf("\nNo active tracking available.\n");
            } else {
                printf("\nEnter Booking ID to track: ");
                scanf("%lld", &enteredId);
                getchar();

                if (enteredId == bookingId) {

                    if (typeChoice == 1)
                        currentETA = 25 + rand() % 21;  // Normal
                    else
                        currentETA = 5 + rand() % 16;   // ICU

                    printf("\n[Tracking STARTED for %s (%s)]\n",
                           patientName, ambulanceType);
                    printf("Patient Position   : (%d, %d)\n",
                           pickupPos.x, pickupPos.y);
                    printf("Ambulance Pos      : (%d, %d) | ETA: %d mins\n",
                           ambulancePos.x, ambulancePos.y, currentETA);

                    /* 👇 Countdown line created HERE */
                    printf("[ETA COUNTDOWN] ETA: %d mins\n", currentETA);
                    printf("(Tracking running in background.Press ENTER to return to menu)");
                    getchar();   // OPTION-1

                    trackingActive = 1;
                    pthread_create(&trackingThread, NULL, trackAmbulance, NULL);
                    pthread_detach(trackingThread);
                }
            }
        }

        /* ---------- EXIT ---------- */
        else if (choice == 4) {
            printf("\nThank you for using BAPESSS Ambulance App.\n");
            break;
        }
    }

    return 0;
}
