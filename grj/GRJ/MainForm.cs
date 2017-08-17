using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GRJ {
    public partial class MainForm : Form {
    protected string kbdText;

    public MainForm() {
      InitializeComponent();
      btnPanel.Hide( );
      outputPanel.Show( );
      string[] r = { "a", "b" };
      answerGrid.Rows.Add(r );
    }

    private void MainForm_KeyPress( object sender, KeyPressEventArgs e ) {
      if( e.KeyChar != 13 ) {
        kbdText += e.KeyChar.ToString( );
      } else {
        InputCode.Text = kbdText;
        kbdText = "";
      }      
    }
  }
}
