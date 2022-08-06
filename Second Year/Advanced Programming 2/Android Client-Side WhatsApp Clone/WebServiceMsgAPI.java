package com.example.whatsapp_clone_test;

import java.util.List;
import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.DELETE;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.Path;

public interface WebServiceMsgAPI {

    @GET("Messages/{id}")
    Call<List<Message>> getMessages();

    @POST("Messages")
    Call<Void> createMessage(@Body Message message);

    @DELETE("posts/{id}")
    Call<Void> deleteMessage(@Path("id") int id);
}
