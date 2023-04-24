// Copyright (c) 2021 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

import { getLocale } from '../../../../common/locale'

import {
  CloseButton,
  StyledDialogWrapper,
  StyledDialog,
  DialogTitle,
  StyledInputLabel,
  StyledInput,
  StyledButtonsContainer,
  StyledButton,
  StyledDialogAdd,
  StyledModalMain,
  StyledModalHeader,
  StyledModalHeaderFlex,
  StyledModalHeaderIcon,
  StyledModalHeaderText,
  StyledModalHeaderButton,
  StyledModalContentBg,
  StyledModalInputButtonFlex,
  StyledModalInputButtonDiv,
  StyledModalInput,
  StyledModalInputButton,
  StyledModalSitesMainDiv,
  StyledModalSitesDiv,
  StyledModalContentHeaderText,
  StyledModalContentSitesBoxDiv,
  StyledModalContentSitesBox,
  StyledModalContentSitesBoxSpan,
  StyledModalContentSitesBoxNotFound,
  StyledModalSuggestionDiv,
  StyledModalSuggestionDivSpan,
  StyledModalSuggestionBoxDiv,
  StyledModalSuggestionBox
} from './style'
import CloseIcon from './assets/close-icon'
import './addModal.css'

import plus from './assets/plus.svg'
import exit from './assets/exit.svg'
import {suggestions, sites} from './data.js'
import { useCallback, useEffect, useState, useRef } from 'react'

interface Props {
  targetTopSiteForEditing?: NewTab.Site
  textDirection: string
  onClose: () => void
  onSave: (title: string, url: string, newUrl: string) => void
}

