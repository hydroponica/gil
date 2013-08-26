// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 Gil Developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0x9c99b474842364abf2ae6a86adcca3cd01ded2785c1470f13f324bdfa3b0ce7b"))
            (     27573, uint256("0xb36188a82f7cb82a757147c03d3a308db565dc05c99071a677d8379f6e36da1d"))
            (     29589, uint256("0x6133a9f9c9186c785ead59453f7ef862111de00d3f8e4c1094c49cf0cb2ee627"))
            (     35637, uint256("0xf9c702a28953b974a40b11d0c7d4d66147a1468141cef7f7623f123d10cc394a"))
            (     37653, uint256("0x4e7803c5b3d28b504c877ff2abe21747f76447749e41dd68dc9f0db1c409ad8d"))
            (     39669, uint256("0x59f7e17ffe86ff7a784565c2d37d076bd7cd3a751efe4e05a5a9b5ddab3a79a5"))
            (     43701, uint256("0x169df9540a3439d91b191947f867dcc7169904f04543d42e5fa3773feba86ec8"))
            (     47733, uint256("0x1fa40abdbb70b24df67730b5119f9e26bdab27b43b5d18ab1d31e873a597d9b1"))
            (     51764, uint256("0x8fd477f947f874c148539b81f9dc164340170f9203234d436f425b65ed039af6"))
            (     53762, uint256("0xa4ed80be70a332c67693d72bcbd3606c43ce8f5f50c8154bb1ee081ba12edf48"))
			(     82050, uint256("0x461eee53b6ad6e199f44e00dd38d8bdfe72747eda17631823a0ffafa94853a3a"))
            (     82099, uint256("0xa247b8665c7a0fec641c3785d2682c177ccb33c47468d17636e68a275cea2559"))
            (     82138, uint256("0x8eb50d9366870f8348b5dc2482864ada68757835f58e422a8327b3298cbd8f26"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
