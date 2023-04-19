/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/client_hints/browser/client_hints.h"

#define GetUserAgentMetadata GetUserAgentMetadata_ChromiumImpl
#include "src/components/client_hints/browser/client_hints.cc"
#undef GetUserAgentMetadata

namespace client_hints {

blink::UserAgentMetadata ClientHints::GetUserAgentMetadata() {
  return embedder_support::BraveGetUserAgentMetadata(pref_service_);
}

}  // namespace client_hints
