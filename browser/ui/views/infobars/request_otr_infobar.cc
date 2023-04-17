/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/views/infobars/request_otr_infobar.h"

#include <utility>

#include "build/build_config.h"
#include "ui/views/view.h"

RequestOTRInfoBar::RequestOTRInfoBar(
    std::unique_ptr<ConfirmInfoBarDelegate> delegate)
    : ConfirmInfoBar(std::move(delegate)) {
  DCHECK(
      !(GetDelegate()->GetButtons() & ConfirmInfoBarDelegate::BUTTON_CANCEL));
}

RequestOTRInfoBar::~RequestOTRInfoBar() {}
