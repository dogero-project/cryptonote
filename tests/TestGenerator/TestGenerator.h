// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>
#include <list>
#include <vector>
#include <unordered_map>

#include "crypto/hash.h"
#include "DogeroCore/DogeroBasic.h"
#include "DogeroCore/DogeroBasicImpl.h"
#include "DogeroCore/DogeroFormatUtils.h"
#include "DogeroCore/Currency.h"
#include "DogeroCore/Difficulty.h"


class test_generator
{
public:
  struct BlockInfo {
    BlockInfo()
      : previousBlockHash()
      , alreadyGeneratedCoins(0)
      , blockSize(0) {
    }

    BlockInfo(Crypto::Hash aPrevId, uint64_t anAlreadyGeneratedCoins, size_t aBlockSize)
      : previousBlockHash(aPrevId)
      , alreadyGeneratedCoins(anAlreadyGeneratedCoins)
      , blockSize(aBlockSize) {
    }

    Crypto::Hash previousBlockHash;
    uint64_t alreadyGeneratedCoins;
    size_t blockSize;
  };

  enum BlockFields {
    bf_none      = 0,
    bf_major_ver = 1 << 0,
    bf_minor_ver = 1 << 1,
    bf_timestamp = 1 << 2,
    bf_prev_id   = 1 << 3,
    bf_miner_tx  = 1 << 4,
    bf_tx_hashes = 1 << 5,
    bf_diffic    = 1 << 6
  };

  test_generator(const Dogero::Currency& currency, uint8_t majorVersion = Dogero::BLOCK_MAJOR_VERSION_1,
                 uint8_t minorVersion = Dogero::BLOCK_MINOR_VERSION_0)
    : m_currency(currency), defaultMajorVersion(majorVersion), defaultMinorVersion(minorVersion) {
  }


  uint8_t defaultMajorVersion;
  uint8_t defaultMinorVersion;

  const Dogero::Currency& currency() const { return m_currency; }

  void getBlockchain(std::vector<BlockInfo>& blockchain, const Crypto::Hash& head, size_t n) const;
  void getLastNBlockSizes(std::vector<size_t>& blockSizes, const Crypto::Hash& head, size_t n) const;
  uint64_t getAlreadyGeneratedCoins(const Crypto::Hash& blockId) const;
  uint64_t getAlreadyGeneratedCoins(const Dogero::Block& blk) const;

  void addBlock(const Dogero::Block& blk, size_t tsxSize, uint64_t fee, std::vector<size_t>& blockSizes,
    uint64_t alreadyGeneratedCoins);
  bool constructBlock(Dogero::Block& blk, uint32_t height, const Crypto::Hash& previousBlockHash,
    const Dogero::AccountBase& minerAcc, uint64_t timestamp, uint64_t alreadyGeneratedCoins,
    std::vector<size_t>& blockSizes, const std::list<Dogero::Transaction>& txList);
  bool constructBlock(Dogero::Block& blk, const Dogero::AccountBase& minerAcc, uint64_t timestamp);
  bool constructBlock(Dogero::Block& blk, const Dogero::Block& blkPrev, const Dogero::AccountBase& minerAcc,
    const std::list<Dogero::Transaction>& txList = std::list<Dogero::Transaction>());

  bool constructBlockManually(Dogero::Block& blk, const Dogero::Block& prevBlock,
    const Dogero::AccountBase& minerAcc, int actualParams = bf_none, uint8_t majorVer = 0,
    uint8_t minorVer = 0, uint64_t timestamp = 0, const Crypto::Hash& previousBlockHash = Crypto::Hash(),
    const Dogero::difficulty_type& diffic = 1, const Dogero::Transaction& baseTransaction = Dogero::Transaction(),
    const std::vector<Crypto::Hash>& transactionHashes = std::vector<Crypto::Hash>(), size_t txsSizes = 0, uint64_t fee = 0);
  bool constructBlockManuallyTx(Dogero::Block& blk, const Dogero::Block& prevBlock,
    const Dogero::AccountBase& minerAcc, const std::vector<Crypto::Hash>& transactionHashes, size_t txsSize);
  bool constructMaxSizeBlock(Dogero::Block& blk, const Dogero::Block& blkPrev,
    const Dogero::AccountBase& minerAccount, size_t medianBlockCount = 0,
    const std::list<Dogero::Transaction>& txList = std::list<Dogero::Transaction>());

private:
  const Dogero::Currency& m_currency;
  std::unordered_map<Crypto::Hash, BlockInfo> m_blocksInfo;
};

inline Dogero::difficulty_type getTestDifficulty() { return 1; }
void fillNonce(Dogero::Block& blk, const Dogero::difficulty_type& diffic);

bool constructMinerTxManually(const Dogero::Currency& currency, uint32_t height, uint64_t alreadyGeneratedCoins,
  const Dogero::AccountPublicAddress& minerAddress, Dogero::Transaction& tx, uint64_t fee,
  Dogero::KeyPair* pTxKey = 0);
bool constructMinerTxBySize(const Dogero::Currency& currency, Dogero::Transaction& baseTransaction, uint32_t height,
  uint64_t alreadyGeneratedCoins, const Dogero::AccountPublicAddress& minerAddress,
  std::vector<size_t>& blockSizes, size_t targetTxSize, size_t targetBlockSize, uint64_t fee = 0);
