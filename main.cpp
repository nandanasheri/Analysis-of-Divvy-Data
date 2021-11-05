/* program_4.cpp
    Divvy Bike Data Analysis program.
    Author: Nandana Sheri
    Date: 21/10/2021
    Class: CS 141, Fall 2021, UIC
    System: CLion using Windows
    Menu Option 5 Extra Credit URL: https://www.google.com/maps/d/u/0/edit?mid=1kEBEpX9wK7_L-cxFBnXy6ZYR_u0mVIs6&usp=sharing
    Coordinates for Home I would like to live in:  41.92839911055126 -87.64446979389763
*/

#include <iostream>
#include <string>       // To use string functions
#include <vector>       // To use vectors
#include <fstream>      // For file input and output
#include <cassert>      // For the assert statement used to validate file open
#include <sstream>      // To use stringstream
#include <cmath>        // To convert degrees into radians and use mathematical functions
#include <iomanip>      // To use setprecision

using namespace std;    // So that we don't need to preface cin and cout with std::

// Function to Clean Data and to only store the clean data values in the vector as well as separate each data line
// into separate strings so that they can be manipulated
int CleanData (vector <string> &lineData, vector<string> &cleanData) {
    string wordOfData;                                  // To store each word
    bool present;                                       // Boolean variable to check whether the line is already present in clean data
    for (int i = 1; i < lineData.size(); i++) {
        string lineOfData = lineData.at(i);             // Each line excluding header is stored into the string
        stringstream s(lineOfData);                     // To convert each line into a stream
        while (s.good()){                               // Checks whether there is more to be read from the stream
            present = false;                            // Initially the line is not present in the clean data
            for (int j = 0; j < 11; j++) {
                getline(s,wordOfData, ',');     // Stores each word into wordOfData
                if (wordOfData.empty()) {                   // Checks if a word is empty which means it has no value and
                    present = true;                         // hence, is unclean. If not the line is added to the clean vector
                }
            }
            if (present == false) {                         // If the line continues to be not present in the clean data
                cleanData.push_back(lineOfData);            // the line is pushed back into the vector of clean data.
            }
        }
    }
    int cleanTrips = cleanData.size();                   // To store the total number of trips in clean data
    return cleanTrips;
}

// Function to read all the csv files into the program and display the total number of rides as well as clean data
void ReadDataFile(vector <string> &lineData, vector <string> &cleanData, int selection) {
    lineData.clear();                                     // Checking if any previous data was stored in
    cleanData.clear();                                    // both the vectors.
    ifstream inStream;                                    // Declare an input stream for reading
    if (selection == 1) {                                 // Depending on which selection is entered by the user the
        inStream.open( "divvyridesampledata.csv");     // corresponding file would be opened
    }
    else if (selection == 2) {
        inStream.open( "weekdayweekend.csv");
    }
    else if (selection == 3) {
        inStream.open( "all_divvy_rides_september.csv");
    }
    assert( inStream.fail() == false );                         // Ensure file open worked
    // Keep repeating while input from the file yields a line of data
    string dataLine, dataWord;                                  // Store a single line, word
    int i = 1;
    while( inStream.good()) {                                   // When there are more lines to be read
        getline(inStream,dataLine, '\n');           // Reads each line and stores it in dataLine
        lineData.push_back(dataLine);                           // Each line is stored as an element in lineData
        i++;
    }
    int totalTrips = lineData.size() - 2;                                    // To find total number of trips not
    cout << "Total # of trips found in datafile: " << totalTrips << endl;    // clean data excluding header
    int cleanTrips = CleanData(lineData, cleanData);                  // To find trips after clean data
    cout << "Total # of trips in clean data: " << cleanTrips << endl;
}

// Function to read the words from the clean data into a vector of words
void ReadWordsOfData (vector <string> &wordData, vector <string> cleanData ) {
    string wordOfData;                                  // To store each word from clean data
    string dataLine;                                    // To store each line from clean data
    for (int i = 0; i < cleanData.size(); i++) {
        dataLine = cleanData.at(i);
        stringstream s (dataLine);                      // Each line is passed as a stream to use getline
        while (s.good()) {
            getline(s, wordOfData, ',');    // Takes each word until a ',' is found
            wordData.push_back(wordOfData);             // Each word is pushed back into the word vector
        }
    }
}

