using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Whats_App_ServerSide;
using Whats_App_ServerSide.Data;
using Whats_App_ServerSide.Services;

namespace Whats_App_ServerSide.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class UsersController : ControllerBase
    {
        private readonly IUsersService _usersService;

        public UsersController(IUsersService usersService)
        {
            _usersService = usersService;
        }

        // Post: api/Login/5
        [HttpPost("/api/login/{id}")]
        public async Task<ActionResult<User>> Login(string id, User logginUser)
        {

            var loginResult = await _usersService.Login(id, logginUser);
            if (loginResult == -1)
            {
                return BadRequest();
            }
            return Ok();

        }

        // POST: api/Register
        [HttpPost("/api/Register")]
        public async Task<ActionResult<User>> Register(User newUser)
        {

            var registerResult = await _usersService.Register(newUser);
            if (registerResult == -1)
            {
                return BadRequest();
            }
            return Ok();

        }

    }
}
