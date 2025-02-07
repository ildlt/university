using System;
using Dapper;
using System.Data;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.ServiceProcess;
using System.Threading;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;

namespace WindowDataBase
{
    public sealed class RepositoryCheckConnection
    {
        internal IDbConnection Db;
        internal MySqlConnectionStringBuilder mySqlConnectionStringBuilder = null;

        private const int PingTimeoutMs = 3000;
        private const int PingRetryAttempts = 5;
        private const int MysqlServiceStartTimeoutMs = 3000;
        private const int MysqlServiceRetryAttempts = 5;
        private const string MysqlServiceName = "MySQL";

        private readonly string _host;
        private readonly string _dataBase;

        public RepositoryCheckConnection()
        {
            Db = new MySqlConnection("Server=localhost;Database=data;Uid=root;Pwd=root;SslMode=none");
            mySqlConnectionStringBuilder = new MySqlConnectionStringBuilder(Db.ConnectionString);

            _host = mySqlConnectionStringBuilder.Server;
            _dataBase = mySqlConnectionStringBuilder.Database;
        }

        public bool PreCheckRepository()
        {
            if (!CheckDatabaseHostPing())
                return false;

            if (!CheckMySqlService())
                return false;

            if (!CheckDatabaseQuery())
                return false;

            return true;
        }

        private bool CheckDatabaseHostPing()
        {
            bool isHostPinging = IsPingSuccessful(_host, PingTimeoutMs);

            for (int i = 1; !isHostPinging && (i <= PingRetryAttempts); i++)
            {
                Thread.Sleep(100);
                isHostPinging = IsPingSuccessful(_host, PingTimeoutMs);

                if (isHostPinging)
                    break;
            }

            if (!isHostPinging)
                MessageWindow.ShowMessageError($"Ping to database host '{_host}' has FAILED!", "Error");

            return isHostPinging;
        }

        private bool CheckMySqlService()
        {
            if (IsLocalIpAddress(_host))
            {
                if (!ServiceExists(MysqlServiceName))
                {
                    MessageWindow.ShowMessageError("MySQL Service does not exist at localhost Windows Services!", "Error");

                    return false;
                }

                bool isMySqlServiceRunning = IsServiceRunning(MysqlServiceName);

                for (int i = 1; !isMySqlServiceRunning && (i <= MysqlServiceRetryAttempts); i++)
                {
                    StartService(MysqlServiceName, MysqlServiceStartTimeoutMs);
                    isMySqlServiceRunning = IsServiceRunning(MysqlServiceName);

                    if (!isMySqlServiceRunning)
                        continue;

                    break;
                }

                if (!isMySqlServiceRunning)
                    MessageWindow.ShowMessageError("MySQL Service was not found running at localhost!", "Error");

                return isMySqlServiceRunning;
            }

            return true;
        }

        public bool IsLocalIpAddress(string host)
        {
            try
            {
                IPAddress[] hostIPs = Dns.GetHostAddresses(host);
                IPAddress[] localIPs = Dns.GetHostAddresses(Dns.GetHostName());

                foreach (IPAddress hostIp in hostIPs)
                {
                    if (IPAddress.IsLoopback(hostIp))
                        return true;

                    if (localIPs.Contains(hostIp))
                        return true;
                }
            }
            catch (Exception ex)
            {
                MessageWindow.ShowMessageError($"HostCheck: IsLocalIPAddress: {ex.Message}", $"Exception: {nameof(IsLocalIpAddress)}");
            }

            return false;
        }

        public bool ServiceExists(string serviceName)
        {
            try
            {
                return ServiceController.GetServices().Any(service =>
                    service.ServiceName.StartsWithIgnoreCase(serviceName));
            }
            catch (Exception ex)
            {
                MessageWindow.ShowMessageError($"HostCheck: ServiceExists: {ex.Message}", $"Exception: {nameof(ServiceExists)}");
            }

            return false;
        }

        public bool IsServiceRunning(string serviceName)
        {
            try
            {
                return ServiceController.GetServices().Any(service =>
                    service.ServiceName.StartsWithIgnoreCase(serviceName) &&
                        (service.Status == ServiceControllerStatus.Running));
            }
            catch (Exception ex)
            {
                MessageWindow.ShowMessageError($"HostCheck: IsServiceRunning: {ex.Message}", $"Exception: {nameof(IsServiceRunning)}");
            }

            return false;
        }

        public void StartService(string serviceName, int timeoutMs)
        {
            ServiceController service = ServiceController.GetServices().FirstOrDefault(filter =>
                filter.ServiceName.StartsWithIgnoreCase(serviceName));

            switch (service.Status)
            {
                case ServiceControllerStatus.Running:
                    break;
                case ServiceControllerStatus.Stopped:
                    try
                    {
                        TimeSpan timeout = TimeSpan.FromMilliseconds(timeoutMs);

                        service.Start();
                        service.WaitForStatus(ServiceControllerStatus.Running, timeout);
                    }
                    catch (Exception ex)
                    {
                        MessageWindow.ShowMessageError($"HostCheck: StartService: {ex.Message}", $"Exception: {nameof(StartService)}");
                    }
                    break;
                default:
                    Thread.Sleep(timeoutMs);
                    break;
            }
        }

        public bool IsPingSuccessful(string host, int timeoutMs)
        {
            try
            {
                PingReply pingReply = new Ping().Send(host, timeoutMs, new byte[1]);
                return (pingReply != null) && (pingReply.Status == IPStatus.Success);
            }
            catch (Exception ex)
            {
                MessageWindow.ShowMessageError($"HostCheck: IsPingSuccessful: {ex.Message}", $"Exception: {nameof(IsPingSuccessful)}");
            }

            return false;
        }

        private bool CheckDatabaseQuery()
        {
            bool isQuerySuccessful = TryQueryDatabase();

            if (!isQuerySuccessful)
                MessageWindow.ShowMessageError($"Query to database '{_dataBase}' has FAILED!", "Error");

            return isQuerySuccessful;
        }

        private bool TryQueryDatabase()
        {
            try
            {
                return Db.Query("SELECT 1").Any();
            }
            catch (MySqlException ex)
            {
                MessageWindow.ShowMessageError($"Message: {ex.Message}", $"Method: " +
                    $"{nameof(TryQueryDatabase)}. (Error Number: \'{ex.Number}\')");
            }

            return false;
        }
    }
}