package com.example.whatsapp_clone_test.ViewModels;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;
import androidx.lifecycle.ViewModelProvider;

import com.example.whatsapp_clone_test.ContactsRepository;
import com.example.whatsapp_clone_test.Entities.Contact;
import java.util.List;

public class ContactViewModel extends ViewModel {

    private LiveData<List<Contact>> contacts;
    private ContactsRepository contactsRepository;

    public ContactViewModel(String user) {
        super();
        contactsRepository = new ContactsRepository();
        contacts = contactsRepository.getAll(user);
    }

    public LiveData<List<Contact>> getContacts(String user) {
        contacts = contactsRepository.getAll(user);
        return contacts;
    }

    public void insert (Contact c, String user) {
        contactsRepository.add(c);
        contacts = contactsRepository.getAll(user);
    }

}
