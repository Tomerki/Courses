package com.example.whatsapp_clone_test;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.Entities.User;
import com.example.whatsapp_clone_test.ModalsActivities.loginError;
import com.google.firebase.iid.FirebaseInstanceId;

public class SingIn extends AppCompatActivity {

private UserRepository userRepository;
private String token;
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
            userRepository = new UserRepository(userName.getText().toString());
            User u = userRepository.login(userName.getText().toString(), password.getText().toString());

            if (u != null) {

                FirebaseInstanceId.getInstance().getInstanceId().addOnSuccessListener(SingIn.this, instanceIdResult -> {
                    String newtoken = instanceIdResult.getToken();
                    userRepository.createToken(newtoken);

                });
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