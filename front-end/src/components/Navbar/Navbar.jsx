import React, { useEffect, useState } from "react";
import { Link } from "react-router-dom";
import "./Navbar.css";
import logo from "../../assets/logo.png";
import PropTypes from "prop-types";

//classType 0 => stays transparent first, then purple, anything else purple all the time
const Navbar = ({ classType }) => {
  const [sticky, setSticky] = useState(false);

  useEffect(() => {
    window.addEventListener("scroll", () => {
      window.scrollY > 700 ? setSticky(true) : setSticky(false);
    });
  }, []);

  return (
    <nav
      className={`container ${
        classType === 0 ? (sticky ? "dark-nav" : "") : "dark-nav"
      }`}
    >
      <img src={logo} alt="" className="logo" />
      <ul>
        <li>
          <Link to="/">Home</Link>
        </li>
        <li>
          <Link to="/about-us">About Us</Link>
        </li>
        <li>
          <Link to="/video">Live Video</Link>
        </li>
        <li>
          <button className="button">Contact Us</button>
        </li>
      </ul>
    </nav>
  );
};

Navbar.propTypes = {
  classType: PropTypes.number.isRequired,
};

export default Navbar;
