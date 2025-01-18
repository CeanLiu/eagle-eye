import "../style/Error.css";
import Navbar from "../components/navbar/Navbar";

const Error = () => {
  return (
    <div>
      <Navbar classType={1} />
      <h1 className="error-text">404 Not Found</h1>
    </div>
  );
};

export default Error;
