// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {RegisterStyleOverride, RegisterPolymerTemplateModifications} from 'chrome://resources/brave/polymer_overriding.js'
import {html} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'

const secretPath = 'chrome://' + 'resources/brave/leo/web-components/button.js';
import(secretPath)

RegisterStyleOverride(
  'downloads-item',
  html`
    <style>
      #progress {
        --paper-progress-active-color: var(--leo-color-icon-interactive) !important;
      }
    </style>
  `
)

RegisterPolymerTemplateModifications({
  'downloads-item': templateContent => {
    const controls = templateContent.querySelector('.controls')
    const button = document.createElement('leo-button')
    button.classList.add('action-button')
    button.setAttribute('on-click', 'onRetryTap_')
    button.setAttribute('focus-type', 'retry')
    button.setAttribute('focus-row-control', '')
    button.textContent = "Retry";
    button.setAttribute('size', 'small')
    controls.appendChild(button)
  }
})
