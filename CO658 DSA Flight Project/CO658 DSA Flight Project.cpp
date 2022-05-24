// CO658 DSA Flight Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "HashTable.h"
#include "Stack.h"

using namespace std;

enum DepartureControlState{
        SELECT, AVAILABILITY, CALCULATE, ALLOCATION
};

enum Destinations {
    MALTA = 100, ATHENS = 200, ROME = 300
};

struct Flights {
    Destinations destination;
    HashTable passengerManifestHT;
    Stack* luggageStack;
    int availability;
    int price;
};

struct Tourist
{
    string name;
    int credits;
};

void StackTest() {
    Stack* myStack = new Stack(10);
    myStack->Push(5);
    myStack->Push(7);
    myStack->Push(3);
    myStack->Push(11);
    while (!myStack->IsEmpty()) 
    {
        cout << myStack->Pop() << endl;
    }
}

void HashTableTest() {
    HashTable HT;

    if (HT.isEmpty()) {
        cout << "Correct answer. Good job" << endl;
    }
    else {
        cout << "Oh oh. We need to check out code!" << endl;
    }

    HT.insertItem(905, "Jim");
    HT.insertItem(201, "Tom");
    HT.insertItem(782, "Dick");
    HT.insertItem(344, "Harry");
    HT.insertItem(747, "James");
    HT.insertItem(169, "Lewis");
    HT.insertItem(958, "Capaldi");
    HT.insertItem(323, "Leroy");
    HT.insertItem(323, "Lewandowski");

    HT.printTable();

    HT.removeItem(344);
    HT.removeItem(100);

    if (HT.isEmpty()) {
        cout << "Oh oh. We need to check out code!" << endl;
    }
    else {
        cout << "Correct answer. Good job" << endl;
    }

    cout << HT.searchTable(344) << endl;
};

