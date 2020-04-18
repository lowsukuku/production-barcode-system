using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using Models;
using Newtonsoft.Json;

namespace HTTPListener
{
    class HTTPListener
    {
        private static Random random = new Random();
        private static Dictionary<uint,Model> models = new Dictionary<uint, Model>();
        private static Dictionary<ulong, Device> devices = new Dictionary<ulong, Device>();

        static void Main(string[] args)
        {
            Console.WriteLine("HTTP Listener");
            foreach (var i in Enumerable.Range(0,5))
            {
                models.Add((uint)i, new Model {
                    creationUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(10000, 11000),
                    modelId = (uint)i,
                    modelName = $"Model {i}"
                });
                foreach (var j in Enumerable.Range(0,3))
                {
                    ulong newId = (ulong)random.Next() * (ulong)random.Next();
                    devices.Add(newId, new Device
                    {
                        creationUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(9000, 10000),
                        deviceId = newId,
                        modelId = (uint)i,
                        mountingPassed = true,
                        mountingUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(8000, 9000),
                        tuningPassed = true,
                        tuningUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(7000, 8000),
                        qualityCheckPassed = true,
                        qualityCheckUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(6000, 7000),
                        shipmentPassed = true,
                        shipmentUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(5000, 6000),
                        serialNumber = (uint)random.Next()
                    });
                }
            }
            ListenHttp().GetAwaiter().GetResult();

        }

        static async Task ListenHttp()
        {
            string localAddr = "127.0.0.1";
            Int32 port = 8001;
            Console.WriteLine("Enter ip address. Skip for 127.0.0.1");
            var answer = Console.ReadLine();
            if (answer != String.Empty)
            {
                localAddr = answer;
            }
            Console.WriteLine("Enter port. Skip for 8001");
            answer = Console.ReadLine();
            if (answer != string.Empty)
                port = Int32.Parse(Console.ReadLine());

            HttpListener listener = new HttpListener();

            listener.Prefixes.Add($"http://{localAddr}:{port}/");
            listener.Start();
            while (true)
            {
                
                Console.WriteLine("Listening...");
                // Note: The GetContext method blocks while waiting for a request. 
                HttpListenerContext context = await listener.GetContextAsync();
                HttpListenerRequest request = context.Request;
                String data = null;
                Byte[] bytes = new Byte[request.ContentLength64];

                await request.InputStream.ReadAsync(bytes, 0, (int)request.ContentLength64);
                data = System.Text.Encoding.UTF8.GetString(bytes, 0, (int)request.ContentLength64);
                string responseString = "";
                if (request.HttpMethod == "POST")
                {
                    PostContent postContent = JsonConvert.DeserializeObject<PostContent>(data);

                    if (postContent.clientType == "Scanner")
                    {
                        var subString = data.Substring(1, data.Length - 2);
                        var searchString = subString.Substring(subString.IndexOf('{'));
                        Scanner a = JsonConvert.DeserializeObject<Scanner>(searchString);
                    }

                    else if (postContent.clientType == "User")
                    {
                        var subString = data.Substring(1, data.Length - 2);
                        var searchString = subString.Substring(subString.IndexOf('{'));
                        User a = JsonConvert.DeserializeObject<User>(searchString);
                    }
                }
                else if (request.HttpMethod == "GET")
                {
                    var a = request.QueryString;
                    if (a[nameof(User.contextType)] == typeof(GetAllDevices).Name)
                    {
                        responseString = JsonConvert.SerializeObject(devices);
                    }
                    else if (a[nameof(User.contextType)] == typeof(GetAllModels).Name)
                    {
                        responseString = JsonConvert.SerializeObject(models);
                    }
                    else if (a[nameof(User.contextType)] == typeof(GetDevicesByModel).Name)
                    {
                        uint modelId = uint.Parse(a[nameof(GetDevicesByModel.modelId)]);
                        if (!models.ContainsKey(modelId))
                        {
                            models.Add(modelId, new Model
                            {
                                creationUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(10000, 11000),
                                modelId = modelId,
                                modelName = $"Model {modelId}"
                            });
                            foreach (var j in Enumerable.Range(0, 3))
                            {
                                ulong newId = (ulong)random.Next() * (ulong)random.Next();
                                devices.Add(newId, new Device
                                {
                                    creationUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(9000, 10000),
                                    deviceId = newId,
                                    modelId = (uint)modelId,
                                    mountingPassed = true,
                                    mountingUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(8000, 9000),
                                    tuningPassed = true,
                                    tuningUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(7000, 8000),
                                    qualityCheckPassed = true,
                                    qualityCheckUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(6000, 7000),
                                    shipmentPassed = true,
                                    shipmentUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(5000, 6000),
                                    serialNumber = (uint)random.Next()
                                });
                            }
                        }
                        responseString = JsonConvert.SerializeObject(devices.Values.Where(d => d.modelId == modelId));
                    }
                    else if (a[nameof(User.contextType)] == typeof(GetDeviceById).Name)
                    {
                        ulong deviceId = ulong.Parse(a[nameof(GetDeviceById.id)]);
                        if (!devices.ContainsKey(deviceId))
                        {
                            devices.Add(deviceId, new Device
                            {
                                creationUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(9000, 10000),
                                deviceId = deviceId,
                                modelId = (uint)random.Next(models.Keys.Count),
                                mountingPassed = true,
                                mountingUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(8000, 9000),
                                tuningPassed = true,
                                tuningUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(7000, 8000),
                                qualityCheckPassed = true,
                                qualityCheckUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(6000, 7000),
                                shipmentPassed = true,
                                shipmentUtc = (uint)DateTime.UtcNow.Subtract(DateTime.UnixEpoch).TotalSeconds - (uint)random.Next(5000, 6000),
                                serialNumber = (uint)random.Next()
                            });
                        }

                    }
                    else if (a[nameof(User.contextType)] == typeof(GenerateUniqueID).Name)
                    {
                        responseString = $"{(ulong)random.Next() * (ulong)random.Next()}";
                    }
                }
                Console.WriteLine("{0}", data);
                // Obtain a response object.
                HttpListenerResponse response = context.Response;
                // Construct a response.
                byte[] buffer = System.Text.Encoding.UTF8.GetBytes(responseString);
                // Get a response stream and write the response to it.
                response.ContentLength64 = buffer.Length;
                System.IO.Stream output = response.OutputStream;
                output.Write(buffer, 0, buffer.Length);
                // You must close the output stream.
                output.Close();
                
            }
            listener.Stop();
        }
    }
}
