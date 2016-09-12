// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "IDogeroProtocolQueryStub.h"

bool IDogeroProtocolQueryStub::addObserver(Dogero::IDogeroProtocolObserver* observer) {
  return false;
}

bool IDogeroProtocolQueryStub::removeObserver(Dogero::IDogeroProtocolObserver* observer) {
  return false;
}

uint32_t IDogeroProtocolQueryStub::getObservedHeight() const {
  return observedHeight;
}

size_t IDogeroProtocolQueryStub::getPeerCount() const {
  return peers;
}

bool IDogeroProtocolQueryStub::isSynchronized() const {
  return synchronized;
}

void IDogeroProtocolQueryStub::setPeerCount(uint32_t count) {
  peers = count;
}

void IDogeroProtocolQueryStub::setObservedHeight(uint32_t height) {
  observedHeight = height;
}

void IDogeroProtocolQueryStub::setSynchronizedStatus(bool status) {
    synchronized = status;
}
