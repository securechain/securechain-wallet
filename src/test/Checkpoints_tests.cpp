// Copyright (c) 2011-2013 The Bitcoin Core developers
// Copyright (c) 2015-2018 The Securechain developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//
// Unit tests for block-chain checkpoints
//

#include "checkpoints.h"

#include "uint256.h"

#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(Checkpoints_tests)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p0 = uint256("0x0000047462b7a97ff0e85630d00e57352d98ab4c17156273f22415fe8d78a104");
    uint256 p134444 = uint256("0x00000000048ed80d65bd2b2ef52e2960bd4b7d54534ac3d4881a7aac6c559733");
    BOOST_CHECK(Checkpoints::CheckBlock(0, p0));

    
    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckBlock(0, p134444));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckBlock(0+1, p134444));
    BOOST_CHECK(Checkpoints::CheckBlock(134444+1, p0));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 0);
}

BOOST_AUTO_TEST_SUITE_END()
