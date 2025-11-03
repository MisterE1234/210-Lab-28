//COMSC-210|Ethan Aylard|Lab-28
//IDE used: Visual Studio Code
//This program manages a list of goats, allowing the user to manipulate them with different stl opperations.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <numeric>
#include <random>
#include "Goat.h"

using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void search_name(list<Goat> trip);
void search_age(list<Goat> trip);
void search_color(list<Goat> trip);
void average_age(list<Goat> trip);
void sort_goats(list<Goat> & trip);
void simulate(list<Goat> trip);
void rename_goat(list<Goat>& trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Searching for goats by name.\n";
                search_name(trip);
                break;

            case 5:
                cout << "Searching for goats by age. \n";
                search_age(trip);
                break;
            case 6:
                cout << "Searching for goats by color. \n";
                search_color(trip);
                break;
            case 7:
                cout << "Calculating average age of goats. \n";
                average_age(trip);
                break;
            case 8:
                cout << "Sorting goats by age. \n";
                sort_goats(trip);
                break;
            case 9:
                cout << "Simulating n years. \n";
                simulate(trip);
                break;
            case 10:
                cout << "Renaming goat. \n";
                rename_goat(trip);
                break;

            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    int choice;
    bool valid = false;

    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Search for goats by name\n";
    cout << "[5] Search for goats by age\n";
    cout << "[6] Search for goats by color\n";
    cout << "[7] Calculate average age of goats\n";
    cout << "[8] Sort goats by age\n";
    cout << "[9] Simulate n years\n";
    cout << "[10] Rename goat of choice \n";
    cout << "[11] \n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    
    while(!valid) {
        cin >> choice;

        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input, not an integer.\n";
        }
        else{

            if(choice < 1 || choice > 12){
                cout << "Invalid number, try again. \n";        
            }

            else{
                valid = true;
            }
        }
    }

    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

//search_name() finds all goats that have a user specified name and displays their data if found.
//requires: a list of Goats
//returns: nothing
void search_name(list<Goat> trip){
string nm;
//Getting the name to search for:
cout << "Enter the name of the goats to search for: ";
cin.clear();//clearing input buffer
cin.ignore(10000, '\n');

getline(cin, nm);

//Searching through the list and displaying any matches:
for_each(trip.begin(), trip.end(), [nm](Goat g){
    if(g.get_name() == nm){
        cout << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")\n";
        
    }
});
//Displaying search complete message:
cout << "Search complete. \n";

}

//search_age() finds all goats that have a user specified age and displays their data if found.
//requires: a list of Goats
//returns: nothing
void search_age(list<Goat> trip){
int age;
bool valid = false; // a bool to check for valid input

//Getting the age to search for by using a while loop to validate:
while(!valid){
    cout << "Enter the age of the goats to search for (integer: 0-20): ";
    cin >> age;

    //Input validation:
    if(cin.fail()){ // If input is not an integer:
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input, not an integer. Try again:\n";
    }
    else if(age > 20 || age < 0){ //If input is out of range:
        cout << "Invalid age, out of range. try again:\n";
    }
    else{ //If input is valid:
        cout << "Searching ...\n";
        valid = true;
    }

}

//Searching through the list and displaying any matches:
for_each(trip.begin(), trip.end(), [age](Goat g){
    if(g.get_age() == age){
        cout << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")\n";
        
    }
});
//Displaying search complete message:
cout << "Search complete. \n";

}

//search_color() finds all goats that have a user specified color and displays their data if found.
//requires: a list of Goats
//returns: nothing
void search_color(list<Goat> trip){
string color;
//Getting the color to search for:
cout << "Enter the color of the goats to search for(ex. Blue, Magenta): ";
cin.clear(); //clearing input buffer
cin.ignore(10000, '\n');

getline(cin, color);

//Searching through the list and displaying any matches:
for_each(trip.begin(), trip.end(), [color](Goat g){
    if(g.get_color() == color){
        cout << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")\n";
        
    }
});
//Displaying search complete message:
cout << "Search complete. \n";

}


