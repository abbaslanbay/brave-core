// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'
import styled from 'styled-components'
import { getLocale } from '$web-common/locale'
import minegoLogo from '../assets/minego_logo.svg'

const Box = styled.div`
  display: flex;
  justify-content: center;
  flex-direction: column;
  align-items: center;
  gap: 40px;
  width: 100%;
`

const Form = styled.form`
  --bg-color: rgba(255, 255, 255, 0.22);
  --box-shadow: 0px 2px 70px rgba(0, 0, 0, 0.3);

  display: grid;
  grid-template-columns: 1fr 50px;
  align-items: center;
  width: 100%;
  height: 52px;
  font-family: ${p => p.theme.fontFamily.heading};
  color: white;
  font-size: 14px;
  font-weight: 400;
  background: var(--bg-color);
  border-radius: 8px;
  transition: box-shadow 0.3s ease-in-out;
  overflow: hidden;

  &:focus-within,
  &:hover {
    box-shadow: var(--box-shadow);
  }

  input[type="text"] {
    width: 100%;
    height: 36px;
    border: 0;
    background-color: transparent;
    padding: 5px 16px;

    &:focus {
      outline: 0;
    }

    &::placeholder {
      color: rgba(255,255,255,0.7);
    }
  }
`

const IconButton = styled.button`
background: transparent;
padding: 0;
margin: 0;
border: 0;
width: 100%;
height: 100%;
cursor: pointer;

&:hover {
  background: linear-gradient(304.74deg,#ffffff 15.81%,#adadad 63.17%,#737373 100%)

  path {
    fill: white;
  }
}
`

function MinegoSearchLogo () {
  return (
    <img src={minegoLogo} width="40%" />
  
  )
}

interface Props {
  onSubmit?: (value: string, openNewTab: boolean) => unknown
}

function Search (props: Props) {
  const [value, setValue] = React.useState('')
  const inputRef = React.useRef<HTMLInputElement>(null)

  const onInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setValue(e.currentTarget.value)
  }

  const handleFormBoxClick = () => {
    inputRef.current && inputRef.current.focus()
  }

  const handleSubmit = (e: React.ChangeEvent<HTMLFormElement>) => {
    e.preventDefault()
    props.onSubmit?.(value, false)
  }

  const handleKeyDown = (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (value === '') return

    if ((e.metaKey || e.ctrlKey) && (e.key === 'Enter')) {
      props.onSubmit?.(value, true)
    }
  }

  return (
    <Box>
      <MinegoSearchLogo />
      <Form onSubmit={handleSubmit} onClick={handleFormBoxClick} role="search" aria-label="Brave">
        <input ref={inputRef} onChange={onInputChange} onKeyDown={handleKeyDown} type="text" placeholder={getLocale('searchPlaceholderLabel')} value={value} autoCapitalize="off" autoComplete="off" autoCorrect="off" spellCheck="false" aria-label="Search" title="Search" aria-autocomplete="none" aria-haspopup="false" maxLength={2048} autoFocus />
        <IconButton data-test-id="submit_button" aria-label="Submit">
        <svg version="1.1" width="20px" height="20px" viewBox="0 0 20.0 20.0" xmlns="http://www.w3.org/2000/svg"><defs><clipPath id="i0"><path d="M1280,0 L1280,957 L0,957 L0,0 L1280,0 Z"></path></clipPath><clipPath id="i1"><path d="M1.7456619,3.5097853 C4.64234068,-0.361187009 10.1286352,-1.15101689 13.9996075,1.7456619 C17.8705798,4.64234068 18.6604097,10.1286352 15.7637309,13.9996075 L19.6350147,17.8725264 C20.1216748,18.3608606 20.1216748,19.1499508 19.6349757,19.6366498 C19.1483156,20.1233489 18.3592255,20.1233489 17.8725264,19.6366498 L13.9996075,15.7637309 C10.890083,18.0905891 6.61927081,18.0905891 3.5097853,15.7637309 C-0.361187009,12.8670521 -1.15101689,7.3807576 1.7456619,3.5097853 Z M8.78697169,2.55772241 C5.34663518,2.55772241 2.55772241,5.34663518 2.55772241,8.78697169 C2.55772241,12.2273082 5.34663518,15.016221 8.78697169,15.016221 C12.2257898,15.0125613 15.0125613,12.2257509 15.016221,8.78697169 C15.016221,5.34663518 12.2273082,2.55772241 8.78697169,2.55772241 Z"></path></clipPath><linearGradient id="i2" x1="-1.31156942e-15px" y1="10.0008371px" x2="20px" y2="10.0008371px" gradientUnits="userSpaceOnUse"><stop stop-color="#9725FF" offset="0%"></stop><stop stop-color="#3F1BFF" offset="100%"></stop></linearGradient></defs><g transform="translate(-221.0 -394.0)"><g clip-path="url(#i0)"><g transform="translate(208.0 382.0)"><g transform="translate(13.0 11.99999999999971)"><g clip-path="url(#i1)"><polygon points="-2.22044605e-16,0 20,0 20,20.0016741 -2.22044605e-16,20.0016741 -2.22044605e-16,0" stroke="none" fill="url(#i2)"></polygon></g></g></g></g></g></svg>
        </IconButton>
      </Form>
    </Box>
  )
}

export default Search
