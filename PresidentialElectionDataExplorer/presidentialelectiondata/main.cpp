/*  Name:        Musa Tahir
    Course:      CS 141
    Date:        11/09/24
    Description: This program is basically an election data search and analysis tool. It parses through
    the MIT presidential election data by taking it is as a text file and performs various functions to 
    provide insights and visualizations about the data. The functions include data overview, national 
    results, state results, a specific candidate's results, and a county search.
*/

/*UPDATES:
-Add additional information for each function
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

//class header files
#include "Votes.h"
#include "Candidate.h"
#include "CandResults.h"

//function declarations
//int binarySearch(vector<string>& vect, string word);
void dataOverview (vector<Votes>& votingList);
void nationalResults (vector<Votes>& votingList);
void stateResults (vector<Votes>& votingList);
void candidateResults (vector<Votes>& votingList);
void countySearch (vector<Votes>& votingList);
string allCaps(string word);


const string STATES[] = {"ALABAMA", "ALASKA", "ARIZONA", "ARKANSAS", "CALIFORNIA", "COLORADO",
	"CONNECTICUT", "DELAWARE", "FLORIDA", "GEORGIA", "HAWAII", "IDAHO", "ILLINOIS",
	"INDIANA", "IOWA", "KANSAS", "KENTUCKY", "LOUISIANA", "MAINE", "MARYLAND", "MASSACHUSETTS", "MICHIGAN",
	"MINNESOTA", "MISSISSIPPI", "MISSOURI", "MONTANA", "NEBRASKA", "NEVADA", "NEW HAMPSHIRE", "NEW JERSEY",
	"NEW MEXICO", "NEW YORK", "NORTH CAROLINA", "NORTH DAKOTA", "OHIO", "OKLAHOMA", "OREGON", "PENNSYLVANIA",
	"RHODE ISLAND", "SOUTH CAROLINA", "SOUTH DAKOTA", "TENNESSEE", "TEXAS", "UTAH", "VERMONT", "VIRGINIA",
	"WASHINGTON", "WASHINGTON DC", "WEST VIRGINIA", "WISCONSIN", "WYOMING"};
const int NUM_STATES = 51;

//color settings
void static SetColor(int textColor)
{
    cout << "\033[" << textColor << "m";
}

// Function to reset the console color
void static ResetColor() { 
    cout << "\033[0m"; 
}

int main() {
    vector<Votes> votingList; // vector obj. to store multiple vote objects
    Votes currVoteObj;
    string fileName;
    string currState, currCounty, currCandidate, currParty, strVotes;
    int currVotes;
    int userChoice = 1;

    // get file name
    cout << "Enter file to use: ";
    cin >> fileName;
    cout << endl;

    // create file obj 
    ifstream fileIn;
    fileIn.open(fileName);

    //error handling
    if (!fileIn) {
        cout << "Error opening file." << endl;
        return 1;
    }

    // loop that reads the file and stores them in the vector obj.
    while (!fileIn.eof()) {
        //store input
        getline(fileIn, currState, ',');
        getline(fileIn, currCounty, ',');
        getline(fileIn, currCandidate, ',');
        getline(fileIn, currParty, ',');
        getline(fileIn, strVotes, '\n');

        //string to int
        currVotes = stoi(strVotes);

        //set current voting data from current line in txt
        currVoteObj.setVotingData(currState, currCounty, currCandidate, currParty, currVotes);

        //push back curr voting obj to list vector
        votingList.push_back(currVoteObj);
    }

    // looping the options to the user and calling functions based on their choice(s)
    while (userChoice >= 1 && userChoice <= 6 ) {
        cout << "/-------\\" << endl;
        cout << " Options" << endl;
        cout << "\\-------/" << endl;
        cout << endl;
        cout << "  |1| Data Overview" << endl;
        cout << "  |2| National Results" << endl;
        cout << "  |3| Visual State Results" << endl;
        cout << "  |4| Candidate Results" << endl;
        cout << "  |5| County Search" << endl;
        cout << "  |6| Exit" << endl;
        cout << endl;

        cout << "Select an option: ";
        cin >> userChoice;
        cout << endl;

        if (userChoice == 1) {
            cout << endl;
            cout << "======================================================================" << endl;

            cout << "| Data Overview: |" << endl;
            cout << endl;
            dataOverview(votingList);

            cout << "======================================================================" << endl;
            cout << endl;
            cout << endl;
            continue;
        }

        else if (userChoice == 2) {
            cout << endl;
            cout << "======================================================================" << endl;

            cout << "| National Results |" << endl;
            cout << endl;

            nationalResults(votingList);
            cout << "======================================================================" << endl;
            cout << endl;
            cout << endl;
            continue;
        }
        else if (userChoice == 3) {
            cout << endl;
            cout << "======================================================================" << endl;

            cout << "| Visual State Results |" << endl;
            cout << endl;
            
            cout << "(Each bar ";
            SetColor(33);
            cout << "'|' ";
            ResetColor();
            cout << "represents approx. 150,000 votes)\n" << endl;

            stateResults(votingList);
            cout << "======================================================================" << endl;
            cout << endl;
            cout << endl;
            continue;
        }
        else if (userChoice == 4) {
            cout << endl;
            cout << "======================================================================" << endl;

            cout << "| Candidate Results |" << endl;
            cout << endl;

            candidateResults(votingList);
            cout << "======================================================================" << endl;
            cout << endl;
            cout << endl;
            continue;
        }
        else if (userChoice == 5) {
            cout << endl;
            cout << "======================================================================" << endl;

            cout << "| County Search |" << endl;
            cout << endl;

            countySearch(votingList);
            cout << "======================================================================" << endl;
            cout << endl;
            cout << endl;
            continue;
        }
        else {
            SetColor(31);
            cout << "\nExiting\n";
            ResetColor();
            break;
        }
    }
    fileIn.close();
}

// ** FUNCTION DEFINITIONS: ** //

//This function takes a word as a parameter and then returns it in all caps
string allCaps(string word) {
    string caps;
    for (unsigned int i = 0; i < word.length(); i++) {
        caps += toupper(word.at(i));
    }

    return caps;
}

/* This function that takes in all the voting data (vector) as a parameter and prints the number of 
vote objects in the vector (election records), and the total sum of the num of votes (total votes) */
void dataOverview (vector<Votes>& votingList) {
    int sum = 0;
    
    cout << "Election Records Found: ";
    SetColor(33);
    cout << votingList.size() << endl;
    ResetColor();
    
    for (unsigned int i = 0; i < votingList.size(); i++) {
        sum += votingList[i].getNumVotes();
    }

    cout << "Total Votes Recorded: ";
    SetColor(33);
    cout << sum << endl;
    ResetColor();
}

