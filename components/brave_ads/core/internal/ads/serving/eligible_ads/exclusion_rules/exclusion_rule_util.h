/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ADS_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULE_UTIL_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ADS_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULE_UTIL_H_

#include <string>

#include "base/check.h"
#include "brave/components/brave_ads/core/internal/ads/ad_events/ad_event_info.h"
#include "brave/components/brave_ads/core/internal/ads/serving/eligible_ads/exclusion_rules/exclusion_rule_interface.h"
#include "brave/components/brave_ads/core/internal/common/logging_util.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace brave_ads {

class ConfirmationType;
struct CreativeAdInfo;

bool DoesRespectCampaignCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            const ConfirmationType& confirmation_type,
                            base::TimeDelta time_constraint,
                            int cap);
bool DoesRespectCreativeSetCap(const CreativeAdInfo& creative_ad,
                               const AdEventList& ad_events,
                               const ConfirmationType& confirmation_type,
                               base::TimeDelta time_constraint,
                               int cap);
bool DoesRespectCreativeCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            const ConfirmationType& confirmation_type,
                            base::TimeDelta time_constraint,
                            int cap);

template <typename T>
bool ShouldExclude(const T& ad, ExclusionRuleInterface<T>* exclusion_rule) {
  DCHECK(exclusion_rule);

  if (!exclusion_rule->ShouldExclude(ad)) {
    return false;
  }

  const std::string& last_message = exclusion_rule->GetLastMessage();
  if (!last_message.empty()) {
    BLOG(2, last_message);
  }

  return true;
}

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ADS_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULE_UTIL_H_
