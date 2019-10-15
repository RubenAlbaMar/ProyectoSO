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
    
    public partial class Wellcome : Form
    {
        Socket server;

        public Wellcome()
        {
            InitializeComponent();

        }

        private void buttonCONNECT_Click(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.56.101");
            IPEndPoint ipep = new IPEndPoint(direc, 9200);

            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                MessageBox.Show("Conectado");

            }
            catch (SocketException ex)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }
        }

        private void button1_Click(object sender, EventArgs e) //sign in
        {
            SignIn signIn = new SignIn();

            signIn.ShowDialog();
            string mensaje = signIn.Mensaje();
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);
        }

        private void button2_Click(object sender, EventArgs e) //log in
        {
            LogIn logIn = new LogIn();

            logIn.ShowDialog();
            string mensaje2 = logIn.Mensaje();
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje2);
            server.Send(msg);

            byte[] msg2 = new byte[100];
            server.Receive(msg2);
            string respuesta = Encoding.ASCII.GetString(msg2).Split('\0')[0];
            if (respuesta == "1")
            {
                MessageBox.Show("Welcome");
                logIn.Close();
            }
            else
            {
                MessageBox.Show("TRY AGAIN");
            }
        }

        private void buttonDESCONNECT_Click(object sender, EventArgs e)
        {

            //Mensaje de desconexión
            string mensaje = "0/";

            byte[] msg34 = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg34);
            // Nos desconectamos
            this.BackColor = Color.Gray;
            server.Shutdown(SocketShutdown.Both);
            server.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string mensaje3;

            if (textBoxGAMENUMBER.Text != null)
            {
                mensaje3 = "3/" + textBoxGAMENUMBER.Text;
                //MessageBox.Show(mensaje3);
                byte[] msg3 = System.Text.Encoding.ASCII.GetBytes(mensaje3);
                server.Send(msg3);

                byte[] msg33 = new byte[1000];
                server.Receive(msg33);
                string respuesta33 = Encoding.ASCII.GetString(msg33).Split('\0')[0];
                MessageBox.Show(respuesta33);
            }
            else
            {
                MessageBox.Show("PLEASE, INSERT THE GAME NUMBER");
            }
        }

        private void buttonSEARCHUSERNAME_Click(object sender, EventArgs e)
        {
            string mensaje4;

            if (textBoxUSERNAME.Text != null)
            {
                mensaje4 = "4/" + textBoxUSERNAME.Text;
                byte[] msg4 = System.Text.Encoding.ASCII.GetBytes(mensaje4);
                server.Send(msg4);

                byte[] msg44 = new byte[1000];
                server.Receive(msg44);
                string respuesta44 = Encoding.ASCII.GetString(msg44).Split('\0')[0];
                MessageBox.Show(respuesta44);
            }
            else
            {
                MessageBox.Show("PLEASE, INSERT THE USERNAME");
            }
        }

        private void buttonRANKING_Click(object sender, EventArgs e)
        {
            string mensaje5;

            if (textBoxRANKING.Text != null)
            {
                mensaje5 = "5/" + textBoxRANKING.Text;
                byte[] msg5 = System.Text.Encoding.ASCII.GetBytes(mensaje5);
                server.Send(msg5);

                byte[] msg55 = new byte[1000];
                server.Receive(msg55);
                string respuesta55 = Encoding.ASCII.GetString(msg55).Split('\0')[0];
                MessageBox.Show(respuesta55);
            }
            else
            {
                MessageBox.Show("PLEASE, INSERT THE GAME NUMBER");
            }
        }
    }
}

    