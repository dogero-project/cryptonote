// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "DogeroCore/DogeroBasic.h"
#include "DogeroCore/DogeroFormatUtils.h"

#include "SingleTransactionTestBase.h"

class test_is_out_to_acc : public single_tx_test_base
{
public:
  static const size_t loop_count = 1000;

  bool test()
  {
    const Dogero::KeyOutput& tx_out = boost::get<Dogero::KeyOutput>(m_tx.outputs[0].target);
    return Dogero::is_out_to_acc(m_bob.getAccountKeys(), tx_out, m_tx_pub_key, 0);
  }
};
