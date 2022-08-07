package com.example.whatsapp_clone_test;

import java.util.List;
import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.DELETE;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.Path;
import retrofit2.http.Query;

public interface WebServiceMsgAPI {

    @GET("Contacts/{id}/Messages")
    Call<List<Message>> getMessages(@Path("id") String Id, @Query("user") String user);

    @POST("Contacts/{id}/Messages")
    Call<Void> postMessage(@Body Message message, @Path("id") String Id, @Query("user") String user);

    @DELETE("Contacts/Messages/{id}")
    Call<Void> deleteMessages(@Path("id") int id);

    @POST("transfer")
    Call<Message> transfer (@Body Transfer transfer);
}
