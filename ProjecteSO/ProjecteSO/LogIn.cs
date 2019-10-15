using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace ProjecteSO
{
    public partial class LogIn : Form
    {
        int done = 0;
        string mensaje2;
        public string Mensaje()
        {
            return mensaje2;
        }
        public LogIn()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if ((textBoxPASSWORD.Text != null) && (textBoxUSERNAME.Text != null))
            {
                    
                    mensaje2 = "2/" + textBoxUSERNAME.Text + "/" + textBoxPASSWORD.Text;


                    done = 1;
            }

                else
                {
                    MessageBox.Show("Please try inputing your data again");
                }

            if (done == 1)
            {
                Close();
            }


        }
    }
}
