namespace WindowDataBase
{
    public class UserContract
    {
        public int id { get; set; }
        public string phone { get; set; }
        public string password { get; set; }
        public string name { get; set; }
        public string surname { get; set; }
        public int age { get; set; }

        public UserContract()
            : this(0, string.Empty, 
                  string.Empty, string.Empty, string.Empty, 0)
        { }

        public UserContract(int id, string phone, string password,
            string name, string surname, int age)
        {
            this.id = id;
            this.phone = phone;
            this.password = password;
            this.name = name;
            this.surname = surname;
            this.age = age;
        }
    }
}