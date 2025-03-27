const char fuel_flow_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html lang="en">
    <head>
      <meta charset="UTF-8" />
      <meta name="viewport" content="width=device-width, initial-scale=1.0" />
      <title>Fuel Flow Monitor</title>
      <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.7.0/chart.min.js"></script>
      <style>
        * {
          margin: 0;
          padding: 0;
          box-sizing: border-box;
          font-family: Arial, sans-serif;
        }
  
        body {
          min-height: 100vh;
          background: linear-gradient(45deg, #000000, #4b0082, #ff69b4);
          display: flex;
          flex-direction: column;
        }       
  
        nav {
          padding: 1rem;
          color: white;
        }
  
        .nav-content {
          max-width: 1200px;
          margin: 0 auto;
          display: flex;
          justify-content: space-between;
          align-items: center;
        }
  
        .back-btn {
          background: white;
          color: #1a73e8;
          border: none;
          padding: 0.5rem 1rem;
          border-radius: 4px;
          cursor: pointer;
        }
  
        .main-content {
          flex: 1;
          display: flex;
          flex-direction: column;
          justify-content: center;
          align-items: center;
          padding: 20px;
        }
  
        .monitor-title {
          font-size: 2.5rem;
          color: white;
          text-align: center;
          margin-bottom: 20px;
          text-shadow: 0 0 10px rgba(255,255,255,0.5);
        }
  
        .data-container {
          background: rgba(255, 255, 255, 0.9);
          backdrop-filter: blur(10px);
          border-radius: 15px;
          padding: 20px;
          width: 90%;
          max-width: 800px;
          box-shadow: 0 8px 32px rgba(0, 0, 0, 0.3);
        }
  
        .data-row {
          display: flex;
          justify-content: space-between;
          margin-bottom: 15px;
          padding: 10px;
          border-bottom: 1px solid #eee;
        }
  
        .data-label {
          font-weight: bold;
          color: #4b0082;
        }
  
        .data-value {
          font-size: 1.2rem;
          font-weight: bold;
          color: #1a73e8;
        }
  
        #chart-container {
          width: 100%;
          height: 300px;
          margin-top: 20px;
        }
  
        .refresh-btn {
          background: #1a73e8;
          color: white;
          border: none;
          padding: 10px 20px;
          border-radius: 20px;
          margin-top: 20px;
          cursor: pointer;
          font-weight: bold;
          transition: all 0.3s ease;
        }
  
        .refresh-btn:hover {
          background: #1557b0;
          transform: translateY(-2px);
        }
  
        @media (max-width: 768px) {
          .monitor-title {
            font-size: 1.8rem;
          }
          
          .data-container {
            width: 95%;
          }
        }
      </style>
    </head>
    <body>
      <nav>
        <div class="nav-content">
          <h2>Fuel Flow Monitor</h2>
          <button class="back-btn" onclick="location.href='home.html'">
            Back to Dashboard
          </button>
        </div>
      </nav>
      <div class="main-content">
        <h1 class="monitor-title">FUEL FLOW MONITOR</h1>
        
        <div class="data-container">
          <div class="data-row">
            <span class="data-label">Current Flow Rate:</span>
            <span class="data-value" id="flow-rate">Loading...</span>
          </div>
          <div class="data-row">
            <span class="data-label">Total Fuel Used:</span>
            <span class="data-value" id="total-fuel">Loading...</span>
          </div>
          <div class="data-row">
            <span class="data-label">Last Updated:</span>
            <span class="data-value" id="last-updated">Loading...</span>
          </div>
          
          <div id="chart-container">
            <canvas id="flow-chart"></canvas>
          </div>
          
          <button class="refresh-btn" onclick="fetchFlowData()">Refresh Data</button>
        </div>
      </div>
  
      <script>
        // Chart setup
        let flowChart;
        const flowData = {
          labels: [],
          datasets: [{
            label: 'Flow Rate (L/min)',
            data: [],
            borderColor: '#7209b7',
            backgroundColor: 'rgba(114, 9, 183, 0.2)',
            tension: 0.4,
            fill: true
          }]
        };
        
        // Initialize the chart
        function initChart() {
          const ctx = document.getElementById('flow-chart').getContext('2d');
          flowChart = new Chart(ctx, {
            type: 'line',
            data: flowData,
            options: {
              responsive: true,
              maintainAspectRatio: false,
              scales: {
                y: {
                  beginAtZero: true,
                  title: {
                    display: true,
                    text: 'Flow Rate (L/min)'
                  }
                },
                x: {
                  title: {
                    display: true,
                    text: 'Time'
                  }
                }
              }
            }
          });
        }
        
        // Fetch flow data from API
        async function fetchFlowData() {
          try {
            const response = await fetch('/api/flow-data');
            if (!response.ok) {
              throw new Error('Network response was not ok');
            }
            const data = await response.json();
            
            // Update UI with latest data
            document.getElementById('flow-rate').textContent = data.flow.toFixed(2) + ' L/min';
            document.getElementById('total-fuel').textContent = data.total.toFixed(2) + ' L';
            document.getElementById('last-updated').textContent = new Date().toLocaleTimeString();
            
            // Update chart
            const now = new Date().toLocaleTimeString([], {hour: '2-digit', minute:'2-digit', second:'2-digit'});
            flowData.labels.push(now);
            flowData.datasets[0].data.push(data.flow);
            
            // Keep last 10 data points for clarity
            if (flowData.labels.length > 10) {
              flowData.labels.shift();
              flowData.datasets[0].data.shift();
            }
            
            flowChart.update();
          } catch (error) {
            console.error('Error fetching flow data:', error);
            document.getElementById('flow-rate').textContent = 'Error loading data';
            document.getElementById('total-fuel').textContent = 'Error loading data';
          }
        }
        
        // Initialize everything when page loads
        document.addEventListener('DOMContentLoaded', function() {
          initChart();
          fetchFlowData();
          
          // Auto refresh every 10 seconds
          setInterval(fetchFlowData, 10000);
        });
      </script>
    </body>
  </html>
  )rawliteral";