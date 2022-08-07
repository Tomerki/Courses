using System.ComponentModel.DataAnnotations;

namespace Whatsapp_Rating.Models
{
    public class ClientRate
    {
        public int Id { get; set; }

        [Required]
        public string Name { get; set; }

        [Required]
        [Range(1,5)]
        public int Rate { get; set; }

        [Required]
        [MaxLength(40)]
        public string FeedBack { get; set; }

        public string? Hour { get; set; }

        public string? Date { get; set; }

    }
}
