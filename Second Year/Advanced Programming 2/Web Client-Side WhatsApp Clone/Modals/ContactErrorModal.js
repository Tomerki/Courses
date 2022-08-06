import React from 'react'
import { Button, Modal } from 'react-bootstrap'

function ContactErrorModal({ close_modal_error, message }) {
    //modal for error when register with ilegel fields (for example - password without numbers)
    return (
        <div className='leftModal'>
            <Modal.Dialog className='modal-dialog'>
                <Modal.Header>
                    <Modal.Title>Error</Modal.Title>
                </Modal.Header>

                <Modal.Body>
                    <p>{message}</p>
                </Modal.Body>

                <Modal.Footer>
                    <Button variant="secondary" onClick={() => { close_modal_error(false) }}>Close</Button>
                </Modal.Footer>
            </Modal.Dialog>
        </div>

    );
}

export default ContactErrorModal
