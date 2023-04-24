// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'
import styled, { css } from 'styled-components'
import PrivateWindow from '../assets/private_window.jpg'

interface BoxProps {
  isTor?: boolean
}

const Box = styled.div<BoxProps>`
  background-repeat: no-repeat;
  background-size: 100% 100%!important;
  background-image: url("${PrivateWindow}")!important;

  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: column;
  font-family: ${p => p.theme.fontFamily.heading};
  font-weight: 400;
  color: white;
  width: 100%;
  height: 100%;
  min-height: 100vh;
  background: var(--bg-gr);
  position: relative;

  ${p => p.isTor && css`
    --bg-gr: linear-gradient(180deg, #0C041E -9.18%, #5F0D89 98.85%);
  `}
`



interface Props {
  children: React.ReactNode | React.ReactNode[]
  isTor?: boolean
}

function BackgroundView (props: Props) {
  return (
    <Box isTor={props.isTor}>
      {props.children}
    </Box>
  )
}

export default BackgroundView
