/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENDPOINT_PROMOTION_PROMOTION_SERVER_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENDPOINT_PROMOTION_PROMOTION_SERVER_H_

#include <memory>

#include "brave/components/brave_rewards/core/endpoint/promotion/get_available/get_available.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/get_captcha/get_captcha.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/get_signed_creds/get_signed_creds.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/get_wallet/get_wallet.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/post_bat_loss/post_bat_loss.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/post_captcha/post_captcha.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/post_clobbered_claims/post_clobbered_claims.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/post_creds/post_creds.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/post_devicecheck/post_devicecheck.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/post_safetynet/post_safetynet.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/post_suggestions/post_suggestions.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/post_suggestions_claim/post_suggestions_claim.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/put_captcha/put_captcha.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/put_devicecheck/put_devicecheck.h"
#include "brave/components/brave_rewards/core/endpoint/promotion/put_safetynet/put_safetynet.h"
#include "brave/components/brave_rewards/core/ledger_callbacks.h"

namespace ledger {
class LedgerImpl;

namespace endpoint {

class PromotionServer {
 public:
  explicit PromotionServer(LedgerImpl& ledger);
  ~PromotionServer();

  promotion::GetAvailable* get_available() const;

  promotion::PostCreds* post_creds() const;

  promotion::GetSignedCreds* get_signed_creds() const;

  promotion::PostClobberedClaims* post_clobbered_claims() const;

  promotion::PostBatLoss* post_bat_loss() const;

  promotion::GetWallet* get_wallet() const;

  promotion::PostCaptcha* post_captcha() const;

  promotion::GetCaptcha* get_captcha() const;

  promotion::PutCaptcha* put_captcha() const;

  promotion::PostSafetynet* post_safetynet() const;

  promotion::PutSafetynet* put_safetynet() const;

  promotion::PostDevicecheck* post_devicecheck() const;

  promotion::PutDevicecheck* put_devicecheck() const;

  promotion::PostSuggestions* post_suggestions() const;

  promotion::PostSuggestionsClaim* post_suggestions_claim() const;

 private:
  std::unique_ptr<promotion::GetAvailable> get_available_;
  std::unique_ptr<promotion::PostCreds> post_creds_;
  std::unique_ptr<promotion::GetSignedCreds> get_signed_creds_;
  std::unique_ptr<promotion::PostClobberedClaims> post_clobbered_claims_;
  std::unique_ptr<promotion::PostBatLoss> post_bat_loss_;
  std::unique_ptr<promotion::GetWallet> get_wallet_;
  std::unique_ptr<promotion::PostCaptcha> post_captcha_;
  std::unique_ptr<promotion::GetCaptcha> get_captcha_;
  std::unique_ptr<promotion::PutCaptcha> put_captcha_;
  std::unique_ptr<promotion::PostSafetynet> post_safetynet_;
  std::unique_ptr<promotion::PutSafetynet> put_safetynet_;
  std::unique_ptr<promotion::PostDevicecheck> post_devicecheck_;
  std::unique_ptr<promotion::PutDevicecheck> put_devicecheck_;
  std::unique_ptr<promotion::PostSuggestions> post_suggestions_;
  std::unique_ptr<promotion::PostSuggestionsClaim> post_suggestions_claim_;
};

}  // namespace endpoint
}  // namespace ledger

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENDPOINT_PROMOTION_PROMOTION_SERVER_H_
