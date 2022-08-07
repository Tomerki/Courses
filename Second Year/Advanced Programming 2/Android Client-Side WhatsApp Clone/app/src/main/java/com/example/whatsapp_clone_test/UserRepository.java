package com.example.whatsapp_clone_test;

import androidx.room.Room;

import com.example.whatsapp_clone_test.Api.UserApi;
import com.example.whatsapp_clone_test.Daos.UserDao;
import com.example.whatsapp_clone_test.Entities.User;

public class UserRepository {
    private UserDB userDB;
    private UserDao userDao;
    private UserApi userApi;
    private String userActive;

    public UserRepository(String userActive) {
        userDB = Room.databaseBuilder(MyApplication.context, UserDB.class, "userDB").allowMainThreadQueries().fallbackToDestructiveMigration().build();
        userDao = userDB.userDao();
        this.userActive = userActive;
        userApi = new UserApi(userDao, userActive);
        userApi.getAll();
    }

    public boolean register (final User user, String confirmPassword){
        if (userDao.checkUser(user.getId()) == null) {
            boolean checkResult = checkValidPassword(user.getPassword(), confirmPassword);
            if(checkResult) {
                userApi.register(user);
                userDao.register(user);
                return true;
            }
        }
        return false;
    }

    public User login (String id, String password){
        return userDao.login(id, password);
    }

    public void createToken(String token) {
        userApi.createToken(token);
    }

    public User getUser (String id) {
        return userDao.checkUser(id);
    }

    public void update (final User user) {
        userDao.update(user);
    }

    public boolean checkValidPassword(String password, String confirmPassword) {
        int passwordSize = password.length();
        if (passwordSize < 2 || confirmPassword.length() < 2) {
            return false;
        }
        if(!password.equals(confirmPassword)) {
            return false;
        }
        int lettersNum = 0;
        int numbersNum = 0;
        for (int i=0; i < passwordSize; i++) {
            if ((!Character.isLetterOrDigit(password.charAt(i)))) {
                return false;
            } else if (Character.isDigit(password.charAt(i))){
                numbersNum ++;
            } else {
                lettersNum ++;
            }
        }
        if (numbersNum > 0 && lettersNum > 0) {
            return true;
        }
        return false;
    }
}
