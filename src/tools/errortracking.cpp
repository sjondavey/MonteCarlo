#include "errortracking.h"

namespace sjd
{
    ErrorTracking::ErrorTracking(string classNameInput)
    {
        errorMessages = vector<string>();
        hasErrors = false;
        className = classNameInput;
    }

   string ErrorTracking::getClassName() 
   {
      return className;
   }

   void ErrorTracking::clearErrorMessages()
    {
        hasErrors = false;
        errorMessages.clear();
    }

    void ErrorTracking::populateErrorMessage(string msg)
    {
        errorMessages.push_back(className + ": " + msg);
        hasErrors = true;
    }

    void ErrorTracking::populateErrorMessage(vector<string> msgs)
    {
        errorMessages.push_back(className);
        for (vector<string>::iterator it = msgs.begin(); it != msgs.end(); ++it)
        {
            errorMessages.push_back(*it);
        }
        hasErrors = true;
    }

    bool ErrorTracking::getHasErrors() const
    {
        return hasErrors;
    }

    vector<string> ErrorTracking::getErrorMessages() const 
    {
        return errorMessages;
    }

   string ErrorTracking::getErrorMessagesAsString() const
   {
      string allErrorMessages = "";
      for (size_t i = 0; i < errorMessages.size(); ++i) {
         allErrorMessages = allErrorMessages + errorMessages[i];
            if (i < errorMessages.size() - 1)
            {
                allErrorMessages = allErrorMessages + ", ";
            }
      }
      return allErrorMessages;
   }
}