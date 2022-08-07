using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Whats_App_ServerSide.Controllers;
using Whats_App_ServerSide.Data;

namespace Whats_App_ServerSide.Services
{
    public class ContactsService : IContactsService
    {

        private readonly Whats_App_ServerSideContext _context;
        public ContactsService(Whats_App_ServerSideContext context)
        {
            _context = context;
        }

        public async Task<int> DeleteContact(string id, string user)
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

            _context.Contact.Remove(c);
            await _context.SaveChangesAsync();

            return 0;
        }

        public async Task<ActionResult<ContactResponse>>? GetContact(string id, string user)
        {
            if (_context.Contact == null)
            {
                return null;
            }

            var allContacts = await _context.Contact.ToListAsync();
            var contactOfUser = from u in allContacts
                                where u.FriendOf == user && u.Id == id
                                select u;

            if (!contactOfUser.Any())
            {
                return null;
            }

            var c = contactOfUser.First();
            var msgId = await LastMessage(c.RealId, user);

            if (msgId == -1)
            {
                return new ContactResponse { Id = c.Id, Name = c.Name, Server = c.Server, Last = null, Lastdate = null };
            }

            var msg = await _context.Message.FindAsync(msgId);
            return new ContactResponse { Id = c.Id, Name = c.Name, Server = c.Server, Last = msg.Content, Lastdate = msg.Created };

        }

        public async Task<ActionResult<IEnumerable<ContactResponse>>?> GetContacts(string user)
        {
            if (_context.Contact == null)
            {
                return null;
            }

            var allContacts = await _context.Contact.ToListAsync();
            var contactsofUser = from u in allContacts
                                 where u.FriendOf == user
                                 select u;

            List<ContactResponse> contactsList = new List<ContactResponse>();
            foreach (var c in contactsofUser)
            {
                var msgId = await LastMessage(c.RealId, user);
                if (msgId == -1)
                {
                    contactsList.Add(new ContactResponse { Id = c.Id, Name = c.Name, Server = c.Server, Last = null, Lastdate = null });
                }
                else
                {
                    var msg = await _context.Message.FindAsync(msgId);
                    contactsList.Add(new ContactResponse { Id = c.Id, Name = c.Name, Server = c.Server, Last = msg.Content, Lastdate = msg.Created });
                }
            }

            return contactsList.ToArray();
        }

        public async Task<int> PostContact(Contact contact, string user)
        {
            if (_context.Contact == null)
            {
                contact.FriendOf = user;
                contact.sideBarOn = true;
                _context.Contact.Add(contact);
                await _context.SaveChangesAsync();
                return 0;
            }

            var allContacts = await _context.Contact.ToListAsync();
            var contactOfUser = from u in allContacts
                                where u.FriendOf == user && u.Id == contact.Id
                                select u;

            if (!contactOfUser.Any())
            {
                contact.FriendOf = user;
                _context.Contact.Add(contact);
                await _context.SaveChangesAsync();
                return 0;
            }

            else
            {
                var firstContact = contactOfUser.First();

                if (firstContact.sideBarOn == true)
                {
                    return -1;
                }

                firstContact.sideBarOn = true;
                _context.Entry(firstContact).State = EntityState.Modified;
                await _context.SaveChangesAsync();
                return 1;
            }

        }

        public async Task<int> CheckInvitaionValid(Invitation invitation)
        {
            var fromContact = invitation.from;
            var toUser = invitation.to;

            var user = await _context.User.FindAsync(toUser);

            if (user == null)
            {
                return -1;
            }
            if (_context.Contact == null)
            {
                return 0;
            }

            var allContacts = await _context.Contact.ToListAsync();
            var contactOfUser = from u in allContacts
                                where u.FriendOf == toUser && u.Id == fromContact
                                select u;

            if (contactOfUser.Any())
            {
                return 1;
            }

            return 0;

        }
        public async Task<Contact> postInvitation(Invitation invitation)
        {
            var fromContact = invitation.from;
            var toUser = invitation.to;

            var user = await _context.User.FindAsync(toUser);

            var newContact = new Contact { Id = fromContact, FriendOf = toUser, Name = invitation.from, Server = invitation.server, sideBarOn = false };
            _context.Contact.Add(newContact);
            await _context.SaveChangesAsync();
            return newContact;
        }

        public async Task<int> PutContact(string id, string user, PutContant contactChanged)
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

            if (contactChanged.Server != null)
            {
                c.Server = contactChanged.Server;
            }

            if (contactChanged.Name != null)
            {
                c.Name = contactChanged.Name;
            }

            _context.Entry(c).State = EntityState.Modified;

            await _context.SaveChangesAsync();

            return 0;
        }

        public async Task<int> hasUser( string user)
        {
            if (_context.Contact == null)
            {
                return -1;
            }

            var userFind = await _context.User.FindAsync(user);
            if (userFind == null)
            {
                return -1;
            }

            return 0;
        }

        private async Task<int> LastMessage(int contactID, string user)
        {
            if (_context.Message == null)
            {
                return -1;
            }

            var allMessages = await _context.Message.ToListAsync();
            var contactMessages = from m in allMessages
                                  where m.contactId == contactID
                                  select m;

            if (!contactMessages.Any())
            {
                return -1;
            }

            var lastmsgId = contactMessages.Last().Id;

            return lastmsgId;
        }


    }
}
