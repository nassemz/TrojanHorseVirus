using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Split_File
{
    public partial class Form1 : Form
    {
        StreamReader sr;
        StreamWriter sw;
        public Form1()
        {
            InitializeComponent();
        }

        private void Opnbutt_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            textBox3.Text = openFileDialog1.FileName;        
        }

        private void button1_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
            textBox2.Text = saveFileDialog1.FileName;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            sr = new StreamReader(textBox3.Text);
            sw = new StreamWriter(textBox2.Text);
            try
            {
                string temp2 = "";
                string start = "0x";
                char[] buff = new char[32];
                int j = 1;
                int count = 0;
                int countall = 0;
                int count2 = 0;
                while (j != 0)
                {
                    count2 = sr.Read(buff, 0, 32);
                    countall = countall + count2;
                    if (count2 == 0)
                    {
                        if (temp2 != "")
                            sw.WriteLine(temp2);
                        break;
                    }
                    for (int i = 0; i < count2; i = i + 2)
                    {
                        temp2 = temp2 + start + buff[i] + buff[i + 1] + ", ";
                        count++;
                        if (count == ((count2 / 2)+(count2 % 2)))
                        {
                            sw.WriteLine(temp2);
                            temp2 = "";
                            count = 0;
                        }
                    }
                }
                sr.Close();
                sw.Close();
                int fin = countall / 2;
                textBox1.Text = fin.ToString();
                //MessageBox.Show(countall.ToString());

            }
            catch (Exception)
            {
                try
                {
                    sr.Close();
                    sw.Close();
                }
                catch (Exception)
                {
 
                }
                //MessageBox.Show("EOF");
            }
        }


    }
}