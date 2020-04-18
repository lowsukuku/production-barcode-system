using System;
using System.IO;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Models
{
    public class Requests
    {
    }

    [DataContract]
    public class PostContent : HttpContent
    {
        private byte[] serializedData = null;

        [DataMember]
        [JsonProperty(Order = -2)]
        public string clientType;
        [DataMember]
        public ClientModel client;

        public PostContent(ClientModel client)
        {
            this.client = client;
            clientType = client.GetType().Name;
            Headers.ContentType = new MediaTypeHeaderValue("application/json");
        }

        protected override Task SerializeToStreamAsync(Stream stream, TransportContext context)
        {
            if (serializedData == null)
            {
                serializedData = Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(this));
            }
            return stream.WriteAsync(serializedData, 0, serializedData.Length);
        }

        protected override bool TryComputeLength(out long length)
        {
            if (serializedData == null)
            {
                serializedData = Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(this));
            }
            length = serializedData.Length;
            return true;
        }
    }

    public enum ScannerRole
    {
        None,
        Mounting,
        Tuning,
        QualityCheck,
        Shipment
    }


    public class ClientModel
    {
    }

    public class RequestContext
    {
        public virtual string GetQuery() { return ""; }
    }

    public class GetAllDevices : RequestContext { }
    public class GetAllModels : RequestContext { }
    public class GetDevicesByModel : RequestContext
    {
        public uint modelId;

        public GetDevicesByModel(uint modelId) => this.modelId = modelId;

        public override string GetQuery()
        {
            return $"&modelId={modelId}";
        }
    }

    public class GetDeviceById : RequestContext
    {
        public ulong id;

        public GetDeviceById(ulong id) => this.id = id;
        public override string GetQuery()
        {
            return $"&id={id}";
        }
    }

    public class GenerateUniqueID : RequestContext { }

    public class AddDevice : RequestContext
    {
        public uint modelId;
        public ulong deviceID;

        public AddDevice(uint modelId, ulong deviceID) => (this.modelId, this.deviceID) = (modelId, deviceID);
    }

    public class AddModel : RequestContext
    {
        public string modelName;

        public AddModel(string modelName) => this.modelName = modelName;
    }

    public class DeleteDevice : RequestContext
    {
        public ulong deviceID;

        public DeleteDevice(ulong deviceID) => this.deviceID = deviceID;
    }

    public class DeleteModel : RequestContext
    {
        public uint modelId;

        public DeleteModel(uint modelId) => this.modelId = modelId;
    }

    public class Scanner : ClientModel
    {
        public ulong apiKey = 0;
        public ulong deviceID = 0;
        public string role = "Mounting";
        public uint utcTime = 0;
    }

    public class User : ClientModel
    {
        [JsonProperty(Order = 1)]
        public string login;
        [JsonProperty(Order = 2)]
        public string password;
        [JsonProperty(Order = 3)]
        public string contextType { get { return context.GetType().Name; } }
        [JsonProperty(Order = 4)]
        public RequestContext context;

        public string GetQuery()
        {
            return $"contextType={contextType}{context.GetQuery()}";
        }
    }
}
