/*
Student Name:Zehranaz Canfes
Student Number:2017205138
Project Number: 3
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "SeatOperations.h"

using namespace std;

SeatOperations::SeatOperations(int N, int M){
    this->M = M;
    this->N = N;
    lines[0].resize(N);//the size of line A is N
    lines[1].resize(M);//the size of line B is M
}

void SeatOperations::addNewPerson(int personType, const string& ticketInfo){
    Person p(personType, ticketInfo[0], 0 ,stoi(ticketInfo.substr(1, ticketInfo.length())));
    if(p.line == 'A'){ //if the line is 'A' i.e. 65
        p.seatNumber = p.initial % N;//finds the suitable seat number for the new person
        if (!p.seatNumber) //if the seat number is 0
            p.seatNumber = N;
    }
    else{
        p.seatNumber = p.initial % M;
        if (!p.seatNumber)
            p.seatNumber = M;
    }
    p.seated = 1; //the person is seated
    swap(lines[p.line - 65][p.seatNumber - 1], p);
    do { //find a place for the replaced person
        if(p.type == 1){ //type 1
            if(p.line == 'A'){// if the line is 'A' i.e. 65
                p.seatNumber = p.initial % M;
                if(!p.seatNumber)//if the seat number is zero
                    p.seatNumber = M;
                p.line = 'B';//change the line
                p.seated = 1;
            }
            else { // if the line is 'B'
                p.seatNumber = p.initial % N;
                if(!p.seatNumber)
                    p.seatNumber = N;
                p.line = 'A';
                p.seated = 1;
            }
            swap(lines[p.line - 65][p.seatNumber - 1], p);
            p.seated = 0;
        }
        else if(p.type == 2){ //type 2
            if(p.line == 'A' && p.seatNumber == N){ //line A
                p.line = 'B';// if the person sits on the last seat on line A, change the line
                p.seatNumber = 1;
            }
            else if(p.line == 'B' && p.seatNumber == M){ // line B
                p.line = 'A';
                p.seatNumber = 1;
            }
            else
                p.seatNumber ++; //go one seat back
            p.seated = 1;
            swap(lines[p.line - 65][p.seatNumber - 1], p);
            p.seated = 0;
        }
        else if(p.type == 3){ //type 3
            p.seatNumber += p.type3LastOperation;
            p.type3LastOperation += 2;
            bool check = true; //checks whether the while loop should stop or continue
            while(check){
                if(p.line == 'A'){//line A
                    if(p.seatNumber > N){//if the seat number is greater than the size of A, switch to line B
                        p.seatNumber -= N;
                        p.line = 'B';
                    }
                    else{ //if the person can be seated in line A
                        p.seated = 1;
                        swap(lines[p.line - 65][p.seatNumber - 1], p);
                        p.seated = 0;
                        check = false;
                    }
                }
                else{//line B
                    if(p.seatNumber > M){// if the seat number is greater than line B, switch to line A
                        p.seatNumber -= M;
                        p.line = 'A';
                    }
                    else { //the person can be seated in line B
                        p.seated = 1;
                        swap(lines[p.line - 65][p.seatNumber - 1], p);
                        p.seated = 0;
                        check = false;
                    }
                }
            }
        }
        if(!p.type)//if the type is zero, then the swapped seat is empty, so break
            break;
    } while(!p.seated);//while the person is not seated
}

void SeatOperations::printAllSeats(ofstream& outFile){
    for(Person p : lines[0]) { //line A
        if (!p.type)// if it is 0
            outFile << "0" << endl;
        else
            outFile << p.type << " " << p.line0 << p.initial << endl;
    }
    for(Person p : lines[1]) { //line B
        if (!p.type)
            outFile << "0" << endl;
        else
            outFile << p.type << " " << p.line0 << p.initial << endl;
    }
}


// YOU CAN ADD YOUR HELPER FUNCTIONS