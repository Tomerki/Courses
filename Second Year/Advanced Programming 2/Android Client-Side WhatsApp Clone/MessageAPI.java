package com.example.whatsapp_clone_test;

import android.content.Context;

import androidx.lifecycle.MutableLiveData;

import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class MessageAPI {

    private MutableLiveData<List<Message>> messageListData;
    private MessageDao dao;
    Retrofit retrofit;
    WebServiceMsgAPI webServiceMsgAPI;

    public MessageAPI(MutableLiveData<List<Message>> messageListData, MessageDao dao) {
        this.messageListData = messageListData;
        this.dao = dao;

        retrofit = new Retrofit.Builder()
                .baseUrl(MyApplication.context.getString(R.string.BaseUrl))
                .addConverterFactory(GsonConverterFactory.create())
                .build();
        webServiceMsgAPI = retrofit.create(WebServiceMsgAPI.class);
    }

    public void get() {
        Call<List<Message>> call = webServiceMsgAPI.getMessages();
        call.enqueue(new Callback<List<Message>>() {
            @Override
            public void onResponse(Call<List<Message>> call, Response<List<Message>> response) {

                List<Message> messages = response.body();

//                new Thread(() -> {
//                    dao.clear();
//                    dao.insertList(response.body());
//                    messageListData.postValue(dao.get());
//                }).start();
            }

            @Override
            public void onFailure(Call<List<Message>> call, Throwable t) {
            }
        });
    }


    public void add(Message msg){
        dao.insert(msg);
    }
    public void delete(Message msg){
        dao.delete(msg);
    }

}
