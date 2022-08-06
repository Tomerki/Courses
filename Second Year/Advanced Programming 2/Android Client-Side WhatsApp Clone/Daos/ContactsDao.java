package com.example.whatsapp_clone_test.Daos;

import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.Query;
import androidx.room.Update;

import com.example.whatsapp_clone_test.Entities.Contact;

import java.util.List;

@Dao
public interface ContactsDao {
    @Query("SELECT * FROM Contact")
    List<Contact> index();

    @Query("SELECT * FROM Contact WHERE id = :id AND friendsOf = :user")
    Contact get(String id, String user);

    @Query("SELECT * FROM Contact WHERE realId = :realId")
    Contact getByRealId(int realId);

    @Query("SELECT * FROM Contact WHERE friendsOf = :user")
    List<Contact> getContacts(String user);

    @Insert
    void insert(Contact... contacts);

    @Update
    void update(Contact... contacts);

    @Delete
    void delete(Contact... contacts);

}
