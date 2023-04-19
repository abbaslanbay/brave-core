/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_SERVICES_BAT_ADS_IN_PROCESS_BAT_ADS_SERVICE_H_
#define BRAVE_COMPONENTS_SERVICES_BAT_ADS_IN_PROCESS_BAT_ADS_SERVICE_H_

#include "brave/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

namespace bat_ads {

void LaunchInProcessBatAdsService(
    mojo::PendingReceiver<mojom::BatAdsService> pending_receiver);

}  // namespace bat_ads

#endif  // BRAVE_COMPONENTS_SERVICES_BAT_ADS_IN_PROCESS_BAT_ADS_SERVICE_H_
