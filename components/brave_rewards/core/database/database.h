/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_DATABASE_DATABASE_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_DATABASE_DATABASE_H_

#include <stdint.h>

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "base/functional/callback_forward.h"
#include "base/memory/raw_ref.h"
#include "base/time/time.h"
#include "brave/components/brave_rewards/core/database/database_activity_info.h"
#include "brave/components/brave_rewards/core/database/database_balance_report.h"
#include "brave/components/brave_rewards/core/database/database_contribution_info.h"
#include "brave/components/brave_rewards/core/database/database_contribution_queue.h"
#include "brave/components/brave_rewards/core/database/database_creds_batch.h"
#include "brave/components/brave_rewards/core/database/database_event_log.h"
#include "brave/components/brave_rewards/core/database/database_external_transactions.h"
#include "brave/components/brave_rewards/core/database/database_initialize.h"
#include "brave/components/brave_rewards/core/database/database_media_publisher_info.h"
#include "brave/components/brave_rewards/core/database/database_multi_tables.h"
#include "brave/components/brave_rewards/core/database/database_promotion.h"
#include "brave/components/brave_rewards/core/database/database_publisher_info.h"
#include "brave/components/brave_rewards/core/database/database_publisher_prefix_list.h"
#include "brave/components/brave_rewards/core/database/database_recurring_tip.h"
#include "brave/components/brave_rewards/core/database/database_server_publisher_info.h"
#include "brave/components/brave_rewards/core/database/database_sku_order.h"
#include "brave/components/brave_rewards/core/database/database_sku_transaction.h"
#include "brave/components/brave_rewards/core/database/database_unblinded_token.h"
#include "brave/components/brave_rewards/core/ledger_callbacks.h"
#include "brave/components/brave_rewards/core/publisher/prefix_list_reader.h"

namespace ledger {
class LedgerImpl;

namespace database {

class Database {
 public:
  explicit Database(LedgerImpl& ledger);
  virtual ~Database();

  void Initialize(ledger::LegacyResultCallback callback);

  void Close(ledger::LegacyResultCallback callback);

  /**
   * ACTIVITY INFO
   */
  void SaveActivityInfo(mojom::PublisherInfoPtr info,
                        ledger::LegacyResultCallback callback);

  void NormalizeActivityInfoList(std::vector<mojom::PublisherInfoPtr> list,
                                 ledger::LegacyResultCallback callback);

  void GetActivityInfoList(uint32_t start,
                           uint32_t limit,
                           mojom::ActivityInfoFilterPtr filter,
                           ledger::GetActivityInfoListCallback callback);

  void DeleteActivityInfo(const std::string& publisher_key,
                          ledger::LegacyResultCallback callback);

  void GetPublishersVisitedCount(base::OnceCallback<void(int)> callback);

  /**
   * BALANCE REPORT
   */
  void SaveBalanceReportInfo(mojom::BalanceReportInfoPtr info,
                             ledger::LegacyResultCallback callback);

  void SaveBalanceReportInfoList(std::vector<mojom::BalanceReportInfoPtr> list,
                                 ledger::LegacyResultCallback callback);

  void SaveBalanceReportInfoItem(mojom::ActivityMonth month,
                                 int year,
                                 mojom::ReportType type,
                                 double amount,
                                 ledger::LegacyResultCallback callback);

  void GetBalanceReportInfo(mojom::ActivityMonth month,
                            int year,
                            ledger::GetBalanceReportCallback callback);

  void GetAllBalanceReports(ledger::GetBalanceReportListCallback callback);

  void DeleteAllBalanceReports(ledger::LegacyResultCallback callback);

  /**
   * CONTRIBUTION INFO
   */
  void SaveContributionInfo(mojom::ContributionInfoPtr info,
                            ledger::LegacyResultCallback callback);

  virtual void GetContributionInfo(const std::string& contribution_id,
                                   GetContributionInfoCallback callback);

  void GetOneTimeTips(const mojom::ActivityMonth month,
                      const int year,
                      ledger::GetOneTimeTipsCallback callback);

  void GetContributionReport(const mojom::ActivityMonth month,
                             const int year,
                             ledger::GetContributionReportCallback callback);

  void GetNotCompletedContributions(
      ledger::ContributionInfoListCallback callback);

  void UpdateContributionInfoStep(const std::string& contribution_id,
                                  mojom::ContributionStep step,
                                  ledger::LegacyResultCallback callback);

  void UpdateContributionInfoStepAndCount(
      const std::string& contribution_id,
      mojom::ContributionStep step,
      int32_t retry_count,
      ledger::LegacyResultCallback callback);

  void UpdateContributionInfoContributedAmount(
      const std::string& contribution_id,
      const std::string& publisher_key,
      ledger::LegacyResultCallback callback);

  void GetAllContributions(ledger::ContributionInfoListCallback callback);

