package com.example.whatsapp_clone_test;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.result.ActivityResult;
import androidx.activity.result.ActivityResultCallback;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;

import com.example.whatsapp_clone_test.Entities.User;
import com.example.whatsapp_clone_test.ModalsActivities.registerError;

import de.hdodenhof.circleimageview.CircleImageView;

public class SignUp extends AppCompatActivity {

    private UserRepository userRepository;

    public SignUp() {
        userRepository = new UserRepository();
    }

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

            User user = new User(userName.getText().toString(), password.getText().toString(),
                    nickName.getText().toString());


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