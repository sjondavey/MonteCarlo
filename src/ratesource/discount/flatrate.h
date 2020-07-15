#ifndef SJD_FLATRATE_INCLUDED
#define SJD_FLATRATE_INCLUDED

#include "discountratesource.h"
#include <ql/time/date.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>

namespace sjd 
{
   /*======================================================================================
    FlatRate: A flat, continuously compounded interest rate used for discounting

    =======================================================================================*/
    class FlatRate : public DiscountRateSource
    {
    public:
        FlatRate(QuantLib::Date anchorDate, 
                 double naccRate, 
                 std::string currencyCode);    // the ISO 4217 three-letter code, e.g, "USD"
        
        virtual ~FlatRate() {};

        virtual bool isOK();

        virtual double getDiscountFactor(QuantLib::Date toDate) const;
        virtual const std::string& getCurrencyCode() const;

    protected:
        std::string currencyCode;
        double naccRate;
        std::unique_ptr<QuantLib::DayCounter> dc;
    };
}

#endif