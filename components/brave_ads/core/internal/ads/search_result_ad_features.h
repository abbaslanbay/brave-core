/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ADS_SEARCH_RESULT_AD_FEATURES_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ADS_SEARCH_RESULT_AD_FEATURES_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace brave_ads::search_result_ads {

BASE_DECLARE_FEATURE(kAdsFeature);

bool IsEnabled();

constexpr base::FeatureParam<int> kMaximumAdsPerHour{
    &kAdsFeature, "maximum_ads_per_hour", 10};

constexpr base::FeatureParam<int> kMaximumAdsPerDay{&kAdsFeature,
                                                    "maximum_ads_per_day", 40};

}  // namespace brave_ads::search_result_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ADS_SEARCH_RESULT_AD_FEATURES_H_
