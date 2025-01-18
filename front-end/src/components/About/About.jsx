import React from 'react'
import './About.css'
import about_img from '../../assets/about.png'
import play_icon from '../../assets/play-icon.png'

const About = () => {
  return (
    <div className='about'>
        <div className='about-left'>
            <img src={about_img} alt="" className='about-img'/>
            <img src={play_icon} alt="" className='play-icon'/>
        </div>
        <div className='about-right'>
            <h3>ABOUT US</h3>
            <h2>Just Three Students Building a Project</h2>
            <p>Lorem ipsum odor amet, consectetuer adipiscing elit. Nulla faucibus netus non platea dignissim porta. Elementum nunc augue per non nunc. Fermentum fermentum class erat odio aptent congue sociosqu. Congue proin quis inceptos velit nec senectus ornare tempor. Viverra mi enim non vehicula a sem. Tempus sapien volutpat interdum aliquet viverra taciti ultricies inceptos. Iaculis natoque quis pulvinar volutpat magna eros. Ad varius class natoque aenean egestas montes habitasse aliquam montes.</p>
            <p>Lorem ipsum odor amet, consectetuer adipiscing elit. Nulla faucibus netus non platea dignissim porta. Elementum nunc augue per non nunc. Fermentum fermentum class erat odio aptent congue sociosqu. Congue proin quis inceptos velit nec senectus ornare tempor. Viverra mi enim non vehicula a sem. Tempus sapien volutpat interdum aliquet viverra taciti ultricies inceptos. Iaculis natoque quis pulvinar volutpat magna eros. Ad varius class natoque aenean egestas montes habitasse aliquam montes.</p>
        </div>
    </div>
  )
}

export default About