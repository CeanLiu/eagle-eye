import React from 'react'
import './Page.css'
import dark_arrow from '../../assets/dark-arrow.png'


//change the description of the page later -- just a placeholder for now
const Page = () => {
  return (
    <div className="page container">
      <div className="page-text">
        <h1>Welcome to Eagle-Eye</h1>
        <p>Our camera captures and records videos seamlessly. Easily access previous content or view live from our website.</p>
        <button className="button">Explore More<img src = {dark_arrow} alt ="" /></button>
      </div>
    </div>
  )
}

export default Page
