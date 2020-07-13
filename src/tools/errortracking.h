#ifndef SJD_ERRORTRACKING_INCLUDED
#define SJD_ERRORTRACKING_INCLUDED

#pragma once

#include <string>
#include <vector>

using namespace std;
/*======================================================================================
Overview

=======================================================================================*/

namespace sjd
{
    class ErrorTracking 
    {
    public:
        ErrorTracking(string className);

        string getClassName();

        void clearErrorMessages();
        void populateErrorMessage(string msg);
        void populateErrorMessage(vector<string> msg);
        bool getHasErrors() const;
        vector<string> getErrorMessages() const;
        string getErrorMessagesAsString() const;

    private:
        bool hasErrors;
        vector<string> errorMessages;
        string className;
    };
}

#endif