  void FinishAllInProgressContributions(ledger::LegacyResultCallback callback);

  /**
   * CONTRIBUTION QUEUE
   */
  void SaveContributionQueue(mojom::ContributionQueuePtr info,
                             ledger::LegacyResultCallback callback);

  void GetFirstContributionQueue(GetFirstContributionQueueCallback callback);

  void MarkContributionQueueAsComplete(const std::string& id,
                                       ledger::LegacyResultCallback callback);

  /**
   * CREDS BATCH
   */
  void SaveCredsBatch(mojom::CredsBatchPtr info,
                      ledger::LegacyResultCallback callback);

  void GetCredsBatchByTrigger(const std::string& trigger_id,
                              const mojom::CredsBatchType trigger_type,
                              GetCredsBatchCallback callback);

  void SaveSignedCreds(mojom::CredsBatchPtr info,
                       ledger::LegacyResultCallback callback);

  void GetAllCredsBatches(GetCredsBatchListCallback callback);

  void UpdateCredsBatchStatus(const std::string& trigger_id,
                              mojom::CredsBatchType trigger_type,
                              mojom::CredsBatchStatus status,
                              ledger::LegacyResultCallback callback);

  void UpdateCredsBatchesStatus(const std::vector<std::string>& trigger_ids,
                                mojom::CredsBatchType trigger_type,
                                mojom::CredsBatchStatus status,
                                ledger::LegacyResultCallback callback);

  void GetCredsBatchesByTriggers(const std::vector<std::string>& trigger_ids,
                                 GetCredsBatchListCallback callback);

  /**
   * EVENT LOG
   */
  void SaveEventLog(const std::string& key, const std::string& value);

  void SaveEventLogs(const std::map<std::string, std::string>& records,
                     ledger::LegacyResultCallback callback);

  void GetLastEventLogs(ledger::GetEventLogsCallback callback);

  /**
   * EXTERNAL TRANSACTIONS
   */
  void SaveExternalTransaction(mojom::ExternalTransactionPtr,
                               ledger::ResultCallback);

  void GetExternalTransaction(const std::string& contribution_id,
                              const std::string& destination,
                              GetExternalTransactionCallback);

  /**
   * MEDIA PUBLISHER INFO
   */
  void SaveMediaPublisherInfo(const std::string& media_key,
                              const std::string& publisher_key,
                              ledger::LegacyResultCallback callback);

  void GetMediaPublisherInfo(const std::string& media_key,
                             ledger::PublisherInfoCallback callback);

  /**
   * MULTI TABLE
   * for queries that are not limited to one table
   */
  void GetTransactionReport(const mojom::ActivityMonth month,
                            const int year,
                            ledger::GetTransactionReportCallback callback);

  /**
   * PROMOTION
   */
  virtual void SavePromotion(mojom::PromotionPtr info,
                             ledger::LegacyResultCallback callback);

  void GetPromotion(const std::string& id, GetPromotionCallback callback);

  virtual void GetAllPromotions(ledger::GetAllPromotionsCallback callback);

  void SavePromotionClaimId(const std::string& promotion_id,
                            const std::string& claim_id,
                            ledger::LegacyResultCallback callback);

  void UpdatePromotionStatus(const std::string& promotion_id,
                             mojom::PromotionStatus status,
                             ledger::LegacyResultCallback callback);

  void UpdatePromotionsStatus(const std::vector<std::string>& promotion_ids,
                              mojom::PromotionStatus status,
                              ledger::LegacyResultCallback callback);

  void PromotionCredentialCompleted(const std::string& promotion_id,
                                    ledger::LegacyResultCallback callback);

  void GetPromotionList(const std::vector<std::string>& ids,
                        GetPromotionListCallback callback);

  void UpdatePromotionsBlankPublicKey(const std::vector<std::string>& ids,
                                      ledger::LegacyResultCallback callback);

  /**
   * PUBLISHER INFO
   */
  void SavePublisherInfo(mojom::PublisherInfoPtr publisher_info,
                         ledger::LegacyResultCallback callback);

  void GetPublisherInfo(const std::string& publisher_key,
                        ledger::GetPublisherInfoCallback callback);

  void GetPanelPublisherInfo(mojom::ActivityInfoFilterPtr filter,
                             ledger::GetPublisherPanelInfoCallback callback);

  void RestorePublishers(ledger::ResultCallback callback);

  void GetExcludedList(ledger::GetExcludedListCallback callback);

  /**
   * RECURRING TIPS
   */

  // DEPRECATED
  void SaveRecurringTip(mojom::RecurringTipPtr info,
                        ledger::LegacyResultCallback callback);

  void SetMonthlyContribution(const std::string& publisher_id,
                              double amount,
                              base::OnceCallback<void(bool)> callback);

  void AdvanceMonthlyContributionDates(
      const std::vector<std::string>& publisher_ids,
      base::OnceCallback<void(bool)> callback);

