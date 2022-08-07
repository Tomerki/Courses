package com.example.whatsapp_clone_test.Api;

import com.example.whatsapp_clone_test.Entities.User;
import java.util.List;
import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.Path;
import retrofit2.http.Query;

public interface UserServiceApi {

    @POST("api/login/{id}")
    Call<User> login(@Path("id") String id, @Body User user);

    @POST("api/Register")
    Call<Void> register(@Body User user);

    @GET("users")
    Call<List<User>> index();

    @POST("api/createToken")
    Call<Void> createToken (@Body String token, @Query("user") String user);
}
