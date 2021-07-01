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
    public static class SetLedState
    {
        private static readonly HttpClient client = new HttpClient();

        [FunctionName("SetLedState")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Function, "get", "post", Route = null)] HttpRequest req,
            ILogger log)
        {
            const string baseUrl = "http://82.64.172.94:8181/setLedState";

            var state = req.Query["state"];

            await client.GetAsync($"{baseUrl}?state={state}", HttpCompletionOption.ResponseContentRead);

            log.LogInformation("C# HTTP trigger function processed a request.");

            string responseMessage = $"Azure Function -> Led state set to ={state}";

            return new OkObjectResult(responseMessage);
        }
    }
}
