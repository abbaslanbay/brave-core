/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import customize from './minegoAssets/customize.svg'
export default class CustomizeIcon extends React.PureComponent {
  render () {
    return (
      <img 
      src={customize}
      width={'30px'}
      height={'30px'}
      />
    )
  }
}
