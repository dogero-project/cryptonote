// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>
#include <unordered_map>

#include "DogeroCore/Account.h"
#include "DogeroCore/DogeroBasic.h"
#include "DogeroCore/Currency.h"
#include "DogeroCore/BlockchainIndices.h"
#include "crypto/hash.h"

#include "../TestGenerator/TestGenerator.h"

class TestBlockchainGenerator
{
public:
  TestBlockchainGenerator(const Dogero::Currency& currency);

  //TODO: get rid of this method
  std::vector<Dogero::Block>& getBlockchain();
  std::vector<Dogero::Block> getBlockchainCopy();
  void generateEmptyBlocks(size_t count);
  bool getBlockRewardForAddress(const Dogero::AccountPublicAddress& address);
  bool generateTransactionsInOneBlock(const Dogero::AccountPublicAddress& address, size_t n);
  bool getSingleOutputTransaction(const Dogero::AccountPublicAddress& address, uint64_t amount);
  void addTxToBlockchain(const Dogero::Transaction& transaction);
  bool getTransactionByHash(const Crypto::Hash& hash, Dogero::Transaction& tx, bool checkTxPool = false);
  const Dogero::AccountBase& getMinerAccount() const;
  bool generateFromBaseTx(const Dogero::AccountBase& address);

  void putTxToPool(const Dogero::Transaction& tx);
  void getPoolSymmetricDifference(std::vector<Crypto::Hash>&& known_pool_tx_ids, Crypto::Hash known_block_id, bool& is_bc_actual,
    std::vector<Dogero::Transaction>& new_txs, std::vector<Crypto::Hash>& deleted_tx_ids);
  void putTxPoolToBlockchain();
  void clearTxPool();

  void cutBlockchain(uint32_t height);

  bool addOrphan(const Crypto::Hash& hash, uint32_t height);
  bool getGeneratedTransactionsNumber(uint32_t height, uint64_t& generatedTransactions);
  bool getOrphanBlockIdsByHeight(uint32_t height, std::vector<Crypto::Hash>& blockHashes);
  bool getBlockIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t blocksNumberLimit, std::vector<Crypto::Hash>& hashes, uint32_t& blocksNumberWithinTimestamps);
  bool getPoolTransactionIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t transactionsNumberLimit, std::vector<Crypto::Hash>& hashes, uint64_t& transactionsNumberWithinTimestamps);
  bool getTransactionIdsByPaymentId(const Crypto::Hash& paymentId, std::vector<Crypto::Hash>& transactionHashes);

  bool getTransactionGlobalIndexesByHash(const Crypto::Hash& transactionHash, std::vector<uint32_t>& globalIndexes);
  bool getMultisignatureOutputByGlobalIndex(uint64_t amount, uint32_t globalIndex, Dogero::MultisignatureOutput& out);
  void setMinerAccount(const Dogero::AccountBase& account);

private:
  struct MultisignatureOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };

  struct KeyOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };
  
  void addGenesisBlock();
  void addMiningBlock();

  const Dogero::Currency& m_currency;
  test_generator generator;
  Dogero::AccountBase miner_acc;
  std::vector<Dogero::Block> m_blockchain;
  std::unordered_map<Crypto::Hash, Dogero::Transaction> m_txs;
  std::unordered_map<Crypto::Hash, std::vector<uint32_t>> transactionGlobalOuts;
  std::unordered_map<uint64_t, std::vector<MultisignatureOutEntry>> multisignatureOutsIndex;
  std::unordered_map<uint64_t, std::vector<KeyOutEntry>> keyOutsIndex;

  std::unordered_map<Crypto::Hash, Dogero::Transaction> m_txPool;
  mutable std::mutex m_mutex;

  Dogero::PaymentIdIndex m_paymentIdIndex;
  Dogero::TimestampTransactionsIndex m_timestampIndex;
  Dogero::GeneratedTransactionsIndex m_generatedTransactionsIndex;
  Dogero::OrphanBlocksIndex m_orthanBlocksIndex;

  void addToBlockchain(const Dogero::Transaction& tx);
  void addToBlockchain(const std::vector<Dogero::Transaction>& txs);
  void addToBlockchain(const std::vector<Dogero::Transaction>& txs, const Dogero::AccountBase& minerAddress);
  void addTx(const Dogero::Transaction& tx);

  bool doGenerateTransactionsInOneBlock(Dogero::AccountPublicAddress const &address, size_t n);
};
