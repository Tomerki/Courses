namespace Whats_App_ServerSide
{
    public class MessageResponse
    {
        public int Id { get; set; }

        public string Content { get; set; }

        public DateTime? Created { get; set; }

        public bool? Send { get; set; }
    }
}
