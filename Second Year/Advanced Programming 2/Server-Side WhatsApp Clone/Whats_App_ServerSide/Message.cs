using System.ComponentModel.DataAnnotations;

namespace Whats_App_ServerSide
{
    public class Message
    {
        public int Id { get; set; }

        [Required]
        public string Content { get; set; }

        public DateTime? Created { get; set; }

        public bool? Send { get; set; }

        public int? contactId { get; set; }
    }
}
