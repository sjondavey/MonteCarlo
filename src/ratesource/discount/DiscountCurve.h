#ifndef SJD_DISCOUNTCURVE_INCLUDED
#define SJD_DISCOUNTCURVE_INCLUDED

#include "discountratesource.h"
#include <ql/math/interpolations/linearinterpolation.hpp>
#include <ql/time/date.hpp>

namespace sjd 
{
   /*======================================================================================
    DiscountCurve: The simplest DiscountRateSource 

    NOTE : There are no calendar objects here, all dates are assumed to be good dates
            by the time they hit this class
    =======================================================================================*/
    class DiscountCurve : public DiscountRateSource
    {
    public:
        // Currently only implemented for interpolationType == linear
        // TODO: Add other types, especially loglinear
        DiscountCurve(QuantLib::Date anchorDate, 
                      std::vector<QuantLib::Date> observationDates, 
                      std::vector<double> discountFactors, 
                      std::string interpolationType, 
                      std::string currencyCode);    // the ISO 4217 three-letter code, e.g, "USD"
        
        virtual ~DiscountCurve() {};

        virtual bool isOK();

        virtual double getDiscountFactor(QuantLib::Date toDate) const;
        virtual const std::string& getCurrencyCode() const;

        std::vector<QuantLib::Date> getObservationDates() const;

    protected:
        std::string currencyCode;
        std::vector<QuantLib::Date> observationDates;
        std::vector<QuantLib::Date::serial_type> serialNumbers; // for the interpolator which does not keep the vector
        std::vector<double> discountFactors;
        QuantLib::Interpolation interpolator;
    };
}

#endif