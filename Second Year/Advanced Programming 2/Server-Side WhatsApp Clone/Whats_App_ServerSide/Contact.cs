using System.ComponentModel.DataAnnotations;

namespace Whats_App_ServerSide
{
    public class Contact
    {
        [Key]
        public int RealId { get; set; }

        public String Id { get; set; }

        //nickname
        public String Name { get; set; } 

        public String Server { get; set; }

        public String? Last { get; set; }

        public DateTime? Lastdate { get; set; }

        public string? FriendOf { get; set; }

        public bool? sideBarOn { get; set; } = true;


    }
}
