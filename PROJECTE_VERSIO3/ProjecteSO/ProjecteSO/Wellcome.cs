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
using System.Threading;

namespace ProjecteSO
{
    
    public partial class Wellcome : Form
    {
        Socket server;
        Thread atender;

        int var_logIn = 0;


        public Wellcome()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false; // NECESARIO PARA QUE LOS ELEMENTOS DE LOS FORMULARIOS PUEDAN SER ACCEDIDOS DESDE THREADS DIFERENTES A LOS QUE CREARON.

        }
        private void AtenderServidor()
        {
            while (true)
            {
                //recibimos mensaje del servidor
                byte[] msg999 = new byte[1000];
                server.Receive(msg999);
                //MessageBox.Show(Encoding.ASCII.GetString(msg999));
                string[] trozos = Encoding.ASCII.GetString(msg999).Split('/');
                //MessageBox.Show("codigo "+ trozos[0]);
                int codigo = Convert.ToInt32(trozos[0]);
                string mensaje;

                switch (codigo)
                {
                    case 1:
                        mensaje = ("Wellcome "+trozos[1].Split('\0')[0]);
                        MessageBox.Show(mensaje);
                        break;

                    case 2:
                        mensaje = trozos[1].Split('\0')[0];
           
                        if (mensaje == "1")
                        {
                            MessageBox.Show("Welcome");
                            var_logIn = 1;
                        }

                        else
                        {
                            MessageBox.Show("TRY AGAIN");
                        }

                        break;

                    case 3:
                        mensaje = trozos[1].Split('\0')[0];
                        MessageBox.Show(mensaje);

                        break;

                    case 4:
                        mensaje = trozos[1].Split('\0')[0];
                        MessageBox.Show(mensaje);
                        break;

                    case 5:
                        mensaje = trozos[1].Split('\0')[0];
                        MessageBox.Show(mensaje);
                        break;

                    case 6: //actualiza los conectados
                        
                        //MessageBox.Show("Ha entrado en el juego");
                        //se tiene que poner en la grid
                        
                        //mensaje = trozos[2].Split('\0')[0];
                        //int n = dataGridViewConectados.Rows.Add();

                        //dataGridViewConectados.Rows[n].Cells[0].Value = mensaje;
                        dataGridViewConectados.RowCount = Convert.ToInt32(trozos[1]);
                        int numRow = Convert.ToInt32(trozos[1]);
                        
                        int r = 0;
                        for ( r = 0; r < dataGridViewConectados.RowCount; r++)
                        {
                            dataGridViewConectados.Rows[r].Cells[0].Value = "";
                        }


                        int b = 0;
                        for ( b = 0; b < numRow; b++)
                        {
                            dataGridViewConectados.Rows[b].Cells[0].Value = trozos[b+2];
                        }


                        //for (int b = 0; b < numRow; b++)
                        //{
                        //    if (b < Convert.ToInt32(trozos[1]))
                        //        dataGridViewConectados.Rows[b].Cells[0].Value = trozos[b + 2];
                        //    else
                        //        dataGridViewConectados.Rows[b].Cells[0].Value = "";
                        //}


                        //--------------
                        //int n=0;
                        //int a;
                        //for (int b = 0; b < dataGridViewConectados.RowCount; b++)
                        //{
                        //    dataGridViewConectados.Rows[b].Cells[0].Value = "";
                        //}
                        //while (n < Convert.ToInt32(trozos[1]))
                        //{
                        //    if (n + 1 > dataGridViewConectados.RowCount)
                        //    {
                        //        a = dataGridViewConectados.Rows.Add();
                        //        dataGridViewConectados.Rows[a].Cells[0].Value = trozos[n+2];
                        //    }
                        //    else
                        //        dataGridViewConectados.Rows[n].Cells[0].Value = trozos[n+2];
                        //    n++;
                        //}
                        //---------------------------


                        //int r = 0;
                        //while (lista.Split('/') != null)
                        //{
                        //    dataGridViewConectados.Rows[n].Cells[0].Value = lista.Split('/');
                        //    r++;
                        //}
                        break;
                }
            }
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

            ThreadStart ts = delegate { AtenderServidor(); };
            atender = new Thread(ts);
            atender.Start();

        
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

            if (var_logIn==1)
                logIn.Close();

        }

        private void buttonDESCONNECT_Click(object sender, EventArgs e)
        {

            //Mensaje de desconexión
            string mensaje = "0/DESCONECTATE";

            byte[] msg34 = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg34);

            int r = 0;
            for (r = 0; r < dataGridViewConectados.RowCount; r++)
            {
                dataGridViewConectados.Rows[r].Cells[0].Value = "";
            }

            // Nos desconectamos
            atender.Abort(); //Paro el thread porque nos desconectamos
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

       

        private void label22_Click(object sender, EventArgs e)
        {

        }

        private void Wellcome_Load(object sender, EventArgs e)
        {
            
        }

        private void label26_Click(object sender, EventArgs e)
        {

        }

        private void L1_Click(object sender, EventArgs e)
        {

        }

        private void L2_Click(object sender, EventArgs e)
        {

        }
    }
}

    