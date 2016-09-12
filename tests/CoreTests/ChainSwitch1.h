// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once 
#include "Chaingen.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
class gen_chain_switch_1 : public test_chain_unit_base
{
public: 
  gen_chain_switch_1();

  bool generate(std::vector<test_event_entry>& events) const;

  bool check_split_not_switched(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry>& events);
  bool check_split_switched(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry>& events);

private:
  std::list<Dogero::Block> m_chain_1;

  Dogero::AccountBase m_recipient_account_1;
  Dogero::AccountBase m_recipient_account_2;
  Dogero::AccountBase m_recipient_account_3;
  Dogero::AccountBase m_recipient_account_4;

  std::vector<Dogero::Transaction> m_tx_pool;
};
