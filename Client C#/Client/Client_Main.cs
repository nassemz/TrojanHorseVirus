using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Net.Sockets;
  
namespace Client
{

    public partial class Form1 : Form
    {
        TcpClient myClient;
        NetworkStream myns;
        StreamWriter mysw;
        StreamReader mysr;
        const int MAX_KEY_LENGTH = 255;
        char[] buff;
        string temprory;
        string temprory2;

        public Form1()
        {
            InitializeComponent();
            HideAll(tabPage1.Text);
            HideAll(tabPage2.Text);
            HideAll(tabPage3.Text);
            HideAll(tabPage4.Text);
            HideAll(tabPage5.Text);
            HideAll(tabPage6.Text);
            ShowStartFunc();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                StatusConnection.Text = "Connecting...";
                this.Refresh();
                string str;
                buff = new char[1024];
                int port_t = Int32.Parse(txtPort.Text);
             
                myClient = new TcpClient(txtIP.Text, port_t);
               
                myns = myClient.GetStream();
                mysw = new StreamWriter(myns);
                mysr = new StreamReader(myns);
                StatusConnection.Text = "Connected";
     
                mysw.AutoFlush = true;

                mysr.Read(buff, 0, 255);


                str = new String(buff);

                mysr.DiscardBufferedData();
                sendAck();

                mysr.Read(buff, 0, 255);
                str = new String(buff);
                mysr.DiscardBufferedData();
                sendAck();
                getAck();
                button1.Visible = false;
                button2.Visible = true;

                
            }

            catch (FormatException)
            {
                MessageBox.Show("Illigal Port");
                
            }

            catch (Exception)
            {
                BackToMain();
                StatusConnection.Text = "Disconnected";
                
            }

        }

