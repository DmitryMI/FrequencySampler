using System.Windows.Forms;

using uint8_t = System.Byte;
using uint16_t = System.UInt16;
using uint32_t = System.UInt32;
using real_t = System.Single;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;
using System.Diagnostics;

namespace FrequencySamplerFloatCalculations
{
    public partial class MainForm : Form
    {
		private const int F_CPU = 1000000;
		private const uint8_t TIMER_USED_PRESCALER = 128;
		private const uint16_t RESISTOR_VALUE = 2700;
		private const int RHEOSTAT_MAX_VALUE = 50000;

        private LineSeries _floatSeries;
        private LineSeries _intSeries;

        uint8_t get_resistance_float(uint16_t timer1_time)
		{
			const real_t a = (real_t)0.01146;
			const real_t b = (real_t)29.70;
			real_t delay_time = (real_t)timer1_time / (F_CPU / TIMER_USED_PRESCALER);
			real_t resistance = (((real_t)delay_time * 1000 - b) / a - RESISTOR_VALUE);
            //Debug.WriteLine($"Float:\t {resistance}");
            if (resistance < 0)
			{
				return 0;
			}
			if (resistance >= RHEOSTAT_MAX_VALUE)
			{
				return 0xFF;
			}
			uint8_t rheostat_coefficient = (uint8_t)(resistance / RHEOSTAT_MAX_VALUE * 255);
			return rheostat_coefficient;
		}

        uint8_t get_resistance(uint16_t timer1_time)
        {
            const real_t a = (real_t)0.01146;
            const uint16_t invA = (uint16_t)(1.0f / a); //~87
            const real_t b = (real_t)29.70;
            const uint16_t bDivA = (uint16_t)(b / a);

            if (timer1_time < 476)
            {
                return 0;
            }
            if (timer1_time > 6359)
            {
                return 0xFF;
            }

            uint32_t timeSecInvA = (uint32_t)1000UL * timer1_time * invA;
            uint32_t freqDivResult = timeSecInvA / (F_CPU / TIMER_USED_PRESCALER);
            uint16_t resistance = (uint16_t)(freqDivResult - bDivA - RESISTOR_VALUE);
            //uint16_t resistance = (uint16_t)(1000 * timer1_time * invA / (F_CPU / TIMER_USED_PRESCALER) - bDivA - RESISTOR_VALUE);

            if (resistance >= RHEOSTAT_MAX_VALUE)
            {
                return 0xFF;
            }

            uint32_t resistanceUpper = (uint32_t)255 * resistance;

            uint8_t rheostat_coefficient = (uint8_t)(resistanceUpper / RHEOSTAT_MAX_VALUE);
            return rheostat_coefficient;
        }

        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, System.EventArgs e)
        {
            var model = new PlotModel() { Title = "Functions comparison", LegendSymbolLength = 24 };
            var yAxis = new LinearAxis()
            {
                Position = AxisPosition.Left,
                Title = "Return value"
            };
            var xAxis = new LinearAxis()
            {
                Position = AxisPosition.Bottom,
                Title = "Input value"
            };
            model.Axes.Add(yAxis);
            model.Axes.Add(xAxis);
            _floatSeries = new LineSeries()
            {
                Color = OxyColors.Green,
                MarkerType = MarkerType.None,
                MarkerSize = 0,
                MarkerStroke = OxyColors.DarkGreen,
                MarkerFill = OxyColors.Green,
                MarkerStrokeThickness = 1.5
            };

            _intSeries = new LineSeries()
            {
                Color = OxyColors.Red,
                MarkerType = MarkerType.None,
                MarkerSize = 0,
                MarkerStroke = OxyColors.DarkRed,
                MarkerFill = OxyColors.Red,
                MarkerStrokeThickness = 1.5
            };

            model.Series.Add(_floatSeries);
            model.Series.Add(_intSeries);
            MainPlotView.Model = model;

            StartFunctionsComparison();
        }

		private void StartFunctionsComparison()
        {
			int maxValue = ushort.MaxValue;
			for(int i = 0; i < maxValue; i++)
            {
				uint8_t resultFloat = get_resistance_float((uint16_t)i);
                _floatSeries.Points.Add(new DataPoint(i, resultFloat));

                uint8_t resultInt = get_resistance((uint16_t)i);
                _intSeries.Points.Add(new DataPoint(i, resultInt));
            }

            MainPlotView.Invalidate();
        }
    }
}
