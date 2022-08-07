package com.example.whatsapp_clone_test;


import androidx.room.Database;
import androidx.room.RoomDatabase;


@Database(entities = {Message.class}, version = 3)
public abstract class MessagesDB extends RoomDatabase{
    public abstract MessageDao messageDao();
}
