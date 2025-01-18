import React from 'react'
import './LiveVideo.css'
import gallery_1 from '../../assets/gallery-1.jpg'
import gallery_2 from '../../assets/gallery-2.jpg'
import gallery_3 from '../../assets/gallery-3.jpg'
import gallery_4 from '../../assets/gallery-4.jpg'
import white_arrow from '../../assets/white-arrow.png'

const LiveVideo = () => {
  return (
    <div className='live-video'>
        <div className='gallery'>
            <img src={gallery_1} alt="" />
            <img src={gallery_2} alt="" />
            <img src={gallery_3} alt="" />
            <img src={gallery_4} alt="" />
        </div>
        <button className="button dark-button">See More<img src={white_arrow} alt="" /></button>
    </div>
  )
}

export default LiveVideo