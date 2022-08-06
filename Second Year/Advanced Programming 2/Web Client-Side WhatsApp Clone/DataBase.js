import User from "./User";

import daddyPic from './profilePictures/daddyPic.png'
import mommyPic from './profilePictures/momPic.jpg'
import noamitPic from './profilePictures/noamitPic.jpg'
import tomerPic from './profilePictures/tomerPic.jpeg'
import sisPic from './profilePictures/sisPic.jpeg'
import bobMarly from './profilePictures/bobMarly.jpg';
import mommyVideo from './photosAndFiles/mommyvideo.mp4'
import audioFile from './photosAndFiles/audio.mp3'
import noadog from './photosAndFiles/dog.jpg';

import './cssFiles/Chat.css'

//DataBase to manage all the users and their chats with the messages.

class DataBase {
    constructor() {
        this.usersDataBase = new Map();
    }

    addUserToDataBase(key, user) {
        this.usersDataBase.set(key,user);
    }
}


const dataBase = new DataBase();

//Hard-Coded users and messages
dataBase.addUserToDataBase('noamit', new User('noamit', 'noa amit', 'noa1', noamitPic));
dataBase.addUserToDataBase('tomerk',new User('tomerk', 'Tomer Hadar', 'tomer1', tomerPic));
dataBase.addUserToDataBase('mommy', new User('mommy', 'best mommy', 'mommy1', mommyPic));
dataBase.addUserToDataBase('daddy',new User('daddy', 'best daddy', 'daddy1', daddyPic));
dataBase.addUserToDataBase('sister',new User('sister', 'my sister', 'sister1', sisPic));
dataBase.addUserToDataBase('bob',new User('bob', 'bob bobby', 'bob1', bobMarly));


//bob
dataBase.usersDataBase.get('bob').userChats.set('noamit', {msgArray:[], lastMsg:"", lastMsgTime:""})
dataBase.usersDataBase.get('bob').userChats.set('tomerk', {msgArray:[], lastMsg:"", lastMsgTime:""})
dataBase.usersDataBase.get('bob').userChats.set('mommy', {msgArray:[], lastMsg:"", lastMsgTime:""})
dataBase.usersDataBase.get('bob').userChats.set('daddy', {msgArray:[], lastMsg:"", lastMsgTime:""})
dataBase.usersDataBase.get('bob').userChats.set('sister', {msgArray:[], lastMsg:"", lastMsgTime:""})

//noamit
dataBase.usersDataBase.get('bob').userChats.get('noamit').msgArray.push(<p className={`message ${true && 'recive_message'}`}>
<audio src={audioFile} controls />  <span className='message_time'>8:00</span></p>)
dataBase.usersDataBase.get('bob').userChats.get('noamit').lastMsg = 'VOICE MESSAGE';
dataBase.usersDataBase.get('bob').userChats.get('noamit').lastMsgTime = '8:00';


//tomerK
dataBase.usersDataBase.get('bob').userChats.get('tomerk').msgArray.push(<p className={`message ${true && 'recive_message'}`}>
<img className="send_img" src={noadog}/> <br /> <span className='message_time'>9:00</span></p>)
 dataBase.usersDataBase.get('bob').userChats.get('tomerk').lastMsg = 'IMAGE';
 dataBase.usersDataBase.get('bob').userChats.get('tomerk').lastMsgTime = '9:00';

//mommy
dataBase.usersDataBase.get('bob').userChats.get('mommy').msgArray.push(<p className={`message ${true && 'recive_message'}`}>
<video className="send_img" src={mommyVideo} controls/> <br /> <span className='message_time'>10:00</span></p>)
dataBase.usersDataBase.get('bob').userChats.get('mommy').lastMsg = 'VIDEO';
dataBase.usersDataBase.get('bob').userChats.get('mommy').lastMsgTime = '10:00';

//daddy
dataBase.usersDataBase.get('bob').userChats.get('daddy').msgArray.push(<p className={`message ${true && 'recive_message'}`}>
love you
<span className='message_time'>11:00</span></p>)
dataBase.usersDataBase.get('bob').userChats.get('daddy').lastMsg = 'love you'
dataBase.usersDataBase.get('bob').userChats.get('daddy').lastMsgTime = '11:00'

//sister
dataBase.usersDataBase.get('bob').userChats.get('sister').msgArray.push(<p className={`message ${true && 'recive_message'}`}>
how are you today?
<span className='message_time'>12:00</span></p>)
dataBase.usersDataBase.get('bob').userChats.get('sister').lastMsg = 'how are you today?'
dataBase.usersDataBase.get('bob').userChats.get('sister').lastMsgTime = '12:00'


export default dataBase;