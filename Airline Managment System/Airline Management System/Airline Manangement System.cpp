
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct Flight {
    string flightID;
    string destination;
    string departureTime;
    string arrivalTime;
    int totalSeats;
    int availableSeats;
    float Economy_fare;
    float Business_fare;
};

int TotalFlights = 0;
Flight* flights = new Flight[100];


struct Passenger {
    int passengerID;
    string name;
    string email;
    string password;
    string phone;
    float totalSpent = 0;

    // booking info.
    int bookedFlightIndex = -1;
    int bookedClass = 0;
    int bookedSeats = 0;

    bool isBooked = false;
};

int MaxPassenger = 1000;
Passenger passenger[1000];

int PassengerCount = 0;

struct Admin {
    string Admin_Username = "admin";
    string Admin_Pswrd = "admin123";
};



void saveAdmin(Admin& admin) {
    ofstream fout("admin.txt");
    if (!fout.is_open()) {
        cout << "File not open.";
    }
    fout << admin.Admin_Username << "," << admin.Admin_Pswrd;
    fout.close();

}
void AdminLogin(Admin& admin) {
    string username;
    string password;

    cout << "\t\t\t\t---------- Admin Login ----------";
    int login_count = 0;
    while (true) {
        cout << "\nEnter username: ";
        getline(cin, username);

        cout << "Enter Password: ";
        getline(cin, password);

        if (username == admin.Admin_Username && password == admin.Admin_Pswrd) {
            cout << "Login Successfully." << endl;
            return;
        }

        login_count++;
        cout << "Wrong Credentials!\n";
        if (login_count == 3) {
            char choice;
            cout << "\nDo you want to reset your password? (Y/N): ";
            cin >> choice;
            cin.ignore();
            if (choice == 'Y' || choice == 'y')
            {
                cout << "Enter new password: ";
                getline(cin, admin.Admin_Pswrd);
                saveAdmin(admin);
                cout << "\nPassword changed successfully. Please Login Again.\n";
                login_count = 0;

            }
            else {
                cout << "Access Denied.\n";
                return;
            }
        }
    }

}
string breakData(string& line) {
    string token = "";
    int i = 0;
    while (i < line.length() && line[i] != ',') {
        token += line[i];
        i++;
    }
    if (i < line.length()) {
        line.erase(0, i + 1);
    }
    else {
        line.erase(0, i);
    }
    return token;
}
void loadadmin(Admin& admin) {
    ifstream fin("admin.txt");

    if (!fin.is_open()) {

        return;
    }
    string line;
    while (getline(fin, line)) {
        admin.Admin_Username = breakData(line);
        admin.Admin_Pswrd = breakData(line);
    }
    fin.close();
}
void loadFlights(Flight flights[]) {
    ifstream fin("Flights.txt");

    if (!fin.is_open()) {
        return;
    }
    string line;
    int i = 0;
    while (getline(fin, line)) {
        flights[i].flightID = breakData(line);
        flights[i].destination = breakData(line);
        flights[i].departureTime = breakData(line);
        flights[i].arrivalTime = breakData(line);
        flights[i].totalSeats = stoi(breakData(line));
        flights[i].availableSeats = stoi(breakData(line));
        flights[i].Economy_fare = stof(breakData(line));
        flights[i].Business_fare = stof(breakData(line));
        i++;
    }

    TotalFlights = i;
    fin.close();
}
void addFlight(Flight flights[]) {
    ofstream fout("Flights.txt", ios::app);
    if (!fout.is_open()) {
        cout << "File is not open!";
        return;
    }

    int newFlights;
    cout << "Enter total/Available number of flights: ";
    cin >> newFlights;
    cin.ignore();

    for (int i = TotalFlights; i < TotalFlights + newFlights; i++)
    {
        cout << "Enter the ID of Flight " << (i - TotalFlights) + 1 << " : ";
        getline(cin, flights[i].flightID);
        fout << flights[i].flightID << ",";
        cout << "Enter the Destination of Flight " << (i - TotalFlights) + 1 << " : ";
        getline(cin, flights[i].destination);
        fout << flights[i].destination << ",";
        cout << "Enter the Departure time of the Flight " << (i - TotalFlights) + 1 << " : ";
        getline(cin, flights[i].departureTime);
        fout << flights[i].departureTime << ",";
        cout << "Enter the Arrival time of the Flight " << (i - TotalFlights) + 1 << " : ";
        getline(cin, flights[i].arrivalTime);
        fout << flights[i].arrivalTime << ",";
        cout << "Enter the Total seats of the Flight " << (i - TotalFlights) + 1 << " : ";
        cin >> flights[i].totalSeats;
        cin.ignore();
        fout << flights[i].totalSeats << ",";

        flights[i].availableSeats = flights[i].totalSeats;
        fout << flights[i].availableSeats << ",";

        cout << "Enter the Economy Class Fare of the Flight " << (i - TotalFlights) + 1 << " : ";
        cin >> flights[i].Economy_fare;
        cin.ignore();
        fout << flights[i].Economy_fare << ",";
        cout << "Enter the Business ClassFare of the Flight " << (i - TotalFlights) + 1 << " : ";
        cin >> flights[i].Business_fare;
        cin.ignore();
        fout << flights[i].Business_fare;
        fout << endl;

    }

    // Updating Total Flights
    TotalFlights += newFlights;

    fout.close();
    cout << "Flight Added Successfully!\n";
}
void removeFlights(Flight flights[], int& TotalFlights) {
    ifstream fin("Flights.txt");
    if (!fin.is_open()) {
        cout << "Flights not available.\n";
        return;
    }

    TotalFlights = 0;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        flights[TotalFlights].flightID = breakData(line);
        flights[TotalFlights].destination = breakData(line);
        flights[TotalFlights].departureTime = breakData(line);
        flights[TotalFlights].arrivalTime = breakData(line);
        flights[TotalFlights].totalSeats = stoi(breakData(line));
        flights[TotalFlights].availableSeats = flights[TotalFlights].totalSeats;
        flights[TotalFlights].Economy_fare = stof(breakData(line));
        flights[TotalFlights].Business_fare = stof(breakData(line));
        TotalFlights++;
    }
    fin.close();

    string id;
    cout << "Enter the Flight ID to delete: ";
    getline(cin, id);
    bool found = false;
    for (int i = 0; i < TotalFlights; i++) {
        if (flights[i].flightID == id) {
            found = true;
            for (int j = i; j < TotalFlights - 1; j++) {
                flights[j] = flights[j + 1];
            }
            TotalFlights--;
            cout << "Flight " << id << " deleted successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "Flight not found!\n";
        return;
    }

    ofstream fout("Flights.txt", ios::trunc);
    for (int i = 0; i < TotalFlights; i++) {
        fout << flights[i].flightID << ","
            << flights[i].destination << ","
            << flights[i].departureTime << ","
            << flights[i].arrivalTime << ","
            << flights[i].totalSeats << ","
            << flights[i].availableSeats << ","
            << flights[i].Economy_fare << ","
            << flights[i].Business_fare << "\n";

    }
    fout.close();
    cout << "\nUpdated Flight List:\n";
    for (int i = 0; i < 117; i++) {
        cout << "-";
    }
    cout << endl;
    cout << setw(12) << left << "Flight ID"
        << setw(12) << left << "Destination"
        << setw(15) << left << "Departure time"
        << setw(15) << left << "Arrival time"
        << setw(12) << left << "Total seats"
        << setw(15) << left << "Available seats"
        << setw(15) << left << "Economy fare"
        << setw(15) << left << "Business Fare" << endl;

    for (int i = 0; i < 117; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < TotalFlights; i++) {

        cout << setw(10) << left << flights[i].flightID
            << setw(10) << left << flights[i].destination
            << setw(15) << left << flights[i].departureTime
            << setw(15) << left << flights[i].departureTime
            << setw(15) << left << flights[i].arrivalTime
            << setw(10) << left << flights[i].totalSeats
            << setw(15) << left << flights[i].availableSeats
            << setw(15) << left << flights[i].Economy_fare
            << setw(15) << left << flights[i].Business_fare << endl;
    }
    for (int i = 0; i < 117; i++) {
        cout << "-";
    }
    cout << endl;
}
void viewFlights(Flight flights[], int& TotalFlights) {
    cout << "\n\t\t\t================ FLIGHT LIST ================\n\n";

    for (int i = 0; i < 117; i++) {
        cout << "-";
    }
    cout << endl;
    cout << setw(12) << left << "Flight ID"
        << setw(12) << left << "Destination"
        << setw(15) << left << "Departure time"
        << setw(15) << left << "Arrival time"
        << setw(12) << left << "Total seats"
        << setw(15) << left << "Available seats"
        << setw(15) << left << "Economy fare"
        << setw(15) << left << "Business Fare" << endl;

    for (int i = 0; i < 117; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < TotalFlights; i++) {

        cout << setw(10) << left << flights[i].flightID
            << setw(10) << left << flights[i].destination
            << setw(15) << left << flights[i].departureTime
            << setw(15) << left << flights[i].departureTime
            << setw(15) << left << flights[i].arrivalTime
            << setw(10) << left << flights[i].totalSeats
            << setw(15) << left << flights[i].availableSeats
            << setw(15) << left << flights[i].Economy_fare
            << setw(15) << left << flights[i].Business_fare << endl;
    }
    for (int i = 0; i < 117; i++) {
        cout << "-";
    }
    cout << endl;
}
void updateFlights() {
    ofstream fout("Flights.txt", ios::trunc);
    for (int i = 0; i < TotalFlights; i++) {
        fout << flights[i].flightID << ","
            << flights[i].destination << ","
            << flights[i].departureTime << ","
            << flights[i].arrivalTime << ","
            << flights[i].totalSeats << ","
            << flights[i].availableSeats << ","
            << flights[i].Economy_fare << ","
            << flights[i].Business_fare << endl;
    }
    fout.close();
}

