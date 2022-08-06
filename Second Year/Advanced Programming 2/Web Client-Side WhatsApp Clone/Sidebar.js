import React, { useEffect, useState } from 'react';
import axios from 'axios';
import './cssFiles/Sidebar.css'
import { PersonPlus } from 'react-bootstrap-icons'
import SingleSideChat from './SingleSideChat'
import SideBarModal from './Modals/SideBarModal'
import ContactErrorModal from './Modals/ContactErrorModal';
import dataBase from './DataBase'
import defaultImg from './photosAndFiles/DefaultImage.jpg'


function Sidebar({ user, chatWith }) {

  const [showChats, setShowChats] = useState([]);
  const [renderShow, setRenderShow] = useState(true);

  useEffect(() => {
    renderSideBar();
  }, [showChats])

  useEffect(() => {
    setRenderShow(!renderShow);
  }, [showChats])

  async function renderSideBar() {
    try {
      const response = await axios.get('https://localhost:7288/api/Contacts/'+ "?user="+user);

      if (response.status == 200) {
        setShowChats (response.data.map((u) => { return <SingleSideChat userJson={u} myname={user} chatWithX={chatWith} /> }))
      }
    } catch (err) {
      console.log(err);
    }
  }

  const [chatsArray, setChatsArray] = useState([]);
  const [openModel, setOpenModel] = useState(false);

  const [openErrorModel, setOpenErrorModel] = useState(() => false);
  const [errorDescription, seterrorDescription] = useState('');


  //Array to save all the Chats
  // const showChats = chatsArray.map((username) => { return <SingleSideChat name={username} myname={user} chatWithX={chatWith} /> })

  //returning the html that describe the sidebar with all the logic inside(as function calls).
  return (
    <>
      <div className='sidebar'>
        <div className='sideBarModal'>
          {openModel && <SideBarModal myUser={user} close_modal={setOpenModel} setterContactsArray={setChatsArray} contactsArray={chatsArray}
            errorModalSetter={setOpenErrorModel} errorMessage={seterrorDescription} />}
        </div>
        <div className='sideBarModal'>
          {openErrorModel && <ContactErrorModal close_modal_error={setOpenErrorModel} message={errorDescription} />}
        </div>
        <div className='sidebar_header'>
          {/* <img src={dataBase.usersDataBase.get(user).img} className="rounded-circle" alt="user" /> */}
          <img src={defaultImg} className="rounded-circle" alt="user" />
          {/* <div id="userName">{dataBase.usersDataBase.get(user).displayName}</div> */}
          <div id="userName">{user}</div>
          <button id='presonPlus_button' onClick={() => { setOpenModel(true); }}>
            <PersonPlus />
          </button>
        </div>
        <div className='sidebar_chats'>
          {showChats}
        </div>
      </div>
    </>
  )
}

export default Sidebar