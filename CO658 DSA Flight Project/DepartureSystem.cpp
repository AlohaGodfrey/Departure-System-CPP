#include "DepartureSystem.h"
#include <string>
using namespace std;
DepartureSystem::DepartureSystem()
{
    currentState = SELECT;

    //Poppulate Departure System with Flights
    

    //Load flights to MALTA
    departureSystem[0].destination = MALTA;
    departureSystem[0].availability = 10;
    departureSystem[0].price = 100;
    departureSystem[0].priceDelta = 3;
    departureSystem[0].luggageStack = new Stack(10);
    //Load flights to ATHENS
    departureSystem[1].destination = ATHENS;
    departureSystem[1].availability = 15;
    departureSystem[1].price = 120;
    departureSystem[1].priceDelta = 8;
    departureSystem[1].luggageStack = new Stack(10);
    //Load flights to MALTA
    departureSystem[2].destination = ROME;
    departureSystem[2].availability = 5;
    departureSystem[2].price = 150;
    departureSystem[2].priceDelta = 10;
    departureSystem[2].luggageStack = new Stack(10);

   
    
    tourist.name = "User";
    tourist.credits = 10000; //10,000 credits in account
}

void DepartureSystem::runDepartureSystemFSM()
{
    while (true)
    {
        switch (currentState)
        {
        case SELECT:

            printSystemStatus(tourist, departureSystem);
            // User inputs the destination. if valid destination selected, move to next state; else go back to SELECT
            int selectedDestination;
            cin >> selectedDestination;

            switch (selectedDestination)
            {
            case MALTA:
                saveDestination("MALTA", MALTA, selectedFlight, currentState);
                break;
            case ATHENS:
                saveDestination("ATHENS", ATHENS, selectedFlight, currentState);
                break;
            case ROME:
                saveDestination("ROME", ROME, selectedFlight, currentState);
                break;
            case 500:
                //ticket search system uses a key to search the passenger Manifest
                searchPassengerManifest(passengerManifestHT);
                currentState = SELECT;
                cout << "Invalid Destination Selected" << endl;
                cout << endl << endl;
                break;
            default:
                currentState = SELECT;
                cout << "Invalid Destination Selected" << endl;
                cout << endl << endl;
                break;
            }
            break;
        case AVAILABILITY:
            //retrive the amount of seats the user wants to reserve
            cout << "How many seats would you like to reserve? ";
            int ticketQuantity;
            cin >> ticketQuantity;
            //Check if flight is overbooked
            switch (selectedFlight.destination) {
            case MALTA:
                departureSystemAvailability(0, ticketQuantity, currentState, departureSystem);
                break;
            case ATHENS:
                departureSystemAvailability(1, ticketQuantity, currentState, departureSystem);
                break;
            case ROME:
                departureSystemAvailability(2, ticketQuantity, currentState, departureSystem);
                break;
            default:
                cout << "Invalid Amount Recieved." << endl;
                break;
            }
            break;
        case CALCULATE:
            //calcualte the final ticket price
            cout << "The total cost for your ticket(s) is: ";
            int cost;
            switch (selectedFlight.destination)
            {
            case MALTA:
                departureSystemCalculate(0, cost, ticketQuantity, departureSystem);
                break;
            case ATHENS:
                departureSystemCalculate(1, cost, ticketQuantity, departureSystem);
                break;
            case ROME:
                departureSystemCalculate(2, cost, ticketQuantity, departureSystem);
                break;
            default:
                cout << "Error!" << endl;
                break;
            }

            //collect payment from customer and adjust balance
            collectPayment(cost, tourist, currentState);
            break;
        case ALLOCATION:
            //Allocate the seats on flight, update the departure system (increase ticket price and update new availablitiy)
            //stores baggage in luggage system
            //issue the customers with their ticket ID's

            for (int i = 0; i < ticketQuantity; i++) {
                cout << endl << "Enter Name for Passenger " << i + 1 << ": ";
                string name;
                cin >> name;

                int ticketNumber = 0;
                string ticketDetails;
                switch (selectedFlight.destination)
                {
                case MALTA:
                    departureSystemAllocation(100, 0, departureSystem, passengerManifestHT, ticketDetails, name);
                    break;
                case ATHENS:
                    departureSystemAllocation(200, 1, departureSystem, passengerManifestHT, ticketDetails, name);
                    break;
                case ROME:
                    departureSystemAllocation(300, 2, departureSystem, passengerManifestHT, ticketDetails, name);
                    break;
                default:
                    cout << "Error!" << endl;
                    currentState = SELECT;
                    cout << endl << endl;
                    break;
                }
            }
            cout << endl;
            cout << "[[[[  ...Automatically Checked in Baggage...  ]]]" << endl;
            cout << "[[[[   Take Tickets and Proceed to Boarding   ]]]" << endl;
            cout << "[[[[         Departure System Updated         ]]]" << endl;
            currentState = SELECT;
            cout << endl << endl;
            break;
        default:
            cout << "Error Invalid State Detected " << endl;
            currentState = SELECT;
            break;
        }
    }
}

