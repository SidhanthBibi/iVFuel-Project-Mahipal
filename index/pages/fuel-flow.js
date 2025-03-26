export default function FuelFlow() {
    return (
      <div style={{ minHeight: '100vh', background: 'linear-gradient(45deg, #000000, #4b0082, #ff69b4)', color: 'white', fontFamily: 'Arial, sans-serif' }}>
        <nav style={{ padding: '1rem' }}>
          <div style={{ maxWidth: '1200px', margin: '0 auto', display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
            <h2>Fuel Flow Monitor</h2>
            <button onClick={() => window.location.href = '/'} style={{ background: 'white', color: '#1a73e8', padding: '0.5rem 1rem', borderRadius: '4px', border: 'none', cursor: 'pointer' }}>
              Back to Dashboard
            </button>
          </div>
        </nav>
  
        <main style={{ flex: 1, display: 'flex', flexDirection: 'column', justifyContent: 'center', alignItems: 'center', padding: '2rem' }}>
          <h1 style={{ fontSize: '3rem', marginBottom: '2rem', color: '#1a73e8' }}>FUEL FLOW MONITOR</h1>
  
          <div style={{ display: 'flex', gap: '2rem' }}>
            <div style={{ background: 'rgba(255, 255, 255, 0.1)', borderRadius: '10px', padding: '1.5rem', minWidth: '250px', backdropFilter: 'blur(10px)' }}>
              <div style={{ fontSize: '1.2rem', color: '#94a3b8' }}>Flow Rate</div>
              <div style={{ fontSize: '2.5rem', fontWeight: 'bold', color: '#1a73e8' }} id="flow-rate">-- L/min</div>
            </div>
            <div style={{ background: 'rgba(255, 255, 255, 0.1)', borderRadius: '10px', padding: '1.5rem', minWidth: '250px', backdropFilter: 'blur(10px)' }}>
              <div style={{ fontSize: '1.2rem', color: '#94a3b8' }}>Total Volume</div>
              <div style={{ fontSize: '2.5rem', fontWeight: 'bold', color: '#1a73e8' }} id="total-volume">-- L</div>
            </div>
          </div>
        </main>
  
        <script dangerouslySetInnerHTML={{
          __html: `
            function fetchData() {
              fetch('/api/data')
                .then(res => res.json())
                .then(data => {
                  document.getElementById('flow-rate').textContent = data.flow.toFixed(2) + ' L/min';
                  document.getElementById('total-volume').textContent = data.total.toFixed(2) + ' L';
                })
                .catch(err => {
                  console.error('❌ Error:', err);
                  document.getElementById('flow-rate').textContent = 'Error';
                  document.getElementById('total-volume').textContent = 'Error';
                });
            }
            setInterval(fetchData, 200);
            window.onload = fetchData;
          `
        }} />
      </div>
    );
  }
  