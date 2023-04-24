import './addModal.css'

import plus from './assets/plus.svg'
import exit from './assets/exit.svg'
import { useState } from 'react'
import {suggestions, sites} from './data.js'
import {
  StyledDialogAdd
} from './style'
  export default function AddModal(){
  const [mode, setMode] = useState(true)
  const [inputValue, setInputValue] = useState('')
  const [newSites, setNewSites] = useState(sites)
  const [newSuggestions, setNewSuggestions] = useState(suggestions)
  const [filteredSites, setFilteredSites] = useState(sites)
  const [filteredSuggestions, setFilteredSuggestions] = useState(suggestions)

  const inputSearch = (e) => {
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

  return (
    <StyledDialogAdd>

    <div
      className='modalMain'
      style={{
        color: mode ? 'white' : 'black',
        backgroundColor: mode ? '#202124' : '#D4D8DB',
      }}
    >
      <div
        className='modalHeaderBg'
        style={{ backgroundColor: mode ? '#35363A' : '#FFFFFF' }}
      >
        <div className='modalHeaderFlex'>
          <div
            className='modalHeaderIcon'
            style={{
              backgroundColor: mode ? '#202124' : 'RGBA(0, 0, 0, 0.15)',
            }}
          >
            <img src={plus} alt='add' />
          </div>
          <span className='modalHeaderText'>Add more</span>
        </div>
        <div style={{ marginRight: '20px' }}>
          <button className='modalHeaderButton'>
            <img src={exit} width='20px' alt='exit' />
          </button>
        </div>
      </div>

      <div className='modalContentBg'>
        <div className='inputButtonFlex'>
          <div className='inputButtonDiv'>
            <input
              onChange={(e) => inputSearch(e)}
              className='modalInput'
              style={{
                backgroundColor: mode ? '#2B2B2B' : '#FFFFFF',
                color: mode ? 'white' : 'black',
              }}
              type='text'
              placeholder='Bir web sitesi adresi yazın'
            />
            <button className='modalButton'>Add</button>
          </div>
        </div>

        <div className='sitesMainDiv'>
          <div className='sitesDiv'>
            <span className='modalContentHeaderText'>Sites</span>
            <div className='sitesBoxDiv row'>
              {filteredSites?.length > 0 ? (
                filteredSites.map((item) => {
                  return (
                    <div
                      className='sitesBox col-12 col-sm-2'
                      style={{
                        backgroundColor: mode
                          ? 'RGB(19, 20, 21)'
                          : 'RGBA(0, 0, 0, 0.15)',
                      }}
                    >
                      <img
                        src={item.icon}
                        width={item.width ? item.width : '40px'}
                        alt='icon'
                      />

                      <span style={{ marginTop: '5px' }}>{item.name}</span>
                    </div>
                  )
                })
              ) : (
                <span style={{ color: mode ? 'white' : 'black' }}>
                  Sites not found.
                </span>
              )}
            </div>
          </div>
          <div className='suggestionsDiv'>
            <span className='modalContentHeaderText'>Suggestions</span>
            <div className='suggestionsBoxDiv row'>
              {filteredSuggestions?.length > 0 ? (
                filteredSuggestions.map((item) => {
                  return (
                    <div
                      className='suggestionsBox col-12 col-sm-2'
                      style={{
                        backgroundColor: mode
                          ? 'RGB(19, 20, 21)'
                          : 'RGBA(0, 0, 0, 0.15)',
                      }}
                    >
                      <img src={item.icon} alt='icon' />
                      <span style={{ marginTop: '5px' }}>{item.name}</span>
                    </div>
                  )
                })
              ) : (
                <span style={{ color: mode ? 'white' : 'black' }}>
                  Suggestions not found.
                </span>
              )}
            </div>
          </div>
        </div>
      </div>
    </div>
    </StyledDialogAdd>

  )
}
