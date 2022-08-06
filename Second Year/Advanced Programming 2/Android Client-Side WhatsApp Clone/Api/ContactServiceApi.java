package com.example.whatsapp_clone_test.Api;

import com.example.whatsapp_clone_test.Entities.Contact;

import java.util.List;

import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.Path;
import retrofit2.http.Query;

public interface ContactServiceApi {

    @GET("Contacts")
    Call<List<Contact>> getContacts(@Query("id") String user);

    @GET("Contacts/{id}")
    Call<Contact> getContact(@Path("id") String id, @Query("id") String user);

    @POST("Contacts")
    Call<Void> createPost(@Body Contact contact);

}
