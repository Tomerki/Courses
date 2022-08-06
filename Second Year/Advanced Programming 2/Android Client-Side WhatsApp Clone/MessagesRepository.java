package com.example.whatsapp_clone_test;

import androidx.lifecycle.MutableLiveData;
import androidx.room.Room;

import java.util.ArrayList;
import java.util.List;

public class MessagesRepository {

    private MessagesDB dataBase;
    private MessageDao dao;
    private MessageListData messageListData;
    private MessageAPI api;


    public MessagesRepository(){
        dataBase = Room.databaseBuilder(MyApplication.context, MessagesDB.class, "MessagesDB").allowMainThreadQueries().build();
        dao = dataBase.messageDao();
        messageListData = new MessageListData();
        api = new MessageAPI(messageListData, dao);
    }


    class MessageListData extends MutableLiveData<List<Message>> {
        public MessageListData() {
            super();
            setValue(new ArrayList<>());
        }

        @Override
        protected void onActive(){
            super.onActive();
            new Thread(()-> messageListData.postValue(new ArrayList<>())).start();
        }
    }

    public MutableLiveData<List<Message>> getAll(){
        return messageListData;
    }

    public MutableLiveData<List<Message>> getContactMessages(int contactId){
         messageListData.postValue(dao.getMessages(contactId));
         return messageListData;
    }


    public void add (final Message msg){
        dao.insert(msg);
        messageListData.setValue(dao.getMessages(msg.getContactId()));
    }

    public void delete (final Message msg){
        dao.delete(msg);
    }

    public void reload(){
        dao.get();
    }
}