/* This function takes all the voting data (vector) as the parameter and prints the candidates, 
their party, and number of votes received. The output is in ascending order for number of votes. 
It does so with the help of the sort function in the algorithm library and an overloaded operator 
in the candidate class */ 
void nationalResults(vector<Votes>& votingList) {
    vector<string> candNames;
    vector<Candidate> results;
    Candidate currCandidate;
    string tempName;
    
    for (unsigned int i = 0; i < votingList.size(); i++) {
        tempName = votingList[i].getVoteCandidate();
        auto iter = find(candNames.begin(), candNames.end(), tempName);

        if (iter == candNames.end()) {
            candNames.push_back(tempName);
        }

        else {
            continue;
        }
    }

    for (unsigned int i = 0; i < candNames.size(); i++) {
        currCandidate.candName = candNames[i];
        results.push_back(currCandidate);
    }
    
    for (unsigned int i = 0; i < votingList.size(); i++) {
        for (unsigned int j = 0; j < results.size(); j++) {
            if (results[j].candName == votingList[i].getVoteCandidate()) {
                results[j].party = votingList[i].getVoteParty();
                results[j].numVotes += votingList[i].getNumVotes();
            }
        }
    }

    sort(results.begin(), results.end());
    reverse(results.begin(), results.end());

    SetColor(33);
    cout << setw(20) << left << "|CANDIDATE|";
    cout << setw(15) << left << "|PARTY|";
    cout << setw(10) << right << "|VOTES|";
    cout << endl;
    ResetColor();

    for (auto& objs : results) {
        cout << setw(20) << left << objs.candName;
        cout << setw(15) << left << objs.party;
        cout << setw(10) << right << objs.numVotes;
        cout << endl;
    }
}

