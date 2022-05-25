#pragma once
#include <string>
#include "Stack.h"
#include "HashTable.h"

using namespace std;
class DepartureSystem
{
private:
    enum DepartureControlState { SELECT, AVAILABILITY, CALCULATE, ALLOCATION };
    enum Destinations { MALTA = 100, ATHENS = 200, ROME = 300, FINDFLIGHT = 500 };
    struct Flights {
        Destinations destination;
        //HashTable passengerManifestHT;
        Stack* luggageStack;
        int availability;
        int price;
        int priceDelta;
    };
    struct Tourist
    {
        string name;
        int credits = 0;
    };
    HashTable passengerManifestHT;
    Flights selectedFlight;
    Tourist tourist;
    Flights departureSystem[3];
    DepartureControlState currentState = SELECT;
    void printSystemStatus(Tourist tourist, Flights departureSystem[]);
    void saveDestination(string country, Destinations countryEnum, Flights& selectedFlight, DepartureControlState& currentState);
    void collectPayment(int cost, Tourist tourist, DepartureControlState& currentState);
    void departureSystemCalculate(int flightIndex, int& cost, int ticketQuantity, Flights departureSystem[]);
    void departureSystemAvailability(int flightIndex, int ticketQuantity, DepartureControlState& currentState, Flights departureSystem[]);
    void departureSystemAllocation(int flightMultiplier, int flightIndex, Flights departureSystem[], HashTable& passengerManifestHT, string ticketDetails, string name);
    void searchPassengerManifest(HashTable passengerManifestHT);
public:
    DepartureSystem();
    void startDepartureSystem();
};

