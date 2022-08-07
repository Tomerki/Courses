package com.example.whatsapp_clone_test.Api;

import androidx.lifecycle.MutableLiveData;

import com.example.whatsapp_clone_test.Daos.ContactsDao;
import com.example.whatsapp_clone_test.Entities.Contact;
import com.example.whatsapp_clone_test.Invitation;
import com.example.whatsapp_clone_test.MyApplication;
import com.example.whatsapp_clone_test.R;

import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class ContactsApi {

    private MutableLiveData<List<Contact>> contacts;
    Retrofit retrofit;
    ContactServiceApi contactServiceApi;
    private ContactsDao contactsDao;
    private String userActive;

    public ContactsApi(ContactsDao contactsDao, MutableLiveData<List<Contact>> contactsListData, String userActive) {
        this.contacts = contactsListData;
        this.userActive = userActive;
        this.contactsDao = contactsDao;
        retrofit = new Retrofit.Builder()
                .baseUrl(MyApplication.context.getString(R.string.BaseUrl))
                .addConverterFactory(GsonConverterFactory.create())
                .build();
        contactServiceApi = retrofit.create(ContactServiceApi.class);
    }

    public void getAll () {
        Call<List<Contact>> call = contactServiceApi.getContacts(userActive);
        call.enqueue(new Callback<List<Contact>>() {
            @Override
            //when the response is ready
            public void onResponse(Call<List<Contact>> call, Response<List<Contact>> response) {
                new Thread(() -> {
                    List<Contact> contacts1 = response.body();
                    contactsDao.delete(contactsDao.index().toArray(new Contact[0]));
                    for (Contact contact: contacts1) {
                        contact.setFriendsOf(userActive);
                        contactsDao.insert(contact);
                    }
                    for (Contact contact1: contactsDao.getContacts(userActive)) {
                        getContactRealId(contact1);
                    }
                    contacts.postValue(contactsDao.getContacts(userActive));
                }).start();
            }
            @Override
            public void onFailure(Call<List<Contact>> call, Throwable t) {}
        });
    }

    public void getContactRealId (Contact contact) {
        Call<Integer> call = contactServiceApi.getContactRealId(contact.getId(), userActive);
        call.enqueue(new Callback<Integer>() {
            @Override
            public void onResponse(Call<Integer> call, Response<Integer> response) {
                Contact prev = contact;
                prev.setRealId(response.body());
                contactsDao.update(contact);
                List<Contact> a = contactsDao.getContacts(userActive);
            }

            @Override
            public void onFailure(Call<Integer> call, Throwable t) {

            }
        });
    }
    public void add (Contact contact) {
        Call<Void> call = contactServiceApi.postContact(contact, userActive);
        call.enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {}

            @Override
            public void onFailure(Call<Void> call, Throwable t) {}
        });
        String s = "http://" + contact.getServer() + "/api/";
        Retrofit retrofit2 = new Retrofit.Builder()
                .baseUrl(s)
                .addConverterFactory(GsonConverterFactory.create())
                .build();
        ContactServiceApi contactServiceApi1 = retrofit2.create(ContactServiceApi.class);
        Invitation i = new Invitation(userActive, contact.getId(), "10.0.2.2:7288");
        Call<Void> call2 = contactServiceApi1.invitations(i);
        call2.enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call2, Response<Void> response2) {
                getAll();
            }

            @Override
            public void onFailure(Call<Void> call2, Throwable t2) {}
        });
    }

}