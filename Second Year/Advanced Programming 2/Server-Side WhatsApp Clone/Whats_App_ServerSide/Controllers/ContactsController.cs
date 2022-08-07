using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Whats_App_ServerSide;
using Whats_App_ServerSide.Data;


namespace Whats_App_ServerSide.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ContactsController : ControllerBase
    {
        private readonly IContactsService _contactsService;

        public ContactsController(IContactsService contactsService)
        {
            _contactsService = contactsService;
        }

        // GET: api/Contacts
        [HttpGet]
        public async Task<ActionResult<IEnumerable<ContactResponse>>> GetContacts([FromQuery] string user)
        {

            var contact = await _contactsService.hasUser(user);

            if (contact == -1)
            {
                return NotFound();
            }
            var getResult = await _contactsService.GetContacts(user);
            return getResult;
        }

        // POST: api/Contacts
        [HttpPost]
        public async Task<ActionResult<Contact>> PostContact(Contact contact, [FromQuery] string user)
        {
            var postResult = await _contactsService.PostContact(contact, user);

            if (postResult == -1)
            {
                return Ok("already in contact list");
            }

            if (postResult == 1)
            {
                return Ok("sideBarOn");
            }

            return CreatedAtAction("GetContact", new { id = contact.RealId }, contact);

        }

        // GET: api/Contacts/5
        [HttpGet("{id}")]
        public async Task<ActionResult<ContactResponse>> GetContact(string id, [FromQuery] string user)
        {
            var contact = await _contactsService.GetContact(id, user);
            if (contact == null)
            {
                return NotFound();
            }

            return contact;

        }

        // PUT: api/Contacts/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutContact(string id, [FromQuery] string user, PutContant contactChanged)
        {
            var putResult = await _contactsService.PutContact(id, user, contactChanged);

            if (putResult == -1)
            {
                return NotFound();
            }

            return NoContent();

        }

        // DELETE: api/Contacts/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteContact(string id, [FromQuery] string user)
        {
            var deletetResult = await _contactsService.DeleteContact(id, user);

            if (deletetResult == -1)
            {
                return NotFound();
            }

            return NoContent();
        }

        // POST: api/invitations
        [HttpPost("/api/invitations")]
        public async Task<ActionResult<Contact>> postInvitation(Invitation invitation)
        {
            var checkInvitaionResult = await _contactsService.CheckInvitaionValid(invitation);

            if (checkInvitaionResult == -1)
            {
                return NotFound();
            }
            if (checkInvitaionResult == 1)
            {
                return Ok("already in contact list");
            }

            var invitaionResult = await _contactsService.postInvitation(invitation);

            return CreatedAtAction("GetContact", new { id = invitaionResult.RealId }, invitaionResult);
        }

    }


}
