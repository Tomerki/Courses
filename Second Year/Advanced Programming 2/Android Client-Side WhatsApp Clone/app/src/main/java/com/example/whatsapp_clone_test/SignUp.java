package com.example.whatsapp_clone_test;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.Entities.User;
import com.example.whatsapp_clone_test.ModalsActivities.registerError;

public class SignUp extends AppCompatActivity {


    private UserRepository userRepository;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sign_up);

        TextView btnLoginFromRegister = findViewById(R.id.LoginFromRegister);
        btnLoginFromRegister.setOnClickListener(v -> {
            Intent i = new Intent(this, SingIn.class);
            startActivity(i);
        });

        Button btnRegister = findViewById(R.id.btnRegister);
        btnRegister.setOnClickListener(v -> {
            TextView userName = findViewById(R.id.input_userName);
            TextView password = findViewById(R.id.input_Password);
            TextView confirmPassword = findViewById(R.id.input_confirmPassword);
            TextView nickName = findViewById(R.id.input_displayName);

            userRepository = new UserRepository(userName.getText().toString());
            User user = new User(userName.getText().toString(), password.getText().toString(),
                    nickName.getText().toString());
            user.setProfilePicture(Uri.parse("android.resource://com.example.whatsapp_clone_test/drawable/image_name").getPath());


            if (userRepository.register(user, confirmPassword.getText().toString())) {
                Intent i = new Intent(this, SingIn.class);
                startActivity(i);
            } else {
                Intent i = new Intent(this, registerError.class);
                startActivity(i);
            }
        });
    }


}