using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Whats_App_ServerSide.Data;

namespace Whats_App_ServerSide.Services
{
    public class MessagesService : IMessagesService
    {
        private readonly Whats_App_ServerSideContext _context;
        public MessagesService(Whats_App_ServerSideContext context)
        {
            _context = context;
        }
        public async Task<int> CheckTransferValid(Invitation invitation)
        {
            throw new NotImplementedException();
        }

        public async Task<int> DeleteMessage(int id2, string id, string user)
        {
            var contactRealId = await ContactExists(id, user);
            if (contactRealId == -1)
            {
                return -1;
            }

            if (_context.Message == null)
            {
                return -1;
            }
            var msg = await _context.Message.FindAsync(id2);

            if (msg == null)
            {
                return -1;
            }

            if (msg.contactId == contactRealId)
            {
                _context.Message.Remove(msg);
                await _context.SaveChangesAsync();
                return 0;
            }

            return -1;
        }

        public async Task<ActionResult<MessageResponse>>? GetMessage(int id2, string id, string user)
        {
            var contactRealId = await ContactExists(id, user);
            if (contactRealId == -1)
            {
                return null;
            }

            if (_context.Message == null)
            {
                return null;
            }
            var msg = await _context.Message.FindAsync(id2);

            if (msg == null)
            {
                return null;
            }

            if (msg.contactId == contactRealId)
            {
                return (new MessageResponse { Id = msg.Id, Content = msg.Content, Created = msg.Created, Send = msg.Send });
            }

            return null;
        }

        public async Task<int> hasContact(string id, string user)
        {
            if (_context.Contact == null)
            {
                return -1;
            }

            var allContacts = await _context.Contact.ToListAsync();
            var contactOfUser = from u in allContacts
                                where u.FriendOf == user && u.Id == id
                                select u;

            if (!contactOfUser.Any())
            {
                return -1;
            }

            return 0;
        }

        public async Task<ActionResult<IEnumerable<MessageResponse>>?> GetMessages(string id, string user)
        {
            var allContacts = await _context.Contact.ToListAsync();
            var contactOfUser = from u in allContacts
                                where u.FriendOf == user && u.Id == id
                                select u;

            var c = contactOfUser.First();
            var contactRealId = c.RealId;

            if (_context.Message == null)
            {
                return null;
            }

            var allMessages = await _context.Message.ToListAsync();
            var contactMessages = from m in allMessages
                                  where m.contactId == contactRealId
                                  select m;

            List<MessageResponse> messageList = new List<MessageResponse>();
            foreach (var msg in contactMessages)
            {
                messageList.Add(new MessageResponse { Id = msg.Id, Content = msg.Content, Created = msg.Created, Send = msg.Send });
            }

            return messageList.ToArray();
        }

        public async Task<int> PostMessage(Message message, string id, string user)
        {
            if (_context.Contact == null)
            {
                return -1;
            }

            var allContacts = await _context.Contact.ToListAsync();
            var contactOfUser = from u in allContacts
                                where u.FriendOf == user && u.Id == id
                                select u;

            if (!contactOfUser.Any())
            {
                return -1;
            }

            var c = contactOfUser.First();
            var contactRealId = c.RealId;

            message.contactId = contactRealId;
            message.Send = true;
            message.Created = DateTime.Now;

            _context.Message.Add(message);
            await _context.SaveChangesAsync();
            return 0;
        }

        public async Task<Message> postTransfer(Transfer transfer)
        {
            var fromContact = transfer.from;
            var toUser = transfer.to;

            if (_context.Contact == null)
            {
                return null;
            }

            var allContacts = await _context.Contact.ToListAsync();
            var contactOfUser = from u in allContacts
                                where u.FriendOf == toUser && u.Id == fromContact
                                select u;

            if (!contactOfUser.Any())
            {
                return null;
            }

            var c = contactOfUser.First();
            var contactRealId = c.RealId;

            var message = new Message { contactId = contactRealId, Content = transfer.content, Created = DateTime.Now, Send = false };

            if (c.sideBarOn == false)
            {
                c.sideBarOn = true;
                _context.Entry(c).State = EntityState.Modified;
                await _context.SaveChangesAsync();
            }
            _context.Message.Add(message);
            await _context.SaveChangesAsync();

            return message;

        }

        public async Task<int> PutMessage(int id2, string id, string content, string user)
        {
            var contactRealId = await ContactExists(id, user);
            if (contactRealId == -1)
            {
                return -1;
            }

            if (_context.Message == null)
            {
                return -1;
            }
            var msg = await _context.Message.FindAsync(id2);

            if (msg == null)
            {
                return -1;
            }

            if (msg.contactId == contactRealId)
            {
                msg.Content = content;
                _context.Entry(msg).State = EntityState.Modified;
                await _context.SaveChangesAsync();
                return 0;
            }

            return -1;
        }

        private async Task<int> ContactExists(string id, string user)
        {
            if (_context.Contact == null)
            {
                return -1;
            }

            var allContacts = await _context.Contact.ToListAsync();
            var contactOfUser = from u in allContacts
                                where u.FriendOf == user && u.Id == id
                                select u;

            if (!contactOfUser.Any())
            {
                return -1;
            }

            var c = contactOfUser.First();
            var contactRealId = c.RealId;

            return contactRealId;
        }
    }
}