/*This function takes in all the voting data (vector) as a parameter and then prints the candidates, and a 
representation of the number of votes they received in a state that the user picks 
(a bar, '|', denoting about 150k votes). The output is in ascending order based on the number of votes
received in that state.*/ 
void stateResults (vector<Votes>& votingList) {
    vector<Votes> stateVotes;
    vector<string> candNames;
    Votes currVoteObj;
    string userState;
    string tempName;

    cout << "Enter State: ";
    cin.ignore();
    getline(cin, userState);
    userState = allCaps(userState);
    cout << endl;
    
    // Checking if the state exists
    bool validState = 0;
    for (int i = 0; i < 51; i++) {
        if (STATES[i] == userState) {
            validState = 1;
            break;
        }
    }
    if (validState == 0) {
        cout << "State Not Found." << endl;
        return;
    }

    //get unique candidate names into a string vector
    for (unsigned int i = 0; i < votingList.size(); i++) {
        tempName = votingList[i].getVoteCandidate();
        auto iter = find(candNames.begin(), candNames.end(), tempName);

        if (iter == candNames.end()) {
            candNames.push_back(tempName);
        }

        else {
            continue;
        }
    }
    //create candidate objects in stateVotes vector
    for (unsigned int i = 0; i < candNames.size(); i++) {
        string name = candNames.at(i);
        currVoteObj.setVoteCandidate(name);
        stateVotes.push_back(currVoteObj);
    }

    /*checks votinglist for the state the user inputs, and then checks candidates, 
    and sums votes in the corresponding objects vector */
    for (unsigned int i = 0; i < votingList.size(); i++) {
        string listState = votingList[i].getVoteState();
        string listCand = votingList[i].getVoteCandidate();
        if (userState == listState) {
            for (unsigned int j = 0; j < stateVotes.size(); j++) {
                string stateCand = stateVotes[j].getVoteCandidate();
                if (stateCand == listCand) {
                    int listVotes = votingList[i].getNumVotes();
                    int stateNumVotes = stateVotes[j].getNumVotes();
                    stateVotes[j].setNumVotes(stateNumVotes + listVotes);
                }
            }
        }
    }
    //sort in ascending order then reverse
    sort(stateVotes.begin(), stateVotes.end());
    reverse(stateVotes.begin(), stateVotes.end());

    //iterate thru stateVotes vector and compute the number of bars to output
    for (unsigned int i = 0; i < stateVotes.size(); i++) {
        double stateVoteRatio = round(stateVotes[i].getNumVotes() / 150000.0);
        cout << setw(20) << left << stateVotes[i].getVoteCandidate();
        for (int i = 0; i < stateVoteRatio; i++) {
            SetColor(33);
            cout << "|";
            ResetColor();
        }
        cout << endl;
    }
}