// Function to convert the degrees of latitudes and longitudes into radians
long double toRadians(const long double degree) {            // cmath library in C++ defines the constant M_PI
    long double one_deg = (3.14159265358979323846) / 180;    // as the value of pi accurate to 1e-30
    return (one_deg * degree);
}

// Function to calculate the distance travelled using latitudes and longitudes
long double DistanceTraveled(long double lat1, long double long1,
                     long double lat2, long double long2) {
    lat1 = toRadians(lat1);                                 // Latitudes and longitudes are first converted from
    long1 = toRadians(long1);                               // degrees to radians.
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
    long double dlong = long2 - long1;                      // Haversine Formula
    long double dlat = lat2 - lat1;
    long double ans = pow(sin(dlat / 2), 2) +
            cos(lat1) * cos(lat2) *
            pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));                              // Radius of Earth in Kilometers, R = 6371
    long double R = 3956;                                   // Use R = 3956 for miles
    ans = ans * R;                                          // Calculate the result
    return ans;
}

// Function to display the information of the longest trip
void DisplayMaxTrip (string maxTripInfo, long double maxTrip) {
    stringstream  s (maxTripInfo);
    string ride_id, rideable_type, started_at, ended_at, start_station_name, end_station_name;      // Stores info
    getline(s,ride_id,',');                     // Each word is accessed using getline and stored
    getline(s,rideable_type,',');
    getline(s,started_at,',');
    getline(s,ended_at,',');
    getline(s,start_station_name,',');
    getline(s,end_station_name,',');
    double roundedMaxTrip = round(10 * maxTrip) / 10;     // To only have one decimal place in the number
    cout << "Longest trip information below: \n"            // Displaying all the necessary information
            "-------------------------------" << endl;
    cout << "Trip ID: " << ride_id << endl;
    cout << "Trip start location: " << start_station_name << endl;
    cout << "Trip end location: " << end_station_name << endl;
    cout << "Trip distance in miles: " << roundedMaxTrip << endl;
}

// Function to display the overall trip information from the clean data
void DisplayTripInfo(const vector <string> &cleanData,
                      vector <string> &wordData) {            // Clean data is passed as a const and reference parameter
    long double totalMiles = 0;                               // Stores the total miles traveled as well as average
    double averageLengthOfTrips;
    long double lat1, long1, lat2, long2;
    long double maxTrip = 0;                                 // Stores the Maximum Number of miles traveled
    string maxTripInfo;                                      // Stores information about the longest trip
    ReadWordsOfData( wordData, cleanData);       // All the words are individually stored and accessible
    for (int i = 0; i < cleanData.size(); i++) {             // Goes through the clean data to retrieve latitude and longitude
        int index = (i * 11) + 6;                            // Formula to find the position of the starting latitude
        lat1  = stod (wordData.at(index));                   // As each latitude and longitude are stored as strings,
        long1 = stod (wordData.at(index + 1));        // stod converts them to their corresponding double.
        lat2  = stod (wordData.at(index + 2));
        long2 = stod (wordData.at(index + 3));
        long double milesTraveled = DistanceTraveled(lat1, long1, lat2, long2);
        totalMiles += milesTraveled;                         // Calculates total miles traveled
        if (milesTraveled > maxTrip) {                       // Checks whether each trip is greater than the previous
            maxTrip = milesTraveled;
            maxTripInfo = cleanData.at(i);                   // Stores the longest trip
        }
    }
    double totalTrips = cleanData.size() * 1.0;                 // Returns the number of trips as double
    averageLengthOfTrips = totalMiles / totalTrips;             // Calculates and stores the average
    cout << "Total # of miles traveled: " << fixed << setprecision(0) << totalMiles << endl;
    cout << "Average length of trips in miles: " << fixed << setprecision(1) << averageLengthOfTrips << endl << endl;
    DisplayMaxTrip(maxTripInfo,maxTrip);
}

// Function to get membership type of each rider and count them categorically
void GetMembershipInfo (vector<string> cleanData, vector <string> wordData, int &casualRider, int &memberRider) {
    casualRider = 0;
    memberRider = 0;
    for (int i = 0; i < cleanData.size(); i++) {
        int index = (i * 11) + 10;                              // Formula to calculate the position of membership data
        if (wordData.at(index) == "member" or wordData.at(index) == "member\r") {      // Checks if rider is a member and adds to counter
            memberRider += 1;
        }
        else if (wordData.at(index) == "casual" or wordData.at(index) == "casual\r") { // Checks if rider is a casual rider and adds to counter
            casualRider += 1;
        }
    }
}

