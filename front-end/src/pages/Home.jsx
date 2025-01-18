import React from "react";
import Navbar from "../components/navbar/Navbar";
import Page from "../components/Page/Page";
import Contents from "../components/Contents/Contents";
import Title from "../components/Title/Title";
import About from "../components/About/About";
import LiveVideo from "../components/LiveVideo/LiveVideo";

const Home = () => {
  return (
    <div>
      <Navbar classType={0} />
      <Page />
      <div className="container">
        <Title subTitle="Our Videos" title="What We Offer" />
        <Contents />
        <About />
        <Title subTitle="Gallery" title="Past Photos" />
        <LiveVideo />
      </div>
    </div>
  );
};

export default Home;
