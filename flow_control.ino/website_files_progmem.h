const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Login Page</title>
    <link rel="stylesheet" href="style.css" />
  </head>
  <body>
    <div class="login-container">
      <form class="login-form">
        <h2>Login</h2>
        <div class="form-group">
          <label for="email">Email</label>
          <input type="email" id="email" name="email" required />
        </div>
        <div class="form-group">
          <label for="password">Password</label>
          <input type="password" id="password" name="password" required />
        </div>
        <button type="submit">Login</button>
        <div class="form-footer">
          <a href="#">Forgot Password?</a>
          <p>Don't have an account? <a href="#">Sign Up</a></p>
        </div>
      </form>
    </div>
    <script src="script.js"></script>
  </body>
</html>

)rawliteral";

const char home_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Dashboard</title>
    <link rel="stylesheet" href="style.css" />
    <link
      rel="stylesheet"
      href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css"
    />
    <style>
      * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
        font-family: Arial, sans-serif;
      }

      nav {
        background: #1a73e8;
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

      .welcome-section {
        text-align: center;
        padding: 3rem;
      }

      .welcome-section h1 {
        color: rgb(142, 51, 202);
        margin-bottom: 1rem;
      }

      .logout-btn {
        background: white;
        color: rgb(112, 26, 232);
        border: none;
        padding: 0.5rem 1rem;
        border-radius: 4px;
        cursor: pointer;
      }

      .logout-btn:hover {
        background: #f1f1f1;
      }
    </style>
  </head>
  <body>
    <nav>
      <div class="nav-content">
        <h2>Fuel Flow Detector</h2>
        <button class="logout-btn" onclick="location.href='index.html'">
          Logout
        </button>
      </div>
    </nav>

    <main class="main-content">
      <div class="dashboard">
        <!-- Bluetooth Card -->
        <div class="flash-card bluetooth-card">
          <div class="bluetooth-content">
            <h3>Wi-fi Control</h3>
            <div class="bluetooth-toggle">
              <label class="switch">
                <input type="checkbox" id="bluetoothToggle" />
                <span class="slider round"></span>
              </label>
              <p id="bluetoothStatus">Bluetooth is ON</p>
            </div>
          </div>
        </div>

        <!-- Recent Fuel Card -->
        <div class="flash-card fuel-card">
          <div class="flash-card-inner">
            <div class="flash-card-front">
              <i class="card-icon fas fa-gas-pump"></i>
              <h3 class="card-title">Recent Fuel Up</h3>
            </div>
            <div class="flash-card-back">
              <div class="card-content">
                <p>Last Refuel: 23 Mar 2024</p>
                <p>Amount: ₹500</p>
                <p>Quantity: 5.2 L</p>
              </div>
            </div>
          </div>
        </div>

        <!-- Fuel Details Card -->
        <div class="flash-card details-card">
          <div class="flash-card-inner">
            <div class="flash-card-front">
              <i class="card-icon fas fa-chart-line"></i>
              <h3 class="card-title">Fuel Details</h3>
            </div>
            <div class="flash-card-back">
              <div class="card-content">
                <p>Average Mileage: 45 km/L</p>
                <p>Total Distance: 1250 km</p>
                <p>Fuel Efficiency: Good</p>
              </div>
            </div>
          </div>
        </div>

        <!-- User Details Card -->
        <div class="flash-card user-card">
          <div class="flash-card-inner">
            <div class="flash-card-front">
              <i class="card-icon fas fa-user"></i>
              <h3 class="card-title">User Details</h3>
            </div>
            <div class="flash-card-back">
              <div class="card-content">
                <p>Name: John Doe</p>
                <p>Vehicle Type: <span id="vehicleType">Two Wheeler</span></p>
                <p>Member Since: March 2024</p>
              </div>
            </div>
          </div>
        </div>
      </div>
    </main>
    <div class="fuel-flow-button-container">
      <button class="fuel-flow-btn" onclick="location.href='fuel-flow.html'">
        Fuel Flow
      </button>
    </div>
  </body>
</html>

)rawliteral";

const char fuel_flow_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Fuel Flow Monitor</title>
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
        justify-content: center;
        align-items: center;
      }

      .monitor-title {
        font-size: 3rem;
        color: #1a73e8;
        text-align: center;
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
    </div>
  </body>
</html>

)rawliteral";

const char style_css[] PROGMEM = R"rawliteral(
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
    font-family: Arial, sans-serif;
}

/* Modern Color Variables */
:root {
    --primary: #7209b7;
    --secondary: #3a0ca3;
    --accent: #f72585;
    --background: #10002b;
    --card-bg: #240046;
    --text-primary: #ffffff;
    --text-secondary: #e0aaff;
}

body {
    margin: 0;
    min-height: 100vh;
    background: var(--background);
    color: var(--text-primary);
    font-family: 'Poppins', sans-serif;
    background-size: 400% 400%;
    animation: gradientBG 15s ease infinite;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}

