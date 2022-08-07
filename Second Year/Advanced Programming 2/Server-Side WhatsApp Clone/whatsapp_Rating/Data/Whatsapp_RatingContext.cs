using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Whatsapp_Rating.Models;

namespace Whatsapp_Rating.Data
{
    public class Whatsapp_RatingContext : DbContext
    {
        public Whatsapp_RatingContext (DbContextOptions<Whatsapp_RatingContext> options)
            : base(options)
        {
        }

        public DbSet<Whatsapp_Rating.Models.ClientRate>? ClientRate { get; set; }
    }
}
