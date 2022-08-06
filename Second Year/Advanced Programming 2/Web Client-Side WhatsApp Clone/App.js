import { useState } from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Login from './Login';
import Register from './Register'
import Appbody from './Appbody'
import './Modals/Modal.css'
import Realod from "./Reload";
import {  HubConnectionBuilder } from '@microsoft/signalr';

function App() {

  const [newUser, setNewUser] = useState('')
  const [hubConnection, setHubConnection] = useState(true)
  const [connection, setConnection] = useState(true)

  async function connectHub(user) {
    try {
        const connection = new HubConnectionBuilder().withUrl('https://localhost:7288/Chats', {
        }).build();
        connection.on("ReceiveMessage",  () => {
        setHubConnection(!hubConnection);
        });
        await connection.start();
        await connection.invoke("connectUserToServer", user);
        setConnection(connection);
    } catch (e) {
      console.log(e);
    }
} 
  const startApp = () => {
    if (newUser === '') {
      return (
        <BrowserRouter>
          <Routes>
          <Route path='/' element={<Login userSetter={setNewUser} cunnectionFunc = {connectHub} />}></Route>
          <Route path='/register' element={<Register />}></Route>
          <Route path='/chat' element={<Realod userSetter={setNewUser} />}></Route>
          </Routes>
        </BrowserRouter>
      );
    }
    else {
      return (
        <>
        <BrowserRouter>
          <Routes>
            <Route path='/' element={<Login userSetter={setNewUser} cunnectionFunc = {connectHub}/>}></Route>
            <Route path='/register' element={<Register />}></Route>
            <Route path='/chat' element={<Appbody userChat={newUser} hubRenderring ={hubConnection} connectionChat = {connection}/>}></Route>
            
          </Routes>
        </BrowserRouter>
      </>
      )
    }

  }

  //using routes to nevigate without re-fresh the page
  return (
    startApp()
  );

}
export default App;
