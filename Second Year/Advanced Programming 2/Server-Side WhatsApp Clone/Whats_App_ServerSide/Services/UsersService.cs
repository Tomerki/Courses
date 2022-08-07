using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Whats_App_ServerSide.Data;

namespace Whats_App_ServerSide.Services
{
    public class UsersService : IUsersService
    {

        private readonly Whats_App_ServerSideContext _context;
        public UsersService(Whats_App_ServerSideContext context)
        {
            _context = context;
        }

        public async Task<int> Login(string id, User logginUser)
        {
            if (_context.User == null)
            {
                return -1;
            }
            var u = await _context.User.FindAsync(id);

            if (u == null)
            {
                return -1;
            }

            if (u.password != logginUser.password)
            {
                return -1;
            }

            return 0;
        }

        public async Task<int> Register(User newUser)
        {
            newUser.user = newUser.Id;
            _context.User.Add(newUser);
            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateException)
            {
                if (UserExists(newUser.Id))
                {
                    return -1;
                }
                else
                {
                    throw;
                }
            }

            return 0;
        }

        private bool UserExists(string id)
        {
            return (_context.User?.Any(e => e.Id == id)).GetValueOrDefault();
        }
    }
}
