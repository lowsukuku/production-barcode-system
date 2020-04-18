using System;
using System.Net.Http;
using System.IO;
using System.Net;
using System.Threading.Tasks;
using System.Text;
using System.Net.Http.Headers;
using System.Runtime.Serialization;
using System.Linq;
using Models;

namespace Application
{
    class Program
    {
        private static Random random = new Random();
        static void Main(string[] args)
        {
            try
            {
                MainAsync().GetAwaiter().GetResult();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.ReadKey();
            }
        }

        static async Task MainAsync()
        {

            
            HttpClient client = new HttpClient();
            string localAddr = "127.0.0.1";
            Int32 port = 8000;
            Console.WriteLine("Enter ip address. Skip for 127.0.0.1");
            var answer = Console.ReadLine();
            if (answer != String.Empty)
            {
                localAddr = answer;
            }
            Console.WriteLine("Enter port. Skip for 8000");
            answer = Console.ReadLine();
            if (answer != string.Empty)
                port = Int32.Parse(Console.ReadLine());

            var uriBuilder = new UriBuilder(new Uri($"http://{localAddr}"))
            {
                Path = "/",
                Port = port
            };
            Scanner scanner = new Scanner
            {
                apiKey = (ulong)random.Next() * (ulong)random.Next(),
                deviceID = (ulong)random.Next() * (ulong)random.Next(),
                utcTime = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds,
            };
            await client.PostAsync(uriBuilder.Uri, new PostContent(scanner));
            User user = new User
            {
                login = RandomString(10),
                password = RandomString(8)
            };
            
            user.context = new AddDevice((uint)random.Next(100), (ulong)random.Next() * (ulong)random.Next());
            await client.PostAsync(uriBuilder.Uri, new PostContent(user));
            user.context = new AddModel($"Model {random.Next(100)}");
            await client.PostAsync(uriBuilder.Uri, new PostContent(user));
            user.context = new DeleteDevice((ulong)random.Next() * (ulong)random.Next());
            await client.PostAsync(uriBuilder.Uri, new PostContent(user));
            user.context = new DeleteModel((uint)random.Next(100));
            await client.PostAsync(uriBuilder.Uri, new PostContent(user));

            user.context = new GetAllDevices();
            uriBuilder.Query = user.GetQuery();
            await client.GetAsync(uriBuilder.Uri);
            user.context = new GetAllModels();
            uriBuilder.Query = user.GetQuery();
            await client.GetAsync(uriBuilder.Uri);
            user.context = new GetDevicesByModel((uint)random.Next(100));
            uriBuilder.Query = user.GetQuery();
            await client.GetAsync(uriBuilder.Uri);
            user.context = new GetDeviceById((ulong)random.Next() * (ulong)random.Next());
            uriBuilder.Query = user.GetQuery();
            await client.GetAsync(uriBuilder.Uri);
            user.context = new GenerateUniqueID();
            uriBuilder.Query = user.GetQuery();
            await client.GetAsync(uriBuilder.Uri);

            Console.WriteLine("Hello World!");
            Console.ReadKey();
        }


        public static string RandomString(int length)
        {
            const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefjhijklmnopqrstuvwxyz0123456789_";
            return new string(Enumerable.Repeat(chars, length)
              .Select(s => s[random.Next(s.Length)]).ToArray());
        }
    }

    

    


}