int main()
{
    //HashTableTest();
    //StackTest();
    //Initial Departure System state is SELECT  . Update upon state change
    DepartureControlState currentState = SELECT;

    //Poppulate Departure System with Flights
    Flights departureSystem[3];

    //Load flights to MALTA
    departureSystem[0].destination = MALTA;
    departureSystem[0].availability = 10;
    departureSystem[0].price = 100;
    departureSystem[0].luggageStack = new Stack(10);
    //Load flights to ATHENS
    departureSystem[1].destination = ATHENS;
    departureSystem[1].availability = 15;
    departureSystem[1].price = 120;
    //Load flights to MALTA
    departureSystem[2].destination = ROME;
    departureSystem[2].availability = 5;
    departureSystem[2].price = 150;

    Flights selectedFlight;
    Tourist customer;
    customer.name = "John";
    customer.credits = 100000; //100,000 credits in account

    while (true)
    {
        switch (currentState)
        {
        case SELECT:
            //1. Display the current status for the Departure System and the customers Wallet
            cout << " <<<<<<---CURRENT STATUS--->>>>>>" << endl;
            cout << "[[[Departure System]]]" << endl;
            for (int i = 0; i < 3; i++) {
                cout << departureSystem[i].destination << " has " << departureSystem[i].availability << " seats available, and each costs " << departureSystem[i].price << " credts." << endl;
            }
            cout << "[[[Tourist]]]" << endl;
            cout << customer.name << " has " << customer.credits << " credits total." << endl;
            cout << "<<<<<<   END STATUS   >>>>>>" << endl << endl;
            //2. Ask the user what is their desired destination
            cout << "Please select a drink from the following avaialble options: " << endl;
            //3. Display the Destinations and the corresponding ID values
            cout << "MALTA = 100\nATHENS = 200\nROME = 300" << endl;
            //4. User inputs the destination
            int selectedDestination;
            cin >> selectedDestination;
            //5. if valid destination selected, move to next state; else go back to SELECT
            switch (selectedDestination)
            {
            case MALTA:
                cout << "You have selected MALTA" << endl;
                selectedFlight.destination = MALTA;
                currentState = AVAILABILITY;
                break;
            case ATHENS:
                cout << "You have selected ATHENS" << ATHENS;
                selectedFlight.destination = ATHENS;
                currentState = AVAILABILITY;
                break;
            case ROME:
                cout << "You have selected ROME" << endl;
                selectedFlight.destination = ROME;
                currentState = AVAILABILITY;
                break;
            default:
                cout << "Invalid Destination Selected" << endl;
                currentState = SELECT;
                break;
            }
            break;
        case AVAILABILITY:
            //retrive the amount of seats the user wants to reserve
            //maybe add max???
            cout << "How many seats would you like to reserve? ";
            int ticketQuantity;
            cin >> ticketQuantity;

            cout << "Your order has been recieved. You reserved " << ticketQuantity << " seat(s)." << endl;
            switch (selectedFlight.destination) {
            case MALTA:
                if (ticketQuantity < 0 || ticketQuantity > departureSystem[0].availability) {
                    cout << "Flight Overbooked" << endl;
                    currentState = SELECT;
                    cout << endl << endl;
                }
                else
                {
                    currentState = CALCULATE;
                }
                break;
            case ATHENS:
                if (ticketQuantity < 0 || ticketQuantity > departureSystem[1].availability) {
                    cout << "Flight Overbooked" << endl;
                    currentState = SELECT;
                    cout << endl << endl;
                }
                else
                {
                    currentState = CALCULATE;
                }
                break;
            case ROME:
                if (ticketQuantity < 0 || ticketQuantity > departureSystem[2].availability) {
                    cout << "Flight Overbooked" << endl;
                    currentState = SELECT;
                    cout << endl << endl;
                }
                else
                {
                    currentState = CALCULATE;
                }
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
                cost = departureSystem[0].price * ticketQuantity;
                cout << cost << endl;
                break;
            case ATHENS:
                cost = departureSystem[1].price * ticketQuantity;
                cout << cost << endl;
                break;
            case ROME:
                cost = departureSystem[2].price * ticketQuantity;
                cout << cost << endl;
                break;
            default:
                cout << "Error!" << endl;
                break;
            }

            //collect payment from customer
            int payment;
            cout << "Please type in your payment (credits): ";
            cin >> payment;

            if (payment > customer.credits || payment < cost || payment <= 0) {
                cout << "You don't have enough credits" << endl;
                currentState = SELECT;
                cout << endl << endl;
            }
            else {
                customer.credits -= payment;
                int change = payment - cost;
                cout << "Thank you! Your change is " << change << " credits." << endl;
                customer.credits += change;
                currentState = ALLOCATION;
            }
            break;
        case ALLOCATION:
            //replace baggage o=for checkIn name
            //lifo stack add baggage to the bottom. maybe give tickets and add baggage. to stack. yes or no
            //ask if baggage, and for details for each users. then print tickets and baggage id.
            //store baggage in stack
            
           
            for (int i = 0; i < ticketQuantity; i++) {
                //GET DETAILS NAME DEATILS FOR EACH TICKET
                
                //get name
                cout << endl;
                cout << "Enter Name for Passenger " << i + 1 << ": ";
                string name;
                cin >> name;
            
                //get ticket number
                int ticketNumber = 0;
                switch (selectedFlight.destination)
                {
                case MALTA:
                    
                    ticketNumber = departureSystem[0].availability + i + 200;
                    departureSystem[0].luggageStack->Push(ticketNumber);
                    departureSystem[0].passengerManifestHT.insertItem(ticketNumber, name);

                    cout << name << "'s Ticket ID and Baggage ID: " << ticketNumber << endl;

                    //removes seat available and increases price after ticket is allocated
                    departureSystem[2].availability -= 1;
                    departureSystem[2].price += 3;
                    break;
                case ATHENS:
                    ticketNumber = departureSystem[1].availability + i + 200;
                    departureSystem[1].luggageStack->Push(ticketNumber);
                    departureSystem[1].passengerManifestHT.insertItem(ticketNumber, name);
                    cout << name << "'s Ticket ID and Baggage ID: " << ticketNumber << endl;

                    //removes seat available and increases price after ticket is allocated
                    departureSystem[2].availability -= 1;
                    departureSystem[2].price += 3;
                    break;
                case ROME:

                    ticketNumber = departureSystem[2].availability + i + 200;
                    departureSystem[2].luggageStack->Push(ticketNumber);
                    departureSystem[2].passengerManifestHT.insertItem(ticketNumber, name);
                    //removes seat available and increases price after ticket is allocated
                    departureSystem[2].availability -= 1;
                    departureSystem[2].price += 3;
                    cout << name << "'s Ticket ID and Baggage ID: " << ticketNumber << endl;
                    break;
                default:
                    cout << "Error!" << endl;
                    currentState = SELECT;
                    cout << endl << endl;
                    break;
                }
            }
            cout << endl;
            cout << "[[[[...Automatically Checked in Baggage...]]]" << endl;
            cout << "[[[[   Take Tickets and Proceed to Boarding   ]]]" << endl;

            
            
            //modify each flights hT and luggage stack
            //increase the departure price and decrease the available seats
            cout << "Departure System Updated" << endl;
            currentState = SELECT;
            cout << endl << endl;
            break;
        default:
            cout << "Error Invalid State Detected " << endl;
            currentState = SELECT;
            break;
        }
    }
    return 0;
}


