package com.example.whatsapp_clone_test;

import androidx.room.Database;
import androidx.room.RoomDatabase;

import com.example.whatsapp_clone_test.Daos.ContactsDao;
import com.example.whatsapp_clone_test.Entities.Contact;

@Database(entities = {Contact.class}, version = 2)
public abstract class ContactDB extends RoomDatabase {
    public abstract ContactsDao contactsDao();
}

