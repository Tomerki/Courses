package com.example.whatsapp_clone_test;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import com.example.whatsapp_clone_test.Entities.Contact;
import com.example.whatsapp_clone_test.ViewModels.ContactViewModel;

public class AddContact extends AppCompatActivity {

    private ContactViewModel contactViewModel;
    private String userActive;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_contact);
        Intent myIntent = getIntent();
        userActive = myIntent.getStringExtra("userName");
        contactViewModel = new ContactViewModel(userActive);

        Button buttonAddContact = findViewById(R.id.buttonAddContact);
        buttonAddContact.setOnClickListener( v -> {
            TextView userName = findViewById(R.id.addContact_userName);
            TextView nickName = findViewById(R.id.addContact_nickname);
            TextView server = findViewById(R.id.addContact_server);

            Contact contact = new Contact(userName.getText().toString(),nickName.getText().toString(),
                    server.getText().toString(),userActive);
            contactViewModel.insert(contact, userActive);
            finish();
        });

        Button buttonExit = findViewById(R.id.buttonExit);
        buttonExit.setOnClickListener( v -> {
            finish();
        });
    }
}
