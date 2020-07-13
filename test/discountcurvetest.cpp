#include "catch.hpp"
#include "../src/ratesource/discount/discountcurve.h"

using namespace std;
using namespace sjd;

TEST_CASE("Discount Curve Tests", "[ratesource]") {
    unique_ptr<DiscountCurve> dc;
    QuantLib::Date anchorDate = QuantLib::Date(7, QuantLib::Jul, 2020);
    vector<QuantLib::Date> observationDates;
    vector<double> discountFactors;

    observationDates.push_back(anchorDate);
    observationDates.push_back(QuantLib::Date(1, QuantLib::Jul, 2021));
    discountFactors.push_back(1.0);
    discountFactors.push_back(0.95);

    SECTION("Check errors are caught") {
        observationDates.clear();
        discountFactors.clear();

        // different size inputs
        observationDates.push_back(anchorDate);
        observationDates.push_back(QuantLib::Date(1, QuantLib::Jul, 2021));
        discountFactors.push_back(1.0);
        discountFactors.push_back(0.95);
        discountFactors.push_back(0.90);
        dc = make_unique<DiscountCurve>(anchorDate, observationDates, discountFactors, "linear");
        REQUIRE(dc->isOK() == false);

        // No observation date on the anchor date
        observationDates.clear();
        discountFactors.clear();
        observationDates.push_back(QuantLib::Date(6, QuantLib::Jul, 2020));
        observationDates.push_back(QuantLib::Date(1, QuantLib::Jul, 2021));
        discountFactors.push_back(1.0);
        discountFactors.push_back(0.95);
        dc = make_unique<DiscountCurve>(anchorDate, observationDates, discountFactors, "linear");
        REQUIRE(dc->isOK() == false);

        // first discount factor not 1.0
        observationDates.clear();
        discountFactors.clear();
        observationDates.push_back(anchorDate);
        observationDates.push_back(QuantLib::Date(1, QuantLib::Jul, 2021));
        discountFactors.push_back(1.1);
        discountFactors.push_back(0.95);
        dc = make_unique<DiscountCurve>(anchorDate, observationDates, discountFactors, "linear");
        REQUIRE(dc->isOK() == false);

        // negative discount rate
        observationDates.clear();
        discountFactors.clear();
        observationDates.push_back(anchorDate);
        observationDates.push_back(QuantLib::Date(1, QuantLib::Jul, 2021));
        discountFactors.push_back(1.0);
        discountFactors.push_back(-0.95);
        dc = make_unique<DiscountCurve>(anchorDate, observationDates, discountFactors, "linear");
        REQUIRE(dc->isOK() == false);

        // observation dates not strictly increasing
        observationDates.clear();
        discountFactors.clear();
        observationDates.push_back(anchorDate);
        observationDates.push_back(anchorDate); // two of the same points
        observationDates.push_back(QuantLib::Date(1, QuantLib::Jul, 2021));
        discountFactors.push_back(1.0);
        discountFactors.push_back(1.0);
        discountFactors.push_back(-0.95);
        dc = make_unique<DiscountCurve>(anchorDate, observationDates, discountFactors, "linear");
        REQUIRE(dc->isOK() == false);

        // All good
        observationDates.clear();
        discountFactors.clear();
        observationDates.push_back(anchorDate);
        observationDates.push_back(QuantLib::Date(1, QuantLib::Jul, 2021));
        discountFactors.push_back(1.0);
        discountFactors.push_back(0.95);
        dc = make_unique<DiscountCurve>(anchorDate, observationDates, discountFactors, "LINEAR");
        REQUIRE(dc->isOK() == true);
    }

    SECTION("Check class name features") {        
        observationDates.clear();
        discountFactors.clear();

        observationDates.push_back(anchorDate);
        observationDates.push_back(QuantLib::Date(1, QuantLib::Jul, 2021));
        discountFactors.push_back(1.0);
        discountFactors.push_back(0.95);
        dc = make_unique<DiscountCurve>(anchorDate, observationDates, discountFactors, "linear");
        REQUIRE(dc->isOK() == true);

        REQUIRE(dc->getObservationDates().size() == observationDates.size());
        REQUIRE(dc->getObservationDates()[0] == observationDates[0]);
        REQUIRE(dc->getObservationDates()[1] == observationDates[1]);

        // Returns NaN outside of [anchorDate, finalDate] range
        REQUIRE(std::isnan(dc->getDiscountFactor(QuantLib::Date(6, QuantLib::Jul, 2020))));
        REQUIRE(std::isnan(dc->getDiscountFactor(QuantLib::Date(2, QuantLib::Jul, 2021))));
        // Returns the input values on the input dates
        REQUIRE(abs(dc->getDiscountFactor(QuantLib::Date(7, QuantLib::Jul, 2020))-1) < 1e-13);
        REQUIRE(abs(dc->getDiscountFactor(QuantLib::Date(1, QuantLib::Jul, 2021))-0.95) < 1e-13);

    }

    SECTION("Check features from ratesource") {        
        observationDates.clear();
        discountFactors.clear();

        observationDates.push_back(anchorDate);
        observationDates.push_back(QuantLib::Date(1, QuantLib::Jul, 2021));
        discountFactors.push_back(1.0);
        discountFactors.push_back(0.95);
        dc = make_unique<DiscountCurve>(anchorDate, observationDates, discountFactors, "linear");
        REQUIRE(dc->isOK() == true);
        REQUIRE(dc->getAllowsExtrapolation() == false);

        REQUIRE(dc->getAnchorDate() == anchorDate);
        REQUIRE(dc->getFinalDate() == QuantLib::Date(1, QuantLib::Jul, 2021));

        REQUIRE(dc->isInRange(anchorDate) == true);
        REQUIRE(dc->extendsTo(anchorDate) == true);
        // day before anchor date
        REQUIRE(dc->isInRange(QuantLib::Date(6, QuantLib::Jul, 2020)) == false);
        REQUIRE(dc->extendsTo(QuantLib::Date(6, QuantLib::Jul, 2020)) == true);
        // final date
        REQUIRE(dc->isInRange(QuantLib::Date(1, QuantLib::Jul, 2021)) == true);
        REQUIRE(dc->extendsTo(QuantLib::Date(1, QuantLib::Jul, 2021)) == true);
        // day after final date
        REQUIRE(dc->isInRange(QuantLib::Date(2, QuantLib::Jul, 2021)) == false);
        REQUIRE(dc->extendsTo(QuantLib::Date(2, QuantLib::Jul, 2021)) == false);

    }
}