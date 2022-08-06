import React, { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import './cssFiles/Login.css'
import RegisterErrorModal from './Modals/RegisterErrorModal';
import RegisterSuccessModal from './Modals/RegisterSuccessModal';
import User from './User';
import dataBase from './DataBase'
import axios from 'axios';
import defaultImg from './photosAndFiles/DefaultImage.jpg'

function Register() {

    const [isRegistered, setisRegistered] = useState(() => false);
    const [userName, setUserName] = useState(() => '')
    const [displayName, setDisplayName] = useState(() => '')
    const [password, setPassword] = useState(() => '')
    const [confirmedPassword, setcConfirmedPassword] = useState(() => '')
    const [img, setImg] = useState(defaultImg)
    const [openErrorModel, setOpenErrorModel] = useState(() => false);
    const [openSuccessModel, setOpenSuccessModel] = useState(() => false);
    const [errorDescription, seterrorDescription] = useState(() => 'please fill all the fields');
    const [imageString, setImageString] = useState(() => 'Click To Upload Profile Picture')

    useEffect(() => {
        setUserName(userName)
    }, [userName])

    useEffect(() => {
        setisRegistered(false)
        Valid();
    }, [userName, password, displayName, confirmedPassword])

    async function sendServer() {
        const postRequest = {"id": userName, "password":password, "displayName": displayName};
        try {
            const response = await axios.post('https://localhost:7288/api/Register' , postRequest);
        
            if(response.status == 200) {
                setOpenSuccessModel(true);
            }
        } catch (err) {
            seterrorDescription('username already exists, pls pick another One');
            setOpenErrorModel(true);
            setisRegistered(false);
         }
    }

    //while click Register we render the page with new Register button(if one of the details ilegel), or go to the Login page
    const renderAuthButton = () => {
        if (isRegistered) {
            return (
                <input type="button" value="Register" className="btn btn-outline-secondary" onClick={(e) => {
                    e.preventDefault();
                    sendServer();
                    // dataBase.addUserToDataBase(userName, new User(userName, displayName, password, img));
                }} />
            );
        } else {
            return (
                <input type="button" value="Register" className="btn btn-outline-secondary" onClick={() => { setOpenErrorModel(true); Valid(); }} />
            );
        }
    }
    //checks Validetion of username and password
    const Valid = () => {
        if (userName.length > 0 && password.length > 0 && displayName.length > 0
            && String(password) === String(confirmedPassword) && checkPassword()) {
            setisRegistered(bool => bool = true)
        }
        //set the correct error message according the error case.
        else {
            if (userName.length === 0 || confirmedPassword.length === 0 || displayName.length === 0 || password.length === 0) {
                seterrorDescription('please fill all the fields');
            } else if (checkPassword() !== true) {
                seterrorDescription('password must contain at least one letter a-z or A-Z and one digit 0-9');
            } else if (String(password) !== String(confirmedPassword)) {
                seterrorDescription('Incompatible passwords');
            }
        }
    }

    //checks for valid password
    const checkPassword = () => {
        return /[a-zA-Z]/.test(password) && /[0-9]/.test(password);
    }

    //create sourceFile for the profile image after the user upload it
    const readImage = (e) => {
        if(e.target.files){
            if(e.target.files[0]){
                setImg(URL.createObjectURL(e.target.files[0]));
                setImageString('Profile Picture Uploaded Successfully')
            }
        }
    }

    return (
        <div className='login'>
            <div className='allModals'>
                {openSuccessModel && <RegisterSuccessModal close_modal={setOpenSuccessModel} />}
                {openErrorModel && <RegisterErrorModal close_modal={setOpenErrorModel} message={errorDescription} />}
            </div>
            <div className='login_page'>
                <div className='login_header'>
                    <div>NTM</div>
                </div>
                <div className='login_body'>
                    <h2> Register </h2>


                    <form id="RegisterForm" className="form" action="/chat">
                        <div className='login_body_input'>
                            <input placeholder="Username" className="login_input" type="text" value={userName}
                                onChange={e => { setUserName(e.target.value); }} />
                        </div>

                        <div className='login_body_input'>
                            <input placeholder='Display Name' className="login_input" type="text" value={displayName}
                                onChange={e => { setDisplayName(e.target.value); }} />
                        </div>

                        <div className='login_body_input'>
                            <input placeholder="Password" className="login_input" type="password" value={password}
                                onChange={e => { setPassword(e.target.value); }} />
                        </div>

                        <div className='login_body_input'>
                            <input placeholder="Confirm Password" className="login_input" type="password" value={confirmedPassword}
                                onChange={e => { setcConfirmedPassword(e.target.value); }} />
                        </div>

                        <div className='login_body_input'>
                            <label htmlFor="img1" className='btn btn-dark'>{imageString}</label>
                            <input id="img1" type="file" accept="image/png, image/jpeg" hidden onChange={readImage} />
                        </div>

                        <div className='login_buttom'>
                            {renderAuthButton()}
                        </div>

                    </form>

                    <div id='notregistered'>Already Registered?&nbsp;
                        <span>
                            <Link to='/' id="forRegister">
                                click here
                            </Link>
                            &nbsp;to Login.
                        </span>
                    </div>
                </div>
            </div>
        </div>
    )
}


export default Register;