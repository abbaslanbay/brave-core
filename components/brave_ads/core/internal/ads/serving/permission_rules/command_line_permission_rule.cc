/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/ads/serving/permission_rules/command_line_permission_rule.h"

#include "brave/components/brave_ads/core/internal/global_state/global_state.h"

namespace brave_ads {

namespace {

bool IsProductionEnvironment() {
  return GlobalState::GetInstance()->Flags().environment_type ==
         mojom::EnvironmentType::kProduction;
}

bool DoesRespectCap() {
  return !(IsProductionEnvironment() &&
           GlobalState::GetInstance()->Flags().did_override_from_command_line);
}

}  // namespace

bool CommandLinePermissionRule::ShouldAllow() {
  if (!DoesRespectCap()) {
    last_message_ = "Command-line arg is not supported";
    return false;
  }

  return true;
}

const std::string& CommandLinePermissionRule::GetLastMessage() const {
  return last_message_;
}

}  // namespace brave_ads
