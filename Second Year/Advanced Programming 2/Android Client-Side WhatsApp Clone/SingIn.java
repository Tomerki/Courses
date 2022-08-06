package com.example.whatsapp_clone_test;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.ModalsActivities.loginError;

public class SingIn extends AppCompatActivity {

private UserRepository userRepository;

    public SingIn() {
        userRepository = new UserRepository();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sing_in);
        TextView btnLoginFromRegister = findViewById(R.id.registerFromLogin);
        btnLoginFromRegister.setOnClickListener( v -> {

            Intent i = new Intent(this, SignUp.class);
            startActivity(i);
        });

        Button btnLogin = findViewById(R.id.btnLogin);
        btnLogin.setOnClickListener( v -> {
            TextView userName = findViewById(R.id.signIn_userName);
            TextView password = findViewById(R.id.signIn_Password);

            if (userRepository.login(userName.getText().toString(), password.getText().toString()) != null) {
                Intent i = new Intent(this, ContactsList.class);
                i.putExtra("userName",userName.getText().toString());
                startActivity(i);
            } else {
                Intent i = new Intent(this, loginError.class);
                startActivity(i);
            }

        });
    }
}