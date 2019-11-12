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
    public partial class SignIn : Form
    {
        
        int done = 0;
        string mensaje;
        public string Mensaje()
        {
            return mensaje;
        }

        public SignIn()
        {
            InitializeComponent();
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

            if ((textBoxPASSWORD.Text == textBoxREPPASSWORD.Text) && (textBoxREPPASSWORD.Text != null))
            {
                if (textBoxUSERNAME.Text != null)
                {

                    // Enviamos al servidor el USERNAME tecleado
                    mensaje = "1/" + textBoxUSERNAME.Text + "/" + textBoxNAME.Text + "/" + textBoxSURNAME.Text + "/" + textBoxEMAIL.Text + "/" + textBoxPASSWORD.Text;
                    

                    done = 1;

                }

                else
                {
                    MessageBox.Show("Please try inputing your data again");
                }
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
