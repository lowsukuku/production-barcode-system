using System;
using System.Collections.Generic;
using System.Text;

namespace Models
{
    public class Device
    {
        public ulong deviceId;
        public uint modelId;
        public uint creationUtc;
        public uint serialNumber;
        public uint mountingUtc;
        public uint tuningUtc;
        public uint qualityCheckUtc;
        public uint shipmentUtc;
        public bool mountingPassed;
        public bool tuningPassed;
        public bool qualityCheckPassed;
        public bool shipmentPassed;
    }

    public class Model
    {
        public uint modelId;
        public uint creationUtc;
        public string modelName;
    }
}
