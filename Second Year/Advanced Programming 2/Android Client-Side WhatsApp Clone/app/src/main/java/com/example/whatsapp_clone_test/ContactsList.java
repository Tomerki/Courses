package com.example.whatsapp_clone_test;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;
import androidx.recyclerview.widget.DefaultItemAnimator;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.whatsapp_clone_test.Adapters.ContactsAdapter;
import com.example.whatsapp_clone_test.Entities.Contact;
import com.example.whatsapp_clone_test.ViewModels.ContactViewModel;

import java.util.ArrayList;
import java.util.List;

public class ContactsList extends AppCompatActivity {

    private ContactViewModel contactViewModel;
    private List<Contact> contactsList;
    private RecyclerView recyclerView;
    private ContactsAdapter adapter;
    private String userActive;
    private ContactsAdapter.RecycleViewClickListener listener;
    private Intent myIntent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contacts_list);
        myIntent = getIntent();
        userActive = myIntent.getStringExtra("userName");
        contactsList = new ArrayList<>();
        recyclerView = findViewById(R.id.lstContacts);
        setAdapter();

        contactViewModel = new ContactViewModel(userActive);
        contactViewModel.getContacts().observe(this, contactEntities -> {
            contactsList = contactEntities;
            adapter.setContacts(contactEntities);
        });

        setUserInfo();

        Button btnAddContact = findViewById(R.id.btnAddContact);
        btnAddContact.setOnClickListener( v -> {
            Intent i = new Intent(this, AddContact.class);
            i.putExtra("userName",userActive);
            startActivity(i);
        });

        Button settings = findViewById(R.id.settings);
        settings.setOnClickListener( v -> {
            Intent i = new Intent(this, Settings.class);
            i.putExtra("userName",userActive);
            startActivity(i);
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        contactsList.clear();
        contactsList.addAll(contactViewModel.getContacts().getValue());
        adapter.notifyDataSetChanged();
    }

    private void setAdapter () {
        setOnClickListener();
        adapter = new ContactsAdapter(contactsList, this, listener);
        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutManager);
        recyclerView.setItemAnimator(new DefaultItemAnimator());
        recyclerView.setAdapter(adapter);
    }

    private void setOnClickListener() {
        listener = contact -> {
            Intent i = new Intent(this, ChatActivity.class);
            i.putExtra("friendOf", contact.getFriendsOf());
            i.putExtra("contactId", contact.getRealId());
            i.putExtra("contactNickName", contact.getName());
            i.putExtra("userName", userActive);
            i.putExtra("stringId", contact.getId());
            startActivity(i);
        };
    }

    private void setUserInfo () {
        contactsList = contactViewModel.getContacts().getValue();
    }
}