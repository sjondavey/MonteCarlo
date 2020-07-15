#include "flatrate.h"

namespace sjd 
{
   /*======================================================================================
    FlatRate: A flat, continuously compounded, actual/365 interest rate used for discounting
    =======================================================================================*/
    FlatRate::FlatRate(QuantLib::Date anchorDate, 
                        double naccRate, 
                        std::string currencyCode)
    {
        errorTracking = std::make_unique<ErrorTracking>("FlatRate");
        this->currencyCode = currencyCode;
        this->naccRate = naccRate;
        this->anchorDate = anchorDate;
        this->finalDate = anchorDate;
        this->allowExtrapolation = true;
        dc = make_unique<QuantLib::Actual365Fixed>();        
    }
        
    bool FlatRate::isOK()
    {
        if (!RateSource::isOK())
        {
            return false;
        }
        return true;
    }

    double FlatRate::getDiscountFactor(QuantLib::Date toDate) const
    {
        double time = dc->yearFraction(anchorDate, toDate);
        return std::exp(-naccRate * time);
    }

    const std::string& FlatRate::getCurrencyCode() const
    {
        return currencyCode;
    }

}
