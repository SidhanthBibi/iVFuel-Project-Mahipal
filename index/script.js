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