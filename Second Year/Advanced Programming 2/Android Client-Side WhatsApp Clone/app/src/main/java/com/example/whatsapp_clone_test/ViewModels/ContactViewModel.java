package com.example.whatsapp_clone_test.ViewModels;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModel;

import com.example.whatsapp_clone_test.ContactsRepository;
import com.example.whatsapp_clone_test.Entities.Contact;

import java.util.List;

public class ContactViewModel extends ViewModel {

    private LiveData<List<Contact>> contacts;
    private ContactsRepository contactsRepository;
    private String userActive;

    public ContactViewModel(String userActive) {
        super();
        contactsRepository = new ContactsRepository(userActive);
        this.userActive = userActive;
        contacts = contactsRepository.getAll();
    }

    public LiveData<List<Contact>> getContacts() {
        contactsRepository.getAll();
        return contacts;
    }

    public void insert (Contact c) {
        contactsRepository.add(c);
        contacts = contactsRepository.getAll();
    }

    public Contact getContact(String id) {
        return contactsRepository.get(id, userActive);
    }

}
