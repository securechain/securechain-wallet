#include "core.h"
#include "main.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(main_tests)

BOOST_AUTO_TEST_CASE(subsidy_limit_test)
{
    uint64_t nSum = 0;
    int nHeight;
    for (nHeight = 0; nHeight < 10000; nHeight++) {
        uint64_t nSubsidy = GetBlockValue(nHeight, 0);

        if (nHeight == 0)
        {
            BOOST_CHECK(nSubsidy <= 1 * COIN);
        }
        else if(nHeight < 500)
        {
            BOOST_CHECK(nSubsidy <= 0.05 * COIN);
        }
        else if(nHeight < 1000)
        {
            BOOST_CHECK(nSubsidy <= 0.1 * COIN);
        }
        else if(nHeight < 1500)
        {
            BOOST_CHECK(nSubsidy <= 0.25 * COIN);
        }
        else if(nHeight < 2000)
        {
            BOOST_CHECK(nSubsidy <= 0.5 * COIN);
        }
        else if(nHeight < 2500)
        {
            BOOST_CHECK(nSubsidy <= 1 * COIN);
        }
        else if(nHeight < 3000)
        {
            BOOST_CHECK(nSubsidy <= 2 * COIN);
        }
        else if(nHeight < 3500)
        {
            BOOST_CHECK(nSubsidy <= 3 * COIN);
        }
        else if(nHeight < 4000)
        {
            BOOST_CHECK(nSubsidy <= 3.75 * COIN);
        }
        else if(nHeight < 4500)
        {
            BOOST_CHECK(nSubsidy <= 4.5 * COIN);
        }
        else
        {
            BOOST_CHECK(nSubsidy <= 5 * COIN);
        }

        nSum += nSubsidy;
        BOOST_CHECK(MoneyRange(nSum));
    }

    for (; nHeight < 70000000; nHeight += 10000) {
        uint64_t nSubsidy = GetBlockValue(nHeight, 0);
        BOOST_CHECK(nSubsidy <= 5 * COIN);
        nSum += nSubsidy * 10000;
        BOOST_CHECK(MoneyRange(nSum));
    }

    BOOST_CHECK(nSum == 2098492895000ULL);
}

BOOST_AUTO_TEST_SUITE_END()
