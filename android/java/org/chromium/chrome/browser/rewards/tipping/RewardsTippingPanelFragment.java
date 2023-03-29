/**
 * Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.rewards.tipping;

import android.annotation.SuppressLint;
import android.app.Dialog;
import android.os.Bundle;
import android.text.Editable;
import android.text.InputType;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.google.android.material.bottomsheet.BottomSheetDialogFragment;

import org.chromium.base.Log;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.BraveRewardsBalance;
import org.chromium.chrome.browser.BraveRewardsHelper;
import org.chromium.chrome.browser.BraveRewardsNativeWorker;
import org.chromium.chrome.browser.BraveRewardsObserver;
import org.chromium.chrome.browser.BraveWalletProvider;

import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.Locale;

public class RewardsTippingPanelFragment
        extends BottomSheetDialogFragment implements BraveRewardsObserver {
    final public static String TAG_FRAGMENT = "tipping_panel_tag";
    private static final String TAG = "TippingPanelFragment";
    private BraveRewardsNativeWorker mBraveRewardsNativeWorker;
    private String walletType = BraveRewardsNativeWorker.getInstance().getExternalWalletType();

    private TextView radio_tip_amount[] = new TextView[4];
    private double[] mTipChoices;
    private TextView currency1TextView;
    private TextView currency2TextView;
    private EditText currency1ValueEditTextView;
    private TextView currency1ValueTextView;
    private TextView currency2ValueTextView;
    boolean toggle = true;
    public static final double AMOUNT_STEP_BY = 0.25;
    public static final int MAX_BAT_VALUE = 100;

    private static final int DEFAULT_VALUE_OPTION_1 = 1;
    private static final int DEFAULT_VALUE_OPTION_2 = 5;
    private static final int DEFAULT_VALUE_OPTION_3 = 10;

    public static RewardsTippingPanelFragment newInstance() {
        return new RewardsTippingPanelFragment();
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setStyle(STYLE_NORMAL, R.style.AppBottomSheetDialogTheme);
        init();
    }

    private void init() {
        mBraveRewardsNativeWorker = BraveRewardsNativeWorker.getInstance();
        mBraveRewardsNativeWorker.AddObserver(this);
    }

    @Override
    public void show(@NonNull FragmentManager manager, @Nullable String tag) {
        try {
            RewardsTippingPanelFragment fragment =
                    (RewardsTippingPanelFragment) manager.findFragmentByTag(
                            RewardsTippingPanelFragment.TAG_FRAGMENT);
            FragmentTransaction transaction = manager.beginTransaction();
            if (fragment != null) {
                transaction.remove(fragment);
            }
            transaction.add(this, tag);
            transaction.commitAllowingStateLoss();
        } catch (IllegalStateException e) {
            Log.e(TAG, e.getMessage());
        }
    }

    @SuppressLint("RestrictedApi")
    @Override
    public void setupDialog(@NonNull Dialog dialog, int style) {
        super.setupDialog(dialog, style);
        final View view = LayoutInflater.from(getContext())
                                  .inflate(R.layout.brave_rewards_tippingpanel_fragment, null);
        dialog.setContentView(view);
        init(view);
        initTipChoice(toggle);
        setBalanceText(view);
        sendTipButtonClick(view);
        exchangeButtonClick(view);
        setCustodianIconAndName(view);
    }

    private void sendTipButtonClick(View view) {
        Button sendButton = view.findViewById(R.id.send_tip_button);
        sendButton.setOnClickListener(v -> { double amount = selectedAmount(); });
    }

    private void exchangeButtonClick(View view) {
        View exchangeButton = view.findViewById(R.id.exchange_shape);
        exchangeButton.setOnClickListener((v) -> {
            toggle = !toggle;
            currency1ValueEditTextView.setText(currency2ValueTextView.getText());
            currency1ValueTextView.setText(currency2ValueTextView.getText());

            initTipChoice(toggle);
        });
    }

    double rate;
    boolean mIsBatCurrency;

    private TextWatcher textChangeListener = new TextWatcher() {
        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) {}

        @SuppressLint("SetTextI18n")
        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count) {
            if (TextUtils.isEmpty(s)) s = "0";
            Double batValue = getBatValue(s.toString(), mIsBatCurrency);
            Double usdValue = rate * batValue;

            if (mIsBatCurrency) {
                currency2ValueTextView.setText(String.valueOf(roundExchangeUp(usdValue)));
            } else {
                currency2ValueTextView.setText(String.valueOf(batValue));
            }
        }

        @Override
        public void afterTextChanged(Editable s) {}
    };

    private void init(View view) {
        currency1TextView = view.findViewById(R.id.currency1);
        currency2TextView = view.findViewById(R.id.currency2);
        currency1ValueEditTextView = view.findViewById(R.id.currencyOneEditText);
        currency1ValueTextView = view.findViewById(R.id.currencyOneEditText1);
        currency2ValueTextView = view.findViewById(R.id.exchange_amount1);
        currency1ValueEditTextView.addTextChangedListener(textChangeListener);
        rate = mBraveRewardsNativeWorker.GetWalletRate();
        radio_tip_amount[0] = view.findViewById(R.id.tipChoice1);
        radio_tip_amount[1] = view.findViewById(R.id.tipChoice2);
        radio_tip_amount[2] = view.findViewById(R.id.tipChoice3);
        radio_tip_amount[3] = view.findViewById(R.id.tipChoiceCustom);

        for (TextView tb : radio_tip_amount) {
            tb.setOnClickListener(radio_clicker);
        }
    }
    private static final double DEFAULT_AMOUNT = 0.0;

    void setBalanceText(View view) {
        double balance = DEFAULT_AMOUNT;
        BraveRewardsBalance rewards_balance = mBraveRewardsNativeWorker.GetWalletBalance();
        if (rewards_balance != null) {
            balance = rewards_balance.getTotal();
        }

        DecimalFormat df = new DecimalFormat("#.###");
        df.setRoundingMode(RoundingMode.FLOOR);
        df.setMinimumFractionDigits(3);
        String walletAmount = df.format(balance) + " " + BraveRewardsHelper.BAT_TEXT;

        ((TextView) view.findViewById(R.id.wallet_amount_text)).setText(walletAmount);
    }

    private void setCustodianIconAndName(View view) {
        int custodianIcon = R.drawable.ic_logo_bitflyer_colored;
        int custodianName = R.string.bitflyer;

        if (walletType.equals(BraveWalletProvider.UPHOLD)) {
            custodianIcon = R.drawable.uphold_green;
            custodianName = R.string.uphold;
        } else if (walletType.equals(BraveWalletProvider.GEMINI)) {
            custodianIcon = R.drawable.ic_gemini_logo_cyan;
            custodianName = R.string.gemini;
        }

        TextView custodian = view.findViewById(R.id.custodian_text);
        custodian.setText(custodianName);
        custodian.setCompoundDrawablesWithIntrinsicBounds(custodianIcon, 0, 0, 0);
    }

    private void initTipChoice(boolean isBat) {
        mTipChoices = mBraveRewardsNativeWorker.GetTipChoices();
        if (mTipChoices.length < 3) {
            // when native not giving tip choices initialize with default values
            mTipChoices = new double[3];
            mTipChoices[0] = DEFAULT_VALUE_OPTION_1;
            mTipChoices[1] = DEFAULT_VALUE_OPTION_2;
            mTipChoices[2] = DEFAULT_VALUE_OPTION_3;
        }

        double currencyRate = 1;
        mIsBatCurrency = isBat;
        String currency1 = currency1ValueEditTextView.getText().toString();

        Double batValue = getBatValue(currency1, isBat);

        Double usdValue = rate * batValue;

        if (isBat) {
            currencyRate = 1;
            currency1TextView.setText(R.string.bat);
            currency2TextView.setText(R.string.usd);
            currency1ValueEditTextView.setText(String.valueOf(batValue));
            currency1ValueTextView.setText(String.valueOf(batValue));
            currency2ValueTextView.setText(String.valueOf(roundExchangeUp(usdValue)));

        } else {
            currencyRate = rate;
            currency1TextView.setText(R.string.usd);
            currency2TextView.setText(R.string.bat);
            currency1ValueEditTextView.setText(String.valueOf(roundExchangeUp(usdValue)));
            currency1ValueTextView.setText(String.valueOf(roundExchangeUp(usdValue)));
            currency2ValueTextView.setText(String.valueOf(batValue));
        }
        mTipChoices[0] = mTipChoices[0] * currencyRate;
        mTipChoices[1] = mTipChoices[1] * currencyRate;
        mTipChoices[2] = mTipChoices[2] * currencyRate;
        for (int i = 0; i < 3; i++) {
            radio_tip_amount[i].setText(String.valueOf(roundExchangeUp(mTipChoices[i])));
        }
    }

    private View.OnClickListener radio_clicker = view -> {
        currency1ValueEditTextView.removeTextChangedListener(textChangeListener);

        TextView tb_pressed = (TextView) view;
        if (!tb_pressed.isSelected()) {
            tb_pressed.setSelected(true);
        }

        int id = view.getId();
        if (id == R.id.tipChoiceCustom) {
            currency1ValueEditTextView.requestFocus();
            currency1ValueTextView.setVisibility(View.INVISIBLE);
            currency1ValueEditTextView.setVisibility(View.VISIBLE);
        } else {
            currency1ValueTextView.setVisibility(View.VISIBLE);
            currency1ValueEditTextView.setVisibility(View.INVISIBLE);
            currency1ValueTextView.setInputType(InputType.TYPE_NULL);
            String s = ((TextView) view).getText().toString();
            currency1ValueTextView.setText(s);
            currency1ValueEditTextView.setText(s);
            Double batValue = getBatValue(s, mIsBatCurrency);

            Double usdValue = rate * batValue;
            if (mIsBatCurrency)
                currency2ValueTextView.setText(String.valueOf(roundExchangeUp(usdValue)));
            else
                currency2ValueTextView.setText(String.valueOf(roundExchangeUp(batValue)));
        }
        for (TextView tb : radio_tip_amount) {
            if (tb.getId() == id) {
                continue;
            }
            tb.setSelected(false);
        }
        currency1ValueEditTextView.addTextChangedListener(textChangeListener);
    };

    private double selectedAmount() {
        double amount = 0;
        for (TextView tb : radio_tip_amount) {
            if (tb.isSelected()) {
                int id = tb.getId();
                if (id == R.id.tipChoice1) {
                    amount = mTipChoices[0];
                } else if (id == R.id.tipChoice2) {
                    amount = mTipChoices[1];
                } else if (id == R.id.tipChoice3) {
                    amount = mTipChoices[2];
                }

                break;
            }
        }
        // // Selected amount from custom tip
        // BraveRewardsCustomTipConfirmationFragment customTipConfirmationFragment =
        //         (BraveRewardsCustomTipConfirmationFragment) getParentFragmentManager()
        //                 .findFragmentByTag(CUSTOM_TIP_CONFIRMATION_FRAGMENT_TAG);
        // if (customTipConfirmationFragment != null && customTipConfirmationFragment.isVisible()) {
        //     amount = mBatValue;
        // }

        return amount;
    }

    public static void showTippingPanelBottomSheet(AppCompatActivity activity) {
        if (activity != null) {
            RewardsTippingPanelFragment dialog = RewardsTippingPanelFragment.newInstance();
            dialog.show(activity.getSupportFragmentManager(), TAG_FRAGMENT);
        }
    }

    private double roundExchangeUp(double batValue) {
        return Math.ceil(batValue * 100) / 100;
    }

    /**
     * @param inputValue : editText string passed here
     * @return convert to bat value if current editText is USD
     * It will return multiple 0.25
     * And also return which is lower between Max and value
     * decimal points always roundedOff to floor value.
     */
    private double getBatValue(String inputValue, boolean isBatCurrencyMode) {
        double rawValue = 0;
        try {
            rawValue = Double.parseDouble(inputValue);
        } catch (NumberFormatException e) {
        }

        if (!isBatCurrencyMode) {
            // from USD to BAT
            rawValue = rawValue / rate;
        }

        // Round value with 2 decimal
        rawValue = Math.floor(rawValue / AMOUNT_STEP_BY) * AMOUNT_STEP_BY;

        // There is a limit
        return Math.min(MAX_BAT_VALUE, rawValue);
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        if (null != mBraveRewardsNativeWorker) {
            mBraveRewardsNativeWorker.RemoveObserver(this);
        }
    }
}
