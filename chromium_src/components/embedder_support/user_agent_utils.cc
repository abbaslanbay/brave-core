/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "components/embedder_support/user_agent_utils.h"

#include "base/notreached.h"
#include "base/strings/stringprintf.h"
#include "base/version.h"
#include "third_party/blink/public/common/features.h"

namespace {

constexpr char kBraveBrandNameForCHUA[] = "Brave";

}  // namespace

// Chromium uses `version_info::GetProductName()` to get the browser's "brand"
// name, but on MacOS we use different names for different channels (adding Beta
// or Nightly, for example). In the UA client hint, though, we want a consistent
// name regardless of the channel, so we just hard-code it. Note, that we use
// IDS_PRODUCT_NAME from app/chromium_strings.grd (brave_strings.grd) in
// constructing the UA in brave/browser/brave_content_browser_client.cc, but we
// can't use it here in the //components.
#define BRAVE_GET_USER_AGENT_BRAND_LIST brand = kBraveBrandNameForCHUA;

#include "src/components/embedder_support/user_agent_utils.cc"
#undef BRAVE_GET_USER_AGENT_BRAND_LIST

namespace embedder_support {

blink::UserAgentMetadata BraveGetUserAgentMetadata(
    const PrefService* pref_service) {
  blink::UserAgentMetadata metadata = GetUserAgentMetadata(pref_service);
  if (base::FeatureList::IsEnabled(
          blink::features::kClampPlatformVersionClientHint)) {
    // Clamp platform version
    base::Version platform_version(metadata.platform_version);
    metadata.platform_version = base::StringPrintf(
        "%d.%d.%s", platform_version.components()[0],
        platform_version.components()[1],
        blink::features::kClampPlatformVersionClientHintPatchValue.Get()
            .c_str());
  }
  return metadata;
}

// This is added because of the redefinition of GetUserAgentMetadata in 
// brave/chromium_src/components/client_hints/browser/client_hints.cc which
// causes ClientHints::GetUserAgentMetadata() in there to call
// embedder_support::GetUserAgentMetadata_ChromiumImpl(pref_service_);
blink::UserAgentMetadata GetUserAgentMetadata_ChromiumImpl(
    const PrefService* pref_service) {
  NOTREACHED_NORETURN();
}

}  // namespace embedder_support
