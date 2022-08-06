package com.example.whatsapp_clone_test.ModalsActivities;

import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.R;

public class ChangePasswordError extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_password_error);

        Button btnOkChangePassErr = findViewById(R.id.btnOkChangePassErr);
        btnOkChangePassErr.setOnClickListener( v -> {
            finish();
        });
    }
}