export default function EditTopSite ({ targetTopSiteForEditing, textDirection, onClose, onSave }: Props) {
  const dialogRef = useRef<HTMLDivElement>(null)
  const [title, setTitle] = useState(targetTopSiteForEditing?.title ?? '')
  const [url, setUrl] = useState(targetTopSiteForEditing?.url ?? '')
  const [inputValue, setInputValue] = useState('')
  const [newSites, setNewSites] = useState(sites)
  const [newSuggestions, setNewSuggestions] = useState(suggestions)
  const [filteredSites, setFilteredSites] = useState(sites)
  const [filteredSuggestions, setFilteredSuggestions] = useState(suggestions)


  useEffect(() => {
    changeUpdate()
  },[])


const changeUpdate =() => {
  setNewSites(sites)
  setNewSuggestions(suggestions)
}
  const inputSearch = (e: React.ChangeEvent<HTMLInputElement>) => {
    const val = e.target.value.toLowerCase()
    setInputValue(val)
    if (val.length === 0) {
      setFilteredSites(sites)
      setFilteredSuggestions(suggestions)
      return
    }
    let filteredSites = newSites.filter((site) =>
      site.key.toLowerCase().includes(inputValue)
    )
    let filteredSites2 = newSuggestions.filter((site) =>
      site.key.toLowerCase().includes(inputValue)
    )
    setFilteredSites(filteredSites)
    setFilteredSuggestions(filteredSites2)
  }
  const saveTopSite = useCallback(() => {
    if (!url) return
    onSave(title, targetTopSiteForEditing?.url ?? '', url)
  }, [url, title, targetTopSiteForEditing])




  useEffect(() => {
    const handleKeyPress = (e: KeyboardEvent) => {
      if (e.key === 'Escape') onClose()
      if (e.key === 'Enter') saveTopSite()
    }

    const handleClickOutside = (e: Event) => {
      if (dialogRef.current && !dialogRef.current.contains(e.target as Node)) {
        onClose()
      }
    }

    document.addEventListener('keydown', handleKeyPress)
    document.addEventListener('mousedown', handleClickOutside)

    return () => {
      document.removeEventListener('keydown', handleKeyPress)
      document.removeEventListener('mousedown', handleClickOutside)
    }
  }, [saveTopSite, onClose])

  const addNewSite = () => {

    // check if input is empty
    if (inputValue === '') {
      return
    }
    // check inputValue is valid url
    if (!inputValue.includes('.')) {
      return
    }
    let domain = (new URL(inputValue));
    if(domain){
       let host = domain.hostname.replace('www.','');
        // parse after .
      let domainName = host.split('.').pop();
      let domainName2 = host.replace('.'+domainName,'');
      onSave(domainName2, inputValue, inputValue)
      return
    }
   
  }

  return <StyledDialogWrapper textDirection={textDirection}>
    {targetTopSiteForEditing?.url ?
    <StyledDialog
      ref={dialogRef}
      textDirection={textDirection}>
      <DialogTitle>
        {targetTopSiteForEditing
          ? getLocale('editTopSiteDialogTitle')
          : getLocale('addTopSiteDialogTitle')}
      </DialogTitle>
      <CloseButton onClick={onClose}>
        <CloseIcon />
      </CloseButton>
      <StyledInputLabel>
        {getLocale('addTopSiteDialogNameLabel')}
      </StyledInputLabel>
      <StyledInput
        autoFocus={true}
        type='text'
        value={title}
        onChange={e => setTitle(e.target.value)}
        placeholder={getLocale('addTopSiteDialogNameInputPlaceHolder')} />
      <StyledInputLabel>
        {getLocale('addTopSiteDialogURLLabel')}
      </StyledInputLabel>
      <StyledInput
        type='url'
        value={url}
        onChange={e => setUrl(e.target.value)}
        placeholder={getLocale('addTopSiteDialogURLInputPlaceHolder')} />
      <StyledButtonsContainer>
        <StyledButton
          text={getLocale('addTopSiteDialogCancelButtonLabel')}
          level={'secondary'}
          size={'small'}
          onClick={onClose} />
        <StyledButton
          text={getLocale('addTopSiteDialogSaveButtonLabel')}
          level={'primary'}
          type={'accent'}
          size={'small'}
          disabled={!url}
          onClick={saveTopSite} />
      </StyledButtonsContainer>
    </StyledDialog>
    :
    <StyledDialogAdd ref={dialogRef}
    textDirection={textDirection}>

  <StyledModalMain>
      <StyledModalHeader>
        <StyledModalHeaderFlex>
          <StyledModalHeaderIcon>
            <img src={plus} alt='add' />
          </StyledModalHeaderIcon>
          <StyledModalHeaderText>
          Add more
          </StyledModalHeaderText>
        </StyledModalHeaderFlex>
          <StyledModalHeaderButton className='modalHeaderButton' onClick={onClose}>
            <img src={exit} width='20px' alt='exit' />
          </StyledModalHeaderButton>
      </StyledModalHeader>

      <StyledModalContentBg>
        <StyledModalInputButtonFlex >
          <StyledModalInputButtonDiv>
            <StyledModalInput
              onChange={(e) => inputSearch(e)}
              type='text'
              placeholder='Search or enter address'
            />
            <StyledModalInputButton
            onClick={() => {
             addNewSite()
            }}
            >Add</StyledModalInputButton>
          </StyledModalInputButtonDiv>
        </StyledModalInputButtonFlex>

        <StyledModalSitesMainDiv >
          <StyledModalSitesDiv>
            <StyledModalContentHeaderText >Sites</StyledModalContentHeaderText>
            <StyledModalContentSitesBoxDiv >
              {filteredSites?.length > 0 ? (
                filteredSites.map((item,index) => {
                  return (
                    <StyledModalContentSitesBox
                    key={index}
                      onClick={() => {
                        onSave(item.title, item.url, item.url)
                        onClose()
                      }}
                    >
                      <img
                        src={item.icon}
                        width={item.width ? item.width : '40px'}
                        alt='icon'
                      />

                      <StyledModalContentSitesBoxSpan>{item.title}</StyledModalContentSitesBoxSpan>
                    </StyledModalContentSitesBox>
                  )
                })
              ) : (
                <StyledModalContentSitesBoxNotFound>
                  Sites not found.
                </StyledModalContentSitesBoxNotFound>
              )}
            </StyledModalContentSitesBoxDiv>
          </StyledModalSitesDiv>
          <StyledModalSuggestionDiv >
            <StyledModalSuggestionDivSpan>Suggestions</StyledModalSuggestionDivSpan>
            <StyledModalSuggestionBoxDiv>
              {filteredSuggestions?.length > 0 ? (
                filteredSuggestions.map((item,index) => {
                  return (
                    <StyledModalSuggestionBox key={index}
                    onClick={() => {
                      onSave(item.title, item.url, item.url)
                      onClose()
                    }}
                    >
                      <img src={item.icon} alt='icon' />
                      <StyledModalContentSitesBoxSpan>{item.title}</StyledModalContentSitesBoxSpan>
                    </StyledModalSuggestionBox>
                  )
                })
              ) : (
                <StyledModalContentSitesBoxNotFound>
                  Suggestions not found.
                </StyledModalContentSitesBoxNotFound>
              )}
            </StyledModalSuggestionBoxDiv>
          </StyledModalSuggestionDiv>
        </StyledModalSitesMainDiv>
      </StyledModalContentBg>
    </StyledModalMain>
    </StyledDialogAdd>
}
  </StyledDialogWrapper>
}
