import React, { useEffect, useState } from 'react';
import axios from 'axios';
import { Button, Modal } from 'react-bootstrap'
import dataBase from '.././DataBase';


function SideBarModal({ myUser, close_modal, setterContactsArray, contactsArray, errorModalSetter, errorMessage }) {

    const [contactId, setContactid] = useState('');
    const [contactNickName, setContactNickName] = useState('');
    const [contactServer, setContactServer] = useState('');

    const createContact = (e) => {
        e.preventDefault();
        sendServer();
        close_modal(false);
    }

    async function sendServer() {

         const postRequestToMycontactserver = {"from": myUser, "to": contactId ,"server" : "localhost:7288" };
         try {
             const responsecontactserver = await axios.post('https://' + contactServer+ '/api/invitations/'+ "?user="+myUser , postRequestToMycontactserver);
         } catch (err) {
            errorMessage('User Does Not Exsist');
            errorModalSetter(() => true)
            return;
          }

          const postRequestToMySERVER = {"id" : contactId, "name" : contactNickName, "server" : contactServer };
          try {
              const response = await axios.post('https://localhost:7288/api/Contacts'+ "?user="+myUser, postRequestToMySERVER);
               if(response.status == 200 && response.data == "already in contact list") {
                  errorMessage('Already in contact`s List ');
                  errorModalSetter(() => true)
                  return;
              }
              if(response.status == 200 || response.status == 201) {
                setterContactsArray(!contactsArray);
                return;
            }
          } catch (err) {
            return;
           }
    
    }

    return (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        <div className='leftModal'>                                                 
            <Modal.Dialog className='modal-dialog'>
                <Modal.Header>
                    <Modal.Title>Add New Contant</Modal.Title>
                </Modal.Header>
                <Modal.Body>                             
                    <input type="text" id='newContantInput' className="form-control" placeholder="contact's identifier" value={contactId}
                        onChange={(e) => { setContactid(e.target.value) }} />
                    <input type="text" id='newContantInput' className="form-control" placeholder="contact's nickName" value={contactNickName}
                        onChange={(e) => { setContactNickName(e.target.value) }} />
                    <input type="text" id='newContantInput' className="form-control" placeholder="contact's server" value={contactServer}
                        onChange={(e) => { setContactServer(e.target.value) }} />
                </Modal.Body>
                
                <Modal.Footer>
                    <Button onClick={createContact}> Add</Button>

                    <Button variant="secondary" onClick={() => { close_modal(false); }}>Close</Button>
                </Modal.Footer>
            </Modal.Dialog>
        </div>
    );
}
export default SideBarModal;

