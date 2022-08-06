import React from 'react'

function Message ({msg}) {

        function TimeToString (time) {
        if (time == null) {
            return null;
        }
        let hour = time.substr(11,2);
        let min = time.substr(14,2);
        return hour + ":" + min
      }
    return (
        <p className={`message ${msg.send && 'recive_message'}`}>
        {msg.content}
        <span className='message_time'>{TimeToString(String(msg.created))}</span></p>
    )
}

export default Message