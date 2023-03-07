/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <utility>
#include <vector>

#include "base/containers/contains.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/stringprintf.h"
#include "brave/components/brave_wallet/browser/brave_wallet_constants.h"
#include "brave/components/brave_wallet/browser/json_rpc_requests_helper.h"
#include "brave/components/brave_wallet/browser/json_rpc_response_parser.h"
#include "brave/components/brave_wallet/browser/simulation_response_parser.h"
#include "brave/components/brave_wallet/browser/simulation_responses.h"

namespace {}  // namespace

namespace brave_wallet {
mojom::BlowfishEVMContractPtr ParseEVMContract(
    const simulation_responses::EVMContract& value) {
  return mojom::BlowfishEVMContract::New(value.address, value.kind);
}

mojom::BlowfishEVMAmountPtr ParseEVMAmount(
    const simulation_responses::EVMAmount& value) {
  return mojom::BlowfishEVMAmount::New(value.before, value.after);
}

mojom::BlowfishEVMAssetPtr ParseEVMAsset(
    const simulation_responses::EVMAsset& value) {
  auto asset = mojom::BlowfishEVMAsset::New();
  asset->address = value.address;
  asset->symbol = value.symbol;
  asset->name = value.name;
  asset->decimals = value.decimals;
  asset->verified = value.verified;
  asset->lists = value.lists;
  asset->image_url = value.image_url;
  asset->price =
      mojom::BlowfishPrice::New(value.price.source, value.price.last_updated_at,
                                value.price.dollar_value_per_token);
  return asset;
}

mojom::BlowfishEVMStateChangeRawInfoPtr ParseEVMStateChangeRawInfo(
    const simulation_responses::EVMStateChangeRawInfo& value) {
  auto raw_info = mojom::BlowfishEVMStateChangeRawInfo::New();
  raw_info->kind = value.kind;

  if (value.kind == "ERC20_TRANSFER") {
    auto data_value =
        simulation_responses::ERC20TransferData::FromValue(value.data);
    if (!data_value) {
      return nullptr;
    }

    auto data = mojom::BlowfishERC20TransferData::New();
    data->contract = ParseEVMContract(data_value->contract);
    data->amount = ParseEVMAmount(data_value->amount);
    data->asset = ParseEVMAsset(data_value->asset);

    raw_info->data =
        mojom::BlowfishEVMStateChangeRawInfoDataUnion::NewErc20TransferData(
            std::move(data));
  } else if (value.kind == "ERC20_APPROVAL") {
    auto data_value =
        simulation_responses::ERC20ApprovalData::FromValue(value.data);
    if (!data_value) {
      return nullptr;
    }

    auto data = mojom::BlowfishERC20ApprovalData::New();
    data->contract = ParseEVMContract(data_value->contract);
    data->owner = ParseEVMContract(data_value->owner);
    data->spender = ParseEVMContract(data_value->spender);
    data->amount = ParseEVMAmount(data_value->amount);
    data->asset = ParseEVMAsset(data_value->asset);

    raw_info->data =
        mojom::BlowfishEVMStateChangeRawInfoDataUnion::NewErc20ApprovalData(
            std::move(data));
  } else if (value.kind == "NATIVE_ASSET_TRANSFER") {
    auto data_value =
        simulation_responses::NativeAssetTransferData::FromValue(value.data);
    if (!data_value) {
      return nullptr;
    }

    auto data = mojom::BlowfishNativeAssetTransferData::New();
    data->contract = ParseEVMContract(data_value->contract);
    data->decimals = data_value->decimals;
    data->amount = ParseEVMAmount(data_value->amount);
    data->symbol = data_value->symbol;
    data->name = data_value->name;

    raw_info->data = mojom::BlowfishEVMStateChangeRawInfoDataUnion::
        NewNativeAssetTransferData(std::move(data));
  }

  return raw_info;
}

mojom::EVMSimulationResponsePtr ParseEVMSimulationResponse(
    const base::Value& json_value) {
  auto simulation_response_value =
      simulation_responses::EVMSimulationResponse::FromValue(json_value);
  if (!simulation_response_value) {
    return nullptr;
  }

  auto simulation_response = mojom::EVMSimulationResponse::New();
  simulation_response->action = simulation_response_value->action;

  for (const auto& warning_value : simulation_response_value->warnings) {
    simulation_response->warnings.push_back(mojom::BlowfishWarning::New(
        warning_value.severity, warning_value.kind, warning_value.message));
  }

  auto simulation_results = mojom::EVMSimulationResults::New();

  if (!simulation_response_value->simulation_results.error.is_none()) {
    const auto& error_value = simulation_responses::EVMError::FromValue(
        simulation_response_value->simulation_results.error);

    simulation_results->error = mojom::BlowfishEVMError::New(
        error_value->kind, error_value->human_readable_error,
        error_value->error_type);
  }

  for (const auto& state_change_value :
       simulation_response_value->simulation_results.expected_state_changes) {
    auto state_change = mojom::BlowfishEVMStateChange::New();
    state_change->human_readable_diff = state_change_value.human_readable_diff;
    state_change->raw_info =
        ParseEVMStateChangeRawInfo(state_change_value.raw_info);

    simulation_results->expected_state_changes.push_back(
        std::move(state_change));
  }

  simulation_response->simulation_results = std::move(simulation_results);

  return simulation_response;
}
}  // namespace brave_wallet
