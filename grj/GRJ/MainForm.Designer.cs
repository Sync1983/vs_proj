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
      this.outTable = new System.Windows.Forms.TableLayoutPanel();
      this.SuspendLayout();
      // 
      // outTable
      // 
      this.outTable.AutoScroll = true;
      this.outTable.ColumnCount = 1;
      this.outTable.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
      this.outTable.Dock = System.Windows.Forms.DockStyle.Fill;
      this.outTable.Location = new System.Drawing.Point(0, 0);
      this.outTable.Name = "outTable";
      this.outTable.RowCount = 1;
      this.outTable.RowStyles.Add(new System.Windows.Forms.RowStyle());
      this.outTable.Size = new System.Drawing.Size(1008, 1066);
      this.outTable.TabIndex = 0;
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
      this.Controls.Add(this.outTable);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.MaximumSize = new System.Drawing.Size(1024, 1280);
      this.Name = "MainForm";
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "Склад";
      this.TopMost = true;
      this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
      this.Deactivate += new System.EventHandler(this.MainForm_Deactivate);
      this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.MainForm_KeyPress);
      this.ResumeLayout(false);

        }

    #endregion

    private System.Windows.Forms.TableLayoutPanel outTable;
  }
}

