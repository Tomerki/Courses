package com.example.whatsapp_clone_test.Api;

import com.example.whatsapp_clone_test.Entities.Contact;
import com.example.whatsapp_clone_test.Invitation;

import java.util.List;
import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.PUT;
import retrofit2.http.Path;
import retrofit2.http.Query;

public interface ContactServiceApi {

    @GET("Contacts")
    Call<List<Contact>> getContacts(@Query("user") String user);

    @GET("Contacts/{id}")
    Call<Contact> getContact(@Path("id") String id, @Query("user") String user);

    @GET("Contacts/realId/{id}")
    Call<Integer> getContactRealId(@Path("id") String id, @Query("user") String user);

    @POST("Contacts")
    Call<Void> postContact(@Body Contact contact,  @Query("user") String user);

    @PUT("Contacts/{id}")
    Call<Void> putContact(@Path("id") String id, @Body Contact contact,  @Query("user") String user);

    @PUT("Contacts/{id}")
    Call<Void> deleteContact(@Path("id") String id  ,@Query("user") String user);

    @POST("invitations")
    Call<Void> invitations(@Body Invitation invitation);

}
