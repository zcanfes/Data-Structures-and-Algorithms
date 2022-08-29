#ifndef CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#define CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Person{
    int type = 0;
    char line = ' ';
    int seatNumber = 0;
    int initial = 0;
    char line0 = ' ';
    int type3LastOperation = 0;
    int seated = 0;
    Person() {};
    Person (int type, char line, int number, int initial){
        this->type = type;
        this->line = line;
        this->seatNumber = number;
        this->initial = initial;
        this->type3LastOperation = 1;//starts from 1
        this->line0 = line;//keeps the initial line to print
        this->seated = 0;//not seated at first
    }
};

class SeatOperations{

private:
    vector<Person> lines[2];
    int N, M;

public:
    SeatOperations(int N, int M);
    void addNewPerson(int personType, const string& ticketInfo);
    void printAllSeats(ofstream& outFile);
    // YOU CAN ADD YOUR HELPER FUNCTIONS

};

#endif //CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
