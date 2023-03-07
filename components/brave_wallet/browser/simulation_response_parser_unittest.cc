/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>
#include <utility>
#include <vector>

#include "base/i18n/time_formatting.h"
#include "base/json/json_reader.h"
#include "base/strings/stringprintf.h"
#include "base/strings/utf_string_conversions.h"
#include "base/test/values_test_util.h"
#include "brave/components/brave_wallet/browser/json_rpc_requests_helper.h"
#include "brave/components/brave_wallet/browser/simulation_response_parser.h"
#include "brave/components/brave_wallet/common/brave_wallet.mojom.h"
#include "testing/gtest/include/gtest/gtest.h"

using base::test::ParseJson;

namespace brave_wallet {

namespace {}  // namespace

TEST(SimulationResponseParserUnitTest, ParseSwapETHForDAI) {
  std::string json(R"(
    {
      "action": "NONE",
      "simulationResults": {
        "error": null,
        "gas": {
          "gasLimit": null
        },
        "expectedStateChanges": [
          {
            "humanReadableDiff": "Receive 1530.81307 DAI",
            "rawInfo": {
              "data": {
                "amount": {
                  "after": "557039306766411381864245",
                  "before": "555508493698012633714742"
                },
                "contract": {
                  "address": "0x6b175474e89094c44da98b954eedeac495271d0f",
                  "kind": "ACCOUNT"
                },
                "decimals": 18,
                "name": "Dai Stablecoin",
                "symbol": "DAI",
                "asset": {
                  "address": "0x6b175474e89094c44da98b954eedeac495271d0f",
                  "symbol": "DAI",
                  "name": "Dai Stablecoin",
                  "decimals": 18,
                  "verified": true,
                  "lists": [
                    "COINGECKO",
                    "ZERION"
                  ],
                  "imageUrl": "https://example.com/dai.png",
                  "price": {
                    "source": "Defillama",
                    "last_updated_at": "1680557741",
                    "dollar_value_per_token": "1.001"
                  }
                }
              },
              "kind": "ERC20_TRANSFER"
            }
          },
          {
            "humanReadableDiff": "Send 1 ETH",
            "rawInfo": {
              "data": {
                "amount": {
                  "after": "1182957389356504134754",
                  "before": "1183957389356504134754"
                },
                "contract": {
                  "address": "0xeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
                  "kind": "ACCOUNT"
                },
                "decimals": 18,
                "name": "Ether",
                "symbol": "ETH"
              },
              "kind": "NATIVE_ASSET_TRANSFER"
            }
          }
        ]
      },
      "warnings": []
    }
  )");
  auto simulation_response = ParseEVMSimulationResponse(ParseJson(json));
  ASSERT_TRUE(simulation_response);

  ASSERT_EQ(simulation_response->action, "NONE");
  ASSERT_EQ(simulation_response->warnings.size(), 0u);
  ASSERT_FALSE(simulation_response->simulation_results->error);
  ASSERT_EQ(
      simulation_response->simulation_results->expected_state_changes.size(),
      2u);

  const auto& state_change_0 =
      simulation_response->simulation_results->expected_state_changes.at(0);
  ASSERT_EQ(state_change_0->human_readable_diff, "Receive 1530.81307 DAI");
  ASSERT_EQ(state_change_0->raw_info->kind, "ERC20_TRANSFER");
  ASSERT_TRUE(state_change_0->raw_info->data->is_erc20_transfer_data());
  const auto& state_change_0_raw_info =
      state_change_0->raw_info->data->get_erc20_transfer_data();
  ASSERT_EQ(state_change_0_raw_info->amount->before,
            "555508493698012633714742");
  ASSERT_EQ(state_change_0_raw_info->amount->after, "557039306766411381864245");
  ASSERT_EQ(state_change_0_raw_info->contract->address,
            "0x6b175474e89094c44da98b954eedeac495271d0f");
  ASSERT_EQ(state_change_0_raw_info->contract->kind, "ACCOUNT");
  ASSERT_EQ(state_change_0_raw_info->asset->address,
            "0x6b175474e89094c44da98b954eedeac495271d0f");
  ASSERT_EQ(state_change_0_raw_info->asset->symbol, "DAI");
  ASSERT_EQ(state_change_0_raw_info->asset->name, "Dai Stablecoin");
  ASSERT_EQ(state_change_0_raw_info->asset->decimals, 18);
  ASSERT_TRUE(state_change_0_raw_info->asset->verified);
  ASSERT_EQ(state_change_0_raw_info->asset->lists.size(), 2u);
  ASSERT_EQ(state_change_0_raw_info->asset->lists.at(0), "COINGECKO");
  ASSERT_EQ(state_change_0_raw_info->asset->lists.at(1), "ZERION");
  ASSERT_EQ(state_change_0_raw_info->asset->image_url,
            "https://example.com/dai.png");
  ASSERT_EQ(state_change_0_raw_info->asset->price->source, "Defillama");
  ASSERT_EQ(state_change_0_raw_info->asset->price->last_updated_at,
            "1680557741");
  ASSERT_EQ(state_change_0_raw_info->asset->price->dollar_value_per_token,
            "1.001");

  const auto& state_change_1 =
      simulation_response->simulation_results->expected_state_changes.at(1);
  ASSERT_EQ(state_change_1->human_readable_diff, "Send 1 ETH");
  ASSERT_EQ(state_change_1->raw_info->kind, "NATIVE_ASSET_TRANSFER");
  ASSERT_TRUE(state_change_1->raw_info->data->is_native_asset_transfer_data());
  const auto& state_change_1_raw_info =
      state_change_1->raw_info->data->get_native_asset_transfer_data();
  ASSERT_EQ(state_change_1_raw_info->amount->before, "1183957389356504134754");
  ASSERT_EQ(state_change_1_raw_info->amount->after, "1182957389356504134754");
  ASSERT_EQ(state_change_1_raw_info->contract->address,
            "0xeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
  ASSERT_EQ(state_change_1_raw_info->contract->kind, "ACCOUNT");
  ASSERT_EQ(state_change_1_raw_info->decimals, 18);
  ASSERT_EQ(state_change_1_raw_info->name, "Ether");
  ASSERT_EQ(state_change_1_raw_info->symbol, "ETH");
}

TEST(SimulationResponseParserUnitTest, ParseERC20Approval) {
  std::string json(R"(
    {
      "action": "NONE",
      "simulationResults": {
        "error": null,
        "gas": {
          "gasLimit": null
        },
        "expectedStateChanges": [
          {
            "humanReadableDiff": "Approve to transfer up to 1000 USDT",
            "rawInfo": {
              "data": {
                "amount": {
                  "after": "1000000000",
                  "before": "0"
                },
                "asset": {
                  "address": "0xdac17f958d2ee523a2206206994597c13d831ec7",
                  "name": "Tether USD",
                  "decimals": 6,
                  "lists": [
                    "COINGECKO",
                    "ZERION"
                  ],
                  "symbol": "USDT",
                  "verified": true,
                  "imageUrl": "https://example.com/usdt.png",
                  "price": {
                    "source": "Defillama",
                    "last_updated_at": "1680557741",
                    "dollar_value_per_token": "1.001"
                  }
                },
                "contract": {
                  "address": "0xdac17f958d2ee523a2206206994597c13d831ec7",
                  "kind": "ACCOUNT"
                },
                "decimals": 6,
                "name": "Tether USD",
                "owner": {
                  "address": "0xd8da6bf26964af9d7eed9e03e53415d37aa96045",
                  "kind": "ACCOUNT"
                },
                "spender": {
                  "address": "0x68b3465833fb72a70ecdf485e0e4c7bd8665fc45",
                  "kind": "ACCOUNT"
                },
                "symbol": "USDT"
              },
              "kind": "ERC20_APPROVAL"
            }
          }
        ]
      },
      "warnings": []
    }
  )");

  auto simulation_response = ParseEVMSimulationResponse(ParseJson(json));
  ASSERT_TRUE(simulation_response);

  ASSERT_EQ(simulation_response->action, "NONE");
  ASSERT_EQ(simulation_response->warnings.size(), 0u);
  ASSERT_FALSE(simulation_response->simulation_results->error);
  ASSERT_EQ(
      simulation_response->simulation_results->expected_state_changes.size(),
      1u);

  const auto& state_change =
      simulation_response->simulation_results->expected_state_changes.at(0);
  ASSERT_EQ(state_change->human_readable_diff,
            "Approve to transfer up to 1000 USDT");
  ASSERT_EQ(state_change->raw_info->kind, "ERC20_APPROVAL");
  ASSERT_TRUE(state_change->raw_info->data->is_erc20_approval_data());
  const auto& state_change_raw_info =
      state_change->raw_info->data->get_erc20_approval_data();
  ASSERT_EQ(state_change_raw_info->amount->before, "0");
  ASSERT_EQ(state_change_raw_info->amount->after, "1000000000");
  ASSERT_EQ(state_change_raw_info->asset->address,
            "0xdac17f958d2ee523a2206206994597c13d831ec7");
  ASSERT_EQ(state_change_raw_info->asset->symbol, "USDT");
  ASSERT_EQ(state_change_raw_info->asset->name, "Tether USD");
  ASSERT_EQ(state_change_raw_info->asset->decimals, 6);
  ASSERT_TRUE(state_change_raw_info->asset->verified);
  ASSERT_EQ(state_change_raw_info->asset->lists.size(), 2u);
  ASSERT_EQ(state_change_raw_info->asset->lists.at(0), "COINGECKO");
  ASSERT_EQ(state_change_raw_info->asset->lists.at(1), "ZERION");
  ASSERT_EQ(state_change_raw_info->asset->image_url,
            "https://example.com/usdt.png");
  ASSERT_EQ(state_change_raw_info->asset->price->source, "Defillama");
  ASSERT_EQ(state_change_raw_info->asset->price->last_updated_at, "1680557741");
  ASSERT_EQ(state_change_raw_info->asset->price->dollar_value_per_token,
            "1.001");
  ASSERT_EQ(state_change_raw_info->contract->address,
            "0xdac17f958d2ee523a2206206994597c13d831ec7");
  ASSERT_EQ(state_change_raw_info->contract->kind, "ACCOUNT");
  ASSERT_EQ(state_change_raw_info->owner->address,
            "0xd8da6bf26964af9d7eed9e03e53415d37aa96045");
  ASSERT_EQ(state_change_raw_info->owner->kind, "ACCOUNT");
  ASSERT_EQ(state_change_raw_info->spender->address,
            "0x68b3465833fb72a70ecdf485e0e4c7bd8665fc45");
  ASSERT_EQ(state_change_raw_info->spender->kind, "ACCOUNT");
}
}  // namespace brave_wallet
