using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Windows;

namespace SQLiteApp1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ApplicationContext db;

        public MainWindow()
        {
            InitializeComponent();

            db = new ApplicationContext();
            db.Phones.Load();
            this.DataContext = db.Phones.Local.ToBindingList();
        }

        private void Add_Click(object sender, RoutedEventArgs e)
        {
            PhoneWindow phoneWindow = new PhoneWindow(new Phone());
            if (phoneWindow.ShowDialog() == true)
            {
                Phone phone = phoneWindow.Phone;
                db.Phones.Add(phone);
                db.SaveChanges();
            }
        }

        private void Edit_Click(object sender, RoutedEventArgs e)
        {
            // если ни одного объекта не выделено, выходим
            if (phonesList.SelectedItem == null) return;
            // получаем выделенный объект
            Phone phone = phonesList.SelectedItem as Phone;

            PhoneWindow phoneWindow = new PhoneWindow(new Phone
            {
                Id = phone.Id,
                Brand = phone.Brand,
                Price = phone.Price,
                Name = phone.Name
            });

            if (phoneWindow.ShowDialog() == true)
            {
                // получаем измененный объект
                phone = db.Phones.Find(phoneWindow.Phone.Id);
                if (phone != null)
                {
                    phone.Brand = phoneWindow.Phone.Brand;
                    phone.Name = phoneWindow.Phone.Name;
                    phone.Price = phoneWindow.Phone.Price;
                    db.Entry(phone).State = EntityState.Modified;
                    db.SaveChanges();
                }
            }
        }

        private void Delete_Click(object sender, RoutedEventArgs e)
        {
            // если ни одного объекта не выделено, выходим
            if (phonesList.SelectedItem == null) return;
            // получаем выделенный объект
            Phone phone = phonesList.SelectedItem as Phone;
            db.Phones.Remove(phone);
            db.SaveChanges();
        }
    }
}