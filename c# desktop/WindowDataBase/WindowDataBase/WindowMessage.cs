using System;
using System.Windows.Forms;

namespace WindowDataBase
{
    internal static class MessageWindow
    {
        public static void ShowMessageInformation(string text, string caption)
        {
            if (string.IsNullOrEmpty(text) || string.IsNullOrEmpty(caption))
                throw new ArgumentNullException($"{nameof(text)} or {nameof(caption)} is empty.");

            MessageBox.Show(text, caption, MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        public static void ShowMessageWarning(string text, string caption)
        {
            if (string.IsNullOrEmpty(text) || string.IsNullOrEmpty(caption))
                throw new ArgumentNullException($"{nameof(text)} or {nameof(caption)} is empty.");

            MessageBox.Show(text, caption, MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        public static void ShowMessageError(string text, string caption)
        {
            if (string.IsNullOrEmpty(text) || string.IsNullOrEmpty(caption))
                throw new ArgumentNullException($"{nameof(text)} or {nameof(caption)} is empty.");

            MessageBox.Show(text, caption, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public static bool ShowMessageQuesting(string text, string caption)
        {
            if (string.IsNullOrEmpty(text) || string.IsNullOrEmpty(caption))
                throw new ArgumentNullException($"{nameof(text)} or {nameof(caption)} is empty.");

            DialogResult dialogResult = MessageBox.Show(text, caption,
                MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);

            switch (dialogResult)
            {
                case DialogResult.Yes: return true;
                case DialogResult.No: return false;
                case DialogResult.None: return false;
                case DialogResult.Cancel: return false;
            }

            return false;
        }
    }
}