#include "catch.hpp"
#include "../src/ratesource/discount/flatrate.h"

using namespace std;
using namespace sjd;

TEST_CASE("Flat Rate Discounting Rate Source Tests", "[ratesource]") {
    unique_ptr<FlatRate> naccRate;
    string currencyCode = "ZAR";
    QuantLib::Date anchorDate = QuantLib::Date(7, QuantLib::Jul, 2020);


    SECTION("Check errors are caught") {
        // different size inputs
        naccRate = make_unique<FlatRate>(anchorDate, 0.06, currencyCode);
        REQUIRE(naccRate->isOK() == true);
    }

    SECTION("Check class name features") {        
        double rate = 0.06;
        naccRate = make_unique<FlatRate>(anchorDate, rate, currencyCode);
        REQUIRE(naccRate->isOK() == true);
        REQUIRE(naccRate->getCurrencyCode() == currencyCode);
        QuantLib::Date toDate = QuantLib::Date(12, QuantLib::Dec, 2021);
        QuantLib::Actual365Fixed dc = QuantLib::Actual365Fixed();
        double manualTime = dc.yearFraction(anchorDate, toDate);
        REQUIRE(abs(naccRate->getDiscountFactor(toDate) - std::exp(-rate * manualTime)) < 1e-13);
    }
}