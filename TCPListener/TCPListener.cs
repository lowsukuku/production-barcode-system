using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace TCPListener
{
    class TCPListener
    {
        static void Main(string[] args)
        {
            Console.WriteLine("TCP Listener");
            ListenTCP().GetAwaiter().GetResult();
        }

        static async Task ListenTCP()
        {
            TcpListener server = null;
            try
            {

                IPAddress localAddr = IPAddress.Parse("127.0.0.1");
                Int32 port = 8000;
                Console.WriteLine("Enter ip address. Skip for 127.0.0.1");
                var answer = Console.ReadLine();
                if (answer != String.Empty)
                {
                    localAddr = IPAddress.Parse(Console.ReadLine());
                }
                Console.WriteLine("Enter port. Skip for 8000");
                answer = Console.ReadLine();
                if (answer != string.Empty)
                    port = Int32.Parse(Console.ReadLine());
                server = new TcpListener(localAddr, port);


                server.Start();


                Byte[] bytes = new Byte[256];
                String data = null;


                while (true)
                {
                    TcpClient client = server.AcceptTcpClient();
                    TcpClient selfClient = new TcpClient(localAddr.ToString(), 8001);
                    NetworkStream outstream = selfClient.GetStream();
                    NetworkStream stream = client.GetStream();
                    int i, j;
                    try
                    {
                        Console.WriteLine();
                        while (!stream.DataAvailable) { }
                        while (stream.DataAvailable)
                        {
                            i = stream.Read(bytes, 0, bytes.Length);
                            data = System.Text.Encoding.UTF8.GetString(bytes, 0, i);
                            Console.WriteLine("{0}", data);
                            //byte[] msg = System.Text.Encoding.ASCII.GetBytes("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: 0\r\n\r\n");
                            
                            outstream.Write(bytes, 0, i);
                            
                        }
                        bytes = new Byte[256];
                        Console.WriteLine();
                        while (!outstream.DataAvailable) { }
                        while (outstream.DataAvailable)
                        {
                            j = outstream.Read(bytes, 0, bytes.Length);
                            data = System.Text.Encoding.UTF8.GetString(bytes, 0, j);
                            Console.WriteLine("{0}", data);
                            stream.Write(bytes, 0, j);
                        }
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine("Exception: {0}", e);
                    }

                    client.Close();
                    selfClient.Close();
                }
            }
            catch (SocketException e)
            {
                Console.WriteLine("SocketException: {0}", e);
            }

            finally
            {
                server.Stop();
            }

            Console.WriteLine("\nHit enter to continue...");
            Console.Read();

        }
    }
}
