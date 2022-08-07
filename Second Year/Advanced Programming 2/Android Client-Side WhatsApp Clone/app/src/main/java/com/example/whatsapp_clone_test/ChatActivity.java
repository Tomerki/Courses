package com.example.whatsapp_clone_test;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.Resources;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import com.example.whatsapp_clone_test.Adapters.MessagesAdapter;
import com.example.whatsapp_clone_test.ViewModels.ContactViewModel;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;


public class ChatActivity extends AppCompatActivity {

    private MessageViewModel viewModel;
    private ContactViewModel contactViewModel;
    private List<Message> messages;
    private String contactUserName;
    private MessagesAdapter adapter;
    private BroadcastReceiver broadcastReceiver;
    private RecyclerView lstMsg;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat);

        Intent myIntent = getIntent();
        String contactNickName = myIntent.getStringExtra("contactNickName");
        TextView contactViewName = findViewById(R.id.user_name_chat);
        contactViewName.setText(contactNickName);
        contactUserName = myIntent.getStringExtra("stringId");

        messages = new ArrayList<>();
        lstMsg = findViewById(R.id.lstMsg);
        adapter = new MessagesAdapter(this);
        lstMsg.setLayoutManager(new LinearLayoutManager(this));
        lstMsg.setAdapter(adapter);
        String userName = myIntent.getStringExtra("userName");
        viewModel = new MessageViewModel(userName, myIntent.getStringExtra("stringId"));
        contactViewModel = new ContactViewModel(userName);

        viewModel.getContactMessages().observe(this, messagesList -> {
            adapter.setMessages(messagesList);
            messages = messagesList;
            lstMsg.getLayoutManager().scrollToPosition(messages.size() - 1);
        });


        //adapter.setMessages(viewModel.getContactMessages().getValue());
        lstMsg.scrollToPosition(messages.size() - 1);
        ImageButton sendMessageBtn = findViewById(R.id.sendMessageBtn);
        EditText edEditTextChat = findViewById(R.id.editTextChat);
        sendMessageBtn.setOnClickListener(view -> {
            if (!edEditTextChat.getText().toString().equals("")) {
                int contactid = contactViewModel.getContact(contactUserName).getRealId();
                viewModel.add(new Message(contactid, edEditTextChat.getText().toString(), getDate(), true));
                edEditTextChat.setText("");
                adapter.setMessages(viewModel.getContactMessages().getValue());
                adapter.notifyDataSetChanged();
                lstMsg.getLayoutManager().scrollToPosition(messages.size() - 1);
            }
        });

        ImageButton imageButton_prev = findViewById(R.id.imageButton_prev);
        imageButton_prev.setOnClickListener(v -> finish());

        SwipeRefreshLayout refreshLayout = findViewById(R.id.swipe_msg);
        refreshLayout.setOnRefreshListener(() -> {
            viewModel.reload();
            refreshLayout.setRefreshing(false);
        });

        broadcastReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                viewModel.getAll(edEditTextChat.getText().toString());
                adapter.setMessages(viewModel.getContactMessages().getValue());
                adapter.notifyDataSetChanged();
                lstMsg.scrollToPosition(messages.size() - 1);
            }
        };

        LocalBroadcastManager.getInstance(this).registerReceiver(broadcastReceiver,new IntentFilter("1001"));
    }
    @Override
    protected void onResume() {
        super.onResume();
        messages.clear();
        messages.addAll(viewModel.getContactMessages().getValue());
        adapter.notifyDataSetChanged();
    }

    String getHour(){
        DateFormat timeFormat = new SimpleDateFormat("HH:mm");
        return timeFormat.format(new Date());
    }

    String getDate(){
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss");
        return dateFormat.format(new Date());
    }

    public String setDateFormat(String date, String oldPattern, String newPattern)  {
        DateFormat originalFormat = new SimpleDateFormat(oldPattern);
        DateFormat targetFormat = new SimpleDateFormat(newPattern);
        Date dateformat = null;
        try {
            dateformat = originalFormat.parse(date);
        } catch (ParseException e) {
            e.printStackTrace();
        }
        return targetFormat.format(dateformat);
    }

}