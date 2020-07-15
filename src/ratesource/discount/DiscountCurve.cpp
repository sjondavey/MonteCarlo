#include "discountcurve.h"
#include <algorithm>

namespace sjd {

    /*======================================================================================
    DiscountCurve 
    =======================================================================================*/
    DiscountCurve::DiscountCurve(QuantLib::Date anchorDate, 
                                 std::vector<QuantLib::Date> observationDates, 
                                 std::vector<double> discountFactors, 
                                 std::string interpolationType,
                                 std::string currencyCode) 
    {
        errorTracking = std::make_unique<ErrorTracking>("DiscountCurve");
        this->currencyCode = currencyCode;
        this->anchorDate = anchorDate;
        this->observationDates = observationDates;
        this->discountFactors = discountFactors;
        this->finalDate = *(--observationDates.end());
        this->allowExtrapolation = false;

        std::transform(interpolationType.begin(), interpolationType.end(), interpolationType.begin(), ::tolower);
        serialNumbers = std::vector<QuantLib::Date::serial_type>(observationDates.size());
        for(std::size_t i = 0; i < observationDates.size(); ++i) {
            serialNumbers[i] = observationDates[i].serialNumber();
        }

        if (interpolationType == "linear") {
            interpolator = QuantLib::LinearInterpolation(serialNumbers.begin(), serialNumbers.end(), this->discountFactors.begin());
        }
        else {
            interpolator = QuantLib::LinearInterpolation(serialNumbers.begin(), serialNumbers.end(), this->discountFactors.begin());
        }
    }

    bool DiscountCurve::isOK()
    {
        if (!RateSource::isOK())
        {
            return false;
        }
        string errorMessage = "";
        if (observationDates.size() != discountFactors.size())
        {
            errorMessage = "Observation date must have the same number of points as  Discount factors";
            errorTracking->populateErrorMessage(errorMessage);
        }
        if (!is_sorted(serialNumbers.begin(), serialNumbers.end()))
        {
            errorMessage = "Observation dates are not strictly increasing";
            errorTracking->populateErrorMessage(errorMessage);
        }
        if (anchorDate != *(observationDates.begin()))
        {
            errorMessage = "First observation date must be the same as the anchor date for a discount curve";
            errorTracking->populateErrorMessage(errorMessage);
        }
        if (abs(discountFactors[0]-1) > 1e-13) {
            errorMessage = "First discount rate must be 1.0";
            errorTracking->populateErrorMessage(errorMessage);
        }
        for (size_t i = 0; i < discountFactors.size(); ++i) 
        {
            bool hasNegativeInputs = false;
            if ((!hasNegativeInputs) && (discountFactors[i] <= 0) )
            {
                errorTracking->populateErrorMessage("Curve has negative discount factors");
                hasNegativeInputs = true;
            }
        }
        // Not check for discount factors > 1.0 (i.e. negative interest rates). This should not impact this class
        return !errorTracking->getHasErrors();
    }

    double DiscountCurve::getDiscountFactor(QuantLib::Date toDate) const
    {
        if ((toDate < anchorDate) || (toDate > finalDate)) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return this->interpolator(toDate.serialNumber());
    }

    const std::string& DiscountCurve::getCurrencyCode() const
    {
        return currencyCode;
    }

    std::vector<QuantLib::Date> DiscountCurve::getObservationDates() const
    {
        return observationDates;
    }        
}