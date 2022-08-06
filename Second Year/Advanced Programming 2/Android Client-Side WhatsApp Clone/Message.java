package com.example.whatsapp_clone_test;


import androidx.room.Entity;
import androidx.room.PrimaryKey;

@Entity
public class Message {

    @PrimaryKey(autoGenerate = true)
    private int id;
    private int contactId;
    private String msg;
    private String msgTime;
    private boolean sender;

    public Message(int contactId, String msg, String msgTime, boolean sender) {
        this.contactId = contactId;
        this.msg = msg;
        this.msgTime = msgTime;
        this.sender = sender;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getContactId() {
        return contactId;
    }

    public void setContactId(int contactId) {
        this.contactId = contactId;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public String getMsgTime() {
        return msgTime;
    }

    public void setMsgTime(String msgTime) {
        this.msgTime = msgTime;
    }

    public boolean isSender() {
        return sender;
    }

    public void setSender(boolean sender) {
        this.sender = sender;
    }
}