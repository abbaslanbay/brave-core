// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

import {
  StyledSearchPromotionWrapper,
  StyledSearchPromotion,

} from './style'
import SearchBox from './searchBox'


interface Props {
  textDirection: string
  onClose: () => void
  onDismiss: () => void
  onTryBraveSearch: (input: string, openNewTab: boolean) => void
}

export default class SearchPromotion extends React.PureComponent<Props, {}> {
  searchPromotionRef: React.RefObject<any>
  constructor (props: Props) {
    super(props)
    this.searchPromotionRef = React.createRef()
  }

  componentDidMount () {
    document.addEventListener('mousedown', this.handleClickOutside)
    document.addEventListener('keydown', this.onKeyPressSettings)
  }

  componentWillUnmount () {
    document.removeEventListener('mousedown', this.handleClickOutside)
    document.removeEventListener('keydown', this.onKeyPressSettings)
  }

  onKeyPressSettings = (event: KeyboardEvent) => {
    if (event.key === 'Escape') {
      this.props.onClose()
    }
  }

  handleClickOutside = (event: Event) => {
    // Close promotion when user clicks outside of promotion UI.
    if (
      this.searchPromotionRef &&
      this.searchPromotionRef.current &&
      !this.searchPromotionRef.current.contains(event.target)
    ) {
      this.props.onClose()
    }
  }

  render () {
    return (
      <StyledSearchPromotionWrapper>
        <StyledSearchPromotion
          ref={this.searchPromotionRef}
        >
          <SearchBox onSubmit={this.props.onTryBraveSearch} />
        </StyledSearchPromotion>
      </StyledSearchPromotionWrapper>
    )
  }
}
