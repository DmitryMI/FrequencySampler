
namespace FrequencySamplerFloatCalculations
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
            this.MainPlotView = new OxyPlot.WindowsForms.PlotView();
            this.SuspendLayout();
            // 
            // MainPlotView
            // 
            this.MainPlotView.BackColor = System.Drawing.Color.White;
            this.MainPlotView.Location = new System.Drawing.Point(12, 12);
            this.MainPlotView.Name = "MainPlotView";
            this.MainPlotView.PanCursor = System.Windows.Forms.Cursors.Hand;
            this.MainPlotView.Size = new System.Drawing.Size(776, 426);
            this.MainPlotView.TabIndex = 0;
            this.MainPlotView.Text = "MainPlotView";
            this.MainPlotView.ZoomHorizontalCursor = System.Windows.Forms.Cursors.SizeWE;
            this.MainPlotView.ZoomRectangleCursor = System.Windows.Forms.Cursors.SizeNWSE;
            this.MainPlotView.ZoomVerticalCursor = System.Windows.Forms.Cursors.SizeNS;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.MainPlotView);
            this.Name = "MainForm";
            this.Text = "Main Form";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private OxyPlot.WindowsForms.PlotView MainPlotView;
    }
}