/* This function takes in all the voting data (vector) as a parameter, asks the user for a candidate's
name and it prints out that candidate's votes received, total votes in each state, the percent of votes 
the candidate received out of the total votes in a state, and the best state based for that candidate 
based on the highest percentage */
void candidateResults(vector<Votes>& votingList) {
    string userCandidate;
    string candidateFullName;
    string bestState;
    vector<CandResults> candidateData;
    CandResults tempCandData;
    string votingListState, currState, votingListCand = "";
    int currVotes = 0;
    bool validCand = 0;

    cout << "Enter Candidate: ";
    cin.ignore();
    getline(cin, userCandidate);
    userCandidate = allCaps(userCandidate);

    for (unsigned int i = 0; i < NUM_STATES; i++) {

        tempCandData.state = "";
        tempCandData.totalStateVotes = 0;
        tempCandData.candStateVotes = 0;
        tempCandData.votePercent = 0.00;

        for (unsigned int j = 0; j < votingList.size(); j++) {
            votingListState = votingList[j].getVoteState();
            currState = STATES[i];
            
            if (votingListState == currState) {
                votingListCand = votingList[j].getVoteCandidate();
                currVotes = votingList[j].getNumVotes();

                tempCandData.state = currState;
                tempCandData.totalStateVotes += currVotes;
                
                if (votingListCand.find(userCandidate) != string::npos) {
                    candidateFullName = votingListCand;
                    tempCandData.candStateVotes += currVotes;
                    validCand = 1;
                }
            }
        }

        tempCandData.votePercent = ((tempCandData.candStateVotes * 1.0) / (tempCandData.totalStateVotes * 1.0)) * 100.00;
        candidateData.push_back(tempCandData);
    }
    if (validCand == 0) {
        cout << "\nCandidate Not Found." << endl;
        return;
    }

    SetColor(33);
    cout << setw(15) << left << "|STATE|";
    cout << setw(15) << right << "|VOTES RECEIVED|";
    cout << setw(15) << right << "|TOTAL VOTES|";
    cout << setw(16) << right << "|% RECEIVED|";
    cout << endl;
    ResetColor();

    double maxPercent = candidateData[0].votePercent;
    for (unsigned int i = 0; i < candidateData.size(); i++) {
        cout << setw(15) << left << candidateData[i].state;
        cout << setw(15) << right << candidateData[i].candStateVotes;
        cout << setw(16) << right << candidateData[i].totalStateVotes;
        cout << fixed << setprecision(1) << setw(15) << right << candidateData[i].votePercent;
        cout << "%";
        cout << endl;
        if (candidateData[i].votePercent > maxPercent) {
            maxPercent = candidateData[i].votePercent;
            bestState = candidateData[i].state;
        }
    }
    
    cout << "\nThe best state for " << candidateFullName << " is " << bestState << endl;
}

/*This function takes in all the voting data (vector) as a parameter asks the user for a county for input,
and then prints out all the possible counties that the user could be looking for.
It outputs the county, state, candidate, and number of votes they received in that state */
void countySearch (vector<Votes>& votingList) {
    Votes tempCountyData;
    vector<Votes> countyData;
    string userCounty;

    cout << "Enter county: ";
    cin.ignore();
    getline(cin, userCounty);
    userCounty = allCaps(userCounty);

    for (unsigned int i = 0; i < votingList.size(); i++) {
        string currCounty = votingList[i].getVoteCounty();
        if (currCounty.find(userCounty) != string::npos) {
            tempCountyData.setVoteCounty(currCounty);
            tempCountyData.setVoteState(votingList[i].getVoteState());
            tempCountyData.setVoteCandidate(votingList[i].getVoteCandidate());
            tempCountyData.setNumVotes(votingList[i].getNumVotes());
            countyData.push_back(tempCountyData);
        }
    }
    vector<string> countyAndState;
    for (unsigned int i = 0; i < countyData.size(); i++) {
        string temp = countyData[i].getVoteCounty() + ", " + countyData[i].getVoteState();
        countyAndState.push_back(temp);
    }

    if (countyAndState.size() == 0) {
        cout << "No results." << endl;
        return;
    }

    else {
        cout << endl;
        cout << "Results Found:" << endl;
        cout << endl;
    }

    SetColor(33);
    cout << left << setw(40) << "|COUNTY, STATE|";
    cout << left << setw(20) << "|CANDIDATE|";
    cout << right << setw(10) << "|VOTES|";
    cout << endl;
    ResetColor();

    for (unsigned int i = 0; i < countyData.size(); i++) {
        cout << left << setw(40) << countyAndState[i];
        cout << left << setw(20) << countyData[i].getVoteCandidate();
        cout << right<< setw(10) << countyData[i].getNumVotes();
        cout << endl;
    }
}