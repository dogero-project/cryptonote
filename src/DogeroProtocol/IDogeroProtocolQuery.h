// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstddef>
#include <cstdint>

namespace Dogero {
class IDogeroProtocolObserver;

class IDogeroProtocolQuery {
public:
  virtual bool addObserver(IDogeroProtocolObserver* observer) = 0;
  virtual bool removeObserver(IDogeroProtocolObserver* observer) = 0;

  virtual uint32_t getObservedHeight() const = 0;
  virtual size_t getPeerCount() const = 0;
  virtual bool isSynchronized() const = 0;
};

} //namespace Dogero
