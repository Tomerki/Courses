import React from 'react'
import { Button, Modal } from 'react-bootstrap'
import { Link } from 'react-router-dom';

function LoginSuccessModal() {
    //popup modal for successfully Registration
    return (
        <Modal.Dialog>
            <Modal.Header>
                <Modal.Title>Login completed successfully</Modal.Title>
            </Modal.Header>

            <Modal.Body>
                <p>press OK and start chatting</p>
            </Modal.Body>

            <Modal.Footer>
                <Link to="/chat"><Button variant="secondary" >OK</Button></Link>
            </Modal.Footer>
        </Modal.Dialog>
    )
}

export default LoginSuccessModal
