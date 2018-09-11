/*main.cpp*/

//
// Chicago Crime Analysis program in modern C++.
//
// <<Yushen Li>>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 02
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <ctime>
#include "classes.h"

using namespace std;

//Function to sort the the top-5 crime
void doTotalSort(vector<CrimeCode> &C)
{
    sort(C.begin(),
         C.end(),
         [](CrimeCode &c1, CrimeCode &c2)
         {
             if(c1.getTotal() > c2.getTotal())
                 return true;
             else
                 return false;
         }
         );
}

//Function to sort the CrimeCode
void doIUCRsort(vector<CrimeCode> &C)
{
    sort(C.begin(),
         C.end(),
         [](CrimeCode &c1, CrimeCode &c2)
         {
             if(c1.getccIUCR() < c2.getccIUCR())
                 return true;
             else
                 return false;
         }
         );
}

//Print out the top-5 crime
void printTotal(vector<CrimeCode> &C)
{
    int crimeCount = 0;
    for(CrimeCode& cc : C)
    {
        if(crimeCount < 5) //print out vector index 0 - 4
            cout << cc.getccIUCR() << ":   " << cc.getTotal() << ", " << cc.getPrimary_Description() << ": " << cc.getSecondary_Description() << endl;
        crimeCount++;
    }
}
int main()
{
    clock_t start;
    double duration = 0.0;
    start = clock();
    string  crimeCodesFilename, crimesFilename;
    
    cin >> crimeCodesFilename;
    cout << crimeCodesFilename << endl;
    
    cin >> crimesFilename;
    cout << crimesFilename << endl;
    
    ifstream  codesFile(crimeCodesFilename);
    ifstream  crimesFile(crimesFilename);
    
    cout << "** Crime Analysis **" << endl << endl;
    
    cout << std::fixed;
    cout << std::setprecision(2);
    
    //checking if CrimeCode file is good, if not return error message
    if (!codesFile.good())
    {
        cout << "**ERROR: cannot open crime codes file: '" << crimeCodesFilename << "'" << endl;
        return -1;
    }
    //checking if CrimeReport file is good, if not return error message
    if (!crimesFile.good())
    {
        cout << "**ERROR: cannot open crimes file: '" << crimesFilename << "'" << endl;
        return -1;
    }
    
    vector<CrimeCode> crimeCodes; //create crimeCode vector
    vector<CrimeReport> crimeReports; //create CrimeReport vector
    
    string line1, line2, CCIUCR, Pri_Description, Sec_Description ,DT,
    CRIUCR, ArrestStat, DemosticStat, beat, district, ward, community, year; //declaring parsing variables
    getline(codesFile,line1); //Skip the first useless line
    getline(crimesFile,line2); //Skip the first useless line
    
    int CrimeCodeCounter = 0; //Declare a crime code counter
    while(getline(codesFile, line1)) //Start parsing the CrimeCode file
    {
        CrimeCodeCounter++;
        stringstream ss1(line1);
        getline(ss1, CCIUCR, ',');
        getline(ss1, Pri_Description, ',');
        getline(ss1, Sec_Description, ',');
        CrimeCode CC(CCIUCR, Pri_Description, Sec_Description);
        crimeCodes.push_back(CC); //push all the parsing data to the CrimeCode vector
    }
    
    auto &C = crimeCodes; // use an iterator to share the CrimeCode vector
    doIUCRsort(C);
    
    int CrimeReportCounter = 0; //Declare CrimeReport counter
    while(getline(crimesFile, line2)) //Starting parsing the Crimes file
    {
        CrimeReportCounter++;
        stringstream ss2(line2);
        getline(ss2, DT, ',');
        getline(ss2, CRIUCR, ',');
        getline(ss2, ArrestStat, ',');
        getline(ss2, DemosticStat, ',');
        getline(ss2, beat, ',');
        getline(ss2, district, ',');
        getline(ss2, ward, ',');
        getline(ss2, community, ',');
        getline(ss2, year, ',');
        CrimeReport CR(DT, CRIUCR, ArrestStat, DemosticStat, stoi(beat), stoi(district), stoi(ward), stoi(community));
        crimeReports.push_back(CR); //push all the parsing data to the CrimeReport vector
        //Setup an find if function to if the the code is already in
        auto F = find_if(crimeCodes.begin(), crimeCodes.end(),
                         [=](CrimeCode& cc)
                         {
                             return(cc.getccIUCR() == CRIUCR);
                         });
        if(F != crimeCodes.end()) //if the crimeCode found, update the total appearences.
            F->updateTotal();
    }
    
    /*-----------print out the Date Range----------------*/
    auto& A = crimeReports;//
    cout << "Date range: " << A[0].getDateTime() << " - " << A.back().getDateTime() << endl << endl;
    
    /*-----------------crimecode printing----------------*/
    cout << "# of crime codes: " << CrimeCodeCounter << endl;
    int crimeCount = 0;
    for(CrimeCode& c : crimeCodes) //print out the first 3 and the last 3
    {
        if(crimeCount < 3) //print out first 3 individual data
        {
            cout << c.getccIUCR() << ":   " << c.getPrimary_Description() << ":" << c.getSecondary_Description();
            if(crimeCount == 2)  //middle part print out ...
                cout << "..." << endl;
        }
        crimeCount++;
        
        if(crimeCount > C.size()-3) //print out last 3 individual data
            cout << c.getccIUCR() << ":   " << c.getPrimary_Description() << ":" << c.getSecondary_Description();
    }
    /*----------------crimeFile printing----------------*/
    
    cout << endl << endl;
    cout << "# of crimes: " << CrimeReportCounter << endl;
    
    crimeCount = 0;
    for(CrimeReport& c : crimeReports)
    {
        if(crimeCount < 3) //print out first 3 individual data
        {
            cout << c.getcrIUCR() << ":   " << c.getDateTime() << ", " << c.getBeat() << ", "<< c.getDistrict() << ", "<<c.getWard() << ", "<<c.getCommunity();
            if(c.getArrestStatus() == "TRUE" || c.getArrestStatus() == "true" ) //Compare Arrest Status (True or False)
                cout << ", arrested";
            if(c.getDemosticStatus() == "TRUE" || c.getDemosticStatus() == "true") //Compare Domestic Status (True or False)
                cout << ", domestic violence";
            cout << endl;
            if(crimeCount == 2) //middle part print out ...
                cout <<"..." << endl;
            
        }
        crimeCount++;
        if(crimeCount > A.size()-3) //print of last 3 individual data
        {
            cout << c.getcrIUCR() << ":   " << c.getDateTime() << ", " << c.getBeat() << ", "<< c.getDistrict() << ", "<<c.getWard() << ", "<<c.getCommunity();
            if(c.getArrestStatus() == "TRUE" || c.getArrestStatus() == "true" ) //Compare Arrest Status (True or False)
                cout << ", arrested";
            if(c.getDemosticStatus() == "TRUE" || c.getDemosticStatus() == "true") //Compare Domestic Status (True or False)
                cout << ", domestic violence";
            cout << endl;
        }
    }
    
    doTotalSort(C);
    cout << endl << "** Top-5 Crimes **" << endl;
    cout <<"Code:   Total, Description" << endl;
    printTotal(C);
    cout << endl << "** Done **" << endl;
    
/*____________DEBUG______________*/
    duration = (clock()-start) / (double) CLOCKS_PER_SEC;
    cout << "Total Run time: " << duration << endl;
    return 0;
}



