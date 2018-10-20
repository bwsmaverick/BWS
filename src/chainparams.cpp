// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include <iostream>

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x21;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0x24;
        vAlertPubKey = ParseHex("04967d05d980f003d925fe4c10295696c2659d17c5a42f575fa0fe4d3d4e597c9bdc3255f84415bf90bed12f73069418648628470978f3c917ccb6ca1b98f66011");
        nDefaultPort = 22321;
        nRPCPort = 22320;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "ATMs May Pave Way as Cryptocurrency Seeks Route to Mainstream Adoption";
        std::vector<CTxIn> vin;
        std::vector<CTxOut> vout;
        vin.resize(1);
        vout.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        vout[0].nValue = 0;
        vout[0].scriptPubKey = CScript() << ParseHex("04c629dd47950d15c4f63db4e67247335e09dec8b4ca4c157a23858e2503709e5fe3ba75d5b5263b046ae4b20af135a4dc79e66123ad9a15e65a98798bfee60724") << OP_CHECKSIG;
        CTransaction txNew(1, 1539969926, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1539969926;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 21527802;
		
		
/*
nNonce is: 21527802
Hash is: 00000198707c071cdb39cc8332eccfe889013ad88b65a63673672b0bda8177e7
Block is: CBlock(hash=00000198707c071cdb39cc8332eccfe889013ad88b65a63673672b0bda8177e7, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=db02a72ed27a838d4b91ade9852559cde36a598ed20505484e3900202cb4e25a, nTime=1539969926, nBits=1e0fffff, nNonce=21527802, vtx=1, vchBlockSig=)
  Coinbase(hash=db02a72ed27a838d4b91ade9852559cde36a598ed20505484e3900202cb4e25a, nTime=1539969926, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a4641544d73204d61792050617665205761792061732043727970746f63757272656e6379205365656b7320526f75746520746f204d61696e73747265616d2041646f7074696f6e)
    CTxOut(nValue=0.00, scriptPubKey=04c629dd47950d15c4f63db4e67247335e09dec8b4ca4c157a23858e2503709e5fe3ba75d5b5263b046ae4b20af135a4dc79e66123ad9a15e65a98798bfee60724 OP_CHECKSIG)

  vMerkleTree:  db02a72ed27a838d4b91ade9852559cde36a598ed20505484e3900202cb4e25a

*/

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000198707c071cdb39cc8332eccfe889013ad88b65a63673672b0bda8177e7"));
        assert(genesis.hashMerkleRoot == uint256("0xdb02a72ed27a838d4b91ade9852559cde36a598ed20505484e3900202cb4e25a"));
                
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25); // B
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85); // b
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 45); // K
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0x01)(0x37).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0x17)(0x49).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 100;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x27;
        pchMessageStart[1] = 0x12;
        pchMessageStart[2] = 0x40;
        pchMessageStart[3] = 0x11;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04d6450721ab425a37a351b768049b7e7628d0c507d6b40287140b529703b44237067b5175376c862411322a78665470a30706c871a97d8aed5a34630b36094782");
        nDefaultPort = 32321;
        nRPCPort = 32320;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 55495;
		
        hashGenesisBlock = genesis.GetHash();

/*
testnet nNonce is: 55495
Hash is: 00007909e1599f4cbc8251b2a8a7019f723a748f9cc92bbdf1b7819e929b49eb
Block is: CBlock(hash=00007909e1599f4cbc8251b2a8a7019f723a748f9cc92bbdf1b7819e929b49eb, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=db02a72ed27a838d4b91ade9852559cde36a598ed20505484e3900202cb4e25a, nTime=1539969926, nBits=1f00ffff, nNonce=55495, vtx=1, vchBlockSig=)
  Coinbase(hash=db02a72ed27a838d4b91ade9852559cde36a598ed20505484e3900202cb4e25a, nTime=1539969926, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a4641544d73204d61792050617665205761792061732043727970746f63757272656e6379205365656b7320526f75746520746f204d61696e73747265616d2041646f7074696f6e)
    CTxOut(nValue=0.00, scriptPubKey=04c629dd47950d15c4f63db4e67247335e09dec8b4ca4c157a23858e2503709e5fe3ba75d5b5263b046ae4b20af135a4dc79e66123ad9a15e65a98798bfee60724 OP_CHECKSIG)

  vMerkleTree:  db02a72ed27a838d4b91ade9852559cde36a598ed20505484e3900202cb4e25a


*/

        assert(hashGenesisBlock == uint256("0x00007909e1599f4cbc8251b2a8a7019f723a748f9cc92bbdf1b7819e929b49eb"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); // T
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 127); // t
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 58); // Q
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x19)(0x55).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x25)(0x63).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
