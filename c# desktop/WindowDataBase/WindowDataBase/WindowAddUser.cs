using System;
using System.Windows.Forms;
using System.Collections.Generic;

namespace WindowDataBase
{
    public partial class WindowAddUser : Form
    {
        private readonly RepositoryManagerUsers repositoryManagerUsers;
        private Dictionary<int, UserContract> usersContractList = new Dictionary<int, UserContract>();

        public WindowAddUser(RepositoryManagerUsers repositoryManagerUsers,
            Dictionary<int, UserContract> usersContractList)
        {
            this.repositoryManagerUsers = repositoryManagerUsers;
            this.usersContractList = usersContractList;

            InitializeComponent();
        }

        private void ButtonExit_Click(object sender, EventArgs e)
        {
            if (MessageWindow.ShowMessageQuesting("Вы действительно хотите выйти?", "Exit"))
            {
                Dispose();
                Close();
            }
        }

        private void ButtonRemove_Click(object sender, EventArgs e)
        {
            TextBoxPhone.Text = string.Empty;
            TextBoxPassword.Text = string.Empty;
            TextBoxName.Text = string.Empty;
            TextBoxSurname.Text = string.Empty;
            TextBoxAge.Text = string.Empty;
        }

        private void ButtonAdd_Click(object sender, EventArgs e)
        {
            if (!IsValidAdd())
                return;

            UserContract userContract = new UserContract()
            {
                id = GenerateUserId(),
                phone = TextBoxPhone.Text,
                password = TextBoxPassword.Text,
                name = TextBoxName.Text,
                surname = TextBoxSurname.Text,
                age = int.Parse(TextBoxAge.Text)
            };

            repositoryManagerUsers.AddNewUser(userContract);
            MessageWindow.ShowMessageInformation("Вы успешно добавили пользователя.", "Информация");
        }

        private int GenerateUserId()
        {
            int result = 0;

            foreach (KeyValuePair<int, UserContract> keyValuePair in usersContractList)
            {
                if (!keyValuePair.Key.Equals(result))
                    break;

                result++;
            }

            return result;
        }

        private bool IsValidAdd()
        {
            if (string.IsNullOrEmpty(TextBoxPhone.Text))
            {
                MessageWindow.ShowMessageWarning("Номер не может быть пустым!", "Внимание!");
                return false;
            }

            if (string.IsNullOrEmpty(TextBoxPassword.Text))
            {
                MessageWindow.ShowMessageWarning("Пароль не может быть пустым!", "Внимание!");
                return false;
            }

            if (string.IsNullOrEmpty(TextBoxName.Text))
            {
                MessageWindow.ShowMessageWarning("Имя не может быть пустым!", "Внимание!");
                return false;
            }

            if (string.IsNullOrEmpty(TextBoxSurname.Text))
            {
                MessageWindow.ShowMessageWarning("Фамилия не может быть пустой!", "Внимание!");
                return false;
            }

            if (string.IsNullOrEmpty(TextBoxAge.Text))
            {
                MessageWindow.ShowMessageWarning("Возраст не может быть пустым!", "Внимание!");
                return false;
            }

            return true;
        }
    }
}