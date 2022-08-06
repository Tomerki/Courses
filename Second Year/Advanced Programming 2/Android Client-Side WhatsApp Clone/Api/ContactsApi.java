package com.example.whatsapp_clone_test.Api;

import androidx.lifecycle.MutableLiveData;

import com.example.whatsapp_clone_test.Daos.ContactsDao;
import com.example.whatsapp_clone_test.Entities.Contact;
import com.example.whatsapp_clone_test.Message;
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

    public ContactsApi(MutableLiveData<List<Contact>> contactsListData, ContactsDao contactsDao) {
        this.contactsDao = contactsDao;
        this.contacts = contactsListData;
        retrofit = new Retrofit.Builder()
         .baseUrl(MyApplication.context.getString(R.string.BaseUrl))
         .addConverterFactory(GsonConverterFactory.create())
         .build();
        contactServiceApi = retrofit.create(ContactServiceApi.class);
    }

    public void getAll () {
         Call<List<Contact>> call = contactServiceApi.getContacts("noamit1");
         call.enqueue(new Callback<List<Contact>>() {
             @Override
             public void onResponse(Call<List<Contact>> call, Response<List<Contact>> response) {
               new Thread(() -> {
                   contactsDao.delete(contactsDao.index().toArray(new Contact[0]));
                   contactsDao.insert(response.body().toArray(new Contact[0]));
                   contacts.postValue(contactsDao.getContacts("noamit1"));

               }).start();
             }
             @Override
             public void onFailure(Call<List<Contact>> call, Throwable t) {}
         });
    }
}
