import React from 'react'
import Navbar from './components/navbar/Navbar'
import Page from './components/Page/Page'
import Contents from './components/Contents/Contents'
import Title from './components/Title/Title'
import About from './components/About/About'

const App = () => {
  return (
    <div>
        <Navbar/>
        <Page/>
        <div className="container">
          <Title subTitle='Our Videos' title='What We Offer'/>
          <Contents/>
          <About/>
        </div>
    </div>
  )
}

export default App