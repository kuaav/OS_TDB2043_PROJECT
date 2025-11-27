/*
 * Program: C-SCAN Disk Scheduling Algorithm Simulation
 * Course: Operating Systems (TDB2043)
 * Group Project
 * 
 * Authors: 
 * Puteri Banafsha Binti Azmi (22010863)
 * Safa Sarfraz (24001006)
 * Aisyah Sofea Binti Mohd Sallehuddin (22011342)
 * Dania Anessa binti Mohd Aswawi (22011086)
 * Sobena A/P Ramachanthirarao (22010905)
 */
 
#include <iostream>
#include <limits> // Used for input validation
using namespace std;
 
// ==========================================
// FUNCTION: clearInput
// PURPOSE: Clear invalid input from cin buffer
// ==========================================
void clearInput() {
    cin.clear(); // Reset the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove leftover input
}
 
// ==========================================
// FUNCTION: cscan
// PURPOSE: Implement C-SCAN disk scheduling algorithm
// INPUT PARAMETERS:
//    isUp: Direction of scanning (true = UP, false = DOWN)
//    requests: Array of track requests
//    n: Number of requests
//    initial: Initial disk arm position
// OUTPUT:
//    totalTravel: Total number of tracks travelled
// ==========================================
int cscan(bool isUp, int* requests, int n, int initial) {
    int currentPos = initial;
    int totalTravel = 0;
 
    // ==========================
    // DIRECTION: UP (C-SCAN UPWARD)
    // ==========================
    if (isUp) {
        // STEP 1: Service all requests >= current position (moving upward)
        for (int i = 0; i < n; i++) {
            if (requests[i] >= currentPos) {
                // Calculate distance between current position and target request
                int travel = abs(requests[i] - currentPos);
 
                cout << currentPos << "\t\t" << requests[i] 
                     << "\t\t\t" << travel << endl;
 
                totalTravel += travel;
                currentPos = requests[i];
            }
        }
 
        // STEP 2: Move to end of disk (track 199)
        if (currentPos != 199) {
            int travel = 199 - currentPos;
            cout << currentPos << "\t\t199\t\t\t" << travel << endl;
            totalTravel += travel;
            currentPos = 199;
        }
 
        // STEP 3: Wrap around from end to beginning (199 to 0)
        cout << "199\t\t0\t\t\t199" << endl;
        totalTravel += 199;
        currentPos = 0;
 
        // STEP 4: Service remaining requests that are < initial position
        for (int i = 0; i < n; i++) {
            if (requests[i] < initial) {
                int travel = abs(requests[i] - currentPos);
 
                cout << currentPos << "\t\t" << requests[i] 
                     << "\t\t\t" << travel << endl;
 
                totalTravel += travel;
                currentPos = requests[i];
            }
        }
    }
    // ==========================
    // DIRECTION: DOWN (C-SCAN DOWNWARD)
    // ==========================
    else {
        // STEP 1: Service all requests <= current position (moving downward)
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= currentPos) {
                int travel = abs(requests[i] - currentPos);
 
                cout << currentPos << "\t\t" << requests[i] 
                     << "\t\t\t" << travel << endl;
 
                totalTravel += travel;
                currentPos = requests[i];
            }
        }
 
        // STEP 2: Move to start of disk (track 0)
        if (currentPos != 0) {
            int travel = currentPos;
            cout << currentPos << "\t\t0\t\t\t" << travel << endl;
            totalTravel += travel;
            currentPos = 0;
        }
 
        // STEP 3: Wrap around from beginning to end (0 to 199)
        cout << "0\t\t199\t\t\t199" << endl;
        totalTravel += 199;
        currentPos = 199;
 
        // STEP 4: Service remaining requests that are > initial position
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] > initial) {
                int travel = abs(requests[i] - currentPos);
 
                cout << currentPos << "\t\t" << requests[i] 
                     << "\t\t\t" << travel << endl;
 
                totalTravel += travel;
                currentPos = requests[i];
            }
        }
    }
 
    return totalTravel;
}
 