@keyframes gradientBG {
    0% {
        background-position: 0% 50%;
    }
    50% {
        background-position: 100% 50%;
    }
    100% {
        background-position: 0% 50%;
    }
}

.login-container {
    background: rgba(255, 255, 255, 0.9);
    backdrop-filter: blur(10px);
    border: 1px solid rgba(255, 255, 255, 0.2);
    padding: 2rem;
    border-radius: 8px;
    box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
    width: 100%;
    max-width: 400px;
}

.login-form h2 {
    text-align: center;
    background: linear-gradient(45deg, #000000, #4B0082, #FF69B4);
    -webkit-background-clip: text;
    background-clip: text;
    color: transparent;
    margin-bottom: 2rem;
    font-size: 2rem;
    font-weight: 600;
    padding: 10px;
}

.form-group {
    margin-bottom: 1.5rem;
}

.form-group label {
    display: block;
    margin-bottom: 0.5rem;
    color: #333;
}

.form-group input {
    width: 100%;
    padding: 0.8rem;
    border: 1px solid #ddd;
    border-radius: 4px;
    font-size: 1rem;
}

.form-group input:focus {
    outline: none;
    border-color: #1a73e8;
    box-shadow: 0 0 0 2px rgba(26, 115, 232, 0.2);
}

button[type="submit"] {
    width: 100%;
    padding: 0.8rem;
    background: #1a73e8;
    color: white;
    border: none;
    border-radius: 4px;
    font-size: 1rem;
    cursor: pointer;
    transition: background 0.3s ease;
}

button[type="submit"]:hover {
    background: #1557b0;
}

.form-footer {
    margin-top: 1.5rem;
    text-align: center;
}

.form-footer a {
    color: #1a73e8;
    text-decoration: none;
}

.form-footer a:hover {
    text-decoration: underline;
}

.form-footer p {
    margin-top: 1rem;
    color: #666;
}

.vehicle-popup {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0, 0, 0, 0.5);
    display: flex;
    justify-content: center;
    align-items: center;
    z-index: 1000;
}

.popup-content {
    background: white;
    padding: 2rem;
    border-radius: 8px;
    text-align: center;
    box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
}

.popup-content h3 {
    margin-bottom: 1.5rem;
    color: #1a73e8;
}

.popup-content button {
    margin: 0.5rem;
    padding: 0.8rem 1.5rem;
    background: #1a73e8;
    color: white;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: 1rem;
    transition: background 0.3s ease;
}

.popup-content button:hover {
    background: #1557b0;
}

.dashboard {
    display: grid;
    grid-template-columns: repeat(2, 1fr);
    gap: 30px;
    max-width: 1400px;
    width: 90%;
    padding: 100px 40px 40px;
    margin: 0 auto;
    perspective: 1000px;
}

.box {
    background: white;
    padding: 30px;
    border-radius: 15px;
    box-shadow: 0 10px 20px rgba(0, 0, 0, 0.05);
    transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
    min-height: 250px;
    position: relative;
    overflow: hidden;
}

.box:hover {
    transform: translateY(-10px);
    box-shadow: 0 15px 30px rgba(26, 115, 232, 0.15);
}

.box::before {
    content: '';
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    height: 4px;
    background: #1a73e8;
    transform: scaleX(0);
    transition: transform 0.3s ease;
}

.box:hover::before {
    transform: scaleX(1);
}

.box h3 {
    color: #1a73e8;
    font-size: 1.5rem;
    margin-bottom: 25px;
    font-weight: 600;
}

/* Bluetooth Toggle Switch */
.switch {
    position: relative;
    display: inline-block;
    width: 65px;
    height: 35px;
}

.switch input {
    opacity: 0;
    width: 0;
    height: 0;
}

.slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: var(--secondary);
    backdrop-filter: blur(5px);
    transition: .4s;
}

.slider:before {
    position: absolute;
    content: "";
    height: 26px;
    width: 26px;
    left: 4px;
    bottom: 4px;
    background-color: white;
    transition: .4s;
    box-shadow: 0 2px 5px rgba(0,0,0,0.2);
}

input:checked + .slider {
    background: var(--accent);
}

input:checked + .slider:before {
    transform: translateX(26px);
}

.slider.round {
    border-radius: 34px;
}

.slider.round:before {
    border-radius: 50%;
}

/* Box specific styles */
.bluetooth-box {
    text-align: center;
    background: linear-gradient(145deg, #ffffff, #f8f9ff);
}

.bluetooth-box #bluetoothStatus {
    margin-top: 100px;
    font-size: 1.1rem;
    color: #666;
    transition: all 0.3s ease;
}

