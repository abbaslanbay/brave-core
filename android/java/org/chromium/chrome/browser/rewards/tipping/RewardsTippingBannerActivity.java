/**
 * Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.rewards.tipping;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;

import org.json.JSONException;

import org.chromium.base.IntentUtils;
import org.chromium.base.Log;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.BraveRewardsHelper;
import org.chromium.chrome.browser.BraveRewardsNativeWorker;
import org.chromium.chrome.browser.BraveRewardsObserver;
import org.chromium.chrome.browser.init.AsyncInitializationActivity;
import org.chromium.chrome.browser.rewards.BraveRewardsBannerInfo;
import org.chromium.chrome.browser.tab.Tab;

public class RewardsTippingBannerActivity extends AsyncInitializationActivity
        implements BraveRewardsObserver, BraveRewardsHelper.LargeIconReadyCallback {
    public static final String TAB_ID_EXTRA = "currentTabId";
    private BraveRewardsNativeWorker mBraveRewardsNativeWorker;
    private final int PUBLISHER_ICON_SIDE_LEN = 64; // dp
    private static final String TAG = "TippingBanner";
    private int currentTabId_ = -1;
    private BraveRewardsBannerInfo mBannerInfo;

    private BraveRewardsHelper mIconFetcher;

    @Override
    protected void triggerLayoutInflation() {
        setContentView(R.layout.activity_tipping_banner_mobile);
        showCustomUI();
        ((TextView) findViewById(R.id.tipping_details_description))
                .setMovementMethod(new ScrollingMovementMethod());
        currentTabId_ = IntentUtils.safeGetIntExtra(getIntent(), TAB_ID_EXTRA, -1);

        onInitialLayoutInflationComplete();
        Log.e(TAG, "BraveRewardsSiteBannerActivity:triggerLayoutInflation");
        // retriveFavIcon();
        clickOnVerifiedIcon();
        sendTipButtonClick();
    }

    private void clickOnVerifiedIcon() {
        ImageView view = findViewById(R.id.verified_tick_mark);
        view.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TippingVerifiedCreatorToolTip toolTip =
                        new TippingVerifiedCreatorToolTip(RewardsTippingBannerActivity.this);
                toolTip.show(view);
            }
        });
    }

    private void retriveFavIcon() {
        String publisherFavIconURL =
                mBraveRewardsNativeWorker.GetPublisherFavIconURL(currentTabId_);
        Tab currentActiveTab = BraveRewardsHelper.currentActiveChromeTabbedActivityTab();
        String url = currentActiveTab != null ? currentActiveTab.getUrl().getSpec() : "";
        String favicon_url = (publisherFavIconURL.isEmpty()) ? url : publisherFavIconURL;
        mIconFetcher = new BraveRewardsHelper(currentActiveTab);
        mIconFetcher.retrieveLargeIcon(favicon_url, this);
    }

    //        .load("https://www.pakainfo.com/wp-content/uploads/2021/09/image-url-for-testing.jpg")
    //  .load("chrome://rewards-image/https://rewards.brave.com/zZudQGXkooi2TTAbJbcbpLfn")
    //        .load("https://rewards.brave.com/zZudQGXkooi2TTAbJbcbpLfn")

    private void background() {
        // ImageView iv = (ImageView) findViewById(R.id.top_tipping_banner_ui_background_scenery);
        // Glide.with(this)
        //         .load("https://rails/active_storage/disk/eyJfcmFpbHMiOnsibWVzc2FnZSI6IkJBaDdDRG9JYTJWNVNTSWRlbHAxWkZGSFdHdHZiMmt5VkZSQllrcGlZMkp3VEdadUJqb0dSVlE2RUdScGMzQnZjMmwwYVc5dVNTSUJybWx1YkdsdVpUc2dabWxzWlc1aGJXVTlJakpqWWpGa1pqaG1PRGhrT0RJME4yUTVaVGhrTWpjeE16Sm1NRGRoWkdGaVpqSXdOR0kxTVRGaE5XRXhaVFEzTmpBNVlUQmxNakZsTVRJek5HUmpZMlV1YW5Cbklqc2dabWxzWlc1aGJXVXFQVlZVUmkwNEp5Y3lZMkl4WkdZNFpqZzRaRGd5TkRka09XVTRaREkzTVRNeVpqQTNZV1JoWW1ZeU1EUmlOVEV4WVRWaE1XVTBOell3T1dFd1pUSXhaVEV5TXpSa1kyTmxMbXB3WndZN0JsUTZFV052Ym5SbGJuUmZkSGx3WlVraUQybHRZV2RsTDJwd1pXY0dPd1pVIiwiZXhwIjoiMjAyMC0wNS0xOVQwMTo1Mzo1Ni41ODlaIiwicHVyIjoiYmxvYl9rZXkifX0=--d63240300981a36aca542d4f725b026835bbea02/2cb1df8f88d8247d9e8d27132f07adabf204b511a5a1e47609a0e21e1234dcce.jpg?content_type=image%2Fjpeg&disposition=inline%3B+filename%3D%222cb1df8f88d8247d9e8d27132f07adabf204b511a5a1e47609a0e21e1234dcce.jpg%22%3B+filename%2A%3DUTF-8%27%272cb1df8f88d8247d9e8d27132f07adabf204b511a5a1e47609a0e21e1234dcce.jpg")
        //         .into(iv);
    }

    @Override
    public boolean shouldStartGpuProcess() {
        return true;
    }

    @Override
    public void onLargeIconReady(Bitmap icon) {
        SetFavIcon(icon);
    }

    private void SetFavIcon(Bitmap bmp) {
        if (bmp != null) {
            int nPx = BraveRewardsHelper.dp2px(PUBLISHER_ICON_SIDE_LEN);
            Bitmap resized = Bitmap.createScaledBitmap(bmp, nPx, nPx, true);
            runOnUiThread(() -> {
                ImageView iv = (ImageView) findViewById(R.id.publisher_favicon);
                // View fadeout = findViewById(R.id.publisher_favicon_update);
                // BraveRewardsHelper.crossfade(
                //         fadeout, iv, View.GONE, 1f, BraveRewardsHelper.CROSS_FADE_DURATION);
                iv.setImageBitmap(BraveRewardsHelper.getCircularBitmap(resized));
            });
        }
    }

    @Override
    public void onPublisherBanner(String jsonBannerInfo) {
        Log.e(TAG, "BraveRewardsSiteBannerActivity:jsonBannerInfo jsonBannerInfo" + jsonBannerInfo);
        // ((TextView) findViewById(R.id.tipping_details_description)).setText(jsonBannerInfo);
        try {
            mBannerInfo = new BraveRewardsBannerInfo(jsonBannerInfo);
            setTitle();
        } catch (JSONException e) {
            Log.e(TAG, "TippingBanner -> CreatorPanel:onAttach JSONException error " + e);
        }
    }

    private void setTitle() {
        if (mBannerInfo == null) return;
        String title = mBannerInfo.getName();
        if (title != null && !title.isEmpty()) {
            TextView titleTextView = findViewById(R.id.tipping_publisher_name);
            titleTextView.setText(title);
        }
    }

    @Override
    public void finishNativeInitialization() {
        super.finishNativeInitialization();
        Log.e(TAG, "BraveRewardsSiteBannerActivity:triggerLayoutInflation");

        mBraveRewardsNativeWorker = BraveRewardsNativeWorker.getInstance();
        mBraveRewardsNativeWorker.AddObserver(this);
        mBraveRewardsNativeWorker.GetPublisherBanner(
                mBraveRewardsNativeWorker.GetPublisherId(currentTabId_));
        background();
        retriveFavIcon();
    }

    private void showCustomUI() {
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN);
    }

    public void sendTipButtonClick() {
        View sendTipButton = findViewById(R.id.send_tip_button);
        sendTipButton.setOnClickListener(
                (v) -> { RewardsTippingPanelFragment.showTippingPanelBottomSheet(this); });
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (mIconFetcher != null) {
            mIconFetcher.detach();
        }

        if (null != mBraveRewardsNativeWorker) {
            mBraveRewardsNativeWorker.RemoveObserver(this);
        }
    }
}