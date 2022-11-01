#include <fstream>
#include <string> 
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>


using namespace std;
void ISO_format(string, int, int, int, int, int);
void conversion(vector<string>, vector<int>, string, string, int, int, int, int, int);
int city_check(vector<string>, string);

void ISO_format(string chosen, int minute, int hour, int day, int month, int year){

    cout << "For " << chosen << " the date and time is: " << year << "-" << month << "-" << day << "T" << hour << ":" << minute << endl;
    //2022-10-20T08:32

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void conversion(vector<string> city, vector<int> timee, string curr_city, string chosen, int minute, int hour, int day, int month, int year){


    int city_index;
    int curr_city_index; //index of origin city
    int difference;

    for(int i = 0; i < city.size(); i++){

        if(chosen == city[i]){
            city_index = i;
        }

        if(curr_city == city[i]){
            curr_city_index = i;
        }

    }

    difference = timee[curr_city_index] - timee[city_index];

    hour = hour - difference; //For any calculation errors, check signs from this result

    //Checks possible dates
    if(hour < 0){
        day--;
        hour += 24;
    }

    if(hour >= 24){
        day++;
        hour -= 24;
    }

    if(day < 1){

        if(month == 5 || month == 7 || month == 10 || month == 12){ //Months one higher than 30-day months
            day += 30;
        }

        else if(month == 3){ //March
            day += 28;
        }

        else{ //Every other months
            day += 31;
        }

        month--;

    }
    
    if(day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)){ //If days >30 on 30-day months

        day -= 30;
        month++;

    }

    else if(day > 28 && month == 2){
        
        day -= 28;
        month++;

    }
 
    else if(day > 31){ 
        day -= 31;
        month++;
    }

    if(month < 1){
        year--;
        month += 12;
    }

    if(month > 12){
        year++;
        month -= 12;
    }

    ISO_format(chosen, minute, hour, day, month, year);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int city_check(vector<string> cities, string city){

    int valid = 0;

    for(int k = 0; k < cities.size(); k++){
        if(city == cities[k]){
            valid = 1;
        }
    }

    return valid;

}

int main(){

    vector<string> city_and_time; //City and time (time difference between city and international date line)
    vector<string> city;
    vector<int> timee;

    ifstream inputs;
    int new2; //Temporary storage
    string imsad; //Temporary storage
    inputs.open("time.txt");
    string goesin; //temporary storage

    while(inputs >> goesin){
        city_and_time.push_back(goesin); //Fills vector with numbers
    }
    inputs.close(); //closing the file now that we've collected data

    //for(int i = 0; i < city_and_time.size(); i++){
    //    cout << city_and_time[i] << endl;

    //}

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    int iter = 0; //used for iteration
    
    while(iter < city_and_time.size()){
        city.push_back(city_and_time[iter]); //inputs city
        iter++;
        imsad = city_and_time[iter];
        new2 = stoi(imsad);
        timee.push_back(new2); //inputs time as an int
        iter++;
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //https://stackoverflow.com/questions/8343676/how-to-get-current-date-and-time
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);

    int day = aTime->tm_mday;
    int month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    int year = aTime->tm_year + 1900; // Year is # years since 1900
    int hour = aTime->tm_hour;
    int minute = aTime->tm_min;

    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    string current_city; //Stores current city
    vector<string> chosen_cities;
    string city_placeholder;
    string yorn; //yes or no
    int good_city = 0; //Bool for valid city

    while(good_city == 0){

        cout << "What is your current location? (Enter City): ";
        cin >> current_city;
        cout << endl;

        good_city = city_check(city, current_city); //Bool to see if city is valid

        if(good_city == 0){

            cout << "Invalid city. Try a different city or modify the records" << endl;

        }

    }

    int iter2 = 0; //Used as an iterator
    int choice = 1; //Used as a choice

    while(choice != 0 && iter2 < 9){

        good_city = 0; //Resetting variable

        while(good_city == 0){

            cout << "Enter a city you'd like to compare: ";
            cin >> city_placeholder;
            cout << endl;

            good_city = city_check(city, city_placeholder); //Bool to see if city is valid

            if(good_city == 0){

                cout << "Invalid city. Try a different city or modify the records" << endl;

            }

        }

        iter2++;

        chosen_cities.push_back(city_placeholder); //adds your entered city into an array
        
        if (iter2 < 9){
            cout << "Would you like to enter another city? (y/n): ";
            cin >> yorn;
            cout << endl;
        }

        if(yorn == "n"){
            choice = 0; //If you don't want to enter another city, you can end the loop prematurely 
        }

        yorn = "";
        city_placeholder = ""; //clears the input
        
    }
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        yorn = "";
        cout << "Would you like to use the current date to compare or would you like to enter your own?" << endl;
        cout << "(y for current, n for your own): ";
        cin >> yorn;
        cout << endl;

        if (yorn == "n"){

            cout << "Enter the year: ";
            cin >> year;
            cout << endl;

            cout << "Enter the month (1-12): ";
            cin >> month;
            cout << endl;

            cout << "Enter the day (1-31): ";
            cin >> day;
            cout << endl;

            cout << "Enter the hour (0-24): ";
            cin >> hour;
            cout << endl;

            cout << "Enter the minute (0-59): ";
            cin >> minute;
            cout << endl;

        }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    ISO_format(current_city, minute, hour, day, month, year); //Does your origin city only

    for(int j = 0; j < chosen_cities.size(); j++){
        conversion(city, timee, current_city, chosen_cities[j], minute, hour, day, month, year); //Does the rest of the cities
    }

    return 0;
}
