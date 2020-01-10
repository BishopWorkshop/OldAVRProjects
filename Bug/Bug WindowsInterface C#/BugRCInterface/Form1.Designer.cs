namespace BugRCInterface
{
    partial class MainForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.COMchek = new System.Windows.Forms.Button();
            this.LEFTdrivePower = new System.Windows.Forms.ProgressBar();
            this.label2 = new System.Windows.Forms.Label();
            this.RIGHTdrivePower = new System.Windows.Forms.ProgressBar();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.COMstat = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.PADchek = new System.Windows.Forms.Button();
            this.LEFTdriveSTAT = new System.Windows.Forms.Label();
            this.RIGHTdriveSTAT = new System.Windows.Forms.Label();
            this.PADstat = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.PortsBtn = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // COMchek
            // 
            this.COMchek.Location = new System.Drawing.Point(268, 6);
            this.COMchek.Name = "COMchek";
            this.COMchek.Size = new System.Drawing.Size(96, 21);
            this.COMchek.TabIndex = 0;
            this.COMchek.Text = "Проверить порт";
            this.COMchek.UseVisualStyleBackColor = true;
            this.COMchek.Click += new System.EventHandler(this.COMchek_Click);
            // 
            // LEFTdrivePower
            // 
            this.LEFTdrivePower.Location = new System.Drawing.Point(15, 121);
            this.LEFTdrivePower.Maximum = 3200;
            this.LEFTdrivePower.Name = "LEFTdrivePower";
            this.LEFTdrivePower.Size = new System.Drawing.Size(219, 41);
            this.LEFTdrivePower.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.LEFTdrivePower.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(26, 91);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Левый привод";
            // 
            // RIGHTdrivePower
            // 
            this.RIGHTdrivePower.Location = new System.Drawing.Point(268, 121);
            this.RIGHTdrivePower.Maximum = 3200;
            this.RIGHTdrivePower.Name = "RIGHTdrivePower";
            this.RIGHTdrivePower.Size = new System.Drawing.Size(219, 41);
            this.RIGHTdrivePower.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.RIGHTdrivePower.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(403, 91);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(86, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Правый привод";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(26, 49);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(113, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Состояния геймпада";
            // 
            // serialPort1
            // 
            this.serialPort1.PortName = "COM4";
            // 
            // COMstat
            // 
            this.COMstat.BackColor = System.Drawing.Color.Red;
            this.COMstat.Enabled = false;
            this.COMstat.ForeColor = System.Drawing.Color.White;
            this.COMstat.Location = new System.Drawing.Point(370, 6);
            this.COMstat.Name = "COMstat";
            this.COMstat.Size = new System.Drawing.Size(119, 21);
            this.COMstat.TabIndex = 8;
            this.COMstat.Text = "Порт не подключен";
            this.COMstat.UseVisualStyleBackColor = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(204, 179);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(94, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Работа приводов";
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // PADchek
            // 
            this.PADchek.Location = new System.Drawing.Point(192, 44);
            this.PADchek.Name = "PADchek";
            this.PADchek.Size = new System.Drawing.Size(118, 23);
            this.PADchek.TabIndex = 10;
            this.PADchek.Text = "Прверить геймпад";
            this.PADchek.UseVisualStyleBackColor = true;
            this.PADchek.Click += new System.EventHandler(this.PADcheck_Click);
            // 
            // LEFTdriveSTAT
            // 
            this.LEFTdriveSTAT.AutoSize = true;
            this.LEFTdriveSTAT.Location = new System.Drawing.Point(104, 179);
            this.LEFTdriveSTAT.Name = "LEFTdriveSTAT";
            this.LEFTdriveSTAT.Size = new System.Drawing.Size(37, 13);
            this.LEFTdriveSTAT.TabIndex = 11;
            this.LEFTdriveSTAT.Text = "СТОП";
            // 
            // RIGHTdriveSTAT
            // 
            this.RIGHTdriveSTAT.AutoSize = true;
            this.RIGHTdriveSTAT.Location = new System.Drawing.Point(367, 179);
            this.RIGHTdriveSTAT.Name = "RIGHTdriveSTAT";
            this.RIGHTdriveSTAT.Size = new System.Drawing.Size(37, 13);
            this.RIGHTdriveSTAT.TabIndex = 12;
            this.RIGHTdriveSTAT.Text = "СТОП";
            // 
            // PADstat
            // 
            this.PADstat.BackColor = System.Drawing.Color.Red;
            this.PADstat.Enabled = false;
            this.PADstat.ForeColor = System.Drawing.Color.White;
            this.PADstat.Location = new System.Drawing.Point(370, 44);
            this.PADstat.Name = "PADstat";
            this.PADstat.Size = new System.Drawing.Size(119, 21);
            this.PADstat.TabIndex = 13;
            this.PADstat.Text = "Геймпад отключен";
            this.PADstat.UseVisualStyleBackColor = false;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(132, 6);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 21);
            this.comboBox1.TabIndex = 14;
            // 
            // PortsBtn
            // 
            this.PortsBtn.Location = new System.Drawing.Point(15, 6);
            this.PortsBtn.Name = "PortsBtn";
            this.PortsBtn.Size = new System.Drawing.Size(111, 21);
            this.PortsBtn.TabIndex = 15;
            this.PortsBtn.Text = "Доступные порты";
            this.PortsBtn.UseVisualStyleBackColor = true;
            this.PortsBtn.Click += new System.EventHandler(this.PortsBtn_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 40;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(192, 81);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(118, 23);
            this.button1.TabIndex = 16;
            this.button1.Text = "Включить приводы";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ClientSize = new System.Drawing.Size(518, 206);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.PortsBtn);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.PADstat);
            this.Controls.Add(this.RIGHTdriveSTAT);
            this.Controls.Add(this.LEFTdriveSTAT);
            this.Controls.Add(this.PADchek);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.COMstat);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.RIGHTdrivePower);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.LEFTdrivePower);
            this.Controls.Add(this.COMchek);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.Text = "Вундер девайс контрол";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button COMchek;
        private System.Windows.Forms.ProgressBar LEFTdrivePower;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ProgressBar RIGHTdrivePower;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button COMstat;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button PADchek;
        private System.Windows.Forms.Label LEFTdriveSTAT;
        private System.Windows.Forms.Label RIGHTdriveSTAT;
        private System.Windows.Forms.Button PADstat;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button PortsBtn;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button button1;
    }
}

