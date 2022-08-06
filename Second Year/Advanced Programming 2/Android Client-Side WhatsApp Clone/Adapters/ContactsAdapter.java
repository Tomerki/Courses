package com.example.whatsapp_clone_test.Adapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.whatsapp_clone_test.Entities.Contact;
import com.example.whatsapp_clone_test.R;

import java.util.List;

public class ContactsAdapter extends RecyclerView.Adapter<ContactsAdapter.ContactsViewHolder> {

    public interface RecycleViewClickListener {
        void onClick (Contact contact);
    }

    private List<Contact> contacts;
    private LayoutInflater inflater;
    private RecycleViewClickListener listener;

    public ContactsAdapter(List<Contact> contacts, Context context, RecycleViewClickListener listener) {
        this.contacts = contacts;
        inflater = LayoutInflater.from(context);
        this.listener = listener;
    }

    public class ContactsViewHolder extends RecyclerView.ViewHolder {
        private TextView name;
        private TextView message;
        private TextView messageTime;
        private TextView contactUserName;
        private ImageView profilePic;
        public View view;

        public ContactsViewHolder(View itemView) {
            super(itemView);
            this.name = itemView.findViewById(R.id.contact_name);
            this.message = itemView.findViewById(R.id.contact_message);
            this.messageTime = itemView.findViewById(R.id.contact_massageTime);
            this.profilePic = itemView.findViewById(R.id.contact_profilePic);
            this.contactUserName = itemView.findViewById(R.id.contact_userName);
            this.view = itemView;
        }

        public void bind(final Contact contact, final RecycleViewClickListener listener) {
            itemView.setOnClickListener(new View.OnClickListener() {
                @Override public void onClick(View v) {
                    listener.onClick(contact);
                }
            });
        }
    }

    @NonNull
    @Override
    public ContactsAdapter.ContactsViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View itemView = inflater.inflate(R.layout.list_contacts, parent, false);
        return new ContactsViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(ContactsViewHolder holder, int position) {
        String name = contacts.get(position).getName();
        String message = contacts.get(position).getLast();
        String messageTime = contacts.get(position).getLastDate();
        String contactUserName = contacts.get(position).getId();

        holder.name.setText(name);
        holder.message.setText(message);
        holder.messageTime.setText(messageTime);
        holder.contactUserName.setText(contactUserName);

        holder.bind(contacts.get(position), listener);
    }

    @Override
    public int getItemCount() {
        return contacts.size();
    }

    public void setContacts(List<Contact> contacts1) {
        contacts = contacts1;
        notifyDataSetChanged();
    }

    public List<Contact> getContacts() {
        return contacts;
    }



}
