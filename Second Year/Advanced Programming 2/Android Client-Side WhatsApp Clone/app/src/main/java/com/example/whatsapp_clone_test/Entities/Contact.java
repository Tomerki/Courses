package com.example.whatsapp_clone_test.Entities;

import androidx.room.Entity;
import androidx.room.PrimaryKey;

import java.io.Serializable;

@Entity
public class Contact {

    @PrimaryKey(autoGenerate = true)
    private int realId;
    private String id;
    private String name;
    private String server;
    private String last;
    private String lastDate;
    private String friendsOf;
    private boolean sideBarOn;

    public Contact(String id, String name, String server, String friendsOf) {
        this.id = id;
        this.name = name;
        this.server = server;
        this.friendsOf = friendsOf;
        this.last = null;
        this.lastDate = null;
        this.sideBarOn = true;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getServer() {
        return server;
    }

    public void setServer(String server) {
        this.server = server;
    }

    public String getLast() {
        return last;
    }

    public void setLast(String last) {
        this.last = last;
    }

    public String getLastDate() {
        return lastDate;
    }

    public void setLastDate(String lastDate) {
        this.lastDate = lastDate;
    }

    public boolean isSideBarOn() {
        return sideBarOn;
    }

    public void setSideBarOn(boolean sideBarOn) {
        this.sideBarOn = sideBarOn;
    }

    public void setRealId(int realId) {
        this.realId = realId;
    }

    public int getRealId() {
        return realId;
    }

    public void setFriendsOf(String friendsOf) {
        this.friendsOf = friendsOf;
    }

    public String getFriendsOf() {
        return friendsOf;
    }

}

