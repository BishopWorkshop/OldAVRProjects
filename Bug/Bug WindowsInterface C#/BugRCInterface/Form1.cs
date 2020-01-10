using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using Microsoft.DirectX;


using Microsoft.DirectX.DirectInput;


namespace BugRCInterface
{
    public partial class MainForm : Form
    {

        public string[] ports ;// Список всех COM портов компьютера
        private Boolean portIsenable;//Флаг подключения  COM - порта
        Device GamePad;//Геймпад XBOX
      
        

        

        public bool PortIsenable
        {
            get
            {
                return portIsenable;
            }

            set
            {
                portIsenable = value;
            }
        }

        public MainForm()
        {
            
            InitializeComponent();

            
         }

        private void label5_Click(object sender, EventArgs e)
        {
           

        }

        private void MainForm_Load(object sender, EventArgs e)
        {
             
           

        }

        private void PortsBtn_Click(object sender, EventArgs e)
        {
            ports = SerialPort.GetPortNames();//Запрост всех открытых COM портов компьютера
            comboBox1.Items.Clear();//Сброс списка COM портов
            PortIsenable = false;//Сброс флага 
            foreach (string port in ports)
            {
                comboBox1.Items.Add(port);//выводим все найденные COM порты в выпбадающий список
            }
            


        }



        private void COMchek_Click(object sender, EventArgs e)
        {
            serialPort1.PortName = comboBox1.SelectedItem.ToString();// Подключаемся к выбранному COM порту

            try
            {
                // настройки порта

                serialPort1.BaudRate = 9600;
                serialPort1.DataBits = 8;
                serialPort1.Parity = System.IO.Ports.Parity.None;
                serialPort1.StopBits = System.IO.Ports.StopBits.One;
                serialPort1.ReadTimeout = 1000;
                serialPort1.WriteTimeout = 1000;
                serialPort1.Open();
            }
            catch (Exception exep)
            {
                Console.WriteLine("ERROR: невозможно открыть порт:" + exep.ToString());
                return;
            }

            


            
                serialPort1.Write(new Byte[] { 1 }, 0, 1);
                System.Threading.Thread.Sleep(20);
            
            
            


            if(true)
            {
                COMstat.BackColor = Color.Green;
                COMstat.Text = "Порт подключен";
                PortIsenable = true;

                serialPort1.Close();
            }
            else
            {
                COMstat.BackColor = Color.Red;
                COMstat.Text ="Ошибка порта";

            }
           

            





        }

        private void PADcheck_Click(object sender, EventArgs e)
        {
            //ЗАПОМНИ Изменить файл App.Config добавив startup useLegacyV2RuntimeActivationPolicy="true"
            //


            //Поиск всех геймпадов на компьютере 

            DeviceList Js = Microsoft.DirectX.DirectInput.Manager.GetDevices(DeviceClass.GameControl, EnumDevicesFlags.AttachedOnly);
            if(Js.Count>0)
            {

                foreach (DeviceInstance instance in Manager.GetDevices(DeviceClass.GameControl, EnumDevicesFlags.AttachedOnly))
                {
                    //По скольку геймпад в системе один, то сразу подключаемся к нему
                    GamePad = new Device(instance.ProductGuid);
                    // Background - флаг, говорит о том, что данные от руля будут поступать даже в неактивное окно
                    // NonExclusive - говорит о том, что игровой контроллер могут использовать и другие приложения
                    GamePad.SetCooperativeLevel(null, CooperativeLevelFlags.Background | CooperativeLevelFlags.NonExclusive);
                    foreach (DeviceObjectInstance doi in GamePad.Objects)
                    {
                        // Проверяем есть ли на устройстве стики
                        if ((doi.ObjectId & (int)DeviceObjectTypeFlags.Axis) != 0)
                        {
                            // Задаем минимальное и максимальное значение наклона стика
                            GamePad.Properties.SetRange(
                                       ParameterHow.ById,
                                       doi.ObjectId,
                                       new InputRange(-3200, 3200));
                        }
                    }

                    // Применяем настройки
                    GamePad.Acquire();


                }








                PADstat.BackColor = Color.Green;//сообщаем пользователю что всё подключено 
                    PADstat.Text = "Геймпад подключен";

                              

            }
            else
            {
                PADstat.BackColor = Color.Red;
                PADstat.Text = "Ошибка геймпада";

            }



        }

        

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //Таймер основного цикла управления, срабатывает каждых 100мс


            JoystickState j = GamePad.CurrentJoystickState; //запрашиваем у геймпада состояние

            
            
            LEFTdrivePower.Value = Math.Abs(j.Y); //Определяем абсолютную величину наклона стика
            
            RIGHTdrivePower.Value = Math.Abs(j.Ry);

            if((j.Y < 0)&&(LEFTdrivePower.Value>200))
                            LEFTdriveSTAT.Text = "ХОД";
            else if ((j.Y > 0) && (LEFTdrivePower.Value > 200))
                LEFTdriveSTAT.Text = "РЕВЕРС";
            else LEFTdriveSTAT.Text = "СТОП";

            if ((j.Ry < 0) && (RIGHTdrivePower.Value > 200))
                RIGHTdriveSTAT.Text = "ХОД";
            else if ((j.Ry > 0) && (RIGHTdrivePower.Value > 200))
                RIGHTdriveSTAT.Text = "РЕВЕРС";
            else RIGHTdriveSTAT.Text = "СТОП";

            COMtransmitDriveParameters(j.Y, j.Ry);//Передаём методу управления значения наклонов стиков



        }

        private void COMtransmitDriveParameters(Int32 L, Int32 R)//метод вычисляющий и передающий кадр команды управления 
        {
            bool directionR = false;//переменные наличия реверса
            bool directionL = false;

            if (R > 0)
                directionR = true;//проверяем есть ли реверс

            if (L > 0)
                directionL = true;

            R = Math.Abs(R);
            L = Math.Abs(L);

            if (R < 200)//убираем дребезг стиков около нулегвого положения
                R = 0;
            else
                R -= 200;

            if (L < 200)
                L = 0;
            else
                L -= 200;

            int  ComParamR = Convert.ToByte(R/405);//Делим параметр наклона чтобы он вписывался в 3 бита
            int ComParamL = Convert.ToByte(L / 405);

            if (directionR)// если есть реверс то добавляем один бит (8 = 0b1000)
                ComParamR= Convert.ToByte(ComParamR + 8);
            if (directionL)
                ComParamL=Convert.ToByte(ComParamL + 8);


            ComParamL = Convert.ToByte(ComParamL << 4);

            Byte[] transmit = new Byte[] { Convert.ToByte(ComParamL+ ComParamR) };//Convert.ToByte(((ComParamL << 4) + ComParamR))


            serialPort1.Write(transmit,0,1);

            
            
            //Формируем кадр команды управления сдвинув параметр левого  двигателя и добавив параметр левого
            //и кидаем всё в COM порт




        }

        private void portError()
        {
            COMstat.BackColor = Color.Red;
            COMstat.Text = "Ошибка передатчика";
        }
        private void portCorrect()
        {
            PADstat.BackColor = Color.Green;
            PADstat.Text = "Порт подключен";
        }



        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Open();//Открываем порт
            timer1.Enabled = true;//Запускаем таймер цикла управления 

        }
    }
}