        void clearbuff(char[] buffer)
        {
            for (int i = 0; i < buffer.GetUpperBound(0); i++)
            {
                buffer[i] = '\0';
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            txtIP.Text = "localhost";
            txtPort.Text = "8001";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                if (myClient.Connected == true)
                    myClient.Close();
                mysw.Close();
                myns.Close();
                StatusConnection.Text = "Disconnected";
            }
            catch (Exception)
            {
                StatusConnection.Text = "Disconnected";
                BackToMain();
            }
            button1.Visible = true;
            button2.Visible = false;

        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;
                rmotlbl.Text = button3.Text;
                listBox2.Items.Clear();
                clearbuff(buff);
                mysw.Write("COMP_INFO_");
                clearbuff(buff);
                getAck();
                sendAck();
                clearbuff(buff);
                //getAck();
                //clearbuff(buff);

                mysr.Read(buff, 0, 8);
                temp = new String(buff);

                temp.Insert(8, "\0");

                sendAck();

                if (temp.CompareTo("SUCCESS_") == 0)
                {
                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    listBox2.Items.Add("Computer Name : " + temp);
                    sendAck();

                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    listBox2.Items.Add("Owner Name : " + temp);
                    sendAck();

                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    listBox2.Items.Add("Processor Speed : " + temp + " Mhz");
                    sendAck();

                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    listBox2.Items.Add("Processor Type : " + temp);
                    sendAck();

                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    listBox2.Items.Add("System Directory : " + temp);
                    sendAck();

                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    listBox2.Items.Add("Windows ID : " + temp);
                    sendAck();

                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    listBox2.Items.Add("Windows Version : " + temp);
                    sendAck();
                }
                else
                {
                    sendAck();
                }
            }
            catch (Exception)
            {
                BackToMain();
                StatusConnection.Text = "Disconnected";
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;

                if (Drivetxt.Text == "" || Drivetxt.Text == " ")
                {
                    MessageBox.Show("Please Type a Drive name");
                    return;
                }

                temp = Drivetxt.Text.ToString().ToUpper() + ":\\ ";

                rmotlbl.Text = button4.Text;

                //MessageBox.Show(temp);
                listBox2.Items.Clear();
                mysw.Write("FREE_DISK_SPACE_");
                getAck();
                mysw.Write(temp);
                getAck();
                sendAck();

                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                temp = new String(buff);

                if (temp.CompareTo("SUCCESS_") == 0)
                {
                    sendAck();
                    clearbuff(buff);
                    mysr.Read(buff, 0, 8);
                    temp = new String(buff);
                    listBox2.Items.Add("Free Disk Space In " + Drivetxt.Text.ToString().ToUpper() + ":\\ " + " Is: " + temp + " MB");
                    sendAck();
                }
                else
                {
                    sendAck();
                }
            }
            catch (Exception)
            {
                BackToMain();
                StatusConnection.Text = "Disconnected";
            }

        }

        private void button5_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;
                rmotlbl.Text = button5.Text;
                listBox2.Items.Clear();
                mysw.Write("DEVICE_LIST_");
                getAck();
                sendAck();

                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                temp = new String(buff);

                if (temp.CompareTo("SUCCESS_") == 0)
                {
                    sendAck();
                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    sendAck();
                    int i = 0;
                    string tmpBuff1, tmpBuff2;

                    while (i != Length(temp))
                    {
                        tmpBuff1 = temp[i].ToString();
                        tmpBuff1 = tmpBuff1 + ":\\";
                        GetDType(tmpBuff1);
                        tmpBuff2 = new String(buff);
                        DriveTypeString(tmpBuff2);
                        listBox2.Items.Add(temp[i] + ":\\ - Is A " + temprory);
                        i++;
                    }

                }
                else
                {
                    sendAck();
                    MessageBox.Show("Failed to execute operation,Invalid Input!");
                    return;
                }
            }
            catch (Exception)
            {
                BackToMain();
                StatusConnection.Text = "Disconnected";
            }

        }

        int Length(string t)
        {
            int count = 0, i = 0;
            try
            {
                
                while (t[i] != '\0')
                {
                    count++;
                    i++;
                }
                return count;
            }
            catch (Exception)
            {
                return count;
            }
        }

        private void Backbot_Click(object sender, EventArgs e)
        {
            BackToMain();
            listBox2.Items.Clear();
            Drivetxt.Text = "";
            rmotlbl.Text = "";
        }

        void BackToMain()
        {
            try
            {
                HideAll(tabControl1.SelectedTab.Text);
                ShowStartFunc();
                mysw.Write("BACK_TO_MAIN_");
                getAck();

            }
            catch (Exception )
            {
                StatusConnection.Text = "Disconnected";
                button1.Visible = true;
                button2.Visible = false;
            }
        }

        void sendAck()
        {
            try
            {
                mysw.Write("OK");
            }
            catch (Exception)
            {
                StatusConnection.Text = "Disconnected";
                BackToMain();
            }
        }

        void getAck()
        {
            try
            {
                string temp;
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                temp = new String(buff);
                if (temp[0] != 'O' || temp[1] != 'K')
                {
                    MessageBox.Show("Connection Faild");
                    BackToMain();
                }
            }
            catch (Exception)
            {
                BackToMain();
                StatusConnection.Text = "Disconnected";
            }
        }

        void HideAll(string menu)
        {
            switch (menu)
            {
                case "Power Options":
                    button11.Visible = false;
                    button12.Visible = false;
                    button13.Visible = false;
                    button14.Visible = false;
                    label5.Visible = false;
                    ShowStartFunc();
                    break;
                case "File Manager (FTP)":
                    menuStrip2.Visible = false;
                    button34.Visible = false;
                    button35.Visible = false;
                    button36.Visible = false;
                    button37.Visible = false;
                    button38.Visible = false;
                    button39.Visible = false;
                    //listBox4.Visible = false;
                    groupBox4.Visible = false;
                    textBox8.Visible = false;
                    textBox9.Visible = false;
                    label21.Text = "";
                    label20.Text = "";
                    label19.Text = "";
                    button40.Visible = false;
                    groupBox5.Visible = false;
                    break;
                case "Process Manger":
                    label10.Visible = false;
                    button24.Visible = false;
                    button25.Visible = false;
                    button26.Visible = false;
                    textBox4.Visible = false;
                    listBox1.Visible = false;
                    label11.Visible = false;
                    label9.Visible = false;
                    progressBar1.Visible = false;
                    ShowStartFunc();
                    break;
                case "Remote Compyter Information":
                    Backbot.Visible = false;
                    button3.Visible = false;
                    button4.Visible = false;
                    button5.Visible = false;
                    Drivetxt.Visible = false;
                    listBox2.Visible = false;
                    label4.Visible = false;
                    ShowStartFunc();
                    break;
                case "Parctical Operations":
                    button15.Visible = false;
                    button16.Visible = false;
                    button17.Visible = false;
                    button18.Visible = false;
                    button19.Visible = false;
                    groupBox7.Visible = false;
                    button20.Visible = false;
                    button21.Visible = false;
                    button22.Visible = false;
                    button23.Visible = false;
                    textBox2.Visible = false;
                    textBox3.Visible = false;
                    label6.Visible = false;
                    label7.Visible = false;
                    label8.Visible = false;
                    ShowStartFunc();
                    break;
                case "Registry Manager":
                    menuStrip1.Visible = false;
                    groupBox1.Visible = false;
                    groupBox3.Visible = false;
                    groupBox2.Visible = false;
                    ShowStartFunc();
                    break;
                default:
                    break;
            }
            
        }

        void ShowAll(string menu)
        {
            switch (menu)
            {
                case "Power Options":
                    button11.Visible = true;
                    button12.Visible = true;
                    button13.Visible = true;
                    button14.Visible = true;
                    label5.Visible = true;
                    break;
                case "File Manager (FTP)":
                    menuStrip2.Visible = true;
                    listBox4.Items.Clear();
                    textBox8.Text = "";
                    label20.Text = "";
                    label21.Text = "";
                    label19.Text = "";
                    break;
                case "Process Manger":
                    label10.Visible = true;
                    button24.Visible = true;
                    button25.Visible = true;
                    button26.Visible = true;
                    textBox4.Visible = true;
                    listBox1.Visible = true;
                    label11.Visible = true;
                    label9.Visible = true;
                    progressBar1.Visible = true;
                    break;
                case "Remote Compyter Information":
                    Backbot.Visible = true;
                    button3.Visible = true;
                    button4.Visible = true;
                    button5.Visible = true;
                    Drivetxt.Visible = true;
                    listBox2.Visible = true;
                    label4.Visible = true;
                    break;
                case "Parctical Operations":
                    button15.Visible = true;
                    button16.Visible = true;
                    button17.Visible = true;
                    button18.Visible = true;
                    button19.Visible = true;
                    groupBox7.Visible = true;
                    button20.Visible = true;
                    button21.Visible = true;
                    button22.Visible = true;
                    button23.Visible = true;
                    textBox2.Visible = true;
                    textBox3.Visible = true;
                    label6.Visible = true;
                    label7.Visible = true;
                    label8.Visible = true;
                    break;
                case "Registry Manager":
                    menuStrip1.Visible = true;
                    break;
                default:
                    break;
            }
            HideStartFunc();
        }

        bool GetDType(string DriveName)
        {
                string buffe;
                getAck();
                mysw.Write(DriveName);
                getAck();
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                buffe = new String(buff);
                sendAck();
                if (buffe.CompareTo("SUCCESS_") == 0)
                {
                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    sendAck();
                    return true;
                }
                else
                    return false;
   
        }

        private void button6_Click(object sender, EventArgs e)
        {
            ShowFuncGlobal(tabPage4.Text);
        }

        void ShowFuncGlobal(string menu)
        {
            try
            {
                switch (menu)
                {
                    case "Power Options":
                        mysw.Write("POWER_");
                        break;
                    case "File Manager (FTP)":
                        mysw.Write("FILE_MNGR_");
                        break;
                    case "Process Manger":
                        mysw.Write("PROC_MNGR_");
                        break;
                    case "Remote Compyter Information":
                        mysw.Write("PC_INFO_");
                        break;
                    case "Parctical Operations":
                        mysw.Write("PRAC_OPER_");
                        break;
                    case "Registry Manager":
                        mysw.Write("REG_MNGR_");
                        break;
                    case "Delete Service":
                        mysw.Write("SHUT_SERVICE_");
                        break;
                    default:
                        return;
                        break;
                }
                clearbuff(buff);
                getAck();
                HideAll(tabPage1.Text);
                HideAll(tabPage2.Text);
                HideAll(tabPage3.Text);
                HideAll(tabPage4.Text);
                HideAll(tabPage5.Text);
                if (menu != "Delete Service")
                    ShowAll(menu);
            }
            catch (Exception)
            {
                BackToMain();
            }
        }

        void HideStartFunc()
        {
            button6.Visible = false;
            button7.Visible = false;
            button8.Visible = false;
            button9.Visible = false;
            button10.Visible = false;
            button27.Visible = false;
        }

        void ShowStartFunc()
        {
            button6.Visible = true;
            button7.Visible = true;
            button8.Visible = true;
            button9.Visible = true;
            button10.Visible = true;
            button27.Visible = true;
        }

        private void button14_Click(object sender, EventArgs e)
        {
            BackToMain();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            ShowFuncGlobal(tabPage3.Text);
        }
        
        private void button7_Click(object sender, EventArgs e)
        {
            ShowFuncGlobal(tabPage1.Text);
        }

        private void button12_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;
                mysw.Write("LOGOFF_");
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 255);
                temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label5.Text = "The Remote Computer Account Has Successfully Logged Off!";
                else
                    label5.Text = "Failed to execute operation!";
            }
            catch (Exception)
            { BackToMain(); }
        }

        private void button14_Click_1(object sender, EventArgs e)
        {
            BackToMain();
            label5.Text = "";
        }

        private void button11_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;
                mysw.Write("SHUTDOWN_");
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 255);
                temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label5.Text = "The Remote Computer Account Has Successfully Logged Off!";
                else
                    label5.Text = "Failed to execute operation!";
            }
            catch (Exception)
            { BackToMain(); }
        }

        private void button13_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;
                mysw.Write("REBOOT_");
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 255);
                temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label5.Text = "The Remote Computer Has Been Successfully Rebooted !";
                else
                    label5.Text = "Failed to execute operation!";
            }
            catch (Exception)
            { BackToMain(); }
        }

        private void button10_Click(object sender, EventArgs e)
        {
            ShowFuncGlobal(tabPage5.Text);
        }

        private void button22_Click(object sender, EventArgs e)
        {
            BackToMain();
            textBox2.Text = "";
            textBox3.Text = "";
            label8.Text = "";
        }

        private void button21_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox3.Text == "" || textBox3.Text == " ")
                {
                    MessageBox.Show("Please Type a Drive name");
                    return;
                }
                label8.Text = "Waiting for Opening The CD-ROM On Remote Computer!";
                this.Refresh();
                string temp;
                temp = Drivetxt.Text.ToString().ToUpper() + ":\\ ";
                mysw.Write("OPEN_CD_ROM_");
                clearbuff(buff);
                getAck();
                mysw.Write(temp);
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                mysr.Read(buff, 0, 8);
                String temp2 = new String(buff);
                sendAck();
                if (temp2.CompareTo("SUCCESS_") == 0)
                    label8.Text = "CD-ROM Has Successfully Opened On Remote Computer!";
                else
                    label8.Text = "Could not open CD-ROM (Try Again!)";
            }
            catch (Exception)
            {
                MessageBox.Show("Cannot connect to server, and could not open CD-ROM (Try Again!)");
                BackToMain();
            }

        }

        private void button23_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox3.Text == "" || textBox3.Text == " ")
                {
                    MessageBox.Show("Please Type a Drive name");
                    return;
                }
                label8.Text = "Waiting for Closing The CD-ROM On Remote Computer!";
                this.Refresh();
                string temp;
                temp = Drivetxt.Text.ToString().ToUpper() + ":\\ ";
                mysw.Write("CLOSE_CD_ROM_");
                clearbuff(buff);
                getAck();
                mysw.Write(temp);
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                mysr.Read(buff, 0, 8);
                String temp2 = new String(buff);
                sendAck();
                if (temp2.CompareTo("SUCCESS_") == 0)
                    label8.Text = "CD-ROM Has Successfully Closed On Remote Computer!";
                else
                    label8.Text = "Could not Close CD-ROM (Try Again!)";
            }
            catch (Exception)
            {
                MessageBox.Show("Could not Close CD-ROM (Try Again!)");
                BackToMain();
            }
        }

        private void button15_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;
                bool off = true;
                if (button15.Text == "Turn OFF Monitor")
                {
                    temp = "TURN_OFF_MON_";
                    off = false;
                }
                else
                    temp = "TURN_ON_MON_";

                mysw.Write(temp);
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                sendAck();
                temp = new String(buff);
                if (temp.CompareTo("SUCCESS_") == 0)
                {
                    if (off == false)
                    {
                        label8.Text = "The Remote Computer Monitor Has Been Successfully Turned Off!";
                        button15.Text = "Turn ON Monitor";
                    }
                    else
                    {
                        label8.Text = "The Remote Computer Monitor Has Been Successfully Turned On!";
                        button15.Text = "Turn OFF Monitor";
                    }
                }
                else
                {
                    if (off == false)
                        label8.Text = "Could not turn off monitor!";
                    else
                        label8.Text = "Could not turn on monitor!";
                }
            }
            catch (Exception)
            { BackToMain(); }

        }

        private void button16_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;

                mysw.Write("SHOW_START_MENU_");
                clearbuff(buff);
                getAck();
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label8.Text = "Showing Start Menu On Remote Computer,Successfully executed!";
                else
                    label8.Text = "Could not show start menu!";
            }
            catch (Exception)
            { BackToMain(); }
        }

        private void button17_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;
                mysw.Write("START_SCREEN_SAVER_");
                clearbuff(buff);
                getAck();
                sendAck();
                mysr.Read(buff, 0, 8);
                temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label8.Text = "Initiated Screen Saver On Remote Computer,Successfully executed!";
                else
                    label8.Text = "Could not initiate screen saver!";
            }
            catch (Exception)
            { BackToMain(); }
        }

        private void button19_Click(object sender, EventArgs e)
        {
            try
            {
                string temp, seconds;
                if (textBox2.Text == "")
                {
                    MessageBox.Show("Please Type number of Seconds");
                    return;
                }
                seconds = textBox2.Text;
                int number = Int32.Parse(seconds);
                mysw.Write("BEEP_PC_");
                clearbuff(buff);
                getAck();
                mysw.Write(seconds);
                clearbuff(buff);
                getAck();
                sendAck();
                mysr.Read(buff, 0, 8);
                temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label8.Text = "The Remote computer has succefully beeped for " + number.ToString() + " seconds";
                else
                    label8.Text = "Faild to send a Beep";
            }
            catch (System.FormatException)
            {
                MessageBox.Show("Please Type A Number");
            }
            catch (Exception)
            {
                BackToMain();
            }



        }

        private void button20_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;
                bool off = true;
                if (button20.Text == "Disable TaskMngr")
                {
                    temp = "DISABLE_TASK_MNGR_";
                    off = false;
                }
                else
                    temp = "ENABLE_TASK_MNGR_";

                mysw.Write(temp);
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                sendAck();
                temp = new String(buff);
                if (temp.CompareTo("SUCCESS_") == 0)
                {
                    if (off == false)
                    {
                        label8.Text = "Task Manager Has Been Disabled Successfully On Remote Computer!";
                        button20.Text = "Enable TaskMngr";
                    }
                    else
                    {
                        label8.Text = "Task Manager Has Been Enabled Successfully On Remote Computer!";
                        button20.Text = "Disable TaskMngr";
                    }
                }
                else
                {
                    if (off == false)
                        label8.Text = "Could not disable task manager!";
                    else
                        label8.Text = "Could not enable task manager!";
                }
            }
            catch (Exception)
            { BackToMain(); }
        }

        private void button18_Click(object sender, EventArgs e)
        {
            try{
            string temp;
            bool off = true;
            if (button18.Text == "Disable Mouse & Keyboard")
            {
                temp = "DISABLE_MK_";
                off = false;
            }
            else
                temp = "ENABLE_MK_";

            mysw.Write(temp);
            clearbuff(buff);
            getAck();
            clearbuff(buff);
            sendAck();
            clearbuff(buff);
            mysr.Read(buff, 0, 8);
            sendAck();
            temp = new String(buff);
            if (temp.CompareTo("SUCCESS_") == 0)
            {
                if (off == false)
                {
                    label8.Text = "Disabled Mouse and Keyboard Successfully On Remote Computer!";
                    button18.Text = "Enable Mouse & Keyboard";
                }
                else
                {
                    label8.Text = "Enabled Mouse and Keyboard Successfully On Remote Computer!";
                    button18.Text = "Disable Mouse & Keyboard";
                }
            }
            else
            {
                if (off == false)
                    label8.Text = "Could not disable mouse & keyboard!";
                else
                    label8.Text = "Could not enable mouse & keyboard!";
            }
            }
        catch(Exception)
        {BackToMain();}
        }

        private void button24_Click(object sender, EventArgs e)
        {
            try
            {
                string temp;
                mysw.Write("ENUM_PROCESSES_");
                getAck();
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                temp = new String(buff);
                sendAck();

                if (temp.CompareTo("SUCCESS_") == 0)
                {
                    //get list size
                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    sendAck();
                    int ListSize = Int32.Parse(temp);
                    int pide;
                    string Pname, Pid;
                    listBox1.Items.Clear();
                    progressBar1.Maximum = ListSize;
                    progressBar1.Minimum = 0;
                    progressBar1.Step = 1;
                    progressBar1.Value = 0;
                    for (int i = 0; i < ListSize; i++)
                    {
                        clearbuff(buff);
                        Pname = mysr.ReadLine();  //get process name
                        //Pname = new String(buff);
                        sendAck();

                        clearbuff(buff);
                        Pid = mysr.ReadLine();   //get process ID
                        //Pid = new String(buff);
                        pide = Int32.Parse(Pid);
                        sendAck();
                        Pname = Pname + "    " + pide;
                        listBox1.Items.Add(Pname);
                        progressBar1.Value = progressBar1.Value + progressBar1.Step;
                        this.Refresh();
                    }
                    progressBar1.Value = 0;
                    label10.Text = "List Of Processes On Remote Computer: ";
                }
                else
                    label10.Text = "Could not list processes (Try Again!)";
            }
            catch (Exception)
            {
                BackToMain();
            }
        }

        private void button25_Click(object sender, EventArgs e)
        {
            try
            {
                int pid = Int32.Parse(textBox4.Text);
                string temp;

                mysw.Write("KILL_PROCESS_");
                getAck();
                mysw.Write(pid.ToString());	 //send PID
                getAck();
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8); //get if success or not
                temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label10.Text = "Process has successfully Been Terminated On Remote Computer!";
                else
                    label10.Text = "Failed to terminate process (check for valid input!)";

            }
            catch (FormatException)
            {
                MessageBox.Show("Type A ID number");
            }
            catch (Exception)
            {
                BackToMain();
            }
        }

        private void button26_Click(object sender, EventArgs e)
        {
            BackToMain();
            listBox1.Items.Clear();
            textBox4.Text = "";
            label10.Text = "";
        }

        private void button28_Click(object sender, EventArgs e)
        {
            try
            {

                if (textBox5.Text == "")
                {
                    MessageBox.Show("Type the full path of the registry key (including the name)");
                    return;
                }


                string temp;
                object s = comboBox1.SelectedItem;

                if (s != null)
                {
                    mysw.Write("ADD_KEY_");
                    getAck();

                    int res = 0;
                    switch (s.ToString())
                    {
                        case ("HKEY_CLASSES_ROOT"):
                            res = 1;
                            break;
                        case ("HKEY_CURRENT_USER"):
                            res = 2;
                            break;
                        case ("HKEY_LOCAL_MACHINE"):
                            res = 3;
                            break;
                        case ("HKEY_USERS"):
                            res = 4;
                            break;
                        case ("HKEY_CURRENT_CONFIG"):
                            res = 5;
                            break;
                        default:
                            res = 0;
                            break;
                    }
                    mysw.Write(res.ToString()); ;	 //send the hkey
                    getAck();
                    mysw.Write(textBox5.Text);	 //send the full path
                    getAck();
                    sendAck();
                    mysr.Read(buff, 0, 8); //get if success or not
                    temp = new String(buff);
                    sendAck();
                    if (temp.CompareTo("SUCCESS_") == 0)

                        label14.Text = "Registry Key Has Successfully Been Added On Remote Computer!";
                    else
                        label14.Text = "Could not add Registry key (Try Again!)";
                }
                else
                    MessageBox.Show("Choose one of the HKEY");
            }
            catch (Exception)
            {
                BackToMain();
            }
        }

        private void button27_Click(object sender, EventArgs e)
        {
            ShowFuncGlobal(tabPage6.Text);
        }

        private void button29_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox5.Text == "")
                {
                    MessageBox.Show("Type the full path of the registry key (including the name)");
                    return;
                }
                string temp;
                object s = comboBox1.SelectedItem;
                if (s != null)
                {
                    mysw.Write("DEL_KEY_");
                    getAck();

                    int res = 0;
                    switch (s.ToString())
                    {
                        case ("HKEY_CLASSES_ROOT"):
                            res = 1;
                            break;
                        case ("HKEY_CURRENT_USER"):
                            res = 2;
                            break;
                        case ("HKEY_LOCAL_MACHINE"):
                            res = 3;
                            break;
                        case ("HKEY_USERS"):
                            res = 4;
                            break;
                        case ("HKEY_CURRENT_CONFIG"):
                            res = 5;
                            break;
                        default:
                            res = 0;
                            break;
                    }
                    mysw.Write(res.ToString()); ;	 //send the hkey
                    getAck();
                    mysw.Write(textBox5.Text);	 //send the full path
                    getAck();
                    sendAck();
                    mysr.Read(buff, 0, 8); //get if success or not
                    temp = new String(buff);
                    sendAck();
                    if (temp.CompareTo("SUCCESS_") == 0)

                        label14.Text = "Registry Key Has Successfully Been Deleted On Remote Computer!";
                    else
                        label14.Text = "Could not delete Registry key (Try Again!)";
                }
                else
                    MessageBox.Show("Choose one of the HKEY");
            }
            catch (Exception)
            {
                BackToMain();
            }
        }

        private void button30_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox6.Text == "")
                {
                    MessageBox.Show("Type the registry key value description");
                    return;
                }
                string temp;
                object s = comboBox2.SelectedItem;
                object s1 = comboBox1.SelectedItem;
                if (s != null && s1 != null)
                {
                    mysw.Write("ADD_VALUE_TO_KEY_");
                    getAck();

                    int res = 0;
                    switch (s1.ToString())
                    {
                        case ("HKEY_CLASSES_ROOT"):
                            res = 1;
                            break;
                        case ("HKEY_CURRENT_USER"):
                            res = 2;
                            break;
                        case ("HKEY_LOCAL_MACHINE"):
                            res = 3;
                            break;
                        case ("HKEY_USERS"):
                            res = 4;
                            break;
                        case ("HKEY_CURRENT_CONFIG"):
                            res = 5;
                            break;
                        default:
                            res = 0;
                            break;
                    }
                    
                    mysw.Write(res.ToString()); ;	 //send the hkey
                    getAck();
                    mysw.Write(textBox5.Text);	 //send the full path
                    getAck();
                    res = 0;
                    switch (s.ToString())
                    {
                        case ("REG_SZ"):
                            res = 1;
                            break;
                        case ("REG_DWORD"):
                            res = 2;
                            break;
                        case ("REG_BINARY"):
                            res = 3;
                            break;
                        default:
                            res = 0;
                            break;
                    }
                    mysw.Write(res.ToString()); ;	 //send the hkey
                    getAck();

                    mysw.Write(textBox6.Text);	 //send the discripshion
                    getAck();
                    mysw.Write(textBox7.Text);	 //send the data
                    getAck();

                    sendAck();
                    mysr.Read(buff, 0, 8); //get if success or not
                    temp = new String(buff);
                    sendAck();
                    if (temp.CompareTo("SUCCESS_") == 0)

                        label14.Text = "New Value To Registry Key Has Successfully Been Added On Remote Computer!";
                    else
                        label14.Text = "Could not add Registry key value (Try Again!)";
                }
                else
                    MessageBox.Show("Choose the Registry key type");
            }
            catch (Exception)
            {
                BackToMain();
            }
        }

        private void removeKeyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            label14.Text = "";
            label13.Text = "Type the full path of the registry key (including the name)";
            label18.Text = "";
            groupBox2.Visible = true;
            button28.Visible = false;
            button29.Visible = true;
            textBox5.Visible = true;
            groupBox1.Visible = false;
            button31.Visible = false;
            button32.Visible = false;
            button33.Visible = false;
        }

        private void dedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            label13.Text = "Type the full path of the registry key (including the name)";
            label14.Text = "";
            label18.Text = "";
            button31.Visible = false;
            button32.Visible = false;
            button33.Visible = false;
            groupBox2.Visible = true;
            textBox5.Visible = true;
            button28.Visible = true;
            button29.Visible = false;
            groupBox1.Visible = false;
            groupBox3.Visible = false;
        }

        private void setValueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            label14.Text = "";
            label18.Text = "";
            label13.Text = "Type the full path of the registry key (including the name)";
            button31.Visible = false;
            button32.Visible = false;
            textBox6.Visible = true;
            textBox7.Visible = true;
            button33.Visible = false;
            button28.Visible = false;
            textBox5.Visible = true;
            button29.Visible = false;
            groupBox1.Visible = true;
            groupBox2.Visible = true;
            groupBox3.Visible = false;
        }

        private void viewValueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            label14.Text = "";
            label13.Text = "Type the full path of the registry key (including the name)";
            label18.Text = "";
            groupBox3.Visible = true;
            groupBox1.Visible = false;
            groupBox2.Visible = true;
            button31.Visible = true;
            button33.Visible = false;
            textBox5.Visible = true;
            button32.Visible = false;
            button28.Visible = false;
            button29.Visible = false;
            

        }

        private void button31_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox5.Text == "")
                {
                    MessageBox.Show("Choose the HKey Key for Viewing");
                    return;
                }
                string temp;
                object s = comboBox1.SelectedItem;
                if (s != null)
                {
                    mysw.Write("VIEW_VALUE_OF_KEY_");
                    getAck();

                    int res = 0;
                    switch (s.ToString())
                    {
                        case ("HKEY_CLASSES_ROOT"):
                            res = 1;
                            break;
                        case ("HKEY_CURRENT_USER"):
                            res = 2;
                            break;
                        case ("HKEY_LOCAL_MACHINE"):
                            res = 3;
                            break;
                        case ("HKEY_USERS"):
                            res = 4;
                            break;
                        case ("HKEY_CURRENT_CONFIG"):
                            res = 5;
                            break;
                        default:
                            res = 0;
                            break;
                    }

                    mysw.Write(res.ToString()); ;	 //send the hkey
                    getAck();
                    mysw.Write(textBox5.Text); ;	 //send the fullpath
                    getAck();
                    sendAck();
                    clearbuff(buff);
                    mysr.Read(buff, 0, 8); //get if success or not
                    temp = new String(buff);
                    sendAck();
                    if (temp.CompareTo("SUCCESS_") == 0)
                    {
                        clearbuff(buff);
                        mysr.Read(buff, 0, 255); //get if success or not
                        sendAck();
                        temp = new String(buff);
                        int ListSize = Int32.Parse(temp);
                        listBox3.Items.Clear();
                        string Pvalue;
                        for (int i = 0; i < ListSize; i++)
                        {
                            clearbuff(buff);
                            Pvalue = mysr.ReadLine(); //get if success or not
                            sendAck();
                            listBox3.Items.Add(Pvalue);
                        }
                        label18.Visible = false;
                        groupBox3.Visible = true;
                    }
                    else
                    {
                        label18.Text = "Could not list key values (Check for valid input!)";
                        label18.Visible = true;
                        groupBox3.Visible = false;
                    }

                }
            }
            catch (Exception)
            {
                BackToMain();
            }  
            }

        private void button32_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox5.Text == "")
                {
                    MessageBox.Show("Choose the HKey Key for Viewing Sub Keys");
                    return;
                }
                string temp;
                object s = comboBox1.SelectedItem;
                if (s != null)
                {
                    mysw.Write("VIEW_SUBKKEYS_");
                    getAck();

                    int res = 0;
                    switch (s.ToString())
                    {
                        case ("HKEY_CLASSES_ROOT"):
                            res = 1;
                            break;
                        case ("HKEY_CURRENT_USER"):
                            res = 2;
                            break;
                        case ("HKEY_LOCAL_MACHINE"):
                            res = 3;
                            break;
                        case ("HKEY_USERS"):
                            res = 4;
                            break;
                        case ("HKEY_CURRENT_CONFIG"):
                            res = 5;
                            break;
                        default:
                            res = 0;
                            break;
                    }

                    mysw.Write(res.ToString()); ;	 //send the hkey
                    getAck();
                    mysw.Write(textBox5.Text); ;	 //send the fullpath
                    getAck();
                    sendAck();
                    clearbuff(buff);
                    mysr.Read(buff, 0, 8); //get if success or not
                    temp = new String(buff);
                    sendAck();
                    if (temp.CompareTo("SUCCESS_") == 0)
                    {
                        clearbuff(buff);
                        mysr.Read(buff, 0, 255); //get if success or not
                        sendAck();
                        temp = new String(buff);
                        int ListSize = Int32.Parse(temp);
                        listBox3.Items.Clear();
                        string Pvalue;
                        for (int i = 0; i < ListSize; i++)
                        {
                            clearbuff(buff);
                            Pvalue = mysr.ReadLine(); //get if success or not
                            sendAck();
                            listBox3.Items.Add(Pvalue);
                        }
                        label18.Visible = false;
                        groupBox3.Visible = true;
                    }
                    else
                    {
                        label18.Text = "Could not list key subkeys (Check for valid input!)";
                        label18.Visible = true;
                        groupBox3.Visible = false;
                    }

                }
            }
            catch (Exception)
            {
                BackToMain();
            }



                 
        }

        private void searchValueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            label14.Text = "";
            label18.Text = "";
            label13.Text = "Type the full path of the registry key (including the name)";
            groupBox3.Visible = true;
            groupBox1.Visible = false;
            groupBox2.Visible = true;
            button31.Visible = false;
            button32.Visible = true;
            button33.Visible = false;
            textBox5.Visible = true;
            button28.Visible = false;
            button29.Visible = false;
        }

        private void SearchToolStripMenuItem_Click(object sender, EventArgs e)
        {
            label14.Text = "";
            label18.Text = "";
            label13.Text = "Type the registry key name";
            groupBox3.Visible = true;
            groupBox1.Visible = false;
            groupBox2.Visible = true;
            button31.Visible = false;
            button32.Visible = false;
            button33.Visible = true;
            textBox5.Visible = true;
            button28.Visible = false;
            button29.Visible = false;
        }

        private void button33_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox5.Text == "")
                {
                    MessageBox.Show("Type the Key Name that you search for");
                    return;
                }
                string temp;
                object s = comboBox1.SelectedItem;
                if (s != null)
                {
                    mysw.Write("SEARCH_KEY_");
                    getAck();

                    int res = 0;
                    switch (s.ToString())
                    {
                        case ("HKEY_CLASSES_ROOT"):
                            res = 1;
                            break;
                        case ("HKEY_CURRENT_USER"):
                            res = 2;
                            break;
                        case ("HKEY_LOCAL_MACHINE"):
                            res = 3;
                            break;
                        case ("HKEY_USERS"):
                            res = 4;
                            break;
                        case ("HKEY_CURRENT_CONFIG"):
                            res = 5;
                            break;
                        default:
                            res = 0;
                            break;
                    }

                    mysw.Write(res.ToString()); ;	 //send the hkey
                    getAck();
                    mysw.Write(textBox5.Text); ;	 //send the key name
                    getAck();
                    sendAck();
                    clearbuff(buff);
                    mysr.Read(buff, 0, 8); //get if success or not
                    temp = new String(buff);
                    sendAck();
                    if (temp.CompareTo("SUCCESS_") == 0)
                    {
                        clearbuff(buff);
                        mysr.Read(buff, 0, 255); //get if success or not
                        sendAck();
                        temp = new String(buff);
                        int ListSize = Int32.Parse(temp);
                        listBox3.Items.Clear();
                        string Pvalue;
                        for (int i = 0; i < ListSize; i++)
                        {
                            clearbuff(buff);
                            Pvalue = mysr.ReadLine(); //get if success or not
                            sendAck();
                            listBox3.Items.Add(Pvalue);
                        }
                        label18.Visible = false;
                        groupBox3.Visible = true;
                    }
                    else
                    {
                        label18.Text = "Could not find key!";
                        label18.Visible = true;
                        groupBox3.Visible = false;
                    }

                }
            }
            catch (Exception)
            {
                BackToMain();
            }

        }

        private void listBox3_DoubleClick(object sender, EventArgs e)
        {
            object selected = listBox3.SelectedItem;
            textBox5.Text = selected.ToString();
        }

        private void backToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackToMain();
            listBox1.Items.Clear();
            listBox3.Items.Clear();
            textBox5.Visible = false;
            textBox6.Visible = false;
            textBox7.Visible = false;
            label14.Text = "";
            label18.Text = "";
            groupBox1.Visible = false;
            groupBox2.Visible = false;
            groupBox3.Visible = false;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            ShowFuncGlobal(tabPage2.Text);
        }

        private void button34_Click(object sender, EventArgs e)
        {
            try
            {

                if (textBox8.Text == "" || (!radioButton3.Checked && !radioButton4.Checked) || textBox9.Text== "")
                {
                    label20.Text = " Please type the file name and check on of the choose Radio";
                    return;
                }

                if(radioButton3.Checked)
                    if(textBox9.Text == "")
                    {
                        label20.Text = "fill the FTP Server IP";
                        return;
                    }


                mysw.Write("UPLOAD_FILE_");
                getAck();
                mysw.Write(textBox8.Text);
                getAck();
                mysw.Write(textBox9.Text);
                getAck();

                if (radioButton3.Checked)
                    mysw.Write(textBox10.Text);
                else
                {
                    // Get the hostname 
                    string myHost = System.Net.Dns.GetHostName();
                    // Get the IP from the host name
                    string myIP = System.Net.Dns.GetHostByName(myHost).AddressList[0].ToString();
                    // Show the IP 
                    mysw.Write(myIP);
                }


                getAck();

                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                string temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label20.Text = "File has successfully Been Downloaded From Remote Computer!";
                else
                    label20.Text = "Failed to download file (check FTP connection & Valid path)";
            }
            catch (Exception)
            {
                BackToMain();
            }
            

        }

        private void button35_Click(object sender, EventArgs e)
        {

            try
            {
                if (textBox8.Text == "" || (!radioButton1.Checked && !radioButton2.Checked) || (!radioButton3.Checked && !radioButton4.Checked))
                {
                    label20.Text = " Please type the file name and check on of the choose Radio";
                    return;
                }
                if (radioButton3.Checked)
                    if (textBox9.Text == "")
                    {
                        label20.Text = "fill the FTP Server IP";
                        return;
                    }

              mysw.Write("DOWNLOAD_FILE_");
              getAck();
              mysw.Write(textBox8.Text);
              getAck();
              mysw.Write(textBox9.Text);
              getAck();
              if(radioButton2.Checked)
                    mysw.Write("2");
              else
                    mysw.Write("1");
                getAck();

                if (radioButton3.Checked)
                    mysw.Write(textBox10.Text);
                else
                {
                    // Get the hostname 
                    string myHost = System.Net.Dns.GetHostName();
                    // Get the IP from the host name
                    string myIP = System.Net.Dns.GetHostByName(myHost).AddressList[0].ToString();
                    // Show the IP 
                    mysw.Write(myIP);
                }                
              

              getAck();

              sendAck();
              clearbuff(buff);
              mysr.Read(buff, 0, 8);
              string temp = new String(buff);
              sendAck();
              if (temp.CompareTo("SUCCESS_") == 0)
                  label20.Text = "File has successfully Been Uploaded On Remote Computer!";
              else
                  label20.Text = "Failed to upload file (check FTP connection & Valid path)";
          }
          catch (Exception)
          {
              BackToMain();
          }

        }

        private void button36_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox8.Text == "")
                    return;
                mysw.Write("DEL_FILE_");
                getAck();
                mysw.Write(textBox8.Text);
                getAck();
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                string temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label20.Text = "File has successfully Been Deleted On Remote Computer!";
                else
                    label20.Text = "Failed to delete file (possibly,Invalid path or file name!)";
            }
            catch (Exception)
            {
                BackToMain();
            }
        }

        private void button37_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox8.Text == "")
                    return;
                mysw.Write("DEL_DIR_");
                getAck();
                mysw.Write(textBox8.Text);
                getAck();
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                string temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label20.Text = "Directory has successfully Been Deleted On Remote Computer!";
                else
                    label20.Text = "Failed to delete directory (possibly,Invalid path!)";
            }
            catch (Exception)
            {
                BackToMain();
            }
        }

        private void button39_Click(object sender, EventArgs e)
        {
            try
            {
                label20.Text = "List of the files";
                if (textBox8.Text == "")
                    return;
                string temp = textBox8.Text;
                if (Length(temp) == 1)
                    temp = temp + ":\\*.*";
                else
                    temp = temp + "\\*.*";

                mysw.Write("LIST_FILES_");
                getAck();
                mysw.Write(temp);
                getAck();
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                {
                    //get list size
                    clearbuff(buff);
                    mysr.Read(buff, 0, 255);
                    temp = new String(buff);
                    sendAck();
                    int ListSize = Int32.Parse(temp);
                    string Pname;
                    listBox4.Items.Clear();
                    progressBar2.Maximum = ListSize;
                    progressBar2.Minimum = 0;
                    progressBar2.Step = 1;
                    progressBar2.Value = 0;

                    for (int i = 0; i < ListSize; i++)
                    {
                        clearbuff(buff);
                        Pname = mysr.ReadLine();  //get process name
                        sendAck();
                        listBox4.Items.Add(Pname);
                        progressBar2.Value = progressBar2.Value + progressBar2.Step;
                        this.Refresh();
                    }
                    progressBar2.Value = 0;
                }
                else
                {
                    label20.Text = "Failed to add new directory (possibly,Invalid path!)";
                    if (temprory2.CompareTo("") != 0)
                    {
                        textBox8.Text = temprory2;
                        temprory2 = "";
                    }
                }

            }
            catch (Exception)
            {
                BackToMain();
            }
        }

        private void backToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            BackToMain();
            listBox4.Items.Clear();
            //listBox4.Visible = false;
            groupBox4.Visible= false;
            textBox4.Text = "";
            label19.Text = "";
            label20.Text = "";
            textBox8.Text = "";
        }

        private void downloadFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            HideAll(tabControl1.SelectedTab.Text);

            groupBox5.Visible = true;

            radioButton1.Visible=false;
            radioButton2.Visible = false;

            textBox9.Visible = true;
            button34.Visible = true;
            textBox8.Visible = true;
            label19.Text = "Enter the full path of the file on remote computer";
            label21.Text = "Type the new file downloaded name";
            //listBox4.Visible = false;
            groupBox4.Visible = false;
            menuStrip2.Visible = true;

        }

        private void uploadFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            HideAll(tabControl1.SelectedTab.Text);
            textBox8.Text = "";
            button40.Visible = true;
            groupBox5.Visible = true;
            button35.Visible = true;
            textBox9.Visible = true;
            textBox8.Visible = true;
            label19.Text = "Type the file name to upload file must be in the current Folder with FTP.exe";
            label21.Text = "Type the full path for downloading on remote PC";
            //listBox4.Visible = false;
            groupBox4.Visible = false;
            menuStrip2.Visible = true;
            radioButton1.Visible = true;
            radioButton2.Visible = true;
        }

        private void deleteFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            HideAll(tabControl1.SelectedTab.Text);
            textBox8.Text = "";
            button36.Visible = true;
            textBox8.Visible = true;
            label19.Text = "Enter the full path (including the directory name to delete)";
