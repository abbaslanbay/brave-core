/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/ads/serving/eligible_ads/exclusion_rules/marked_to_no_longer_receive_exclusion_rule.h"

#include "brave/components/brave_ads/core/internal/ads/ad_unittest_constants.h"
#include "brave/components/brave_ads/core/internal/common/unittest/unittest_base.h"
#include "brave/components/brave_ads/core/internal/deprecated/client/client_state_manager.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace brave_ads {

class BatAdsMarkedToNoLongerReceiveExclusionRuleTest : public UnitTestBase {
 protected:
  MarkedToNoLongerReceiveExclusionRule exclusion_rule_;
};

TEST_F(BatAdsMarkedToNoLongerReceiveExclusionRuleTest, AllowAd) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.segment = kSegment;

  // Act

  // Assert
  EXPECT_FALSE(exclusion_rule_.ShouldExclude(creative_ad));
}

TEST_F(BatAdsMarkedToNoLongerReceiveExclusionRuleTest, DoNotAllowAd) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.segment = kSegment;

  ClientStateManager::GetInstance()->ToggleMarkToNoLongerReceiveAdsForCategory(
      creative_ad.segment, CategoryContentOptActionType::kNone);

  // Act

  // Assert
  EXPECT_TRUE(exclusion_rule_.ShouldExclude(creative_ad));
}

}  // namespace brave_ads
