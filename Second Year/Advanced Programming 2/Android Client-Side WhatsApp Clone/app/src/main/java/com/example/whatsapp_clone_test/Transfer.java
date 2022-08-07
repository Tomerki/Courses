package com.example.whatsapp_clone_test;

public class Transfer {

    //the contact that send the message
    public String from;

    //the user that get the mesaage
    public String to;

    //the content of the message
    public String content;

    public Transfer(String from, String to, String content) {
        this.from = from;
        this.to = to;
        this.content = content;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
}
