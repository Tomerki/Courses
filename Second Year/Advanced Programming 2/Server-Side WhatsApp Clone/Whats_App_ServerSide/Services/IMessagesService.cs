using Microsoft.AspNetCore.Mvc;

namespace Whats_App_ServerSide.Services
{
    public interface IMessagesService
    {
        public Task<ActionResult<IEnumerable<MessageResponse>>?> GetMessages(string id, string user);

        public Task<int> PostMessage(Message message, string id, string user);

        public Task<ActionResult<MessageResponse>>? GetMessage(int id2, string id, string user);

        public Task<int> PutMessage(int id2, string id, string content, string user);

        public Task<int> DeleteMessage(int id2, string id, string user);

        public Task<int> CheckTransferValid(Invitation invitation);
        public Task<Message> postTransfer(Transfer transfer);
        public Task<int> hasContact(string id, string user);


    }
}