int passengerID() {
    ifstream fin("passengers.txt");
    if (!fin.is_open()) {
        return 1001;
    }

    string line;
    int LastID = 1000;

    while (getline(fin, line)) {
        if (!line.empty()) {
            LastID = stoi(breakData(line));
        }
    }

    fin.close();

    LastID++;

    return LastID;
}
void loadPassengers(Passenger passenger[]) {
    ifstream fin("passengers.txt");

    if (!fin.is_open()) {

        return;
    }
    string line;
    int i = 0;
    while (getline(fin, line) && i < MaxPassenger) {
        if (line.empty())
        {
            continue;
        }
        passenger[i].passengerID = stoi(breakData(line));
        passenger[i].name = breakData(line);
        passenger[i].email = breakData(line);
        passenger[i].password = breakData(line);
        passenger[i].phone = breakData(line);
        passenger[i].totalSpent = stof(breakData(line));
        passenger[i].bookedFlightIndex = stoi(breakData(line));
        passenger[i].bookedClass = stoi(breakData(line));
        passenger[i].bookedSeats = stoi(breakData(line));

        string bookedStatus = breakData(line);
        if (bookedStatus == "1") {
            passenger[i].isBooked = true;
        }
        else {
            passenger[i].isBooked = false;
        }
        i++;
    }
    PassengerCount = i;
    fin.close();
}
void addPassenger(Passenger passenger[], int MaxPassenger) {
    if (PassengerCount >= MaxPassenger) {
        cout << "No more space for new passenger!";
        return;
    }

    ofstream fout("passengers.txt", ios::app);
    if (!fout.is_open()) {
        cout << "File not open!";
        return;
    }
    int i = PassengerCount;
    passenger[i].passengerID = passengerID();

    cout << "Enter Passenger Name: ";
    getline(cin, passenger[i].name);

    cout << "Enter Passenger Email: ";
    getline(cin, passenger[i].email);

    cout << "Enter Passenger Phone Number: ";
    getline(cin, passenger[i].phone);

    passenger[i].password = "P" + to_string(passenger[i].passengerID) + "@";

    passenger[i].totalSpent = 0;


    fout << passenger[i].passengerID << ","
        << passenger[i].name << ","
        << passenger[i].email << ","
        << passenger[i].password << ","
        << passenger[i].phone << ","
        << passenger[i].totalSpent << ","
        << -1 << ","
        << 0 << ","
        << 0 << endl;

    fout.close();
    PassengerCount++;

    cout << "\nPassenger Added Successfully..." << endl;
    cout << "Passenger ID: " << passenger[i].passengerID << endl;
    cout << "Passenger Password: " << passenger[i].password << endl;
}
void viewPassengers(Passenger passenger[]) {
    cout << "\n\t\t\t--------- Passenger List ---------\n";
    if (PassengerCount == 0) {
        cout << "No Student added yet!";
        return;
    }

    for (int i = 0; i <= 115; i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << setw(15) << left << "PassengerID"
        << setw(17) << left << "Name"
        << setw(20) << left << "Email"
        << setw(20) << left << "Phone no."
        << setw(15) << left << "Status"
        << setw(10) << left << "Seats"
        << setw(15) << left << "Total Spent" << endl;
    for (int i = 0; i <= 115; i++)
    {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < PassengerCount; i++) {

        cout << setw(15) << left << passenger[i].passengerID
            << setw(17) << left << passenger[i].name
            << setw(20) << left << passenger[i].email
            << setw(20) << left << passenger[i].phone;
        if (passenger[i].isBooked) {
            cout << setw(15) << left << "Booked";
        }
        else {
            cout << setw(15) << left << "Not Booked";
        }
        cout << setw(10) << left << passenger[i].bookedSeats
            << setw(15) << left << passenger[i].totalSpent << endl;

    }
    for (int i = 0; i <= 115; i++) {
        cout << "-";
    }
    cout << endl;

}
void UpdatePassToFile(Passenger passenger[]) {

    ofstream fout("passengers.txt", ios::trunc);
    if (!fout.is_open()) {
        cout << "File not open!";
        return;
    }
    for (int i = 0; i < PassengerCount; i++) {
        fout << passenger[i].passengerID << ","
            << passenger[i].name << ","
            << passenger[i].email << ","
            << passenger[i].password << ","
            << passenger[i].phone << ","
            << passenger[i].totalSpent << ","
            << passenger[i].bookedFlightIndex << ","
            << passenger[i].bookedClass << ","
            << passenger[i].bookedSeats << ",";
        if (passenger[i].isBooked) {
            fout << 1;
        }
        else {
            fout << 0;
        }
        fout << endl;
    }
    fout.close();


}
void updatePassenger(Passenger passenger[]) {
    if (PassengerCount == 0) {
        cout << "No Student added yet!";
        return;
    }

    int searchID;
    cout << "Enter the Passenger ID to Update passenger: ";
    cin >> searchID;

    int passenIndex = -1;
    for (int i = 0; i < PassengerCount; i++)
    {
        if (searchID == passenger[i].passengerID) {
            passenIndex = i;

        }
    }

    if (passenIndex == -1) {
        cout << "Passenger not found!";
        return;
    }
    else
    {
        for (int i = 0; i <= 80; i++)
        {
            cout << "-";
        }
        cout << endl;
        cout << setw(20) << left << "PassengerID"
            << setw(25) << left << "Name"
            << setw(20) << left << "Email"
            << setw(20) << left << "Phone no." << endl;
        for (int i = 0; i <= 80; i++)
        {
            cout << "-";
        }
        cout << endl;

        cout << setw(20) << left << passenger[passenIndex].passengerID
            << setw(25) << left << passenger[passenIndex].name
            << setw(20) << left << passenger[passenIndex].email
            << setw(20) << left << passenger[passenIndex].phone << endl;
        for (int i = 0; i <= 80; i++) {
            cout << "-";
        }
        cout << endl;

        cout << "------Update Menu------\n";
        int updateChoice;
        cout << "1.Update Name\n"
            << "2.Update email\n"
            << "3.Update Phone no.\n";
        cout << "Enter you choice for update: ";
        cin >> updateChoice;
        cin.ignore();
        switch (updateChoice) {
        case 1:

            cout << "Enter new name: ";
            getline(cin, passenger[passenIndex].name);
            cout << "Update Name successfully!";
            UpdatePassToFile(passenger);
            break;
        case 2:
            cout << "Enter new Email: ";
            getline(cin, passenger[passenIndex].email);
            cout << "Update Email successfully!";
            UpdatePassToFile(passenger);
            break;
        case 3:
            cout << "Enter new phone no.: ";
            getline(cin, passenger[passenIndex].phone);
            cout << "Update Phone no. successfully!";
            UpdatePassToFile(passenger);
            break;
        }

    }

}
void removePassenger(Passenger passenger[]) {
    ifstream fin("passengers.txt");
    if (!fin.is_open()) {
        cout << "file not open.\n";
        return;
    }

    PassengerCount = 0;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        passenger[PassengerCount].passengerID = stoi(breakData(line));
        passenger[PassengerCount].name = breakData(line);
        passenger[PassengerCount].email = breakData(line);
        passenger[PassengerCount].password = breakData(line);
        passenger[PassengerCount].phone = breakData(line);
        passenger[PassengerCount].totalSpent = stof(breakData(line));
        PassengerCount++;
    }
    fin.close();

    int id;
    cout << "Enter the Passenger ID to delete: ";
    cin >> id;
    cin.ignore();
    bool found = false;
    for (int i = 0; i < PassengerCount; i++) {
        if (passenger[i].passengerID == id) {
            found = true;
            for (int j = i; j < PassengerCount - 1; j++) {
                passenger[j] = passenger[j + 1];
            }
            PassengerCount--;
            cout << "Passenger " << id << " deleted successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "Passenger not found!\n";
        return;
    }

    UpdatePassToFile(passenger);

    cout << "\nUpdated Passengers List:\n";
    viewPassengers(passenger);
}

void BookFlights(int PsngrIndex) {
    if (passenger[PsngrIndex].bookedFlightIndex != -1)
    {
        cout << "You Already have an active Booking. Cancel it first.\n";
        return;
    }
    string psngr_destination;
    cout << "\nEnter your desired destination: ";
    getline(cin, psngr_destination);


    for (int i = 0; i <= 117; i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << setw(12) << left << "Flight ID"
        << setw(15) << left << "Destination"
        << setw(15) << left << "Departure Time"
        << setw(15) << left << "Arrival Time"
        << setw(13) << left << "Total seats"
        << setw(15) << left << "Available seats"
        << setw(18) << left << "Economy Fare"
        << setw(18) << left << "Business Fare" << endl;
    for (int i = 0; i <= 117; i++)
    {
        cout << "-";
    }

    bool flightsFound = false;
    cout << endl;
    for (int i = 0; i < TotalFlights; i++) {
        if (psngr_destination == flights[i].destination) {
            flightsFound = true;
            cout << setw(12) << left << flights[i].flightID
                << setw(15) << left << flights[i].destination
                << setw(15) << left << flights[i].departureTime
                << setw(15) << left << flights[i].arrivalTime
                << setw(13) << left << flights[i].totalSeats
                << setw(15) << left << flights[i].availableSeats
                << setw(18) << left << flights[i].Economy_fare
                << setw(18) << left << flights[i].Business_fare << endl;
        }
    }
    if (!flightsFound) {
        cout << "Sorry! No flights Available to " << psngr_destination << endl;
        return;
    }
    for (int i = 0; i <= 117; i++)
    {
        cout << "-";
    }
    cout << endl;

    //to get booked flight index

    string selectedFlightID;
    cout << "Enter the flight ID you want to book: ";
    getline(cin, selectedFlightID);
    int flightIndex = -1;
    for (int i = 0; i < TotalFlights; i++) {
        if (selectedFlightID == flights[i].flightID) {
            flightIndex = i;
            break;
        }
    }
    if (flightIndex == -1)
    {
        cout << "Invalid flight ID!";
        return;
    }

    passenger[PsngrIndex].bookedFlightIndex = flightIndex;

    //to get travel class

    int selectedClass;

    cout << "Select Class ( 1.Economy\t2.Business ): ";
    cin >> selectedClass;
    cin.ignore();
    while (selectedClass != 1 && selectedClass != 2) {
        cout << "Invalid Choice! Select Again: ";
        cin >> selectedClass;
        cin.ignore();
    }
    passenger[PsngrIndex].bookedClass = selectedClass;

    // to get passengerSeats

    int bookedSeats;
    cout << "Enter number of seats ";
    cin >> bookedSeats;
    cin.ignore();
    if (bookedSeats > flights[flightIndex].availableSeats) {
        cout << "Not enough seats available. Only " << flights[flightIndex].availableSeats << " left." << endl;
        return;
    }
    flights[flightIndex].availableSeats -= bookedSeats;
    passenger[PsngrIndex].bookedSeats = bookedSeats;

    // Calculate Fare.

    double fare = 0;
    if (passenger[PsngrIndex].bookedClass == 1) {
        fare = flights[flightIndex].Economy_fare * bookedSeats;
    }
    if (passenger[PsngrIndex].bookedClass == 2) {
        fare = flights[flightIndex].Business_fare * bookedSeats;

    }

    passenger[PsngrIndex].totalSpent += fare;
    passenger[PsngrIndex].isBooked = true;

    // Passenger Booked Flight Update To File

    UpdatePassToFile(passenger);
    updateFlights();
    cout << "Booked flight successfully...";
}
void cancelReservations(int PsngrIndex) {
    if (passenger[PsngrIndex].bookedFlightIndex == -1)
    {
        cout << "No booking found for your destination\n";
        return;
    }

    int flightIndex = passenger[PsngrIndex].bookedFlightIndex;
    cout << "You booked Flight ID: " << flights[flightIndex].flightID << endl;
    cout << "Destination: " << flights[flightIndex].destination << endl;
    cout << "Seats: " << passenger[PsngrIndex].bookedSeats << endl;

    char confirm;
    cout << "Do you really want to cancel your reservations (Y/N) ?: ";
    cin >> confirm;
    cin.ignore();

    if (confirm == 'Y' || confirm == 'y') {
        double refund = 0;
        if (passenger[PsngrIndex].bookedClass == 1) {
            refund = flights[flightIndex].Economy_fare * passenger[PsngrIndex].bookedSeats;
        }

        if (passenger[PsngrIndex].bookedClass == 2) {
            refund = flights[flightIndex].Business_fare * passenger[PsngrIndex].bookedSeats;

        }
        flights[flightIndex].availableSeats += passenger[PsngrIndex].bookedSeats;
        passenger[PsngrIndex].totalSpent -= refund;
        passenger[PsngrIndex].bookedFlightIndex = -1;
        passenger[PsngrIndex].bookedClass = 0;
        passenger[PsngrIndex].bookedSeats = 0;
        passenger[PsngrIndex].isBooked = false;

        UpdatePassToFile(passenger);

        cout << "Booking cancelled Successfully. Refund Rupees: " << refund << endl;
    }
    else if (confirm == 'N' || confirm == 'n') {
        cout << "Exiting Cancel menu....";
        return;
    }
    else {
        cout << "Invalid Input!";
        return;
    }
    updateFlights();
}
void generateReport(int PsngrIndex) {
    if (passenger[PsngrIndex].bookedFlightIndex == -1)
    {
        cout << "No booking found for your destination ";
        return;
    }

    int findex = passenger[PsngrIndex].bookedFlightIndex;
    cout << "=============== BOOKING REPORT ===============";
    cout << "\nPassenger Name    : " << passenger[PsngrIndex].name;
    cout << "\nPassemger ID      : " << passenger[PsngrIndex].passengerID;
    cout << "\nPhone Number      : " << passenger[PsngrIndex].phone;
    cout << "\nEmail             : " << passenger[PsngrIndex].email;

    cout << "\n--- Flight Details ---\n";
    cout << "Flight ID           : " << flights[findex].flightID;
    cout << "\nDestination       : " << flights[findex].destination;
    cout << "\nDeparture Time    : " << flights[findex].departureTime;
    cout << "\nArrival Time      : " << flights[findex].arrivalTime;
    cout << "\nSeats Bookes      : " << passenger[PsngrIndex].bookedSeats << endl;

    cout << "Class               : ";
    if (passenger[PsngrIndex].bookedClass == 1) {
        cout << "Economy" << endl;
    }
    else if (passenger[PsngrIndex].bookedClass == 2) {
        cout << "Business" << endl;
    }
    else {
        cout << "Unknown" << endl;
    }

    double fare = 0;
    if (passenger[PsngrIndex].bookedClass == 1) {
        fare = flights[findex].Economy_fare * passenger[PsngrIndex].bookedSeats;
    }
    if (passenger[PsngrIndex].bookedClass == 2) {
        fare = flights[findex].Business_fare * passenger[PsngrIndex].bookedSeats;
    }

    cout << "Total Fare          : " << fare << " Rupees" << endl;
    cout << "Total Amount Spent  : " << passenger[PsngrIndex].totalSpent << " Rupees" << endl;
    cout << "Available seats left on Flight: " << flights[findex].availableSeats << endl;
    cout << "===============================================================";
}

void passengerMenu(int PsngrIndex) {
    int choice;
    do {
        cout << "\n--- PASSENGER MENU ---\n"
            << "1. Book Flights\n"
            << "2. Cancel Reservations\n"
            << "3. View Available Flights\n"
            << "4. Generate Booking Report\n"
            << "0. Exit\n"
            << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: BookFlights(PsngrIndex); break;
        case 2: cancelReservations(PsngrIndex); break;
        case 3: viewFlights(flights, TotalFlights); break;
        case 4: generateReport(PsngrIndex); break;
        case 0: cout << "Exit successfully.";
            return;
        default: cout << "Invalid Input." << endl; break;
        }

    } while (choice != 0);
}
void passengerlogin(Passenger passenger[]) {
    int loginID;
    cout << "Enter your ID provided by Admin: ";
    cin >> loginID;
    cin.ignore();

    int PsngrIndex = -1;
    for (int i = 0; i < PassengerCount; i++) {

        if (loginID == passenger[i].passengerID) {
            PsngrIndex = i;
            break;
        }
    }
    if (PsngrIndex == -1) {
        cout << "ID not found, Kindly Register first from Admin.\n";
        return;
    }
    cout << "ID Found." << endl;
    int attempts = 0;
    string loginPswrd;
    while (attempts < 3) {
        cout << "Enter your Password provided by Admin: ";
        getline(cin, loginPswrd);
        if (loginPswrd == passenger[PsngrIndex].password) {
            cout << "\nLogin Successfully...\n\n";
            passengerMenu(PsngrIndex);
            return;
        }
        else {
            attempts++;
            cout << "\nWrong Password!. Attempts Left: " << (3 - attempts) << endl;
        }
    }
    cout << "Too Many wrong Attempts. Access Denied!" << endl;
}

void adminMenu(Passenger passenger[], int MaxPassenger) {
    int choice;
    do {
        cout << "\n--- ADMIN MENU ---\n"
            << "1. Add Flights\n"
            << "2. Remove Flight\n"
            << "3. View Flights\n"
            << "4. Add Passenger\n"
            << "5. Update Passenger\n"
            << "6. Remove Passenger\n"
            << "7. View Passengers\n"
            << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addFlight(flights); break;
        case 2: removeFlights(flights, TotalFlights); break;
        case 3: viewFlights(flights, TotalFlights); break;
        case 4: addPassenger(passenger, MaxPassenger); break;
        case 5: updatePassenger(passenger); break;
        case 6: removePassenger(passenger); break;
        case 7: viewPassengers(passenger); break;
        case 0: cout << "Exit successfully.";
            return;
        default: cout << "Invalid Input." << endl; break;
        }
    } while (choice != 0);
}

