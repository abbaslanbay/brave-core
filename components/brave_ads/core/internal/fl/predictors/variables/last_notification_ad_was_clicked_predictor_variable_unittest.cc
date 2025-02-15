/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/fl/predictors/variables/last_notification_ad_was_clicked_predictor_variable.h"

#include <memory>

#include "brave/components/brave_ads/core/history_item_info.h"
#include "brave/components/brave_ads/core/internal/common/unittest/unittest_base.h"
#include "brave/components/brave_ads/core/internal/creatives/notification_ads/creative_notification_ad_unittest_util.h"
#include "brave/components/brave_ads/core/internal/creatives/notification_ads/notification_ad_builder.h"
#include "brave/components/brave_ads/core/internal/history/history_manager.h"
#include "brave/components/brave_ads/core/notification_ad_info.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace brave_ads {

class BatAdsLastNotificationAdWasClickedPredictorVariableTest
    : public UnitTestBase {};

TEST_F(BatAdsLastNotificationAdWasClickedPredictorVariableTest, GetDataType) {
  std::unique_ptr<PredictorVariableInterface> predictor_variable =
      std::make_unique<LastNotificationAdWasClickedPredictorVariable>();

  // Act

  // Assert
  EXPECT_EQ(brave_federated::mojom::DataType::kBool,
            predictor_variable->GetDataType());
}

TEST_F(BatAdsLastNotificationAdWasClickedPredictorVariableTest,
       GetValueForNoHistory) {
  // Arrange
  std::unique_ptr<PredictorVariableInterface> predictor_variable =
      std::make_unique<LastNotificationAdWasClickedPredictorVariable>();

  // Act

  // Assert
  EXPECT_EQ("-1", predictor_variable->GetValue());
}

TEST_F(BatAdsLastNotificationAdWasClickedPredictorVariableTest,
       GetValueAfterExceedingTimeWindow) {
  // Arrange
  std::unique_ptr<PredictorVariableInterface> predictor_variable =
      std::make_unique<LastNotificationAdWasClickedPredictorVariable>();

  const CreativeNotificationAdInfo creative_ad =
      BuildCreativeNotificationAd(/*should_use_random_guids*/ true);
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);

  HistoryManager::GetInstance()->Add(ad, ConfirmationType::kViewed);
  HistoryManager::GetInstance()->Add(ad, ConfirmationType::kClicked);

  AdvanceClockBy(base::Days(31));

  // Act

  // Assert
  EXPECT_EQ("-1", predictor_variable->GetValue());
}

TEST_F(BatAdsLastNotificationAdWasClickedPredictorVariableTest,
       GetValueWhenLastClicked) {
  // Arrange
  std::unique_ptr<PredictorVariableInterface> predictor_variable =
      std::make_unique<LastNotificationAdWasClickedPredictorVariable>();

  const CreativeNotificationAdInfo creative_ad =
      BuildCreativeNotificationAd(/*should_use_random_guids*/ true);
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);

  HistoryManager::GetInstance()->Add(ad, ConfirmationType::kViewed);
  HistoryManager::GetInstance()->Add(ad, ConfirmationType::kClicked);

  // Act

  // Assert
  EXPECT_EQ("1", predictor_variable->GetValue());
}

TEST_F(BatAdsLastNotificationAdWasClickedPredictorVariableTest,
       GetValueWhenLastViewed) {
  // Arrange
  std::unique_ptr<PredictorVariableInterface> predictor_variable =
      std::make_unique<LastNotificationAdWasClickedPredictorVariable>();

  const CreativeNotificationAdInfo creative_ad =
      BuildCreativeNotificationAd(/*should_use_random_guids*/ true);
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);

  HistoryManager::GetInstance()->Add(ad, ConfirmationType::kClicked);
  HistoryManager::GetInstance()->Add(ad, ConfirmationType::kViewed);

  // Act

  // Assert
  EXPECT_EQ("0", predictor_variable->GetValue());
}

}  // namespace brave_ads
