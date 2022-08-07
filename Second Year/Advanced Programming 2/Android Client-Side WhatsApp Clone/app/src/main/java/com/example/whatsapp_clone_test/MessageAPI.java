package com.example.whatsapp_clone_test;

import androidx.lifecycle.MutableLiveData;

import com.example.whatsapp_clone_test.Entities.Contact;

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
    Retrofit retrofitContacts;
    WebServiceMsgAPI webServiceMsgAPI;
    WebServiceMsgAPI contactWebServiceMsgAPI;
    private int contactId;
    private Contact contact;
    private String stringId;
    private String userActive;

    public MessageAPI(MutableLiveData<List<Message>> messageListData, MessageDao dao, int contactId,Contact contact, String stringId, String userActive) {
        this.userActive = userActive;
        this.stringId = stringId;
        this.contact = contact;
        this.messageListData = messageListData;
        this.dao = dao;
        this.contactId = contactId;
        retrofit = new Retrofit.Builder()
                .baseUrl(MyApplication.context.getString(R.string.BaseUrl))
                .addConverterFactory(GsonConverterFactory.create())
                .build();
        String s = "http://" + contact.getServer() + "/api/";
        retrofitContacts = new Retrofit.Builder()
                .baseUrl(s)
                .addConverterFactory(GsonConverterFactory.create())
                .build();
        webServiceMsgAPI = retrofit.create(WebServiceMsgAPI.class);
        contactWebServiceMsgAPI = retrofitContacts.create(WebServiceMsgAPI.class);
    }

    public void get() {
        Call<List<Message>> call = webServiceMsgAPI.getMessages(stringId, userActive);
        call.enqueue(new Callback<List<Message>>() {
            @Override
            public void onResponse(Call<List<Message>> call, Response<List<Message>> response) {
                new Thread(() -> {
                    List<Message> messages = response.body();
                        dao.delete(dao.index().toArray(new Message[0]));
                        if(messages!=null) {
                            for(Message msg : messages){
                                msg.setContactId(contact.getRealId());
                                String newTime = msg.getCreated().substring(11,16);
                                msg.setCreated(newTime);
                                dao.insert(msg);
                            }
                        }
                        messageListData.postValue(messages);
                }).start();
            }

            @Override
            public void onFailure(Call<List<Message>> call, Throwable t) {
            }
        });
    }


    public void add(Message msg){
        msg.setCreated(null);
        Call<Void> call = webServiceMsgAPI.postMessage(msg, stringId, userActive);
        call.enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {
                get();
            }

            @Override
            public void onFailure(Call<Void> call, Throwable t) {
            }
        });

        Call<Message> call2 = webServiceMsgAPI.transfer(new Transfer(userActive, stringId, msg.getContent()));
        call2.enqueue(new Callback<Message>() {
            @Override
            public void onResponse(Call<Message> call, Response<Message> response) {}

            @Override
            public void onFailure(Call<Message> call, Throwable t) {}
        });

    }
    public void delete(Message msg){
        dao.delete(msg);
    }

}
