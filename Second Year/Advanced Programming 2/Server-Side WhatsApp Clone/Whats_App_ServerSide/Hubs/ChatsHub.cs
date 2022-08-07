using Microsoft.AspNetCore.SignalR;

namespace Whats_App_ServerSide.Hubs
{
    public class ChatsHub : Hub
    {
        public async Task connectUserToServer(string user)
        {
            await Groups.AddToGroupAsync(Context.ConnectionId, user);
        }

    }
}
