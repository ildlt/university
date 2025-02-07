using System;
using System.Threading;
using System.Windows.Forms;
using System.Collections.Generic;

namespace WindowDataBase
{
    public partial class WindowDataBase : Form
    {
        private readonly RepositoryCheckConnection repositoryCheckConnection;
        private readonly RepositoryManagerUsers repositoryManagerUsers;

        private Dictionary<int, UserContract> userContracts;

        public WindowDataBase()
        {
            repositoryCheckConnection = new RepositoryCheckConnection();
            repositoryManagerUsers = new RepositoryManagerUsers();
            userContracts = new Dictionary<int, UserContract>();

            if (!repositoryCheckConnection.PreCheckRepository())
            {
                MessageWindow.ShowMessageError("Fatal error MySQL connections...", "Error");
                Environment.Exit(-1);
            }

            InitializeComponent();
        }

        private void ButtonExit_Click(object sender, EventArgs e)
        {
            if (MessageWindow.ShowMessageQuesting("Вы действительно хотите выйти?", "Exit"))
                Environment.Exit(0);
        }

        private void ButtonUpdate_Click(object sender, EventArgs e)
        {
            List<int> ids = repositoryManagerUsers.GetUsersIdList();

            if (ids.Count == 0)
            {
                MessageWindow.ShowMessageInformation("База данных пуста!", "Информация");
                return;
            }

            dataGridView.Rows.Clear();
            foreach (int id in ids)
            {
                UserContract userContract = repositoryManagerUsers.GetUserContractById(id);

                int RowNumber = dataGridView.Rows.Add();

                userContracts.Add(RowNumber, userContract);
                dataGridView.Rows[RowNumber].Cells["ColumnPhone"].Value = userContract.phone;
                dataGridView.Rows[RowNumber].Cells["ColumnPassword"].Value = userContract.password;
                dataGridView.Rows[RowNumber].Cells["ColumnName"].Value = userContract.name;
                dataGridView.Rows[RowNumber].Cells["ColumnSurname"].Value = userContract.surname;
                dataGridView.Rows[RowNumber].Cells["ColumnAge"].Value = userContract.age;

                Thread.Sleep(10);
            }
        }

        private void ButtonDelete_Click(object sender, EventArgs e)
        {
            if (dataGridView.Rows[dataGridView.CurrentRow.Index].Cells["ColumnPhone"].Value == null)
                return;

            dataGridView.Rows.RemoveAt(dataGridView.CurrentRow.Index);
            repositoryManagerUsers.DeleteUserContractById(userContracts[dataGridView.CurrentRow.Index].id);
            userContracts.Remove(dataGridView.CurrentRow.Index);
        }

        private void ButtonAdd_Click(object sender, EventArgs e)
        {
            WindowAddUser windowAddUser = new WindowAddUser(repositoryManagerUsers, userContracts);
            windowAddUser.Show();
        }
    }
}