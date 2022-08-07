using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using Whats_App_ServerSide.Controllers;
using Whats_App_ServerSide.Hubs;
using Whats_App_ServerSide.Services;
using Whats_App_ServerSide.Data;


var builder = WebApplication.CreateBuilder(args);


builder.Services.AddControllersWithViews();
builder.Services.AddSignalR();

builder.Services.AddDbContext<Whats_App_ServerSideContext>(options =>
    options.UseSqlServer(builder.Configuration.GetConnectionString("Whats_App_ServerSideContext") ?? throw new InvalidOperationException("Connection string 'Whats_App_ServerSideContext' not found.")));



builder.Services.AddCors(option =>
{
    option.AddPolicy("Allow All",
        builder =>
        {
            builder.SetIsOriginAllowed(origin => true)
            .AllowCredentials()
            .AllowAnyMethod()
            .AllowAnyHeader();
        }
        );
});

// Add services to the container.

builder.Services.AddControllers();
builder.Services.AddHttpContextAccessor();

// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

builder.Services.AddScoped<IContactsService, ContactsService>();
builder.Services.AddScoped<IMessagesService, MessagesService>();
builder.Services.AddScoped<IUsersService, UsersService>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseCors("Allow All");
app.UseRouting();
app.UseHttpsRedirection();
app.UseAuthentication();
app.UseAuthorization();

app.MapControllers();
app.MapHub<ChatsHub>("/Chats");


app.Run();
