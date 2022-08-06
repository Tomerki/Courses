package com.example.whatsapp_clone_test;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import com.example.whatsapp_clone_test.Adapters.MessagesAdapter;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class ChatActivity extends AppCompatActivity {

    private MessageViewModel viewModel;
    private List<Message> messages;
    private int ContactId;
    private MessagesAdapter adapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat);

        Intent myIntent = getIntent();
        String contactNickName = myIntent.getStringExtra("contactNickName");
        TextView contactViewName = findViewById(R.id.user_name_chat);
        contactViewName.setText(contactNickName);
        ContactId = myIntent.getIntExtra("contactId",0);

        messages = new ArrayList<>();

        RecyclerView lstMsg = findViewById(R.id.lstMsg);
        adapter = new MessagesAdapter(this);
        lstMsg.setAdapter(adapter);
        lstMsg.setLayoutManager(new LinearLayoutManager(this));

        viewModel = new ViewModelProvider(this).get(MessageViewModel.class);
        viewModel.getContactMessages(ContactId).observe(this, new Observer<List<Message>>() {
            @Override
            public void onChanged(List<Message> messagesList) {
                messages = messagesList;
                adapter.setMessages(messagesList);
            }
        });

        adapter.setMessages(viewModel.getContactMessages(ContactId).getValue());
        ImageButton sendMessageBtn = findViewById(R.id.sendMessageBtn);
        sendMessageBtn.setOnClickListener(view -> {
            EditText edEditTextChat = findViewById(R.id.editTextChat);
            if (!edEditTextChat.getText().toString().equals("")) {
                viewModel.add(new Message(ContactId, edEditTextChat.getText().toString(), getHour(), true));
                edEditTextChat.setText("");
                adapter.setMessages(viewModel.getContactMessages(ContactId).getValue());
                adapter.notifyDataSetChanged();

            }
        });

        ImageButton imageButton_prev = findViewById(R.id.imageButton_prev);
        imageButton_prev.setOnClickListener(view -> {
            finish();
        });

        SwipeRefreshLayout refreshLayout = findViewById(R.id.swipe_msg);
        refreshLayout.setOnRefreshListener(() -> {
            viewModel.reload();
            refreshLayout.setRefreshing(false);
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        messages.clear();
        messages.addAll(viewModel.getContactMessages(ContactId).getValue());
        adapter.notifyDataSetChanged();
    }

    String getHour(){
        @SuppressLint("SimpleDateFormat") DateFormat timeFormat = new SimpleDateFormat("HH:mm");
        return timeFormat.format(new Date());
    }

    String getDate(){
        @SuppressLint("SimpleDateFormat") SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss");
        return dateFormat.format(new Date());
    }

}