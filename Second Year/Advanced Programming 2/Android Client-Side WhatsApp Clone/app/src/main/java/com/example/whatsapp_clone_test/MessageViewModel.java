package com.example.whatsapp_clone_test;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModel;

import com.example.whatsapp_clone_test.Entities.Contact;

import java.util.List;

public class MessageViewModel extends ViewModel {

    private MessagesRepository messagesRepository;
    private ContactsRepository contactsRepository;
    private LiveData<List<Message>> messages;
    private String userActive;
    private int id;
    String stringId;

    public MessageViewModel(String userName, String stringId){
        super();
        this.stringId = stringId;
        this.userActive = userName;
        contactsRepository = new ContactsRepository(userActive);
        messagesRepository = new MessagesRepository(userActive ,this.stringId, contactsRepository);
        this.id = contactsRepository.get(stringId, userActive).getRealId();
        messages = messagesRepository.getAll();
    }

    public LiveData<List<Message>> get(){
        return messages;
    }


    public LiveData<List<Message>> getContactMessages(){
//        messages = messagesRepository.getContactMessages();
//        return messages;
        return messagesRepository.getContactMessages();
    }

    public void add(Message msg){
        messagesRepository.add(msg);
//        messages = messagesRepository.getAll();
//        Contact contact = contactsRepository.get(stringId, userActive);
//        contact.setLast(msg.getContent());
//        contactsRepository.update(contact);
    }

    public void delete(Message msg){ messagesRepository.delete(msg);}

    public void reload() {messagesRepository.reload();}

    public void getAll(String last){
        messagesRepository.get();
    }

}
