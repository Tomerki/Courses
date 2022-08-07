using System.ComponentModel.DataAnnotations;

namespace Whats_App_ServerSide
{
    public class User
    {
        [Key]
        [Required]
        public string Id { get; set; }

        public string? user { get; set; }

        [DataType(DataType.Password)]
        [Required]
        public string password { get; set; }

        //displayName
        public string? Name { get; set; }

    }
}