//            listBox4.Visible = false;
            groupBox4.Visible = false;
            menuStrip2.Visible = true;
        }

        private void deleteDirectoryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            HideAll(tabControl1.SelectedTab.Text);
            textBox8.Text = "";
            button37.Visible = true;
            textBox8.Visible = true;
            label19.Text = "Enter the full path including the new directory name";
//            listBox4.Visible = false;
            groupBox4.Visible = false;
            menuStrip2.Visible = true;
        }

        private void createDirectoryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            HideAll(tabControl1.SelectedTab.Text);
            textBox8.Text = "";
            button38.Visible = true;
            textBox8.Visible = true;
            label19.Text = "Type the Directory name that want to Create at remote computer";
            //listBox4.Visible = false;
            groupBox4.Visible = false;
            menuStrip2.Visible = true;
        }

        private void listAllFilesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            listBox4.Items.Clear();
            textBox8.Text = "";
            HideAll(tabControl1.SelectedTab.Text);
            button39.Visible = true;
            textBox8.Visible = true;
            label19.Text = "Enter the Full Path (if it's a drive enter only the letter. ex:C)";
            //listBox4.Visible = true;
            groupBox4.Visible = true;
            label20.Text = "List of the files"; ;
            menuStrip2.Visible = true;
        }

        private void button40_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            string a=openFileDialog1.ToString();
            textBox8.Text= a.Substring(56);
        }

        private void listBox4_DoubleClick(object sender, EventArgs e)
        {
            label20.Text = "List of the files";
            temprory2 = "";
            string temp;
            object selected = listBox4.SelectedItem;
            temp = textBox8.Text;
            temprory2 = temp;
            if (selected.ToString().CompareTo("..") == 0)
            {
                temp = Split(temp);
                textBox8.Text = temp;
                button39_Click(sender, e);
                return;

            }
            
            temp = textBox8.Text;
            if (Length(temp) == 1)
                temp = temp + ":";

            if (temp[Length(temp) - 1].CompareTo('\\') != 0)
                temp = temp + "\\" + selected.ToString();
            else
                temp = temp + selected.ToString();
            textBox8.Text = temp;
            button39_Click(sender,e);
        }

        public string Split(string tempo)
        {
            for (int i = Length(tempo); i > 0; i--)
            {
                if (tempo[i - 1].CompareTo('\\') == 0)
                {
                    if (Length(tempo.Substring(0, i)) == 3)
                        return tempo.Substring(0, i);
                    else
                        return tempo.Substring(0, i-1);
                    
                }
            }
            return tempo;
        }

        private void button38_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox8.Text == "")
                    return;
                mysw.Write("NEW_DIR_");
                getAck();
                mysw.Write(textBox8.Text);
                getAck();
                sendAck();
                clearbuff(buff);
                mysr.Read(buff, 0, 8);
                string temp = new String(buff);
                sendAck();
                if (temp.CompareTo("SUCCESS_") == 0)
                    label20.Text = "New directory has successfully Been Added On Remote Computer!";
                else
                    label20.Text = "Failed to add new directory (possibly,Invalid path!)";
            }
            catch (Exception)
            {
                BackToMain();
            }
        }

