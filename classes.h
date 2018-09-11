/*classes.h*/

//
// Classes for use with Chicago Crime Analysis program, e.g. "CrimeReport"
// and "CrimeCode".
//
// << Yushen Li >>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 02
//

#pragma once

#include <iostream>
#include <string>

using namespace std;


/*------------------CrimeCode Class---------------------*/
class CrimeCode
{
private:
    string ccIUCR;
    string Primary_Description;
    string Secondary_Description;
    int total = 0;
    
public:
    
    //Default Constructor
    CrimeCode()
    : ccIUCR(""), Primary_Description(""), Secondary_Description("")
    {}
    
    //Copy Constructor
    CrimeCode(string CCICUR, string PD, string SD)
    : ccIUCR(CCICUR), Primary_Description(PD), Secondary_Description(SD)
    {}
    
    //Decontructor
    ~CrimeCode()
    {}
    
    string getccIUCR() const
    {
        return ccIUCR;
    }
    string getPrimary_Description() const
    {
        return Primary_Description;
    }
    string getSecondary_Description() const
    {
        return Secondary_Description;
    }
    
    void updateTotal()
    {
        total += 1;
    }
    
    int getTotal()
    {
        return total;
    }
};

/*------------------CrimeReport Class---------------------*/
class CrimeReport
{
private:
    string DateTime;
    string crIUCR;
    string ArrestStatus;
    string DemosticStatus;
    int Beat;
    int District;
    int Ward;
    int Community;
    
public:
    //Default Constructor
    CrimeReport()
    :DateTime(""), crIUCR(""), ArrestStatus(""), DemosticStatus(""), Beat(0), District(0), Ward(0),Community(0)
    {}
    
    //Copy Constructor
    CrimeReport(string DT, string CRIUCR, string AS, string DS,int beat,int district, int ward, int community)
    :DateTime(DT), crIUCR(CRIUCR), ArrestStatus(AS), DemosticStatus(DS), Beat(beat), District(district), Ward(ward),Community(community)
    {}
    
    //Decontructor
    ~CrimeReport()
    {}
    
    string getDateTime() const
    {
        return DateTime;
    }
    string getcrIUCR() const
    {
        return crIUCR;
    }
    string getArrestStatus() const
    {
        return ArrestStatus;
    }
    string getDemosticStatus() const
    {
        return DemosticStatus;
    }
    int getBeat()
    {
        return Beat;
    }
    int getDistrict()
    {
        return District;
    }
    int getWard()
    {
        return Ward;
    }
    int getCommunity()
    {
        return Community;
    }
};