// Function to display the percentage of members vs casual riders
void DisplayPercentage(vector <string> cleanData, vector <string> wordData) {
    int casualRider, memberRider;                               // To store the number of casual riders and member riders
    GetMembershipInfo(cleanData,wordData, casualRider,memberRider);       // Returns number of casual and member riders
    double totalRiders = (casualRider + memberRider) * 1.0;                    // Stores total number of riders
    double casualRiderPercentage = (casualRider / totalRiders) * 100;          // Calculates number of casual riders to
    casualRiderPercentage = round(casualRiderPercentage * 10) / 10;            // an accuracy of one decimal
    double memberRiderPercentage = (memberRider / totalRiders) * 100;          // Calculates similarly for members
    memberRiderPercentage = round(memberRiderPercentage * 10) / 10;
    cout << "Casual Rider Percentage: " << fixed << setprecision(1) << casualRiderPercentage << "%" << endl;
    cout << "Member Rider Percentage: " << fixed << setprecision(1) << memberRiderPercentage << "%" << endl;
}

// Function to return whether data is from a weekday or a weekend
string ReturnDate ( string eachLine) {
    stringstream  s (eachLine);
    string ride_id, rideable_type, started_at, ended_at, start_station_name, end_station_name;      // Stores info
    getline(s,ride_id,',');                     // Each word is accessed using getline and stored
    getline(s,rideable_type,',');
    getline(s,started_at,',');
    string date = started_at.substr(0,8);           // Substring Function returns only part of the string
    return date;                                            // and here it returns only the date.
}

// Function to return start time of a ride
string ReturnStartTime ( string eachLine) {
    stringstream  s (eachLine);
    string ride_id, rideable_type, started_at, ended_at, start_station_name, end_station_name;      // Stores info
    getline(s,ride_id,',');                     // Each word is accessed using getline and stored
    getline(s,rideable_type,',');
    getline(s,started_at,',');
    string time = started_at.substr(9,2);          // Substring Function returns only part of the string
    return time;                                           // and here it returns only the time.
}

// Function to check for number of rides per hour and add to a vector
void NumberOfRidesPerHour (vector <int> &ridesVector, int time) {
     switch (time) {      // According to time mentioned the number of rides is added to the vector and as the vector
                          // is passed by reference the changes are reflected back
         case (0): ridesVector.at(0) += 1; break;
         case (1): ridesVector.at(1) += 1; break;
         case (2): ridesVector.at(2) += 1; break;
         case (3): ridesVector.at(3) += 1; break;
         case (4): ridesVector.at(4) += 1; break;
         case (5): ridesVector.at(5) += 1; break;
         case (6): ridesVector.at(6) += 1; break;
         case (7): ridesVector.at(7) += 1; break;
         case (8): ridesVector.at(8) += 1; break;
         case (9): ridesVector.at(9) += 1; break;
         case (10): ridesVector.at(10) += 1; break;
         case (11): ridesVector.at(11) += 1; break;
         case (12): ridesVector.at(12) += 1; break;
         case (13): ridesVector.at(13) += 1; break;
         case (14): ridesVector.at(14) += 1; break;
         case (15): ridesVector.at(15) += 1; break;
         case (16): ridesVector.at(16) += 1; break;
         case (17): ridesVector.at(17) += 1; break;
         case (18): ridesVector.at(18) += 1; break;
         case (19): ridesVector.at(19) += 1; break;
         case (20): ridesVector.at(20) += 1; break;
         case (21): ridesVector.at(21) += 1; break;
         case (22): ridesVector.at(22) += 1; break;
         case (23): ridesVector.at(23) += 1; break;
     }
}

// Function to find maximum number of rides per hour
int ReturnMaxNumberOfRidesPerHour (vector <int> weekendData, vector <int> weekdayData) {
    int largestRides = 0;                                           // To store the largest number of rides
    for (int i = 0; i < weekdayData.size(); i++) {                  // Iterates to the loop and if the number of rides
        if (largestRides < weekendData.at(i)) {                     // for one day is greater than max value, max value
            largestRides = weekendData.at(i);                       // changes accordingly.
            }
        else if (largestRides < weekdayData.at(i)) {                // Looks through both weekday and weekend to find
            largestRides = weekdayData.at(i);                       // number between the two.
        }
    }
    return largestRides;
}

