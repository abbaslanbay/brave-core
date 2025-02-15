/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_SKU_SKU_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_SKU_SKU_H_

#include <memory>
#include <string>
#include <vector>

#include "base/memory/raw_ref.h"
#include "brave/components/brave_rewards/core/ledger_callbacks.h"
#include "brave/components/brave_rewards/core/sku/sku_common.h"

namespace ledger {
class LedgerImpl;

namespace sku {

class SKU {
 public:
  explicit SKU(LedgerImpl& ledger);
  ~SKU();

  void Process(const std::vector<mojom::SKUOrderItem>& items,
               const std::string& wallet_type,
               ledger::SKUOrderCallback callback,
               const std::string& contribution_id = "");

  void Retry(const std::string& order_id,
             const std::string& wallet_type,
             ledger::SKUOrderCallback callback);

 private:
  void OrderCreated(const mojom::Result result,
                    const std::string& order_id,
                    const std::string& wallet_type,
                    const std::string& contribution_id,
                    ledger::SKUOrderCallback callback);

  void ContributionIdSaved(const mojom::Result result,
                           const std::string& order_id,
                           const std::string& wallet_type,
                           ledger::SKUOrderCallback callback);

  void CreateTransaction(mojom::SKUOrderPtr order,
                         const std::string& wallet_type,
                         ledger::SKUOrderCallback callback);

  void OnOrder(mojom::SKUOrderPtr order,
               const std::string& wallet_type,
               ledger::SKUOrderCallback callback);

  const raw_ref<LedgerImpl> ledger_;
  std::unique_ptr<SKUCommon> common_;
};

}  // namespace sku
}  // namespace ledger

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_SKU_SKU_H_
