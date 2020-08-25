using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.IO.Ports;
using System.Threading;

using System.Net;
using System.Net.Sockets;


namespace xSocketDLL
{
    public class xServer
    {
        Socket listenSocket;
        IPEndPoint endp;
        byte[] RecvBytes = new byte[1024];
        int bytes;
        public void server(string serverIP, int port)
        {
            IPAddress serverIp;
            string host = serverIP;
            int sport = port;
            //Console.WriteLine("1/创建套接字.");
            listenSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            serverIp = IPAddress.Parse(host);
            endp = new IPEndPoint(serverIp, sport);
            //Console.WriteLine("2/绑定套接字.");
            listenSocket.Bind(endp);
            //Console.WriteLine("3/开始监听.");
            listenSocket.Listen(20);
            //Console.WriteLine("4/接受客户端连接等待(Waiting)...."); 
        }
        public Socket Accept()
        {
            Socket AcceptSocket = listenSocket.Accept();
            return AcceptSocket;
        }
        public string Receive(Socket AcceptSocket)//不能用static
        {
            try
            { //阻塞直到发送返回
                bytes = AcceptSocket.Receive(RecvBytes, SocketFlags.None);
                string str1 = Encoding.UTF8.GetString(RecvBytes, 0, bytes);
                if (bytes > 0)
                {
                    //Console.WriteLine("已接收：\n{0}", str1); 
                    return str1;
                }
                return null;
            }

            catch (SocketException e)
            {
                Console.WriteLine("Server Receive -{0} Error code:{1}.", e.Message, e.ErrorCode);
                return null;
            }
        }
        public void Send(Socket AcceptSocket, String msg)
        {
            // Console.WriteLine("请输入:");
            byte[] message = Encoding.UTF8.GetBytes(msg);
            try
            {
                int byteCount = AcceptSocket.Send(message, SocketFlags.None);
            }
            catch (SocketException e)
            {
                Console.WriteLine("Server Send -{0} Error code:{1}.", e.Message, e.ErrorCode);
                ;
            }
        }
        public void SocketClose()
        {
            this.listenSocket.Shutdown(SocketShutdown.Both);
            this.listenSocket.Close();
        }
    }
    //============================================================================================
    public class xClient
    {
        IPEndPoint endpoint;
        Socket socketClient=null;
        byte[] recvBytes = new byte[4096];
        int bytesNum;
        public void Connect(string serverIP, int port)
        {
            socketClient = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPAddress ipAddr = IPAddress.Parse(serverIP.Trim());
            endpoint = new IPEndPoint(ipAddr, port);//网络节点
            try
            {
                socketClient.Connect(endpoint);
            }
            catch (SocketException e)
            {
                Console.WriteLine("Client Connect -{0} Error code:{1}.", e.Message, e.ErrorCode); 
            }
        }
        public string ReceiveStr()
        {
            try
            {
                string recvStr = "";
                bytesNum = socketClient.Receive(recvBytes, recvBytes.Length, 0);
                recvStr += Encoding.ASCII.GetString(recvBytes, 0, bytesNum);
                //Console.WriteLine("接受到的消息为：{0}", recvStr);
                return recvStr;

                //阻塞直到发送返回
            }
            catch (SocketException e)
            {
                Console.WriteLine("Client Receive -{0} Error code:{1}.", e.Message, e.ErrorCode);
                return null;
            }
        }
        public int ReceiveBytes(ref byte[] bytesRecv)
        {
            try
            {
                bytesNum = socketClient.Receive(bytesRecv);
                return bytesNum;
            }
            catch (SocketException e)
            {
                Console.WriteLine("Client Receive -{0} Error code:{1}.", e.Message, e.ErrorCode);
                return 0;
            }
        }
        public void Send(string CommandMessge)
        {
            //string cmdmsg;
            byte[] byteArray = new byte[512];
            //cmdmsg = msg.Replace("\n", "").Replace(" ", "").Replace("\t", "").Replace("\r", ""); //Clear the ilegal string:' ', 
            try
            {
                //byte[] message = Encoding.ASCII.GetBytes(msg);
                byteArray = HexStringToBinary(CommandMessge);
                socketClient.Send(byteArray, SocketFlags.None);
            }
            catch (SocketException e)
            {
                Console.WriteLine("Client Send -{0} Error code:{1}.", e.Message, e.ErrorCode);
            }
        }
        public void SocketClose()
        {
            socketClient.Close();
            socketClient = null;
        }

        public byte[] HexStringToBinary(string hexstring)
        {

            string[] tmpary = hexstring.Trim().Split(' ');
            byte[] buff = new byte[tmpary.Length];
            for (int i = 0; i < buff.Length; i++)
            {
                buff[i] = Convert.ToByte(tmpary[i], 16);
            }
            return buff;
        }
    }

    //==========================================
    public class Net
    {
        public void GetLocalIP()
        {
            string name = Dns.GetHostName();
            IPAddress[] ipadrlist = Dns.GetHostAddresses(name);
            foreach (IPAddress ipa in ipadrlist)
            {
                if (ipa.AddressFamily == AddressFamily.InterNetwork)
                {
                    //Console.Writeline(ipa.ToString());
                }
            }
        }
    }
}
