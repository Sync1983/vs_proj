namespace GRJ
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
      this.AboutPart = new System.Windows.Forms.Button();
      this.AboutStock = new System.Windows.Forms.Button();
      this.Shipment = new System.Windows.Forms.Button();
      this.Inventor = new System.Windows.Forms.Button();
      this.AddPart = new System.Windows.Forms.Button();
      this.btnPanel = new System.Windows.Forms.Panel();
      this.outputPanel = new System.Windows.Forms.Panel();
      this.InputCode = new System.Windows.Forms.Label();
      this.InputTextLabel = new System.Windows.Forms.Label();
      this.answerGrid = new System.Windows.Forms.DataGridView();
      this.Head = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.value = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.btnPanel.SuspendLayout();
      this.outputPanel.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.answerGrid)).BeginInit();
      this.SuspendLayout();
      // 
      // AboutPart
      // 
      this.AboutPart.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.AboutPart.AutoSize = true;
      this.AboutPart.BackColor = System.Drawing.Color.White;
      this.AboutPart.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
      this.AboutPart.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.AboutPart.Font = new System.Drawing.Font("Times New Roman", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.AboutPart.ForeColor = System.Drawing.Color.DarkGreen;
      this.AboutPart.Location = new System.Drawing.Point(0, 3);
      this.AboutPart.Name = "AboutPart";
      this.AboutPart.Size = new System.Drawing.Size(1745, 286);
      this.AboutPart.TabIndex = 0;
      this.AboutPart.Text = "Информация по детали";
      this.AboutPart.UseVisualStyleBackColor = false;
      // 
      // AboutStock
      // 
      this.AboutStock.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.AboutStock.AutoSize = true;
      this.AboutStock.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
      this.AboutStock.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.AboutStock.Font = new System.Drawing.Font("Times New Roman", 24F, System.Drawing.FontStyle.Bold);
      this.AboutStock.ForeColor = System.Drawing.Color.Green;
      this.AboutStock.Location = new System.Drawing.Point(0, 293);
      this.AboutStock.Name = "AboutStock";
      this.AboutStock.Size = new System.Drawing.Size(1745, 286);
      this.AboutStock.TabIndex = 1;
      this.AboutStock.Text = "Информация по месту хранения";
      this.AboutStock.UseVisualStyleBackColor = false;
      // 
      // Shipment
      // 
      this.Shipment.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.Shipment.AutoSize = true;
      this.Shipment.BackColor = System.Drawing.Color.Silver;
      this.Shipment.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.Shipment.Font = new System.Drawing.Font("Times New Roman", 24F, System.Drawing.FontStyle.Bold);
      this.Shipment.ForeColor = System.Drawing.Color.MidnightBlue;
      this.Shipment.Location = new System.Drawing.Point(0, 583);
      this.Shipment.Name = "Shipment";
      this.Shipment.Size = new System.Drawing.Size(1745, 286);
      this.Shipment.TabIndex = 2;
      this.Shipment.Text = "Отгрузка";
      this.Shipment.UseVisualStyleBackColor = false;
      // 
      // Inventor
      // 
      this.Inventor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
      this.Inventor.BackColor = System.Drawing.Color.Gray;
      this.Inventor.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
      this.Inventor.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.Inventor.Font = new System.Drawing.Font("Times New Roman", 24F, System.Drawing.FontStyle.Bold);
      this.Inventor.ForeColor = System.Drawing.Color.MediumBlue;
      this.Inventor.Location = new System.Drawing.Point(0, 919);
      this.Inventor.Name = "Inventor";
      this.Inventor.Size = new System.Drawing.Size(460, 144);
      this.Inventor.TabIndex = 3;
      this.Inventor.Text = "Инвентаризация";
      this.Inventor.UseVisualStyleBackColor = false;
      // 
      // AddPart
      // 
      this.AddPart.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.AddPart.BackColor = System.Drawing.Color.Gray;
      this.AddPart.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
      this.AddPart.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.AddPart.Font = new System.Drawing.Font("Times New Roman", 24F, System.Drawing.FontStyle.Bold);
      this.AddPart.ForeColor = System.Drawing.Color.MediumBlue;
      this.AddPart.Location = new System.Drawing.Point(490, 919);
      this.AddPart.Name = "AddPart";
      this.AddPart.Size = new System.Drawing.Size(518, 144);
      this.AddPart.TabIndex = 4;
      this.AddPart.Text = "Связать код";
      this.AddPart.UseVisualStyleBackColor = false;
      // 
      // btnPanel
      // 
      this.btnPanel.Controls.Add(this.AboutPart);
      this.btnPanel.Controls.Add(this.AddPart);
      this.btnPanel.Controls.Add(this.AboutStock);
      this.btnPanel.Controls.Add(this.Inventor);
      this.btnPanel.Controls.Add(this.Shipment);
      this.btnPanel.Dock = System.Windows.Forms.DockStyle.Fill;
      this.btnPanel.Enabled = false;
      this.btnPanel.Location = new System.Drawing.Point(0, 0);
      this.btnPanel.Name = "btnPanel";
      this.btnPanel.Size = new System.Drawing.Size(1008, 1066);
      this.btnPanel.TabIndex = 1;
      this.btnPanel.Visible = false;
      // 
      // outputPanel
      // 
      this.outputPanel.AllowDrop = true;
      this.outputPanel.AutoSize = true;
      this.outputPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
      this.outputPanel.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
      this.outputPanel.Controls.Add(this.answerGrid);
      this.outputPanel.Controls.Add(this.InputCode);
      this.outputPanel.Controls.Add(this.InputTextLabel);
      this.outputPanel.Dock = System.Windows.Forms.DockStyle.Fill;
      this.outputPanel.Location = new System.Drawing.Point(0, 0);
      this.outputPanel.Name = "outputPanel";
      this.outputPanel.Size = new System.Drawing.Size(1008, 1066);
      this.outputPanel.TabIndex = 5;
      // 
      // InputCode
      // 
      this.InputCode.Dock = System.Windows.Forms.DockStyle.Top;
      this.InputCode.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.InputCode.Font = new System.Drawing.Font("Tahoma", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.InputCode.ForeColor = System.Drawing.Color.LightGreen;
      this.InputCode.Location = new System.Drawing.Point(0, 40);
      this.InputCode.Name = "InputCode";
      this.InputCode.Size = new System.Drawing.Size(1008, 40);
      this.InputCode.TabIndex = 1;
      this.InputCode.Text = "__";
      this.InputCode.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      // 
      // InputTextLabel
      // 
      this.InputTextLabel.Dock = System.Windows.Forms.DockStyle.Top;
      this.InputTextLabel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.InputTextLabel.Font = new System.Drawing.Font("Tahoma", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.InputTextLabel.ForeColor = System.Drawing.Color.MidnightBlue;
      this.InputTextLabel.Location = new System.Drawing.Point(0, 0);
      this.InputTextLabel.Name = "InputTextLabel";
      this.InputTextLabel.Size = new System.Drawing.Size(1008, 40);
      this.InputTextLabel.TabIndex = 0;
      this.InputTextLabel.Text = "Введеный код";
      this.InputTextLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      // 
      // answerGrid
      // 
      this.answerGrid.AllowUserToAddRows = false;
      this.answerGrid.AllowUserToDeleteRows = false;
      this.answerGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.answerGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Head,
            this.value});
      this.answerGrid.Dock = System.Windows.Forms.DockStyle.Fill;
      this.answerGrid.GridColor = System.Drawing.SystemColors.Control;
      this.answerGrid.Location = new System.Drawing.Point(0, 80);
      this.answerGrid.Name = "answerGrid";
      this.answerGrid.ReadOnly = true;
      this.answerGrid.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.Single;
      this.answerGrid.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
      this.answerGrid.Size = new System.Drawing.Size(1008, 986);
      this.answerGrid.TabIndex = 3;
      // 
      // Head
      // 
      this.Head.HeaderText = "Заголовок";
      this.Head.Name = "Head";
      this.Head.ReadOnly = true;
      // 
      // value
      // 
      this.value.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
      this.value.HeaderText = "Значение";
      this.value.Name = "value";
      this.value.ReadOnly = true;
      this.value.Resizable = System.Windows.Forms.DataGridViewTriState.False;
      this.value.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.AutoScroll = true;
      this.AutoSize = true;
      this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
      this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(128)))), ((int)(((byte)(255)))));
      this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
      this.ClientSize = new System.Drawing.Size(1008, 1066);
      this.ControlBox = false;
      this.Controls.Add(this.outputPanel);
      this.Controls.Add(this.btnPanel);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.MaximumSize = new System.Drawing.Size(1024, 1280);
      this.Name = "MainForm";
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.TopMost = true;
      this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
      this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.MainForm_KeyPress);
      this.btnPanel.ResumeLayout(false);
      this.btnPanel.PerformLayout();
      this.outputPanel.ResumeLayout(false);
      ((System.ComponentModel.ISupportInitialize)(this.answerGrid)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

        }

        #endregion

        protected System.Windows.Forms.Button AboutPart;
        private System.Windows.Forms.Button AboutStock;
        private System.Windows.Forms.Button Shipment;
        private System.Windows.Forms.Button Inventor;
        private System.Windows.Forms.Button AddPart;
    private System.Windows.Forms.Panel btnPanel;
    private System.Windows.Forms.Label InputCode;
    private System.Windows.Forms.Label InputTextLabel;
    public System.Windows.Forms.Panel outputPanel;
    private System.Windows.Forms.DataGridView answerGrid;
    private System.Windows.Forms.DataGridViewTextBoxColumn Head;
    private System.Windows.Forms.DataGridViewTextBoxColumn value;
  }
}

