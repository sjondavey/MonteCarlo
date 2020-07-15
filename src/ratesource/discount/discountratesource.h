#ifndef SJD_DISCOUNTRATESOURCE_INCLUDED
#define SJD_DISCOUNTRATESOURCE_INCLUDED
#pragma once

#include "../ratesource.h"

namespace sjd 
{
   /*======================================================================================
   DiscountRateSource 
    
    The base class for any interest rate curves that will be used for discounting (as opposed 
    to those curves that are used to get reference rates for derivatives). DiscountRateSource's 
    are used to move cashflows in time (present value or future value cash flows). Typical examples
    include:
        zero curves, 
        discount curves, 
        stripped interest rate curves etc

    Note: When inheriting from this class it will often be the case that the user will 
        supply input data with an observation point on the anchor date *missing*. Please 
        ensure that implementing classes insure the discount factor to the anchor date is 
        1.0;
    =======================================================================================*/
    class DiscountRateSource : public RateSource
    {
        
    public:
        virtual ~DiscountRateSource() {};

        // NB Dates assumed to be good. Call isInRange(...) before calling this
        virtual double getDiscountFactor(QuantLib::Date toDate) const = 0;
        // returns the ISO 4217 three-letter code, e.g, "USD"
        virtual const std::string& getCurrencyCode() const = 0;
    };
}

#endif