  void GetNextMonthlyContributionTime(
      base::OnceCallback<void(absl::optional<base::Time>)> callback);

  void GetRecurringTips(ledger::GetRecurringTipsCallback callback);

  void RemoveRecurringTip(const std::string& publisher_key,
                          ledger::LegacyResultCallback callback);

  /**
   * SERVER PUBLISHER INFO
   */
  void SearchPublisherPrefixList(const std::string& publisher_key,
                                 SearchPublisherPrefixListCallback callback);

  void ResetPublisherPrefixList(
      std::unique_ptr<publisher::PrefixListReader> reader,
      ledger::LegacyResultCallback callback);

  void InsertServerPublisherInfo(const mojom::ServerPublisherInfo& server_info,
                                 ledger::LegacyResultCallback callback);

  void DeleteExpiredServerPublisherInfo(int64_t max_age_seconds,
                                        ledger::LegacyResultCallback callback);

  void GetServerPublisherInfo(const std::string& publisher_key,
                              GetServerPublisherInfoCallback callback);

  /**
   * SKU ORDER
   */
  void SaveSKUOrder(mojom::SKUOrderPtr order,
                    ledger::LegacyResultCallback callback);

  void UpdateSKUOrderStatus(const std::string& order_id,
                            mojom::SKUOrderStatus status,
                            ledger::LegacyResultCallback callback);

  void GetSKUOrder(const std::string& order_id, GetSKUOrderCallback callback);

  void GetSKUOrderByContributionId(const std::string& contribution_id,
                                   GetSKUOrderCallback callback);

  void SaveContributionIdForSKUOrder(const std::string& order_id,
                                     const std::string& contribution_id,
                                     ledger::LegacyResultCallback callback);

  /**
   * SKU TRANSACTION
   */
  void SaveSKUTransaction(mojom::SKUTransactionPtr transaction,
                          ledger::LegacyResultCallback callback);

  void SaveSKUExternalTransaction(const std::string& transaction_id,
                                  const std::string& external_transaction_id,
                                  ledger::LegacyResultCallback callback);

  void GetSKUTransactionByOrderId(const std::string& order_id,
                                  GetSKUTransactionCallback callback);

  /**
   * UNBLINDED TOKEN
   */
  void SaveUnblindedTokenList(std::vector<mojom::UnblindedTokenPtr> list,
                              ledger::LegacyResultCallback callback);

  void MarkUnblindedTokensAsSpent(const std::vector<std::string>& ids,
                                  mojom::RewardsType redeem_type,
                                  const std::string& redeem_id,
                                  ledger::LegacyResultCallback callback);

  void MarkUnblindedTokensAsReserved(const std::vector<std::string>& ids,
                                     const std::string& redeem_id,
                                     ledger::LegacyResultCallback callback);

  void MarkUnblindedTokensAsSpendable(const std::string& redeem_id,
                                      ledger::LegacyResultCallback callback);

  void GetSpendableUnblindedTokens(GetUnblindedTokenListCallback callback);

  void GetReservedUnblindedTokens(const std::string& redeem_id,
                                  GetUnblindedTokenListCallback callback);

  virtual void GetSpendableUnblindedTokensByBatchTypes(
      const std::vector<mojom::CredsBatchType>& batch_types,
      GetUnblindedTokenListCallback callback);

 private:
  std::unique_ptr<DatabaseInitialize> initialize_;
  std::unique_ptr<DatabaseActivityInfo> activity_info_;
  std::unique_ptr<DatabaseBalanceReport> balance_report_;
  std::unique_ptr<DatabaseContributionInfo> contribution_info_;
  std::unique_ptr<DatabaseContributionQueue> contribution_queue_;
  std::unique_ptr<DatabaseCredsBatch> creds_batch_;
  std::unique_ptr<DatabaseEventLog> event_log_;
  std::unique_ptr<DatabaseExternalTransactions> external_transactions_;
  std::unique_ptr<DatabasePromotion> promotion_;
  std::unique_ptr<DatabaseMediaPublisherInfo> media_publisher_info_;
  std::unique_ptr<DatabaseMultiTables> multi_tables_;
  std::unique_ptr<DatabasePublisherInfo> publisher_info_;
  std::unique_ptr<DatabasePublisherPrefixList> publisher_prefix_list_;
  std::unique_ptr<DatabaseRecurringTip> recurring_tip_;
  std::unique_ptr<DatabaseServerPublisherInfo> server_publisher_info_;
  std::unique_ptr<DatabaseSKUOrder> sku_order_;
  std::unique_ptr<DatabaseSKUTransaction> sku_transaction_;
  std::unique_ptr<DatabaseUnblindedToken> unblinded_token_;
  const raw_ref<LedgerImpl> ledger_;
};

}  // namespace database
}  // namespace ledger

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_DATABASE_DATABASE_H_
