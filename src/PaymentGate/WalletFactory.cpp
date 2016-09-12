// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletFactory.h"

#include "NodeRpcProxy/NodeRpcProxy.h"
#include "Wallet/WalletGreen.h"
#include "DogeroCore/Currency.h"

#include <stdlib.h>
#include <future>

namespace PaymentService {

WalletFactory WalletFactory::factory;

WalletFactory::WalletFactory() {
}

WalletFactory::~WalletFactory() {
}

Dogero::IWallet* WalletFactory::createWallet(const Dogero::Currency& currency, Dogero::INode& node, System::Dispatcher& dispatcher) {
  Dogero::IWallet* wallet = new Dogero::WalletGreen(dispatcher, currency, node);
  return wallet;
}

}
