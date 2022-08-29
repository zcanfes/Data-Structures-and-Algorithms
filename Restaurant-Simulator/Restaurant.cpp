/*
Student Name: Zehranaz Canfes
Student Number: 2017205138
Project Number: 1
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: The execute method successfully places new customers in the restaurant depending on which entrance
 they come from. The method uses the vector that holds the table configuration in the restaurant and empties or
 occupies them according to the instructions in the input file.
*/

#include "Restaurant.h"

using namespace std;

void Restaurant::execute(const vector<string>& operations) {
    for (const string& op : operations){
        cout << "Operation: " << op << "\t";
        int nofTable = this->tables.size();//number of tables in the restaurant

        if(op == "N"){//a customer enters from north
            for(int i = 0; i < nofTable; i++){
                if(!this->tables[i].isOccupied()) {
                    this->tables[i].occupy();
                    break;
                }
            }
        }
        else if (op == "S"){//a customer enters from south
            for(int i = 0; i < nofTable; i++){
                if(!this->tables[nofTable - i - 1].isOccupied()) {
                    this->tables[nofTable - i - 1].occupy();
                    break;
                }
            }
        }
        else {
            int m = stoi(op);//the customer sitting at table m leaves
            this->tables[m - 1].empty();
        }

        cout << "State: " << *this << endl;
    }
}

Restaurant::Restaurant(unsigned int N)
	: tables{N}
{
    cout << "-Starting- \tState: " << *this << endl;
}

ostream &operator<<(ostream &out, Restaurant &restaurant) {
    for (Table table : restaurant.tables) {
        out << table.isOccupied();
    }
	return out;
}