//average_age() calculates the average age by accumulating the ages of the goats then dividing by the number of goats.
//Requires: a list of Goats
//Returns: nothing
void average_age(list<Goat> trip){
    double totalAge = 0;
    
    //Accumulating the ages of all the goats:
    totalAge = accumulate(trip.begin(), trip.end(), 0, [](int sum, Goat g){
        return sum + g.get_age();
    });

    cout << "Average age: " << totalAge / trip.size() << endl;
}

//sort_goats() sorts the list of goats by age. The user gets to choose ascending or descending order.
//requires: a list of Goats
//returns: nothing
void sort_goats(list<Goat>& trip){
    int choice;
    bool valid = false;

    cout << "#1: Sort Ascending (Youngest first)\n";
    cout << "#2: Sort Descending (Oldest first)\n";
    //getting user input for sort order with validation:
    while(!valid){
    cout << "Choose (1 or 2): ";
    cin >> choice;

    //Input validation:
    if(cin.fail()){ // If input is not an integer:
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input, not an integer. Try again:\n";
    }
    else if(choice < 1 || choice > 2){ //If input is out of range:
        cout << "Invalid input, out of range. Try again:\n";
    }
    else{ //If input is valid:
        cout << "Sorting ...\n";
        valid = true;
    }

    }
    //Sorting 
    if(choice == 1){ //Ascending
        trip.sort([](Goat a, Goat b){
            return a.get_age() < b.get_age();
        });

    }
    else{ //Descending
        trip.sort([](Goat a, Goat b){ 
            return a.get_age() > b.get_age();
        });
    }

}

//simulate() will show the user the ages of all surviving goats after a user specified number.
//requires: a list of Goats
//returns: nothing
void simulate(list<Goat> trip){
int years;
bool valid = false;


//Getting user input with validation:
while(!valid){
    cout << "How many years to simulate (1+): ";
    cin >> years;

    //Input validation:
    if(cin.fail()){ // If input is not an integer:
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input, not an integer. Try again:\n";
    }
    else if(years < 1){ //If input is out of range:
        cout << "Invalid input, out of range. Try again:\n";
    }
    else{ //If input is valid:
        cout << "Simulating ...\n";
        valid = true;
    }

    }

    //Simulating the years:

    for (int i = 0; i < years; i++) {
        for_each(trip.begin(), trip.end(), [](Goat& g){
            g.set_age(g.get_age() + 1);

            if(g.get_age() == 21){
                g.set_name(g.get_name() + " Died "); //This is to show that the goat died, but you can still tell which one.
            }
        });
    }

    cout << "Goats in " << years << " years: \n";
    display_trip(trip);
}

//rename_goat() will list the goats then ask the user to choose which goat and what name.
//requires: a list of goats by reference
//returns: nothing
void rename_goat(list<Goat>& trip){
    string tempName;
    int choice;
    bool valid = false;

    //Displaying the list of goats:
    display_trip(trip);

    while(!valid){
        cout << "Which goat do you choose? (integer: 1-" << trip.size() << "): ";
        cin >> choice;

        //Input validation:
    if(cin.fail()){ // If input is not an integer:
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input, not an integer. Try again:\n";
    }
    else if(choice < 1 || choice > trip.size()){ //If input is out of range:
        cout << "Invalid input, out of range. Try again:\n";
    }
    else{ //If input is valid:
        valid = true;
    }
    }
    
    //Asking for the new name:
    cout << "What is the new name? ";
    cin.clear();
    cin.ignore(10000, '\n');
    getline(cin, tempName);

    //locating goat with iterators an the previous choice:
    auto it = trip.begin();
    advance(it, choice - 1);
    //Changing the name and then displaying the data of the goat:
    it->set_name(tempName);
    cout << "\t"
             << it->get_name() 
             << " (" << it->get_age() 
             << ", " << it->get_color() << ")\n";

}