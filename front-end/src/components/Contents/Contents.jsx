import React from 'react'
import './Contents.css'
import content_1 from '../../assets/content-1.jpg'
import content_2 from '../../assets/content-2.png'
import content_3 from '../../assets/content-3.jpg'
import content_icon_1 from '../../assets/content-1-icon.png'
import content_icon_2 from '../../assets/content-2-icon.png'
import content_icon_3 from '../../assets/content-3-icon.png'

const Contents = () => {
  return (
    <div className='contents'>
        <div className="content">
            <img src={content_1} alt="" />
            <div className="caption">
                <img src={content_icon_1} alt="" />
                <p>Live Streaming</p>
            </div>
        </div>
        <div className="content">
            <img src={content_2} alt="" />
            <div className="caption">
                <img src={content_icon_2} alt="" />
                <p>Past Videos</p>
            </div>
        </div>
        <div className="content">
            <img src={content_3} alt="" />
            <div className="caption">
                <img src={content_icon_3} alt="" />
                <p>Secure & Private </p>
            </div>
        </div>
    </div>
  )
}

export default Contents