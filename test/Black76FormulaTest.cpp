#include <boost\test\unit_test.hpp>
#include "../src/formula/Black76Formula.h"
#include <cmath> // std::isnan in C++11

using namespace std;
using namespace boost::unit_test_framework;
using namespace boost::math;
using namespace sjd;

BOOST_AUTO_TEST_SUITE(Black76_test)

    BOOST_AUTO_TEST_CASE(invalid_inputs_test)
    {
        BOOST_TEST_MESSAGE("Testing Black Scholes Inputs ...");

        double F = -100, X = 110, sd = 0.2, df = 0.97;
        unique_ptr<Black76Option> call = make_unique<Black76Call>(F,X,sd,df);
        unique_ptr<Black76Option> put = make_unique<Black76Put>(F,X,sd,df);
        BOOST_CHECK(std::isnan(put->value()));
        BOOST_CHECK(std::isnan(call->value()));
        BOOST_CHECK(std::isnan(put->delta()));
        BOOST_CHECK(std::isnan(call->delta()));

        F = 100;
        sd = 0;
        call = make_unique<Black76Call>(F,X,sd,df);
        put = make_unique<Black76Put>(F,X,sd,df);
        BOOST_CHECK(std::isnan(put->value()));
        BOOST_CHECK(std::isnan(call->value()));
        BOOST_CHECK(std::isnan(put->delta()));
        BOOST_CHECK(std::isnan(call->delta()));

        sd = 0.2;
        call = make_unique<Black76Call>(F,X,sd,df);
        put = make_unique<Black76Put>(F,X,sd,df);
        BOOST_CHECK(abs(put->value() - 13.8632506131676) < 1e-14);
        BOOST_CHECK(abs(call->value() - 4.163250613167595) < 1e-14);
        BOOST_CHECK(abs(put->delta() + 0.6273439192177788) < 1e-14) ;
        BOOST_CHECK(abs(call->delta() - 0.3426560807822211) < 1e-14);
    }


    BOOST_AUTO_TEST_CASE(put_call_parity_test)
    {
        BOOST_TEST_MESSAGE("Testing Black Scholes Put/Call parity ...");

        double F = 100, X = 110, sd = 0.2, df = 0.97;
        unique_ptr<Black76Option> call = make_unique<Black76Call>(F,X,sd,df);
        unique_ptr<Black76Option> put = make_unique<Black76Put>(F,X,sd,df);
        BOOST_CHECK(abs(put->value() - call->value() - (X-F) * df) < 1e-14);
    }

BOOST_AUTO_TEST_SUITE_END()

