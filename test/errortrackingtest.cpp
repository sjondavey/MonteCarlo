#include "catch.hpp"
#include "../src/tools/errortracking.h"

using namespace std;
using namespace sjd;

TEST_CASE("ErrorTracking tools", "[tools]") {
    unique_ptr<ErrorTracking> error;
    string callingClassName = "MyNewClass";
    error = make_unique<ErrorTracking>(callingClassName);

    SECTION("Check class name features") {        
        REQUIRE(error->getClassName() == callingClassName);
    }

    SECTION("Check expected behaviour when logging an error") {
        // Starts off with no errors
        REQUIRE(error->getHasErrors() == false);
        string firstErrorMessage = "First error message";
        error->populateErrorMessage(firstErrorMessage);
        // registers an error when populated with a string
        REQUIRE(error->getHasErrors() == true);
        // returns the expected message
        REQUIRE(error->getErrorMessagesAsString() == callingClassName + ": " + firstErrorMessage);
        error->clearErrorMessages();
        // has no errors when reset
        REQUIRE(error->getHasErrors() == false);
        vector<string> msgs;
        msgs.push_back(firstErrorMessage);
        string secondErrorMessage = "second error message";
        msgs.push_back(secondErrorMessage);
        error->populateErrorMessage(msgs);
        // registers an error when populated with a vector
        REQUIRE(error->getHasErrors() == true);
        // returns the expected string message
        REQUIRE(error->getErrorMessagesAsString() == callingClassName + ", " + firstErrorMessage + ", " + secondErrorMessage);
        // returns the expected vector message
        REQUIRE(error->getErrorMessages()[0] == callingClassName);
        REQUIRE(error->getErrorMessages()[1] == firstErrorMessage);
        REQUIRE(error->getErrorMessages()[2] == secondErrorMessage);
        error->clearErrorMessages();
        // has no errors when reset
        REQUIRE(error->getHasErrors() == false);
    }
}
