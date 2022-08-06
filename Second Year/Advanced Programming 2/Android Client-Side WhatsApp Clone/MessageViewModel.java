package com.example.whatsapp_clone_test;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModel;

import com.example.whatsapp_clone_test.Entities.Contact;

import java.util.List;

public class MessageViewModel extends ViewModel {

    private final MessagesRepository messagesRepository;
    private ContactsRepository contactsRepository;
    private LiveData<List<Message>> messages;

    public MessageViewModel(){
        messagesRepository = new MessagesRepository();
        contactsRepository = new ContactsRepository();
        messages = messagesRepository.getAll();
    }

    public LiveData<List<Message>> get(){
        return messages;
    }


    public LiveData<List<Message>> getContactMessages(int contactId){
        messages = messagesRepository.getContactMessages(contactId);
        return messages;
    }


    public void add(Message msg){
        messagesRepository.add(msg);
        Contact current = contactsRepository.getByRealId(msg.getContactId());
        current.setLast(msg.getMsg());
        current.setLastDate(msg.getMsgTime());
        contactsRepository.update(current);
    }
    public void delete(Message msg){ messagesRepository.delete(msg);}

    public void reload() {messagesRepository.reload();}

}
