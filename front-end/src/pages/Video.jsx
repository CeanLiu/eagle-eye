import React from "react";
import Navbar from "../components/navbar/Navbar";
import Page from "../components/Page/Page";
import Contents from "../components/Contents/Contents";
import Title from "../components/Title/Title";
import About from "../components/About/About";

const Video = () => {
  return (
    <div>
      <Navbar className={1} />
      <Page />
      <div className="container">
        <Title subTitle="WO CAO NI MA" title="What We Offer" />
        <Contents />
        <About />
      </div>
    </div>
  );
};

export default Video;
