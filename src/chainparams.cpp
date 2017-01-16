// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

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
        pchMessageStart[0] = 0x0a;
        pchMessageStart[1] = 0x0f;
        pchMessageStart[2] = 0x0c;
        pchMessageStart[3] = 0x99;
        vAlertPubKey = ParseHex("01a36564b96a4756bc6b111a04b94baafeac5d5257fe028e80695c62f7c2f81f85d111a216df3be197653f454852a2d11c6314aad5ca3cbe5616262ca3e7a6feef");
        nDefaultPort = 7445;
        nRPCPort = 7446;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "Bitcoin Exchange BTCC Halts Fiat And Crypto Lending, by: JP Buntinx - January 13, 2017"; // Fri, 13 Jan 2017 03:35:17 GMT
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1484278517, vin, vout, 0); // Fri, 13 Jan 2017 03:35:17 GMT
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1484278517; // Fri, 13 Jan 2017 03:35:17 GMT
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 968015;

        /** Genesis Block MainNet */
        /*
Hashed MainNet Genesis Block Output
block.hashMerkleRoot == fb5c1cb95b2452f7d5b5c6837812349d681e073af9440438a32305ffed14518c
block.nTime = 1484278517
block.nNonce = 968015
block.GetHash = 0000088a184709d7edfa8c6581e18816846347c6ed7b9b4e8782da902dd5e39f
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000088a184709d7edfa8c6581e18816846347c6ed7b9b4e8782da902dd5e39f"));
        assert(genesis.hashMerkleRoot == uint256("0xfb5c1cb95b2452f7d5b5c6837812349d681e073af9440438a32305ffed14518c"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,51);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,55);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("199.26.184.214:7445",  "199.26.184.214"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 300; // Initially ~300 Sec during PoW
        if(nBestHeight > nLastPoWBlock) // Scaled down for PoS only phase
        {
          nTargetSpacing = 300;
        }
        if(nBestHeight > nStartPoSBlock) // Scaled up for PoW/PoS twin phase
        {
          if(nBestHeight <= nLastPoWBlock)
          {
            nTargetSpacing = 900;
          }
        }
        nTargetTimespan = 10 * nTargetSpacing;
        nLastPoWBlock = 140155; // 21023250 total PoW coins mined ~38Mill overall in supply
        nStartPoSBlock = 151;
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
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0x05;
        pchMessageStart[2] = 0x0f;
        pchMessageStart[3] = 0x0e;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);

        vAlertPubKey = ParseHex("01b47584b96e9056bc6b132a04b94baafeac5d5257fe028e80695c62f7c2f81f85d251a216df3af197653f454852a2d08c6314aad5ca3cbe5616262ca3e7a6faac");
        nDefaultPort = 6444;
        nRPCPort = 6445;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 66946;

        /** Genesis Block TestNet */
        /*
Hashed TestNet Genesis Block Output
block.hashMerkleRoot == fb5c1cb95b2452f7d5b5c6837812349d681e073af9440438a32305ffed14518c
block.nTime = 1484278517
block.nNonce = 66946
block.GetHash = 0000f56d61c85db7da924fd870c62e46573266e810b70d137cbe51986b10feaf
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000f56d61c85db7da924fd870c62e46573266e810b70d137cbe51986b10feaf"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,29);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,59);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,27);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 200;
        nLastPoWBlock = 0x7fffffff;
        nStartPoSBlock = 4500;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0x98;
        pchMessageStart[3] = 0xca;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1484279517;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 5444;
        strDataDir = "regtest";

        /** Genesis Block RegNet */
        /*
Hashed RegNet Genesis Block Output
block.hashMerkleRoot == fb5c1cb95b2452f7d5b5c6837812349d681e073af9440438a32305ffed14518c
block.nTime = 1484279517
block.nNonce = 8
block.GetHash = 61186d2bd78c5334656fc0a79c284f1b223c718878256298597251b54e5b80cf
        */

        assert(hashGenesisBlock == uint256("0x61186d2bd78c5334656fc0a79c284f1b223c718878256298597251b54e5b80cf"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

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
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
