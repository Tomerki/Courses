import React, { useState, useEffect } from 'react'
import { Modal } from 'react-bootstrap'


function ModalRecord({ modalSetter, messageSetter }) {


    function Record() {
        let [myRecored, isRecording, startRecording, stopRecording] = Recorder();
        
        //return after Recorder function return all the values.
        return (
            <>
                <audio src={myRecored} controls />
                <button onClick={startRecording} disabled={isRecording}>
                    start recording
                </button>
                <button onClick={stopRecording} disabled={!isRecording}>
                    stop recording
                </button>
            </>
        )

    }

    function Recorder() {
        const [audioURL, setAudioURL] = useState("");
        const [isRecording, setIsRecording] = useState(false);
        const [recorder, setRecorder] = useState(null);

        useEffect(() => {
            // Lazily obtain recorder first time we're recording.
            if (recorder === null) {
                if (isRecording) {
                    //active setRecorder only after requestRecorder function get a microphone to use.
                    requestRecorder().then(setRecorder, console.error);
                }
                return;
            }

            // controlling the recorder.
            if (isRecording) {
                recorder.start();
            } else {
                recorder.stop();
            }

            // creates the source file
            const handleData = e => {
                setAudioURL(URL.createObjectURL(e.data));
                messageSetter(<audio src={URL.createObjectURL(e.data)} controls />)   
            };

            recorder.addEventListener("dataavailable", handleData);
            
            return () => recorder.removeEventListener("dataavailable", handleData);
            //active useEffect function when one of those field change.
        }, [recorder, isRecording]);


        //It causes the useEffect function to start.
        const startRecording = () => {
            setIsRecording(true);
        };

        const stopRecording = () => {
            setIsRecording(false);
        };

        return [audioURL, isRecording, startRecording, stopRecording];
    }

    //async function because we have to wait until we get Microphon Premission and only then active the setRecorder.
    async function requestRecorder() {
        const stream = await navigator.mediaDevices.getUserMedia({ audio: true });
        return new MediaRecorder(stream);
    }

    //returning modal to make the record and preview it.
    return (
        <div>
            <Modal.Header>
                <Modal.Title>
                    Recording
                </Modal.Title>
            </Modal.Header>
            <Modal.Body>
                {Record()}
                <br/>
                <button variant="secondary" onClick={() => { modalSetter(false) }}>Close</button>
            </Modal.Body>
        </div>
    )
}

export default ModalRecord;