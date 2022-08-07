package com.example.whatsapp_clone_test;

import androidx.lifecycle.MutableLiveData;
import androidx.room.Room;

import com.example.whatsapp_clone_test.Entities.Contact;

import java.util.ArrayList;
import java.util.List;

public class MessagesRepository {

    private MessagesDB dataBase;
    private MessageDao dao;
    private ContactsRepository contactsRepository;
    private MessageListData messageListData;
    private MessageAPI api;
    private String userActive;
    private Contact contact;
    private String stringId;


        public MessagesRepository(String userActive, String stringId, ContactsRepository contactsRepository) {
        this.stringId = stringId;
        this.userActive = userActive;
        this.contactsRepository = contactsRepository;
        this.contact = contactsRepository.get(stringId, userActive);
        dataBase = Room.databaseBuilder(MyApplication.context, MessagesDB.class, "MessagesDB").allowMainThreadQueries().fallbackToDestructiveMigration().build();
        dao = dataBase.messageDao();
        messageListData = new MessageListData();
        api = new MessageAPI(messageListData, dao, contact.getRealId(),contact, stringId, userActive);
        api.get();
    }

    public void get(){
            api.get();
    }


    class MessageListData extends MutableLiveData<List<Message>> {
        public MessageListData() {
            super();
            setValue(new ArrayList<>());
        }

        @Override
        protected void onActive(){
            super.onActive();
            new Thread(()-> messageListData.postValue(dao.getMessages(contact.getRealId()))).start();
        }
    }

    public MutableLiveData<List<Message>> getAll(){
        return messageListData;
    }

    public MutableLiveData<List<Message>> getContactMessages(){
         messageListData.postValue(dao.getMessages(contact.getRealId()));
         return messageListData;
    }

    public void add (Message msg){
        dao.insert(msg);
        api.add(msg);
    }

    public void delete (final Message msg){
        dao.delete(msg);
    }

    public void reload(){
        dao.get();
    }
}
