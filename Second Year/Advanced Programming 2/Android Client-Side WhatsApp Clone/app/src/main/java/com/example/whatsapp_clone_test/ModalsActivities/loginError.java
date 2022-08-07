package com.example.whatsapp_clone_test.ModalsActivities;

import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.R;

public class loginError extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login_error);

        Button buttonOkLogin = findViewById(R.id.buttonOkLogin);
        buttonOkLogin.setOnClickListener( v -> {
            finish();
        });
    }
}