// ==========================================
// FUNCTION: main
// PURPOSE: Program entry point - handles user input and program flow
// ==========================================
int main() {
    int requests[100];  // Array to store disk requests (max 100)
    int n;              // Number of requests
    int initial;        // Initial position of disk arm
    int totalTravel = 0; // Total tracks travelled
    char direction[10]; // Direction string (UP or DOWN)
 
    cout << "=== C-SCAN Disk Scheduling Simulator ===" << endl;
    cout << "Disk Range: 0 to 199 tracks" << endl << endl;
 
    // ==========================
    // 1. INPUT VALIDATION BLOCK
    // ==========================
 
    // Validate initial arm position (0-199)
    do {
        cout << "Enter initial arm position (0-199): ";
        cin >> initial;
 
        // Check for invalid input or out-of-range values
        if (cin.fail() || initial < 0 || initial > 199) {
            cout << "Invalid input! Arm position must be between 0 and 199." << endl;
            clearInput();
        }
    } while (cin.fail() || initial < 0 || initial > 199);
 
    // Validate direction input (UP or DOWN only)
    do {
        cout << "Enter direction (UP/DOWN): ";
        cin >> direction;
 
        // Check if first character is U/u or D/d
        if (!(direction[0] == 'U' || direction[0] == 'u' ||
              direction[0] == 'D' || direction[0] == 'd')) {
            cout << "Invalid direction! Please enter UP or DOWN." << endl;
        }
    } while (!(direction[0] == 'U' || direction[0] == 'u' ||
               direction[0] == 'D' || direction[0] == 'd'));
 
    // Validate number of requests (1-100)
    do {
        cout << "Enter number of track requests (1-100): ";
        cin >> n;
 
        if (cin.fail() || n < 1 || n > 100) {
            cout << "Invalid number! Must be between 1 and 100." << endl;
            clearInput();
        }
    } while (cin.fail() || n < 1 || n > 100);
 
    // Validate each individual track request (0-199)
    cout << "Enter track requests (0-199):" << endl;
    for (int i = 0; i < n; i++) {
        do {
            cout << "Request " << (i + 1) << ": ";
            cin >> requests[i];
 
            // Ensure each track request is within valid range
            if (cin.fail() || requests[i] < 0 || requests[i] > 199) {
                cout << "Invalid track! Must be between 0 and 199." << endl;
                clearInput();
            }
        } while (cin.fail() || requests[i] < 0 || requests[i] > 199);
    }
 
    // ==========================
    // 2. REQUEST SORTING (Bubble Sort Algorithm)
    // ==========================
    // Sort requests in ascending order for C-SCAN processing
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (requests[j] > requests[j + 1]) {
                // Swap elements if they are in wrong order
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
 
    // Display sorted requests to user
    cout << "\nSorted requests: ";
    for (int i = 0; i < n; i++) {
        cout << requests[i] << " ";
    }
    cout << "\n" << endl;
 
    // ==========================
    // 3. C-SCAN ALGORITHM EXECUTION
    // ==========================
    cout << "OUTPUT" << endl;
    cout << "==========" << endl;
    cout << "Initial Arm Position: " << initial 
         << "  Direction: " << direction << endl;
 
    cout << "\nStart\tFinished\tTrack Travelled" << endl;
    cout << "-----\t--------\t---------------" << endl;
 
    // Convert direction string to boolean flag
    bool isUp = (direction[0] == 'U' || direction[0] == 'u');
 
    // Execute C-SCAN algorithm
    totalTravel = cscan(isUp, requests, n, initial);
 
    // ==========================
    // 4. FINAL RESULTS OUTPUT
    // ==========================
    cout << "\nTotal Track Travelled: " << totalTravel << endl;
    cout << "Simulation completed successfully!" << endl;
 
    return 0;
}
