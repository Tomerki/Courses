using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Whatsapp_Rating.Data;
using Whatsapp_Rating.Models;

namespace Whatsapp_Rating.Controllers
{
    public class ClientRatesController : Controller
    {
        private readonly Whatsapp_RatingContext _context;
        private double average;

        public ClientRatesController(Whatsapp_RatingContext context)
        {
            _context = context;
        }

        // GET: ClientRates
        public async Task<IActionResult> Index(string query)
        {
            double average = await CalculateAverage();
            if (average > 0)
            {
                ViewBag.Average = Math.Round(average, 2);
                if (query != null)
                {
                    var q = _context.ClientRate.Where(rate => rate.Name.Contains(query));
                    return Json(await q.ToListAsync());
                }
            }
            else
            {
                ViewBag.Average = "No rating given yet";
            }
            return View(await _context.ClientRate.ToListAsync());
        }

        // GET: ClientRates/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null || _context.ClientRate == null)
            {
                return NotFound();
            }

            var clientRate = await _context.ClientRate
                .FirstOrDefaultAsync(m => m.Id == id);
            if (clientRate == null)
            {
                return NotFound();
            }

            return View(clientRate);
        }

        // GET: ClientRates/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: ClientRates/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Name,Rate,FeedBack,Hour,Date")] ClientRate clientRate)
        {
            if (ModelState.IsValid)
            {

                clientRate.Hour = DateTime.Now.ToString("hh:mm tt");
                clientRate.Date = DateTime.Now.ToString("dddd, dd MMMM yyyy");
                _context.Add(clientRate);
                await _context.SaveChangesAsync();

                return RedirectToAction(nameof(Index));
            }
            return View(clientRate);
        }

        // GET: ClientRates/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null || _context.ClientRate == null)
            {
                return NotFound();
            }

            var clientRate = await _context.ClientRate.FindAsync(id);
            if (clientRate == null)
            {
                return NotFound();
            }

            return View(clientRate);
        }

        /*        public async Task<IActionResult> Search(string query)
                {
                    if (query == null || _context.ClientRate == null)
                    {
                        return NotFound();
                    }

                    var clientRate = await _context.ClientRate.FindAsync(id);
                    if (clientRate == null)
                    {
                        return NotFound();
                    }

                    return View(clientRate);
                }*/


        // POST: ClientRates/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name,Rate,FeedBack,Hour,Date")] ClientRate clientRate)
        {
            if (id != clientRate.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    clientRate.Hour = DateTime.Now.ToString("hh:mm tt");
                    clientRate.Date = DateTime.Now.ToString("dddd, dd MMMM yyyy");
                    _context.Update(clientRate);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!ClientRateExists(clientRate.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(clientRate);
        }

        // GET: ClientRates/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null || _context.ClientRate == null)
            {
                return NotFound();
            }

            var clientRate = await _context.ClientRate
                .FirstOrDefaultAsync(m => m.Id == id);
            if (clientRate == null)
            {
                return NotFound();
            }

            return View(clientRate);
        }

        // POST: ClientRates/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            if (_context.ClientRate == null)
            {
                return Problem("Entity set 'Whatsapp_RatingContext.ClientRate'  is null.");
            }
            var clientRate = await _context.ClientRate.FindAsync(id);
            if (clientRate != null)
            {
                _context.ClientRate.Remove(clientRate);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool ClientRateExists(int id)
        {
            return (_context.ClientRate?.Any(e => e.Id == id)).GetValueOrDefault();
        }

        private async Task<double> CalculateAverage()
        {
            double sum = 0;
            double clients = 0;
            var table = await _context.ClientRate.ToListAsync();
            foreach (var item in table)
            {
                clients++;
                sum = sum + item.Rate;
            }

            if (sum == 0)
            {
                return 0;
            }
            double average = sum / clients;
            return average;
        }
    }
}