int main()
{
    Admin admin;
    cout << "\t\t\t";
    for (int i = 0; i < 60; i++) {
        cout << "=";
    }
    cout << endl;
    cout << "\t\t\t\t\tAirline Management System " << endl;
    cout << "\t\t\t";
    for (int i = 0; i < 60; i++) {
        cout << "=";
    }
    cout << endl;
    loadadmin(admin);
    loadFlights(flights);

    /*int MaxPassenger = 1000;
    Passenger passenger[1000];*/

    loadPassengers(passenger);

    cout << endl;

    int main_selection;

    do {
        cout << "Main Menu:" << endl;
        cout << "1. Passenger\n2. Admin\n0. Exit" << endl;
        cout << "Enter your selection: " << endl;
        cin >> main_selection;
        cin.ignore();
        switch (main_selection)
        {
        case 1:
        {
            passengerlogin(passenger);
            break;
        }
        case 2:
        {
            AdminLogin(admin);
            adminMenu(passenger, MaxPassenger);


            // addFlight(flights,TotalFlights);

            break;
        }
        case 0:
        {
            cout << "\t\t\t--------- Exit Successfully ---------" << endl;
            delete[] flights;
            return 0;
        }
        default:
        {
            cout << "Invalid Selection !" << endl;
            break;
        }
        }

    } while (true);

    return 0;
}



