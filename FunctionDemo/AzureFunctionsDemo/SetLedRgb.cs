using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.Net.Http;

namespace AzureFunctionsDemo
{
    public static class SetLedRgb
    {
        private static readonly HttpClient client = new HttpClient();

        [FunctionName("SetLedRgb")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Function, "get", Route = null)] HttpRequest req,
            ILogger log)
        {
            const string baseUrl = "http://82.64.172.94:8181/setRgb";

            var r = req.Query["red"];
            var g = req.Query["green"];
            var b = req.Query["blue"];

            await client.GetAsync($"{baseUrl}?red={r}&green={g}&blue={b}", HttpCompletionOption.ResponseContentRead);

            log.LogInformation("C# HTTP trigger function processed a request.");

            string responseMessage = $"Azure Function -> RGB value set to red={r}, green={g}, blue={b}";

            return new OkObjectResult(responseMessage);
        }
    }
}
