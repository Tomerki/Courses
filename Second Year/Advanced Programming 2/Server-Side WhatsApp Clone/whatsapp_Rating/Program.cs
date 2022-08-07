using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using Whatsapp_Rating.Data;
var builder = WebApplication.CreateBuilder(args);
builder.Services.AddDbContext<Whatsapp_RatingContext>(options =>
    options.UseSqlServer(builder.Configuration.GetConnectionString("Whatsapp_RatingContext") ?? throw new InvalidOperationException("Connection string 'Whatsapp_RatingContext' not found.")));

builder.Services.AddCors(option =>
{
    option.AddPolicy("Allow All",
        builder =>
        {
            builder.SetIsOriginAllowed(origin => true)
            .AllowAnyOrigin()
            .AllowAnyMethod()
            .AllowAnyHeader();
        }
        );
});


// Add services to the container.
builder.Services.AddControllersWithViews();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}


app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseCors("Allow All");
app.UseAuthorization();


app.MapControllerRoute(
    name: "default",
    pattern: "{controller=ClientRates}/{action=Index}/{id?}");

app.Run();
