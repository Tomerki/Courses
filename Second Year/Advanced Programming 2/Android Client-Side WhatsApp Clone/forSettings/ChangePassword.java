package com.example.whatsapp_clone_test.forSettings;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.Entities.User;
import com.example.whatsapp_clone_test.ModalsActivities.ChangePasswordError;
import com.example.whatsapp_clone_test.R;
import com.example.whatsapp_clone_test.UserRepository;

public class ChangePassword extends AppCompatActivity {

    private String userActive;
    private UserRepository userRepository;

    public ChangePassword() {
        userRepository = new UserRepository();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_password);

        TextView changePassword_prev = findViewById(R.id.changePassword_prev);
        TextView changePassword_new = findViewById(R.id.changePassword_new);
        TextView changePassword_confirm = findViewById(R.id.changePassword_confirm);

        Intent myIntent = getIntent();
        userActive = myIntent.getStringExtra("userName");

        Button btnExitChangePass = findViewById(R.id.btnExitChangePass);
        btnExitChangePass.setOnClickListener(v -> {
            finish();
        });

        Button btnOkChangePass = findViewById(R.id.btnOkChangePass);
        btnOkChangePass.setOnClickListener(v -> {

            if(changePassword_prev == null || changePassword_new == null || changePassword_confirm == null) {
                Intent i = new Intent(this, ChangePasswordError.class);
                startActivity(i);
                finish();
            }

            if(userRepository.getUser(userActive).getPassword().equals(changePassword_prev.getText().toString()) &&
                    userRepository.checkValidPassword( changePassword_new.getText().toString(),  changePassword_confirm.getText().toString())) {
                User u = userRepository.getUser(userActive);
                u.setPassword(changePassword_new.getText().toString());
                userRepository.update(u);
                finish();
            }

            else {
                Intent i = new Intent(this, ChangePasswordError.class);
                startActivity(i);
                finish();
            }

        });
    }
}