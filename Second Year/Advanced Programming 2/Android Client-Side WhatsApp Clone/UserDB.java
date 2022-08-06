package com.example.whatsapp_clone_test;

import androidx.room.Database;
import androidx.room.RoomDatabase;

import com.example.whatsapp_clone_test.Daos.UserDao;
import com.example.whatsapp_clone_test.Entities.User;

@Database(entities = {User.class}, version = 2)

public abstract class UserDB extends RoomDatabase {
    public abstract UserDao userDao();
}