// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

'use strict'

const config = require('../lib/config')

const envVars = new Set()
Object.keys(process.env).forEach((item) => envVars.add(item))
Object.keys(config.defaultOptions.env).forEach((item) => envVars.add(item))

for (let key of envVars) {
  if (process.env[key] !== config.defaultOptions.env[key]) {
    const val = config.defaultOptions.env[key] || ''
    process.stdout.write(`${key}=${val}\n`)
  }
}
