/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_wallet/browser/simulation_service.h"

#include <utility>

#include "base/strings/stringprintf.h"
#include "brave/components/brave_wallet/browser/brave_wallet_constants.h"
#include "brave/components/brave_wallet/browser/json_rpc_service.h"
#include "net/base/load_flags.h"
#include "net/base/url_util.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"
#include "services/network/public/cpp/simple_url_loader.h"
#include "ui/base/l10n/l10n_util.h"

namespace {

net::NetworkTrafficAnnotationTag GetNetworkTrafficAnnotationTag() {
  return net::DefineNetworkTrafficAnnotation("simulation_service", R"(
      semantics {
        sender: "Simulation Service"
        description:
          "This service is used scan proposed transactions and simulate expected state changes."
        trigger:
          "Triggered by uses of the native Brave wallet."
        data:
          "Blowfish API response bodies."
        destination: WEBSITE
      }
      policy {
        cookies_allowed: NO
        setting:
          "You can enable or disable this feature on chrome://flags."
        policy_exception_justification:
          "Not implemented."
      }
    )");
}

std::string GetRelativeScanURL(const std::string& chain_id,
                               brave_wallet::mojom::CoinType coin) {
  std::string url;

  if (coin == brave_wallet::mojom::CoinType::SOL &&
      chain_id == brave_wallet::mojom::kSolanaMainnet) {
    url = "solana/v0/mainnet/scan";
  } else if (coin == brave_wallet::mojom::CoinType::ETH &&
             chain_id == brave_wallet::mojom::kMainnetChainId) {
    url = "ethereum/v0/mainnet/scan";
  } else if (coin == brave_wallet::mojom::CoinType::ETH &&
             chain_id == brave_wallet::mojom::kPolygonMainnetChainId) {
    url = "polygon/v0/mainnet/scan";
  } else if (coin == brave_wallet::mojom::CoinType::ETH &&
             chain_id ==
                 brave_wallet::mojom::kBinanceSmartChainMainnetChainId) {
    url = "bnb/v0/mainnet/scan";
  } else if (coin == brave_wallet::mojom::CoinType::ETH &&
             chain_id == brave_wallet::mojom::kArbitrumMainnetChainId) {
    url = "arbitrum/v0/one/scan";
  }

  return url;
}

}  // namespace

namespace brave_wallet {

GURL SimulationService::base_url_for_test_;

SimulationService::SimulationService(
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
    JsonRpcService* json_rpc_service)
    : api_request_helper_(GetNetworkTrafficAnnotationTag(), url_loader_factory),
      json_rpc_service_(json_rpc_service),
      weak_ptr_factory_(this) {
  DCHECK(json_rpc_service_);
}

SimulationService::~SimulationService() = default;

mojo::PendingRemote<mojom::SimulationService> SimulationService::MakeRemote() {
  mojo::PendingRemote<mojom::SimulationService> remote;
  receivers_.Add(this, remote.InitWithNewPipeAndPassReceiver());
  return remote;
}

void SimulationService::Bind(
    mojo::PendingReceiver<mojom::SimulationService> receiver) {
  receivers_.Add(this, std::move(receiver));
}

void SimulationService::SetBaseURLForTest(const GURL& base_url_for_test) {
  base_url_for_test_ = base_url_for_test;
}

// static
GURL SimulationService::GetScanTransactionURL(const std::string& chain_id,
                                              mojom::CoinType coin) {
  std::string spec = base::StringPrintf(
      "%s/%s/transaction",
      base_url_for_test_.is_empty() ? brave_wallet::kBlowfishBaseAPIURL
                                    : base_url_for_test_.spec().c_str(),
      GetRelativeScanURL(chain_id, coin).c_str());
  GURL url(spec);
  return url;
}

// static
GURL SimulationService::GetScanMessageURL(const std::string& chain_id,
                                          mojom::CoinType coin) {
  std::string spec = base::StringPrintf(
      "%s/%s/message",
      base_url_for_test_.is_empty() ? brave_wallet::kBlowfishBaseAPIURL
                                    : base_url_for_test_.spec().c_str(),
      GetRelativeScanURL(chain_id, coin).c_str());
  GURL url(spec);
  return url;
}

void SimulationService::HasTransactionScanSupport(
    const std::string& chain_id,
    mojom::CoinType coin,
    HasTransactionScanSupportCallback callback) {
  bool result =
      (coin == mojom::CoinType::SOL && chain_id == mojom::kSolanaMainnet) ||
      (coin == mojom::CoinType::ETH && chain_id == mojom::kMainnetChainId) ||
      (coin == mojom::CoinType::ETH &&
       chain_id == mojom::kPolygonMainnetChainId) ||
      (coin == mojom::CoinType::ETH &&
       chain_id == mojom::kBinanceSmartChainMainnetChainId) ||
      (coin == mojom::CoinType::ETH &&
       chain_id == mojom::kArbitrumMainnetChainId);

  std::move(callback).Run(result);
}

void SimulationService::HasMessageScanSupport(
    const std::string& chain_id,
    mojom::CoinType coin,
    HasMessageScanSupportCallback callback) {
  bool result =
      (coin == mojom::CoinType::ETH && chain_id == mojom::kMainnetChainId) ||
      (coin == mojom::CoinType::ETH &&
       chain_id == mojom::kPolygonMainnetChainId) ||
      (coin == mojom::CoinType::ETH &&
       chain_id == mojom::kBinanceSmartChainMainnetChainId) ||
      (coin == mojom::CoinType::ETH &&
       chain_id == mojom::kArbitrumMainnetChainId);
  std::move(callback).Run(result);
}

// void SimulationService::ScanSolanaTransaction(
//         mojom::SolanaTransactionRequestUnionPtr request,
//         const std::string& language) {
//
// }

void SimulationService::ScanEVMTransaction(
    mojom::TransactionInfoPtr tx_info,
    const std::string& language,
    ScanEVMTransactionCallback callback) {
  std::move(callback).Run(true);
}

}  // namespace brave_wallet
