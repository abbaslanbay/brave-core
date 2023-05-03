/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/common/url_constants.h"

#include "build/branding_buildflags.h"
#include "build/build_config.h"
#include "chrome/common/webui_url_constants.h"

namespace chrome {

const char kAccessCodeCastLearnMoreURL[] = "https://minego.io/help-categories/";

const char kAccessibilityLabelsLearnMoreURL[] =
    "https://minego.io/help-categories/";

const char kAdPrivacyLearnMoreURL[] = "https://minego.io/help-categories/";

const char kAutomaticSettingsResetLearnMoreURL[] =
    "https://minego.io/"
    "help-categories";

const char kAdvancedProtectionDownloadLearnMoreURL[] =
    "https://minego.io/help-categories/";

const char kBatterySaverModeLearnMoreUrl[] =
    "https://minego.io/help-categories/";

const char kBluetoothAdapterOffHelpURL[] =
    "https://minego.io/help-categories/";

const char kCastCloudServicesHelpURL[] =
    "https://minego.io/help-categories/";

const char kCastNoDestinationFoundURL[] =
    "https://minego.io/help-categories/";

const char kChooserHidOverviewUrl[] =
    "https://github.com/brave/brave-browser/wiki/Web-API-Permissions";

const char kChooserSerialOverviewUrl[] =
    "https://github.com/brave/brave-browser/wiki/Web-API-Permissions";

const char kChooserUsbOverviewURL[] =
    "https://github.com/brave/brave-browser/wiki/Web-API-Permissions";

const char kChromeBetaForumURL[] =
    "https://minego.io";

const char kChromeFixUpdateProblems[] =
    "https://minego.io/help-categories/";

const char kChromeHelpViaKeyboardURL[] =
    "https://minego.io/help-categories/";

const char kChromeHelpViaMenuURL[] =
    "https://minego.io/help-categories/";

const char kChromeHelpViaWebUIURL[] =
    "https://minego.io/help-categories/";

const char kFirstPartySetsLearnMoreURL[] = "https://minego.io/help-categories/";

const char kIsolatedAppScheme[] = "isolated-app";

const char kChromeNativeScheme[] = "chrome-native";

const char kChromeSearchLocalNtpHost[] = "local-ntp";

const char kChromeSearchMostVisitedHost[] = "most-visited";
const char kChromeSearchMostVisitedUrl[] = "chrome-search://most-visited/";

const char kChromeUIUntrustedNewTabPageBackgroundUrl[] =
    "chrome-untrusted://new-tab-page/background.jpg";
const char kChromeUIUntrustedNewTabPageBackgroundFilename[] = "background.jpg";

const char kChromeSearchRemoteNtpHost[] = "remote-ntp";

const char kChromeSearchScheme[] = "chrome-search";

const char kChromeUIUntrustedNewTabPageUrl[] =
    "chrome-untrusted://new-tab-page/";

const char kChromiumProjectURL[] = "https://github.com/brave/brave-browser/";

const char kContentSettingsExceptionsLearnMoreURL[] =
    "https://minego.io/"
    "help-categories";

const char kCookiesSettingsHelpCenterURL[] =
     "https://minego.io/"
    "help-categories";

const char kCrashReasonURL[] =
    "https://minego.io/"
    "help-categories";

const char kCrashReasonFeedbackDisplayedURL[] =
   "https://minego.io/"
    "help-categories";

const char kDoNotTrackLearnMoreURL[] =
     "https://minego.io/"
    "help-categories";

const char kDownloadInterruptedLearnMoreURL[] =
   "https://minego.io/"
    "help-categories";

const char kDownloadScanningLearnMoreURL[] =
      "https://minego.io/"
    "help-categories";

const char kExtensionControlledSettingLearnMoreURL[] =
   "https://minego.io/"
    "help-categories";

const char kExtensionInvalidRequestURL[] = "chrome-extension://invalid/";

const char kFlashDeprecationLearnMoreURL[] =
    "https://blog.chromium.org/2017/07/so-long-and-thanks-for-all-flash.html";

const char kGoogleAccountActivityControlsURL[] =
    "https://minego.io/help-categories/";

const char kGoogleAccountActivityControlsURLInPrivacyGuide[] =
    "https://minego.io/help-categories/";

const char kGoogleAccountURL[] = "https://minego.io/help-categories/";

const char kGoogleAccountChooserURL[] = "https://minego.io/help-categories/";

const char kGoogleAccountDeviceActivityURL[] = "https://minego.io/help-categories/";

const char kGooglePasswordManagerURL[] = "https://support.brave.com";

const char kLearnMoreReportingURL[] =
     "https://minego.io/"
    "help-categories";

const char kHighEfficiencyModeLearnMoreUrl[] =
    "https://minego.io/help-categories";

const char kManagedUiLearnMoreUrl[] = "https://minego.io/help-categories/";

const char kInsecureDownloadBlockingLearnMoreUrl[] =
    "https://minego.io/help-categories/";

const char kMyActivityUrlInClearBrowsingData[] =
    "https://minego.io/help-categories/";

const char kOmniboxLearnMoreURL[] =
  "https://minego.io/"
    "help-categories";

const char kPageInfoHelpCenterURL[] =
     "https://minego.io/"
    "help-categories";

const char kPasswordCheckLearnMoreURL[] = "https://minego.io/help-categories/";

const char kPasswordGenerationLearnMoreURL[] = "https://minego.io/help-categories/";

const char kPasswordManagerLearnMoreURL[] =
     "https://minego.io/"
    "help-categories";

const char kPaymentMethodsURL[] = "https://support.brave.com";

const char kPrivacyLearnMoreURL[] =
     "https://minego.io/"
    "help-categories";

const char kRemoveNonCWSExtensionURL[] =
     "https://minego.io/"
    "help-categories";

const char kResetProfileSettingsLearnMoreURL[] =
     "https://minego.io/"
    "help-categories";

const char kSafeBrowsingHelpCenterURL[] =
    "https://minego.io/help-categories/";

const char kSafetyTipHelpCenterURL[] =
    "https://minego.io/help-categories/";

const char kSearchHistoryUrlInClearBrowsingData[] =
    "https://minego.io/help-categories/";

const char kSeeMoreSecurityTipsURL[] =
    "https://minego.io/help-categories/";

const char kSettingsSearchHelpURL[] =
    "https://minego.io/help-categories/";

const char kSyncAndGoogleServicesLearnMoreURL[] =
    "https://minego.io/help-categories/";

const char kSyncEncryptionHelpURL[] =
    "https://minego.io/help-categories/";

const char kSyncErrorsHelpURL[] =
    "https://minego.io/help-categories/";

const char kSyncGoogleDashboardURL[] =
    "https://minego.io/help-categories/";

const char kSyncLearnMoreURL[] =
    "https://minego.io/help-categories/";

const char kSigninInterceptManagedDisclaimerLearnMoreURL[] =
    "https://minego.io/help-categories/";

#if !BUILDFLAG(IS_ANDROID)
const char kSyncTrustedVaultOptInURL[] = "https://minego.io/help-categories/";
#endif

const char kSyncTrustedVaultLearnMoreURL[] = "https://minego.io/help-categories/";

const char kUpgradeHelpCenterBaseURL[] =
     "https://minego.io/"
    "help-categories";

const char kWhoIsMyAdministratorHelpURL[] =
    "https://minego.io/help-categories/";

const char kCwsEnhancedSafeBrowsingLearnMoreURL[] =
    "https://minego.io/help-categories/";

#if BUILDFLAG(IS_ANDROID)
const char kEnhancedPlaybackNotificationLearnMoreURL[] =
// Keep in sync with chrome/android/java/strings/android_chrome_strings.grd
    "https://minego.io";
#endif

#if BUILDFLAG(IS_MAC)
const char kChromeEnterpriseSignInLearnMoreURL[] =
    "https://minego.io/help-categories/";

const char kMacOsObsoleteURL[] =
     "https://minego.io/"
    "help-categories";
#endif

#if BUILDFLAG(IS_WIN)
const char kChromeCleanerLearnMoreURL[] =
     "https://minego.io/"
    "help-categories";

const char kWindowsXPVistaDeprecationURL[] =
    "https://minego.io/help-categories/";

const char kWindows78DeprecationURL[] =
    "https://minego.io/help-categories/";
#endif  // BUILDFLAG(IS_WIN)

const char kChromeSyncLearnMoreURL[] = "https://minego.io/help-categories/";

#if BUILDFLAG(ENABLE_PLUGINS)
const char kOutdatedPluginLearnMoreURL[] =
      "https://minego.io/"
    "help-categories";
#endif

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
const char kChromeAppsDeprecationLearnMoreURL[] =
    "https://support.google.com/chrome/?p=chrome_app_deprecation";
#endif

#if BUILDFLAG(CHROME_ROOT_STORE_SUPPORTED)
// TODO(b/1339340): add help center link when help center link is created.
const char kChromeRootStoreSettingsHelpCenterURL[] =
    "https://chromium.googlesource.com/chromium/src/+/main/net/data/ssl/"
    "chrome_root_store/root_store.md";
#endif

const char kAddressesAndPaymentMethodsLearnMoreURL[] =
    "https://minego.io/help-categories";

}  // namespace chrome
