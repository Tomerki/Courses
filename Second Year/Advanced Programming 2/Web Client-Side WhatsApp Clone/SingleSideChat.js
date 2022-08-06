import React from 'react'
import './cssFiles/SingleSideChat.css'
import dataBase from './DataBase'
import defaultImg from './photosAndFiles/DefaultImage.jpg'

function SingleSideChat({ userJson, myname, chatWithX }) {

    function TimeToString (time) {
        var newTime = String(time);
        if (time == null) {
            return null;
        }
        let hour = newTime.substr(11,2);
        let min = newTime.substr(14,2);
        return hour + ":" + min
      }

    return (
        <>
            <label className='SingleSideChat' htmlFor={userJson.id}>
                <img src={defaultImg} className="rounded-circle" alt="new contant" />
                <div className='SingleSideChat_info'>
                    <div className='a'>
                        <div id="info_name">{userJson.name} </div>
                        <p id="info_message">{userJson.last}</p>
                    </div>
                </div>
                {/* <div id="info_lastSeen">{dataBase.usersDataBase.get(myname).userChats.get(name).lastMsgTime}</div> */}
                <div id="info_lastSeen">{TimeToString(userJson.lastdate)}</div>
            </label>
            <input type="button" id={userJson.id} onClick={() => {chatWithX(userJson)}} hidden />
        </>

    )
}

export default SingleSideChat