// Function to populate the weekend and weekday vectors with the number of rides per hours
void PopulateWeekendWeekdayVectors (vector <string> cleanData, vector <int> &weekendData, vector <int> &weekdayData) {
    for (int i = 0; i < cleanData.size(); i++) {
        string line = cleanData.at(i);                              // Stores each line of data
        string date = ReturnDate(line);                     // Returns the date from each line
        int time = stoi(ReturnStartTime( line));        // Converts time to an integer
        if (date == "9/1/2021") {                                  // Checks whether date is a weekday or a weekend
            NumberOfRidesPerHour(weekdayData, time);           // Adds an hour to the respective time slot accordingly
        }
        else if (date == "9/4/2021") {
            NumberOfRidesPerHour(weekendData, time);
        }
    }
}

// Function to display 50 column graph
void DisplayColumnGraph (vector <string> cleanData, vector <int> weekendData, vector <int> weekdayData) {
    PopulateWeekendWeekdayVectors(cleanData, weekendData, weekdayData);     // Populates both vectors
    int largestRides = ReturnMaxNumberOfRidesPerHour(weekendData, weekdayData);
    int numberOfWeekdaySign = 0;                         // To store the number of '@' and '+' required to print out
    int numberOfWeekendSign = 0;
    for (int i = 0; i < weekdayData.size(); i++) {       // Iterates through the entire vector
        cout << i << ": ";                               // Prints the hour of the day to display
        numberOfWeekdaySign = (weekdayData.at(i) / (largestRides * 1.0)) * 50;       // Formula to calculate the number
        numberOfWeekendSign = (weekendData.at(i) / (largestRides * 1.0)) * 50;       // of '@' and '+' to be printed
        for (int j = 0; j < numberOfWeekdaySign; j++) {                             // Loops through and prints '@'
            cout << "@";
        }
        cout << endl;
        for (int k = 0; k < numberOfWeekendSign; k++) {                             // Loops through and prints '+'
            cout << "+";
        }
        cout << endl;
    }
}

// Function to display comparisons of weekend and weekday data
void DisplayWeekdayWeekend(vector <string> cleanData, vector <string> wordData,
                           vector <int> &weekendData, vector <int> &weekdayData) {
    int choice;
    cout << "Select type of display: \n"                                // Prints the menu option
            "      1. Counts of rides per hour in the day\n"
            "      2. Proportional 50 column graph with @ for weekday and + for weekend\n"
            "   Your selection--> ";
    cin >> choice;
    if (choice == 1) {                                                  // If first choice is selected
        PopulateWeekendWeekdayVectors(cleanData, weekendData, weekdayData);     // Populates the vectors
        int largestRides = ReturnMaxNumberOfRidesPerHour(weekendData, weekdayData);   // Returns max rides
        cout << "LargestNumberOfRides is: " << largestRides << endl;
        cout << "Rides per hour for weekday and weekend:" << endl;
        for (int i = 0; i < weekdayData.size(); i++) {                  // Displays weekday and weekend rides per hour in table format
            cout << i << ":      " << weekdayData.at(i) << "    " << weekendData.at(i) << endl;
        }
    }
    else if (choice == 2) {
        DisplayColumnGraph(cleanData, weekendData, weekdayData); // Displays column graph
    }
}

