// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "DogeroCore/Account.h"
#include "DogeroCore/DogeroFormatUtils.h"
#include "DogeroCore/Currency.h"

class TransactionBuilder {
public:

  typedef std::vector<Dogero::AccountKeys> KeysVector;
  typedef std::vector<Crypto::Signature> SignatureVector;
  typedef std::vector<SignatureVector> SignatureMultivector;

  struct MultisignatureSource {
    Dogero::MultisignatureInput input;
    KeysVector keys;
    Crypto::PublicKey srcTxPubKey;
    size_t srcOutputIndex;
  };

  TransactionBuilder(const Dogero::Currency& currency, uint64_t unlockTime = 0);

  // regenerate transaction keys
  TransactionBuilder& newTxKeys();
  TransactionBuilder& setTxKeys(const Dogero::KeyPair& txKeys);

  // inputs
  TransactionBuilder& setInput(const std::vector<Dogero::TransactionSourceEntry>& sources, const Dogero::AccountKeys& senderKeys);
  TransactionBuilder& addMultisignatureInput(const MultisignatureSource& source);

  // outputs
  TransactionBuilder& setOutput(const std::vector<Dogero::TransactionDestinationEntry>& destinations);
  TransactionBuilder& addOutput(const Dogero::TransactionDestinationEntry& dest);
  TransactionBuilder& addMultisignatureOut(uint64_t amount, const KeysVector& keys, uint32_t required);

  Dogero::Transaction build() const;

  std::vector<Dogero::TransactionSourceEntry> m_sources;
  std::vector<Dogero::TransactionDestinationEntry> m_destinations;

private:

  void fillInputs(Dogero::Transaction& tx, std::vector<Dogero::KeyPair>& contexts) const;
  void fillOutputs(Dogero::Transaction& tx) const;
  void signSources(const Crypto::Hash& prefixHash, const std::vector<Dogero::KeyPair>& contexts, Dogero::Transaction& tx) const;

  struct MultisignatureDestination {
    uint64_t amount;
    uint32_t requiredSignatures;
    KeysVector keys;
  };

  Dogero::AccountKeys m_senderKeys;

  std::vector<MultisignatureSource> m_msigSources;
  std::vector<MultisignatureDestination> m_msigDestinations;

  size_t m_version;
  uint64_t m_unlockTime;
  Dogero::KeyPair m_txKey;
  const Dogero::Currency& m_currency;
};
