namespace Whats_App_ServerSide
{
    public class Invitation
    {
        public int Id { get; set; }

        //the contact that invite 
        public string from { get; set; }

        //the user that is invited
        public string to { get; set; }

        //the server of the contact
        public string server { get; set; }
    }
}
