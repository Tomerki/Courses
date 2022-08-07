package com.example.whatsapp_clone_test.ModalsActivities;

import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.R;

public class AddContactError extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_contact_error);

        Button btnOkErrAddContact = findViewById(R.id.btnOkErrAddContact);
        btnOkErrAddContact.setOnClickListener( v -> {
            finish();
        });
    }
}