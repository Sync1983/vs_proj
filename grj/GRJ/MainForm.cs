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
    protected string kbdText, inText;
    protected Server server;

    public MainForm() {
      InitializeComponent();
      server = new Server( );
    }

    private void MainForm_KeyPress( object sender, KeyPressEventArgs e ) {
      if( e.KeyChar != 13 ) {
        kbdText += e.KeyChar.ToString( );
        inText = "";
      } else {
        inText = kbdText;
        kbdText = "";
      }      
    }

    private void MainForm_FormClosing( object sender, FormClosingEventArgs e ) {
      server.Close();      
    }

    private void MainForm_Deactivate( object sender, EventArgs e ) {
      this.Focus( );
    }
  }
}
