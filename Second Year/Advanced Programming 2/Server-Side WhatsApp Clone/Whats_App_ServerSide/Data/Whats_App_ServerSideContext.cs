using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Whats_App_ServerSide;

namespace Whats_App_ServerSide.Data
{
    public class Whats_App_ServerSideContext : DbContext
    {
        public Whats_App_ServerSideContext (DbContextOptions<Whats_App_ServerSideContext> options)
            : base(options)
        {
        }

        public DbSet<Whats_App_ServerSide.Contact>? Contact { get; set; }

        public DbSet<Whats_App_ServerSide.Message>? Message { get; set; }

        public DbSet<Whats_App_ServerSide.User>? User { get; set; }
    }
}
