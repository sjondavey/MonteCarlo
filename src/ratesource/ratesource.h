#ifndef SJD_RATESOURCE_INCLUDED
#define SJD_RATESOURCE_INCLUDED
#pragma once

#include <vector>
#include <set>

#include "../tools/errortracking.h"
#include <ql\time\date.hpp>

namespace sjd 
{

    /*======================================================================================
    RateSource 
    
    The base class for any rate source which contains future dated rates (as opposed to an
    historic rate source). 

    A RateSource must have an:
        - AnchorDate: A date before which there are no observation points
        - FinalDate: A date after which there are no observation points however the source
            *could* still extrapolate after this date

    Notes: 
    1) It is up to the user to insure that dates are in the appropriate range *before* 
    calls to get rates on a particular date. This is intentional as one of the major use 
    cases is Monte Carlo simulation and it would be unnecessary to check all the dates in 
    *every* path of the MC for every rate source. This should be done once, during setup 
    and then calls to getRateSource(date) can assume that 'date' will not cause the method 
    to fail. 

    2) When inheriting from this class it will often be the case that the user will 
    supply input data with an observation point on the anchor date *missing*. Please ensure 
    that implementing classes do something sensible between the anchor date and the first
    observation date
    =======================================================================================*/
    class RateSource 
    {        
    public:
        virtual ~RateSource () {};

        virtual bool isOK();
        void resetErrorMessages();
        vector<string> getErrorMessages() const;
        string getErrorMessagesAsString() const;

        QuantLib::Date getAnchorDate() const;
        QuantLib::Date getFinalDate() const;
        // Use isInRange(..) when you want to include AnchorDate logic
        virtual bool isInRange(QuantLib::Date date) const;
        // Use extendsTo(..) when you want to exclude anchor date logic, most often 
        // to understand if you can call the getValue(..) method from on a contract and get a 
        // number in return which is the case even if the rate source's anchor date is 
        // greater than the contract settlement date (the return value would be zero)
        virtual bool extendsTo(QuantLib::Date date) const;
        
        bool getAllowsExtrapolation() const;

    protected:
        std::unique_ptr<ErrorTracking> errorTracking;

        QuantLib::Date anchorDate;
        QuantLib::Date finalDate;
        
        bool allowExtrapolation;
    };
}

#endif