import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import "./style/index.css";

import { createBrowserRouter, RouterProvider } from "react-router-dom";

import Video from "./pages/Video.jsx";
import Home from "./pages/Home.jsx";
import Error from "./pages/Error.jsx";
import About from "./pages/About.jsx";

const router = createBrowserRouter([
  {
    path: "/",
    element: <Home />,
    errorElement: <Error />,
  },
  {
    path: "/video",
    element: <Video />,
  },
  {
    path: "/about-us",
    element: <About />,
  },
]);

createRoot(document.getElementById("root")).render(
  <StrictMode>
    <RouterProvider router={router} />
  </StrictMode>
);