void DepartureSystem::printSystemStatus(Tourist tourist, Flights departureSystem[])
{
    //1. Display the current status for the Departure System and the customers account balance
    cout << " <<<<<<---CURRENT STATUS--->>>>>>" << endl;
    cout << "[[[Departure System]]]" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Flight ID " << departureSystem[i].destination << " has " << departureSystem[i].availability << " seats available, and each costs " << departureSystem[i].price << " credts." << endl;
    }
    cout << "[[[Logged In]]]" << endl;
    cout << tourist.name << " has " << tourist.credits << " credits total." << endl;
    cout << "<<<<<<   END STATUS   >>>>>>" << endl << endl;
    cout << "Please select a destination (ID) from the following avaialble options: " << endl;
    cout << "MALTA ID = 100\nATHENS ID = 200\nROME ID = 300\nFind Flight? = 500" << endl;
    cout << "Menu Option: ";
}

void DepartureSystem::saveDestination(string country, Destinations countryEnum, Flights& selectedFlight, DepartureControlState& currentState)
{
    cout << "You have selected " << country << endl;
    selectedFlight.destination = countryEnum;
    currentState = AVAILABILITY;
}

void DepartureSystem::collectPayment(int cost, Tourist tourist, DepartureControlState& currentState)
{
    //collect payment from customer and adjust balance
    int payment;
    cout << "Please type in your payment (credits): ";
    cin >> payment;

    if (payment > tourist.credits || payment < cost || payment <= 0) {
        cout << "You don't have enough credits" << endl;
        currentState = SELECT;
        cout << endl << endl;
    }
    else {
        tourist.credits -= payment;
        int change = payment - cost;
        cout << "Thank you! Your change is " << change << " credits." << endl;
        tourist.credits += change;
        currentState = ALLOCATION;
    }
}

void DepartureSystem::departureSystemCalculate(int flightIndex, int& cost, int ticketQuantity, Flights departureSystem[])
{
    cost = departureSystem[0].price * ticketQuantity;
    cout << cost << endl;
}

void DepartureSystem::departureSystemAvailability(int flightIndex, int ticketQuantity, DepartureControlState& currentState, Flights departureSystem[])
{
    if (ticketQuantity < 0 || ticketQuantity > departureSystem[flightIndex].availability) {
        cout << "Flight Overbooked" << endl;
        currentState = SELECT;
        cout << endl << endl;
    }
    else
    {
        cout << "Your order has been recieved. You reserved " << ticketQuantity << " seat(s)." << endl;
        currentState = CALCULATE;
    }
}

void DepartureSystem::departureSystemAllocation(int flightMultiplier, int flightIndex, Flights departureSystem[], HashTable& passengerManifestHT, string ticketDetails, string name)
{
    int ticketNumber = 0;
    ticketNumber = departureSystem[flightIndex].availability + flightMultiplier;
    departureSystem[flightIndex].luggageStack->Push(ticketNumber);

    ticketDetails = "Destination: MALTA\nPassenger Name: " + name;
    passengerManifestHT.insertItem(ticketNumber, ticketDetails);
    cout << name << "'s Ticket ID and Baggage ID: " << ticketNumber << endl;

    //removes seat available and increases price after ticket is allocated
    departureSystem[flightIndex].availability -= 1;
    departureSystem[flightIndex].price += departureSystem[flightIndex].priceDelta;
}

void DepartureSystem::searchPassengerManifest(HashTable passengerManifestHT)
{
    int ticketSearch = 1;
    while (ticketSearch)
    {
        cout << "Enter ticket ID (0 to Exit): ";
        cin >> ticketSearch;
        cout << passengerManifestHT.searchTable(ticketSearch) << endl;
    }
}
