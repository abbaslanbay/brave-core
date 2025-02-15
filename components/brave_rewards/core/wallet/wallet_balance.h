/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_WALLET_WALLET_BALANCE_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_WALLET_WALLET_BALANCE_H_

#include <string>
#include <vector>

#include "base/memory/raw_ref.h"
#include "brave/components/brave_rewards/core/ledger_callbacks.h"

namespace ledger {
class LedgerImpl;

namespace wallet {

class WalletBalance {
 public:
  explicit WalletBalance(LedgerImpl& ledger);
  ~WalletBalance();

  void Fetch(ledger::FetchBalanceCallback callback);

 private:
  void OnGetUnblindedTokens(ledger::FetchBalanceCallback callback,
                            std::vector<mojom::UnblindedTokenPtr> tokens);

  void OnFetchExternalWalletBalance(const std::string& wallet_type,
                                    mojom::BalancePtr balance_ptr,
                                    ledger::FetchBalanceCallback callback,
                                    mojom::Result result,
                                    double balance);

  const raw_ref<LedgerImpl> ledger_;
};

}  // namespace wallet
}  // namespace ledger
#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_WALLET_WALLET_BALANCE_H_
