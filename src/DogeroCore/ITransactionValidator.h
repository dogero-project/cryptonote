// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "DogeroCore/DogeroBasic.h"

namespace Dogero {

  struct BlockInfo {
    uint32_t height;
    Crypto::Hash id;

    BlockInfo() {
      clear();
    }

    void clear() {
      height = 0;
      id = Dogero::NULL_HASH;
    }

    bool empty() const {
      return id == Dogero::NULL_HASH;
    }
  };

  class ITransactionValidator {
  public:
    virtual ~ITransactionValidator() {}
    
    virtual bool checkTransactionInputs(const Dogero::Transaction& tx, BlockInfo& maxUsedBlock) = 0;
    virtual bool checkTransactionInputs(const Dogero::Transaction& tx, BlockInfo& maxUsedBlock, BlockInfo& lastFailed) = 0;
    virtual bool haveSpentKeyImages(const Dogero::Transaction& tx) = 0;
    virtual bool checkTransactionSize(size_t blobSize) = 0;
  };

}
