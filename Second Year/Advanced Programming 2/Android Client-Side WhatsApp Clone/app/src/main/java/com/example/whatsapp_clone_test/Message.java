package com.example.whatsapp_clone_test;

import androidx.room.Entity;
import androidx.room.PrimaryKey;

@Entity
public class Message {


    @PrimaryKey(autoGenerate = true)
    private int Id;
    private int contactId;
    private String content;
    private String created;
    private boolean send;

    public Message( int contactId, String content, String created, boolean Send) {
        this.contactId = contactId;
        this.content = content;
        this.created = created;
        this.send = Send;
    }

    public Message () {}

    public int getId() {
        return Id;
    }

    public void setId(int id) {
        Id = id;
    }

    public int getContactId() {
        return contactId;
    }

    public void setContactId(int contactId) {
        this.contactId = contactId;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public String getCreated() {
        return created;
    }

    public void setCreated(String created) {
        this.created = created;
    }

    public boolean isSend() {
        return this.send;
    }

    public void setSend(boolean send) {
        this.send = send;
    }
}
