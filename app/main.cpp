#include <iostream>
#include <memory> // unique_ptr
#include "../src/formula/Black76Formula.h"
#include "../src/ratesource/discount/DiscountCurve.h"


using namespace sjd;

int main()
{
    std::cout << "Hello, World!" << std::endl;

    double F = 100, X = 110, sd = 0.2, df = 0.97;
    std::unique_ptr<Black76Option> call;
    call = std::make_unique<Black76Call>(F,X,sd,df);
    std::unique_ptr<Black76Option> put = std::make_unique<Black76Put>(F,X,sd,df);
    std::cout << abs(put->value() - call->value());

    // std::unique_ptr<sjd::DiscountCurve> curve = std::make_unique<sjd::DiscountCurve>();
    // std::cout << "Testing QL: " << curve->day();


    return 0;
}

