import React from 'react';
import { Link } from 'react-router-dom';
import './cssFiles/Login.css'

//Login component that implement the logic of 

function Realod() {

    return (
        <div className='login'>
            <div className='login_page'>
                <div className='login_header'>
                    NTM
                </div>
                <div className='login_body'>
                  <Link to='/'>
                  <input type="button" value="click here to return login" className="btn btn-outline-secondary" />
                  </Link>
                </div>
            </div >
        </div >
    );

}


export default Realod;
