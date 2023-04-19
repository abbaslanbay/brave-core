/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/services/bat_ads/in_process_bat_ads_service.h"

#include <memory>
#include <utility>

#include "base/functional/bind.h"
#include "base/task/thread_pool.h"
#include "brave/components/services/bat_ads/bat_ads_service_impl.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"

namespace bat_ads {

namespace {

void BindInProcessBatAdsService(
    mojo::PendingReceiver<mojom::BatAdsService> receiver) {
  mojo::MakeSelfOwnedReceiver(std::make_unique<BatAdsServiceImpl>(),
                              std::move(receiver));
}

}  // namespace

void LaunchInProcessBatAdsService(
    mojo::PendingReceiver<mojom::BatAdsService> pending_receiver) {
  base::ThreadPool::CreateSequencedTaskRunner(
      {base::MayBlock(), base::WithBaseSyncPrimitives()})
      ->PostTask(FROM_HERE, base::BindOnce(&BindInProcessBatAdsService,
                                           std::move(pending_receiver)));
}

}  // namespace bat_ads
