package com.example.whatsapp_clone_test;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;
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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contacts_list);

        Intent myIntent = getIntent();
        userActive = myIntent.getStringExtra("userName");

        contactsList = new ArrayList<>();
        recyclerView = findViewById(R.id.lstContacts);
        setAdapter();

        contactViewModel = new ContactViewModel(userActive);
        contactViewModel.getContacts(userActive).observe(this, new Observer<List<Contact>>() {
            @Override
            public void onChanged(List<Contact> contactEntities) {
                contactsList = contactEntities;
                adapter.setContacts(contactEntities);
            }
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
        contactsList.addAll(contactViewModel.getContacts(userActive).getValue());
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
        listener = new ContactsAdapter.RecycleViewClickListener() {
            @Override
            public void onClick(Contact contact) {
                Intent i = new Intent(getApplicationContext(), ChatActivity.class);
                i.putExtra("friendOf", contact.getFriendsOf());
                i.putExtra("contactId", contact.getRealId());
                i.putExtra("contactNickName", contact.getName());
                startActivity(i);
            }
        };
    }

    private void setUserInfo () {
        contactsList = contactViewModel.getContacts(userActive).getValue();
    }
}