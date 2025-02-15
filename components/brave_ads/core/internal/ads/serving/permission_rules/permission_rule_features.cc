/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/ads/serving/permission_rules/permission_rule_features.h"

namespace brave_ads {

BASE_FEATURE(kPermissionRulesFeature,
             "PermissionRules",
             base::FEATURE_ENABLED_BY_DEFAULT);

bool IsPermissionRulesEnabled() {
  return base::FeatureList::IsEnabled(kPermissionRulesFeature);
}

}  // namespace brave_ads
