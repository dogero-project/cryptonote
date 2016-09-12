// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "TestNode.h"
#include "NetworkConfiguration.h"

#include <future>
#include <memory>
#include <thread>

#include <System/Dispatcher.h>


namespace Dogero {
class core;
class DogeroProtocolHandler;
class NodeServer;
class Currency;
}

namespace Tests {

class InProcTestNode : public TestNode {
public:
  InProcTestNode(const TestNodeConfiguration& cfg, const Dogero::Currency& currency);
  ~InProcTestNode();

  virtual bool startMining(size_t threadsCount, const std::string &address) override;
  virtual bool stopMining() override;
  virtual bool stopDaemon() override;
  virtual bool getBlockTemplate(const std::string &minerAddress, Dogero::Block &blockTemplate, uint64_t &difficulty) override;
  virtual bool submitBlock(const std::string& block) override;
  virtual bool getTailBlockId(Crypto::Hash &tailBlockId) override;
  virtual bool makeINode(std::unique_ptr<Dogero::INode>& node) override;
  virtual uint64_t getLocalHeight() override;

private:

  void workerThread(std::promise<std::string>& initPromise);

  std::unique_ptr<Dogero::core> core;
  std::unique_ptr<Dogero::DogeroProtocolHandler> protocol;
  std::unique_ptr<Dogero::NodeServer> p2pNode;

  std::thread m_thread;
  const Dogero::Currency& m_currency;
  TestNodeConfiguration m_cfg;
};

}
