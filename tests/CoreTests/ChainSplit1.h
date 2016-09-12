// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once 
#include "Chaingen.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
class gen_simple_chain_split_1 : public test_chain_unit_base 
{
public: 
  gen_simple_chain_split_1();
  bool generate(std::vector<test_event_entry> &events) const; 
  bool check_split_not_switched(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_split_not_switched2(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_split_switched(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_split_not_switched_back(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_split_switched_back_1(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_split_switched_back_2(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_mempool_1(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_mempool_2(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  /*bool check_orphaned_chain_1(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_orphaned_switched_to_alternative(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_orphaned_chain_2(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_orphaned_switched_to_main(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_orphaned_chain_38(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_orphaned_chain_39(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_orphaned_chain_40(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events);
  bool check_orphaned_chain_41(Dogero::core& c, size_t ev_index, const std::vector<test_event_entry> &events); */
private:
};
