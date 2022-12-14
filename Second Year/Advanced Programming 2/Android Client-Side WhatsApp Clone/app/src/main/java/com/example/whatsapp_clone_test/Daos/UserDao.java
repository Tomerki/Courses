package com.example.whatsapp_clone_test.Daos;

import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.Query;
import androidx.room.Update;

import com.example.whatsapp_clone_test.Entities.User;

import java.util.List;

@Dao
public interface UserDao {

    @Query("SELECT * FROM user")
    List<User> index();

    @Query("SELECT * FROM User WHERE id = :id AND password = :password")
    User login(String id, String password);

    @Insert
    void register(User... Users);

    @Query("SELECT * FROM User WHERE id = :id")
    User checkUser(String id);

    @Update
    void update(User... Users);

    @Delete
    void delete(User... users);

}
