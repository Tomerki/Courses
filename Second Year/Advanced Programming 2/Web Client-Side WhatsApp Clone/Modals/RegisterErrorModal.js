import React from 'react'
import { Button, Modal } from 'react-bootstrap'

function RegisterErrorModal({ close_modal , message}) {
    //modal that popup if there is some error while register
    return (
        <Modal.Dialog>
            <Modal.Header>
                <Modal.Title>Error</Modal.Title>
            </Modal.Header>

            <Modal.Body>
                {/* present the correct message for each error */}
                <p>{message}</p>
            </Modal.Body>

            <Modal.Footer>
                <Button variant="secondary" onClick={() => { close_modal(false) }}>Close</Button>
            </Modal.Footer>
        </Modal.Dialog>
    );
}

export default RegisterErrorModal
