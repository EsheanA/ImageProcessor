import Home from "./pages/Home.tsx"
import Nav from "@/components/custom/Navigation.tsx"
import { Routes, Route, Link } from "react-router-dom"


function App() {
  return (
    <>
      <Nav/>
      <Routes>
        <Route path = "/" element ={<Home/>}/>
      </Routes>
    </>
  )
}

export default App