.fuel-box {
    background: linear-gradient(145deg, #ffffff, #fff8f8);
}

.fuel-info p {
    padding: 8px 0;
    display: flex;
    justify-content: space-between;
    align-items: center;
    border-bottom: 1px solid #eee;
}

.details-box {
    background: linear-gradient(145deg, #ffffff, #f7fbff);
}

.details-info p {
    padding: 8px 0;
    display: flex;
    justify-content: space-between;
    align-items: center;
    border-bottom: 1px solid #eee;
}

.user-box {
    background: linear-gradient(145deg, #ffffff, #f5f8ff);
}

.user-info p {
    padding: 8px 0;
    display: flex;
    justify-content: space-between;
    align-items: center;
    border-bottom: 1px solid #eee;
}

span {
    color: #1a73e8;
    font-weight: 600;
    font-size: 1.1rem;
}

/* Content styling inside boxes */
.box-content {
    padding: 15px 0;
}

.box-content p {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 12px 0;
    border-bottom: 1px solid rgba(0, 0, 0, 0.05);
}

.box-content span {
    color: #1a73e8;
    font-weight: 500;
}

/* Flash Card specific styles */
.flash-card {
    background: var(--card-bg);
    border: 2px solid var(--primary);
    box-shadow: 0 8px 32px rgba(0, 0, 0, 0.3);
    backdrop-filter: blur(10px);
    border-radius: 20px;
    height: 200px;
    width: 600px;
    transition: all 0.4s cubic-bezier(0.4, 0, 0.2, 1);
    position: relative;
    overflow: hidden;
}

.flash-card:hover {
    border-color: var(--accent);
    transform: translateY(-10px) scale(1.02);
    box-shadow: 0 15px 45px rgba(0, 0, 0, 0.2);
}

.flash-card::before {
    content: '';
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background: linear-gradient(135deg, rgba(255,255,255,0.1), rgba(255,255,255,0));
    pointer-events: none;
}

.flash-card-inner {
    position: relative;
    width: 100%;
    height: 100%;
    transition: transform 0.6s;
    transform-style: preserve-3d;
}

.flash-card:hover .flash-card-inner {
    transform: rotateY(180deg);
}

.flash-card-front, .flash-card-back {
    position: absolute;
    width: 100%;
    height: 100%;
    backface-visibility: hidden;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}

.flash-card-back {
    transform: rotateY(180deg);
    background: #f8f9fa;
}

/* Card specific styles */
.bluetooth-card {
    background: var(--card-bg);
    border: 1px solid rgba(255, 255, 255, 0.2);
    transition: all 0.4s ease;
    display: flex;
    align-items: center;
    justify-content: center;
    text-align: center;
}

.bluetooth-content {
    width: 100%;
    padding: 20px;
}

.bluetooth-content h3 {
    color: #1a73e8;
    font-size: 1.8rem;
    margin-bottom: 30px;
}

.bluetooth-toggle {
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 20px;
}

.fuel-card {
    background: var(--card-bg);
    border: 1px solid rgba(255, 255, 255, 0.2);
    transition: all 0.4s ease;
}

.details-card {
    background: var(--card-bg);
    border: 1px solid rgba(255, 255, 255, 0.2);
    transition: all 0.4s ease;
}

.user-card {
    background: var(--card-bg);
    border: 1px solid rgba(255, 255, 255, 0.2);
    transition: all 0.4s ease;
}

.card-icon {
    font-size: 2.5rem;
    margin-bottom: 15px;
    color: #1a73e8;
}

.card-title {
    font-size: 1.8rem;
    font-weight: 600;
    color: var(--text-primary);
    background: none;
    -webkit-background-clip: unset;
    background-clip: unset;
    background-clip: unset;
    margin-bottom: 20px;
}

.card-content {
    padding: 15px;
    opacity: 0;
    transform: translateY(20px);
    animation: fadeInUp 0.5s forwards;
}

.card-content p {
    margin: 8px 0;
    color: var(--text-secondary);
}

#bluetoothStatus {
    font-size: 1.2rem;
    color: #333;
    transition: all 0.3s ease;
}

/* Responsive Design */
@media (max-width: 768px) {
    .dashboard {
        grid-template-columns: 1fr;
        padding: 80px 20px 20px;
        margin-top: 70px;
    }
    
    .box {
        min-height: 200px;
    }
    
    .flash-card {
        height: 250px;
        width: 100%;
    }
}

@media (max-width: 968px) {
    .flash-card {
        width: 100%;
        height: 180px;
    }
    
    .dashboard {
        grid-template-columns: 1fr;
        gap: 20px;
    }
}

@media (max-width: 1280px) {
    .flash-card {
        width: 100%;
        max-width: 600px;
    }
    
    .dashboard {
        grid-template-columns: 1fr;
        gap: 20px;
    }
}

/* Modern Navigation */
nav {
    position: fixed;
    top: 0;
    left: 0;
    right: 0;
    background: var(--card-bg);
    padding: 1.2rem;
    box-shadow: 0 4px 30px rgba(0, 0, 0, 0.3);
    text-align: center;
    z-index: 1000;
}

nav h2 {
    text-align: center;
    color: var(--text-primary);
    font-size: 2rem;
    font-weight: 700;
    letter-spacing: 2px;
    text-transform: uppercase;
    margin: 0;
    flex: 1;
    padding: 10px;
    animation: gradientText 3s ease infinite;
}

@keyframes gradientText {
    0% {
        background-position: 0% 50%;
    }
    50% {
        background-position: 100% 50%;
    }
    100% {
        background-position: 0% 50%;
    }
}

.nav-content {
    max-width: 1200px;
    margin: 0 auto;
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 0 20px;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 80px 20px 20px;
}

.fuel-flow-button-container {
    position: fixed;
    bottom: 30px;
    right: 50px;  /* Changed from left: 50% and removed transform */
    text-align: center;
}

/* Update Button Styles */
.fuel-flow-btn {
    background: var(--accent);
    font-weight: 600;
    text-transform: uppercase;
    letter-spacing: 1px;
    border: none;
    padding: 15px 40px;
    border-radius: 30px;
    font-size: 1.2rem;
    cursor: pointer;
    transition: all 0.3s ease;
    position: relative;
    overflow: hidden;
    box-shadow: 0 8px 25px rgba(0, 0, 0, 0.2);
}

.fuel-flow-btn:hover {
    background: var(--primary);
    transform: translateY(-3px);
    box-shadow: 0 12px 35px rgba(0, 0, 0, 0.3);
}

.fuel-flow-btn::before {
    content: '';
    position: absolute;
    top: 0;
    left: -100%;
    width: 100%;
    height: 100%;
    background: linear-gradient(90deg, transparent, rgba(255,255,255,0.2), transparent);
    transition: 0.5s;
}

.fuel-flow-btn:hover::before {
    left: 100%;
}

/* Add this in your HTML head */
@import url('https://fonts.googleapis.com/css2?family=Poppins:wght@400;500;600;700&display=swap');

/* Glassmorphism Effects */
.bluetooth-card, .fuel-card, .details-card, .user-card {
    background: var(--card-bg);
    backdrop-filter: none;
    border: 1px solid rgba(255, 255, 255, 0.2);
    transition: all 0.4s ease;
}

/* Modern Title Styles */
.card-title {
    font-size: 1.8rem;
    font-weight: 600;
    color: var(--text-primary);
    background: none;
    -webkit-background-clip: unset;
    margin-bottom: 20px;
}

/* Interactive Hover Effects */
.flash-card:hover .card-content {
    transform: scale(1.05);
}

@keyframes fadeInUp {
    from {
        opacity: 0;
        transform: translateY(20px);
    }
    to {
        opacity: 1;
        transform: translateY(0);
    }
}
)rawliteral";

const char script_js[] PROGMEM = R"rawliteral(
document.querySelector('.login-form').addEventListener('submit', function(e) {
    e.preventDefault();
    
    const email = document.getElementById('email').value;
    const password = document.getElementById('password').value;

    if (email && password) {
        // Create and show the popup
        const popup = document.createElement('div');
        popup.className = 'vehicle-popup';
        popup.innerHTML = `
            <div class="popup-content">
                <h3>Select Vehicle Type</h3>
                <button id="twoWheeler">Two Wheeler</button>
                <button id="fourWheeler">Four Wheeler</button>
            </div>
        `;
        document.body.appendChild(popup);

        // Add event listeners for the buttons
        document.getElementById('twoWheeler').addEventListener('click', () => {
            localStorage.setItem('vehicleType', 'two-wheeler');
            window.location.replace('home.html');
        });

        document.getElementById('fourWheeler').addEventListener('click', () => {
            localStorage.setItem('vehicleType', 'four-wheeler');
            window.location.replace('home.html');
        });
    }
});

document.addEventListener('DOMContentLoaded', function() {
    const bluetoothToggle = document.getElementById('bluetoothToggle');
    const bluetoothStatus = document.getElementById('bluetoothStatus');
    const vehicleTypeElement = document.getElementById('vehicleType');
    
    // Get vehicle type from localStorage
    const vehicleType = localStorage.getItem('vehicleType');
    if (vehicleTypeElement) {
        vehicleTypeElement.textContent = vehicleType || 'Not Selected';
    }

    bluetoothToggle.addEventListener('change', function() {
        if (this.checked) {
            bluetoothStatus.textContent = 'Bluetooth is ON';
            bluetoothStatus.style.color = '#1a73e8';
        } else {
            bluetoothStatus.textContent = 'Bluetooth is OFF';
            bluetoothStatus.style.color = '#333';
        }
    });
});
)rawliteral";
