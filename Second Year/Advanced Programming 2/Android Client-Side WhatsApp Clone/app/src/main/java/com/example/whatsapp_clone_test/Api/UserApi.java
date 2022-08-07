package com.example.whatsapp_clone_test.Api;

import android.net.Uri;

import com.example.whatsapp_clone_test.Daos.UserDao;
import com.example.whatsapp_clone_test.Entities.User;
import com.example.whatsapp_clone_test.MyApplication;
import com.example.whatsapp_clone_test.R;

import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class UserApi {

    Retrofit retrofit;
    UserServiceApi userServiceApi;
    private UserDao userDao;
    private String userActive;

    public UserApi(UserDao userDao, String userActive) {
        this.userActive = userActive;
        this.userDao = userDao;
        retrofit = new Retrofit.Builder()
                .baseUrl(MyApplication.context.getString(R.string.BaseUrlUser))
                .addConverterFactory(GsonConverterFactory.create())
                .build();
        userServiceApi = retrofit.create(UserServiceApi.class);
    }

    public void getAll () {
        Call<List<User>> call = userServiceApi.index();
        call.enqueue(new Callback<List<User>>() {
            @Override
            //when the response is ready
            public void onResponse(Call<List<User>> call, Response<List<User>> response) {
                new Thread(() -> {
                    List<User> users1 = response.body();
                    userDao.delete(userDao.index().toArray(new User[0]));
                    for (User user: users1) {
                        user.setProfilePicture(Uri.parse("android.resource://com.example.whatsapp_clone_test/drawable/image_name").getPath());
                        userDao.register(user);
                    }
                }).start();
            }
            @Override
            public void onFailure(Call<List<User>> call, Throwable t) {}
        });
    }

    public void createToken (String token) {
        Call<Void> call = userServiceApi.createToken(token, userActive);
        call.enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {}

            @Override
            public void onFailure(Call<Void> call, Throwable t) {}
        });
    }


    public void register (User user) {
        Call<Void> call = userServiceApi.register(user);
        call.enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {
                userDao.register(user);
            }

            @Override
            public void onFailure(Call<Void> call, Throwable t) {}
        });
    }

}
