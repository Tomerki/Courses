package com.example.whatsapp_clone_test;

import androidx.lifecycle.MutableLiveData;
import androidx.room.Room;

import com.example.whatsapp_clone_test.Api.ContactsApi;
import com.example.whatsapp_clone_test.Daos.ContactsDao;
import com.example.whatsapp_clone_test.Entities.Contact;

import java.util.ArrayList;
import java.util.List;

public class ContactsRepository {
    private ContactDB contactDB;
    private ContactsDao contactsDao;
    private ContactsListData contactsListData;
    private ContactsApi contactsApi;

    public ContactsRepository() {
        contactDB = Room.databaseBuilder(MyApplication.context, ContactDB.class, "contactDB").allowMainThreadQueries().fallbackToDestructiveMigration().build();
        contactsDao = contactDB.contactsDao();
        contactsListData = new ContactsListData();
        contactsApi = new ContactsApi(contactsListData, contactsDao);
    }

    class ContactsListData extends MutableLiveData<List<Contact>> {
        public ContactsListData() {
            super();
            setValue(new ArrayList<>());
        }
        @Override
        protected void onActive() {
            super.onActive();
            new Thread(() ->
                    contactsListData.postValue(new ArrayList<>())).start();
        }
    }

    public MutableLiveData<List<Contact>> getAll(String user){
        contactsListData.postValue(contactsDao.getContacts(user));
        return contactsListData;
    }

    public Contact get (String id, String user) {
        return contactsDao.get(id, user);
    }

    public Contact getByRealId (int realId) {
        return contactsDao.getByRealId(realId);
    }

    public void add (final Contact contact){
        contactsDao.insert(contact);
    }

    public void delete (final Contact contact){
        contactsDao.delete(contact);
    }

    public void update (final Contact contact) {
        contactsDao.update(contact);
    }

    public void reload () {
        contactsApi.getAll();
    }

}
