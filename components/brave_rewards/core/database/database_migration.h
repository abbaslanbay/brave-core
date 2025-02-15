/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_DATABASE_DATABASE_MIGRATION_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_DATABASE_DATABASE_MIGRATION_H_

#include <memory>
#include <string>

#include "base/memory/raw_ref.h"
#include "brave/components/brave_rewards/core/ledger_callbacks.h"

namespace ledger {
class LedgerImpl;

namespace database {

class DatabaseMigration {
 public:
  explicit DatabaseMigration(LedgerImpl& ledger);
  ~DatabaseMigration();

  void Start(uint32_t table_version, ledger::LegacyResultCallback callback);

  static void SetTargetVersionForTesting(uint32_t version);

 private:
  void GenerateCommand(mojom::DBTransaction* transaction,
                       const std::string& query);

  const raw_ref<LedgerImpl> ledger_;
  static uint32_t test_target_version_;
};

}  // namespace database
}  // namespace ledger
#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_DATABASE_DATABASE_MIGRATION_H_