// Function to find the closest station to coordinates mentioned above
void FindClosestStation(vector <string> riderData, vector <string> cleanData, vector<string> &wordData) {
    long double latitude, longitude;                                    // To store the input coordinates
    cout << "Input latitude and longitude of the home: ";
    cin >> latitude;
    cin >> longitude;                                                   // Stores the input coordinates and prints them
    cout << "You entered: " << fixed << setprecision(1) << latitude << " for latitude and " <<
    fixed << setprecision(1) << longitude << " for longitude" << endl;
    vector <string> startStationNames;                                          // Vectors to store station names, latitudes
    vector <long double> startStationLat, startStationLong, travelDistance;     // longitudes and distance travelled
    ReadWordsOfData( wordData, cleanData);       // All the words are individually stored and accessible
    for (int i = 0; i < cleanData.size(); i++) {             // Goes through the clean data to retrieve latitude and longitude
        int index = (i * 11) + 6;                            // Formula to find the position of the starting latitude
        long double lat1  = stod (wordData.at(index));                   // As each latitude and longitude are stored as strings,
        long double long1 = stod (wordData.at(index + 1));        // stod converts them to their corresponding double.
        string startStation = wordData.at(index - 2);
        long double distanceTraveled = DistanceTraveled(lat1, long1, latitude, longitude);
        startStationNames.push_back(startStation);           // Each value is pushed back to parallel vectors
        startStationLat.push_back(lat1);
        startStationLong.push_back(long1);
        travelDistance.push_back(distanceTraveled);
    }
    long double leastDistance = travelDistance.at(0);       // The first element of the vector is initialized as least distance
    int index = 0;                                             // Stores the index position of the least distance travelled
    for (int i = 0; i < travelDistance.size(); i++) {
        if (leastDistance > travelDistance.at(i)) {
            leastDistance = travelDistance.at(i);
            index = i;
        }
    }
    cout << "Closest Divvy station is: " << startStationNames.at(index) << " at " << fixed << setprecision(8) <<
    startStationLat.at(index) << ", " << startStationLong.at(index) << ", " << fixed << setprecision(1)
    << travelDistance.at(index) << " miles away" << endl;
}
// Function that handles all the Menu Options when the user inputs each option
int MenuOptions(int &x) {              // Changes will be reflected back for x when declared as a reference parameter
    int menuOption = 0;
    cout << "Select a menu option: \n"
            "   1. Select datafile, display rides totals and clean data\n"
            "   2. Display overall trip information\n"
            "   3. Display percentage of members vs. casual riders\n"
            "   4. Display weekday vs weekend usage\n"
            "   5. Extra Credit: find closest station\n"
            "   6. Exit\n"
            "Your choice --> ";
    cin >> menuOption;
    if (menuOption == 1) {              // Variable is changed permanently indicating that user entered option 1
        x++;
    }
    return menuOption;
}

int main() {
    int x = 0;              // Variable to check whether user firsts enters option 1
    cout << "Analyze Divvy bike ride information using September trip data.\n"
            "First select option 1 to read and clean the data.\n";
    vector <string> riderData;                              // To store all the raw data line by line
    vector <string> valueOfLine;                            // To store each word as a separate element
    vector <string> cleanData;                              // To store all the clean data
    vector <int> weekendData (24, 0); // To store the number of rides for weekday and weekend separately
    vector <int> weekdayData (24, 0); // as well as initializing each value to 0 in the beginning
    while (true) {
        int menuOption = MenuOptions(x);
        while (menuOption != 1 && x == 0 && menuOption != 6) {  // User enters option other than 1 without first entering 1 causes this output
            cout << "First read in data by selecting menu option 1" << endl;
            menuOption = MenuOptions(x);
        }
        switch (menuOption) {
            case 1:
                riderData.clear();              // Clearing vectors in case it was populated with previous option values
                cleanData.clear();
                int selection;                  // After menu option 1 is selected user has to select a choice from below
                cout << "Select datafile: \n"
                        "      1. Small subset of data with 14 rides to help create your program\n"
                        "      2. Week day vs weekend rides\n"
                        "      3. All September 2021 data (not tested in Zybooks)\n"
                        "   Your selection-->";
                cin >> selection;
                ReadDataFile(riderData, cleanData, selection);
                break;
                case 2:                          // Menu Option 2 to display trip information
                    DisplayTripInfo(cleanData, valueOfLine);
                    break;
                    case 3:                      // Menu Option 3 to display percentage of casual and member riders
                        valueOfLine.clear();
                        ReadWordsOfData(valueOfLine, cleanData);
                        DisplayPercentage(cleanData, valueOfLine);
                        break;
                        case 4:                 // Menu Option 4 to display weekend and weekday data
                            DisplayWeekdayWeekend(cleanData, valueOfLine, weekendData, weekdayData);
                            break;
                            case 5:             // Menu Option 5 to find the closest station to given coordinates
                                FindClosestStation(riderData, cleanData, valueOfLine);
                                break;
                                case 6:         // Menu Option 6 to exit the program.
                                    exit(0);
        }
    }
}
