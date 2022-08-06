package com.example.whatsapp_clone_test.Entities;
import android.net.Uri;

import androidx.annotation.NonNull;
import androidx.room.Entity;
import androidx.room.PrimaryKey;

import com.example.whatsapp_clone_test.R;

import de.hdodenhof.circleimageview.CircleImageView;

@Entity
public class User {

    @PrimaryKey
    @NonNull
    private String id;
    private String user;
    private String password;
    private String name;

    public User(String user, String password, String name) {
        this.id = user;
        this.user = user;
        this.password = password;
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
