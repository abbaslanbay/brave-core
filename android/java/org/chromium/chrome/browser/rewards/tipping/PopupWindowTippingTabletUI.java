/**
 * Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.rewards.tipping;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.text.method.ScrollingMovementMethod;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.TextView;

import androidx.annotation.NonNull;

import org.chromium.chrome.R;

public class PopupWindowTippingTabletUI {
    private PopupWindow mPopupWindow;

    public PopupWindowTippingTabletUI(@NonNull Context context) {
        init(context);
    }
    private void init(@NonNull Context context) {
        LayoutInflater inflater =
                (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View contentView = inflater.inflate(R.layout.activity_tipping_banner_tablet, null, false);
        ((TextView) contentView.findViewById(R.id.tipping_details_description))
                .setMovementMethod(new ScrollingMovementMethod());

        mPopupWindow = new PopupWindow(context, null, android.R.attr.popupWindowStyle);
        mPopupWindow.setTouchable(true);
        mPopupWindow.setFocusable(true);
        mPopupWindow.setWidth(LinearLayout.LayoutParams.WRAP_CONTENT);
        mPopupWindow.setHeight(LinearLayout.LayoutParams.WRAP_CONTENT);
        mPopupWindow.setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        mPopupWindow.setContentView(contentView);
        mPopupWindow.setTouchInterceptor(new View.OnTouchListener() {
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_OUTSIDE) {
                    mPopupWindow.dismiss();
                    return true;
                }
                return false;
            }
        });

        mPopupWindow.setOnDismissListener(new PopupWindow.OnDismissListener() {
            @Override
            public void onDismiss() {
                mPopupWindow.dismiss();
            }
        });
    }

    public void show(@NonNull View anchorView, int xLocation, int yLocation) {
        mPopupWindow.showAtLocation(anchorView, Gravity.NO_GRAVITY, xLocation, yLocation);
    }
}
