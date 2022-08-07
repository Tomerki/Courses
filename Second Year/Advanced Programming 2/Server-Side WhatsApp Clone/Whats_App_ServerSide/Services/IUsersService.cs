using Microsoft.AspNetCore.Mvc;

namespace Whats_App_ServerSide.Services
{
    public interface IUsersService
    {

        public Task<int> Login(string id, User logginUser);
        public Task<int> Register(User newUser);

    }
}
