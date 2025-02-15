/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <limits>

#include "brave/components/brave_rewards/core/legacy/publisher_settings_properties.h"
#include "brave/components/brave_rewards/core/legacy/report_balance_properties.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --filter=PublisherSettingsStateTest.*

namespace ledger {

TEST(PublisherSettingsStateTest, ToJsonSerialization) {
  // Arrange
  PublisherSettingsProperties publisher_settings_properties;
  publisher_settings_properties.min_page_time_before_logging_a_visit =
      std::numeric_limits<uint32_t>::max();
  publisher_settings_properties.min_visits_for_publisher_relevancy =
      std::numeric_limits<uint32_t>::max();
  publisher_settings_properties.allow_non_verified_sites_in_list = true;

  ReportBalanceProperties report_balance_properties;
  report_balance_properties.grants = 1;
  report_balance_properties.ad_earnings = 1;
  report_balance_properties.auto_contributions = 1;
  report_balance_properties.recurring_donations = 1;
  report_balance_properties.one_time_donations = 1;
  publisher_settings_properties.monthly_balances.insert(
      {{"Date", report_balance_properties}});

  publisher_settings_properties.processed_pending_publishers.push_back(
      "ProcessedPendingPublisher");

  // Assert
  PublisherSettingsProperties expected_publisher_settings_properties;
  expected_publisher_settings_properties.FromJson(
      publisher_settings_properties.ToJson());
  EXPECT_EQ(expected_publisher_settings_properties,
            publisher_settings_properties);
}

TEST(PublisherSettingsStateTest, FromJsonDeserialization) {
  // Arrange
  PublisherSettingsProperties publisher_settings_properties;
  publisher_settings_properties.min_page_time_before_logging_a_visit =
      std::numeric_limits<uint32_t>::max();
  publisher_settings_properties.min_visits_for_publisher_relevancy =
      std::numeric_limits<uint32_t>::max();
  publisher_settings_properties.allow_non_verified_sites_in_list = true;

  ReportBalanceProperties report_balance_properties;
  report_balance_properties.grants = 1;
  report_balance_properties.ad_earnings = 1;
  report_balance_properties.auto_contributions = 1;
  report_balance_properties.recurring_donations = 1;
  report_balance_properties.one_time_donations = 1;
  publisher_settings_properties.monthly_balances.insert(
      {{"Date", report_balance_properties}});

  publisher_settings_properties.processed_pending_publishers.push_back(
      "ProcessedPendingPublisher");

  const std::string json =
      "{\"min_pubslisher_duration\":4294967295,\"min_visits\":4294967295,"
      "\"allow_non_verified\":true,\"monthly_balances\":["
      "{\"Date\":{\"grants\":1,\"earning_from_ads\":1,\"auto_contribute\":1,"
      "\"recurring_donation\":1,\"one_time_donation\":1}}],\"processed_pending_"
      "publishers\":[\"ProcessedPendingPublisher\"]}";  // NOLINT

  // Act
  PublisherSettingsProperties expected_publisher_settings_properties;
  expected_publisher_settings_properties.FromJson(json);

  // Assert
  EXPECT_EQ(expected_publisher_settings_properties,
            publisher_settings_properties);
}

}  // namespace ledger
