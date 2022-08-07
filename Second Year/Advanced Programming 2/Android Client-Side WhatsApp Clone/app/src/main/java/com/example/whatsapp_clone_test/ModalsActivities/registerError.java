package com.example.whatsapp_clone_test.ModalsActivities;

import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.R;

public class registerError extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register_error);

        Button buttonOkRegister = findViewById(R.id.buttonOkRegister);
        buttonOkRegister.setOnClickListener( v -> {
            finish();
        });
    }

}