using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.SignalR;
using Microsoft.EntityFrameworkCore;
using Whats_App_ServerSide;
using Whats_App_ServerSide.Data;
using Whats_App_ServerSide.Hubs;
using Whats_App_ServerSide.Services;

namespace Whats_App_ServerSide.Controllers
{
    [Route("api/contacts")]
    [ApiController]
    public class MessagesController : ControllerBase
    {
        private readonly IMessagesService _messagesService;
        private readonly IHubContext<ChatsHub> _myHub;
        public MessagesController(IMessagesService messagesService, IHubContext<ChatsHub> myHub)
        {
            _messagesService = messagesService;
            _myHub = myHub;
        }

        // GET: api/contacts/{id}/Messages
        [HttpGet("{id}/[Controller]")]
        public async Task<ActionResult<IEnumerable<MessageResponse>>> GetMessages(string id, [FromQuery] string user)
        {

            var findContactExsist = await _messagesService.hasContact(id, user);

            if (findContactExsist == -1)
            {
                return NotFound();
            }

            var messages = await _messagesService.GetMessages(id, user);
            return messages;

        }

        // POST: api/contacts/{id}/Messages
        [HttpPost("{id}/[Controller]")]
        public async Task<ActionResult<Message>> PostMessage(Message message, string id, [FromQuery] string user)
        {
            var postResult = await _messagesService.PostMessage(message, id, user);


            if (postResult == -1)
            {
                return NotFound();
            }

            return CreatedAtAction("GetMessages", new { id = message.Id }, message);

        }

        // GET: api/contacts/{id}/Messages/{id2}
        [HttpGet("{id}/[Controller]/{id2}")]
        public async Task<ActionResult<MessageResponse>> GetMessage(int id2, string id, [FromQuery] string user)
        {

            var getResult = await _messagesService.GetMessage(id2, id, user);

            if (getResult == null)
            {
                return NotFound();
            }
            return getResult;

        }

        // PUT: api/contacts/{id}/Messages/{id2}
        [HttpPut("{id}/[Controller]/{id2}")]
        public async Task<IActionResult> PutMessage(int id2, string id, string content, [FromQuery] string user)
        {

            var putResult = await _messagesService.PutMessage(id2, id, content, user);
            if (putResult == -1)
            {
                return NotFound();
            }
            return NoContent();

        }

        // DELETE: api/contacts/{id}/Messages/{id2}
        [HttpDelete("{id}/[Controller]/{id2}")]
        public async Task<IActionResult> DeleteMessage(int id2, string id, [FromQuery] string user)
        {

            var deletetResult = await _messagesService.DeleteMessage(id2, id, user);
            if (deletetResult == -1)
            {
                return NotFound();
            }
            return NoContent();

        }

        // POST: api/transfer
        [HttpPost("/api/transfer")]
        public async Task<ActionResult<Message>> postTransfer(Transfer transfer)
        {
            var fromContact = transfer.from;
            var toUser = transfer.to;
            var transferResult = await _messagesService.postTransfer(transfer);

            if (transferResult == null)
            {
                return NotFound();
            }

            await _myHub.Clients.Groups(toUser).SendAsync("ReceiveMessage");

            return CreatedAtAction("GetMessages", new { id = transferResult.Id }, transferResult);


        }
    }
}
