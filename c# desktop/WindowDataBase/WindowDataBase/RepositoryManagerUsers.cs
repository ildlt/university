using Dapper;
using System.Data;
using System.Linq;
using MySql.Data.MySqlClient;
using System.Collections.Generic;

namespace WindowDataBase
{
    public sealed class RepositoryManagerUsers
    {
        internal IDbConnection Db;

        public RepositoryManagerUsers()
        {
            Db = new MySqlConnection("Server=localhost;Database=data;Uid=root;Pwd=root;SslMode=none");
        }

        public List<int> GetUsersIdList()
        {
            try
            {
                return Db.Query<int>("select id from users").ToList();
            }
            catch (MySqlException ex)
            {
                MessageWindow.ShowMessageError($"Message: {ex.Message}", $"Method: " +
                    $"{nameof(GetUsersIdList)}. (Error Number: \'{ex.Number}\')");

                return new List<int>();
            }
        }
        
        public UserContract GetUserContractById(int id)
        {
            try
            {
                return Db.Query<UserContract>("select id as id, phone as phone, password as password," +
                    " name as name, surname as surname, age as age from users where id=@id", new { id }).FirstOrDefault();
            }
            catch (MySqlException ex)
            {
                MessageWindow.ShowMessageError($"Message: {ex.Message}", $"Method: " +
                    $"{nameof(GetUserContractById)}. (Error Number: \'{ex.Number}\')");

                return null;
            }
        }

        public void DeleteUserContractById(int id)
        {
            try
            {
                Db.Execute(@"delete from users where id=@id", new { id });
            }
            catch (MySqlException ex)
            {
                MessageWindow.ShowMessageError($"Message: {ex.Message}", $"Method: " +
                    $"{nameof(DeleteUserContractById)}. (Error Number: \'{ex.Number}\')");
            }
        }

        public void AddNewUser(UserContract userContract)
        {
            try
            {
                Db.Execute(@"insert into users (id, phone, password, name, surname, age) values (@id, @phone, @password, @name, @surname, @age)",
                    new {
                        userContract.id,
                        userContract.phone,
                        userContract.password,
                        userContract.name,
                        userContract.surname,
                        userContract.age
                    });
            }
            catch (MySqlException ex)
            {

                MessageWindow.ShowMessageError($"Message: {ex.Message}", $"Method: " +
                    $"{nameof(AddNewUser)}. (Error Number: \'{ex.Number}\')");
            }
        }
    }
}