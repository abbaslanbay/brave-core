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
    "https://support.brave.com/hc/en-us/articles/"
    "360017903152-How-do-I-reset-Brave-settings-to-default-";

const char kAdvancedProtectionDownloadLearnMoreURL[] =
    "https://minego.io/help-categories/";

const char kBatterySaverModeLearnMoreUrl[] =
    "https://support.brave.com/hc/en-us/articles/13380606172557";

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
    "https://community.brave.com/c/beta-builds";

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
    "https://support.brave.com/hc/en-us/articles/"
    "360018205431-How-do-I-change-site-permissions-";

const char kCookiesSettingsHelpCenterURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360018205431-How-do-I-change-site-permissions-";

const char kCrashReasonURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360018192251-How-do-I-fix-page-crashes-and-other-page-loading-errors-";

const char kCrashReasonFeedbackDisplayedURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360018192251-How-do-I-fix-page-crashes-and-other-page-loading-errors-";

const char kDoNotTrackLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360017905612-How-do-I-turn-Do-Not-Track-on-or-off-";

const char kDownloadInterruptedLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360018192491-How-do-I-fix-file-download-errors-";

const char kDownloadScanningLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360018192491-How-do-I-fix-file-download-errors-";

const char kExtensionControlledSettingLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360018185651-How-do-I-stop-extensions-from-changing-my-settings-";

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
    "https://support.brave.com/hc/en-us/articles/"
    "360017905872-How-do-I-enable-or-disable-automatic-crash-reporting-";

const char kHighEfficiencyModeLearnMoreUrl[] =
    "https://support.brave.com/hc/en-us/articles/13383683902733";

const char kManagedUiLearnMoreUrl[] = "https://minego.io/help-categories/";

const char kInsecureDownloadBlockingLearnMoreUrl[] =
    "https://minego.io/help-categories/";

const char kMyActivityUrlInClearBrowsingData[] =
    "https://minego.io/help-categories/";

const char kOmniboxLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360017479752-How-do-I-set-my-default-search-engine-";

const char kPageInfoHelpCenterURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360018185871-How-do-I-check-if-a-site-s-connection-is-secure-";

const char kPasswordCheckLearnMoreURL[] = "https://minego.io/help-categories/";

const char kPasswordGenerationLearnMoreURL[] = "https://minego.io/help-categories/";

const char kPasswordManagerLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360018185951-How-do-I-use-the-built-in-password-manager-";

const char kPaymentMethodsURL[] = "https://support.brave.com";

const char kPrivacyLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360017989132-How-do-I-change-my-Privacy-Settings-";

const char kRemoveNonCWSExtensionURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360017914832-Why-am-I-seeing-the-message-extensions-disabled-by-Brave-";

const char kResetProfileSettingsLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360017903152-How-do-I-reset-Brave-settings-to-default-";

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
    "https://support.brave.com/hc/en-us/articles/"
    "360025390311-How-do-I-download-and-install-Brave-";

const char kWhoIsMyAdministratorHelpURL[] =
    "https://minego.io/help-categories/";

const char kCwsEnhancedSafeBrowsingLearnMoreURL[] =
    "https://minego.io/help-categories/";

#if BUILDFLAG(IS_ANDROID)
const char kEnhancedPlaybackNotificationLearnMoreURL[] =
// Keep in sync with chrome/android/java/strings/android_chrome_strings.grd
    "https://community.brave.com";
#endif

#if BUILDFLAG(IS_MAC)
const char kChromeEnterpriseSignInLearnMoreURL[] =
    "https://minego.io/help-categories/";

const char kMacOsObsoleteURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360025390311-How-do-I-download-and-install-Brave-";
#endif

#if BUILDFLAG(IS_WIN)
const char kChromeCleanerLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360017884152-How-do-I-remove-unwanted-ads-pop-ups-malware-";

const char kWindowsXPVistaDeprecationURL[] =
    "https://minego.io/help-categories/";

const char kWindows78DeprecationURL[] =
    "https://support.brave.com/hc/en-us/articles/11197967945613";
#endif  // BUILDFLAG(IS_WIN)

const char kChromeSyncLearnMoreURL[] = "https://minego.io/help-categories/";

#if BUILDFLAG(ENABLE_PLUGINS)
const char kOutdatedPluginLearnMoreURL[] =
    "https://support.brave.com/hc/en-us/articles/"
    "360018163151-How-do-I-manage-Flash-audio-video-";
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
    "https://support.brave.com";

}  // namespace chrome
