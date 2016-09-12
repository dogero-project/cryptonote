// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "DogeroCore/Currency.h"
#include "INode.h"
#include "IWalletLegacy.h"
#include "System/Dispatcher.h"
#include "System/Event.h"
#include "WalletLegacy/WalletLegacy.h"

namespace Tests {
namespace Common {

class TestWalletLegacy : private Dogero::IWalletLegacyObserver {
public:
  TestWalletLegacy(System::Dispatcher& dispatcher, const Dogero::Currency& currency, Dogero::INode& node);
  ~TestWalletLegacy();

  std::error_code init();
  std::error_code sendTransaction(const std::string& address, uint64_t amount, Crypto::Hash& txHash);
  void waitForSynchronizationToHeight(uint32_t height);
  Dogero::IWalletLegacy* wallet();
  Dogero::AccountPublicAddress address() const;

protected:
  virtual void synchronizationCompleted(std::error_code result) override;
  virtual void synchronizationProgressUpdated(uint32_t current, uint32_t total) override;

private:
  System::Dispatcher& m_dispatcher;
  System::Event m_synchronizationCompleted;
  System::Event m_someTransactionUpdated;

  Dogero::INode& m_node;
  const Dogero::Currency& m_currency;
  std::unique_ptr<Dogero::IWalletLegacy> m_wallet;
  std::unique_ptr<Dogero::IWalletLegacyObserver> m_walletObserver;
  uint32_t m_currentHeight;
  uint32_t m_synchronizedHeight;
  std::error_code m_lastSynchronizationResult;
};

}
}
