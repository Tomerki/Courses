import React from 'react'
import { Modal } from 'react-bootstrap'
import '../cssFiles/Chat.css'

function ModalImage({ modalSetter, fileToSend, kind }) {
//check if the file is an image or video
    const kindOfile = ()=>{
        return (kind === "VIDEO") ? (
            <video controls="controls" src={fileToSend} className='send_img'/>
        ) : (
            <img src={fileToSend} className='send_img' alt=''/>
        )
    }
    //return value according the file kind and preview it before sending.
    return (
        <div>
            <Modal.Header>
                <Modal.Title>
                    {kind}:
                </Modal.Title>
            </Modal.Header>
            <Modal.Body>
                {kindOfile()}
                <br/>
                <button variant="secondary" onClick={()=>modalSetter(false)}>Close</button>
            </Modal.Body>
        </div>
    )
}

export default ModalImage