bool DriveTypeString(string str)
{
           if (str.CompareTo("1") == 0)
            {
                temprory = "Not A Root Directory";
                return true;
            }
            else
                if (str.CompareTo("2") == 0)
                {
                    temprory = "Removable Drive (Floppy,Flash Card,...)";
                    return true;
                }
                else
                    if (str.CompareTo("3") == 0)
                    {
                        temprory = "Hard Drive";
                        return true;
                    }
                    else
                        if (str.CompareTo("4") == 0)
                        {
                            temprory = "Remote (Network) Drive";
                            return true;
                        }
                        else
                            if (str.CompareTo("5") == 0)
                            {
                                temprory = "CD-ROM Drive";
                                return true;
                            }
                            else
                                if (str.CompareTo("6") == 0)
                                {
                                    temprory = "RAM Drive";
                                    return true;
                                }
                                else
                                    return false;

            /*	
            0 DRIVE_UNKNOWN 	The drive type cannot be determined.
            1 DRIVE_NO_ROOT_DIR 	The root path is invalid; for example, there is no volume is mounted at the path.
            2 DRIVE_REMOVABLE 	The drive has removable media; for example, a floppy drive or flash card reader.
            3 DRIVE_FIXED 	The drive has fixed media; for example, a hard drive, flash drive, or thumb drive.
            4 DRIVE_REMOTE 	The drive is a remote (network) drive.
            5 DRIVE_CDROM 	The drive is a CD-ROM drive.
            6 DRIVE_RAMDISK 	The drive is a RAM disk.
        */
        }

        private void button41_Click(object sender, EventArgs e)
        {
            //string temp2;
            BackToMain();
            ShowFuncGlobal(button41.Text);
            clearbuff(buff);
            //sendAck();
            //getAck();
            mysr.Read(buff, 0, 8);
            String temp2 = new String(buff);
            sendAck();
            if (temp2.CompareTo("SUCCESS_") == 0)
                MessageBox.Show("Server was Killed");
            else
                MessageBox.Show("can't Kill Server");
            

        }

        private void button42_Click(object sender, EventArgs e)
        {

            try
            {
                if (textBox1.Text == "" || textBox1.Text == " ")
                {
                    MessageBox.Show("Please Type a Full Path");
                    return;
                }
                label8.Text = "Waiting for Executing file On Remote Computer!";
                this.Refresh();
                string temp;
                temp = textBox1.Text.ToString();
                mysw.Write("EXECUTE_FILE_");
                clearbuff(buff);
                getAck();
                mysw.Write(temp); //send file name
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                temp = textBox11.Text.ToString();
                if (temp.CompareTo("") == 0)
                    temp = "_NON_";
                mysw.Write(temp); //send parameters
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                if (hidden.Checked)
                    mysw.Write("0"); //hidden attribute
                else
                    mysw.Write("1"); //hidden attribute
                clearbuff(buff);
                getAck();
                clearbuff(buff);
                sendAck();
                mysr.Read(buff, 0, 8);
                String temp2 = new String(buff);
                sendAck();
                if (temp2.CompareTo("SUCCESS_") == 0)
                    label8.Text = "File was Execuited On Remote Computer!";
                else
                    label8.Text = "Could not Execite file on Remote Computer (Try Again!)";
            }
            catch (Exception)
            {
                MessageBox.Show("Cannot connect to server, and Could not Execite file on Remote Computer");
                BackToMain();
            }

        }
    }
}



