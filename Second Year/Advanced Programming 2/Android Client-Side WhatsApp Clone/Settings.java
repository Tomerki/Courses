package com.example.whatsapp_clone_test;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.forSettings.ChangePassword;

public class Settings extends AppCompatActivity {

    private String userActive;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        Intent myIntent = getIntent();
        userActive = myIntent.getStringExtra("userName");

        Button btnLogout = findViewById(R.id.btnLogout);
        btnLogout.setOnClickListener(v -> {
            Intent i = new Intent (this, SingIn.class);
            startActivity(i);
        });

        Button btnExitSettings = findViewById(R.id.btnExitSettings);
        btnExitSettings.setOnClickListener(v -> {
            finish();
        });

        Button btnChangePass = findViewById(R.id.btnChangePass);
        btnChangePass.setOnClickListener(v -> {
            Intent i = new Intent (this, ChangePassword.class);
            i.putExtra("userName", userActive);
            startActivity(i);
        });

    }
}