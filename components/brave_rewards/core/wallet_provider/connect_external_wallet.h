/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_WALLET_PROVIDER_CONNECT_EXTERNAL_WALLET_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_WALLET_PROVIDER_CONNECT_EXTERNAL_WALLET_H_

#include <string>

#include "base/containers/flat_map.h"
#include "base/memory/raw_ref.h"
#include "base/types/expected.h"
#include "brave/components/brave_rewards/core/endpoints/post_connect/post_connect.h"
#include "brave/components/brave_rewards/core/ledger_callbacks.h"

namespace ledger {
class LedgerImpl;

namespace wallet_provider {

class ConnectExternalWallet {
 public:
  explicit ConnectExternalWallet(LedgerImpl& ledger);

  virtual ~ConnectExternalWallet();

  void Run(const base::flat_map<std::string, std::string>& query_parameters,
           ledger::ConnectExternalWalletCallback) const;

 protected:
  virtual const char* WalletType() const = 0;

  struct OAuthInfo {
    std::string one_time_string, code_verifier, code;
  };

  virtual void Authorize(OAuthInfo&&,
                         ledger::ConnectExternalWalletCallback) const = 0;

  void OnConnect(ledger::ConnectExternalWalletCallback,
                 std::string&& token,
                 std::string&& address,
                 endpoints::PostConnect::Result&&) const;

  const raw_ref<LedgerImpl> ledger_;

 private:
  absl::optional<OAuthInfo> ExchangeOAuthInfo(
      ledger::mojom::ExternalWalletPtr) const;

  base::expected<std::string, ledger::mojom::ConnectExternalWalletError>
  GetCode(const base::flat_map<std::string, std::string>& query_parameters,
          const std::string& current_one_time_string) const;
};

}  // namespace wallet_provider
}  // namespace ledger

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_WALLET_PROVIDER_CONNECT_EXTERNAL_WALLET_H_
