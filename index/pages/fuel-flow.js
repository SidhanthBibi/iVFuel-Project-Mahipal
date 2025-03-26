import { useEffect, useState } from "react";

export default function FuelFlow() {
  const [data, setData] = useState({ flow: 0, total: 0 });
  const [error, setError] = useState(false);

  const fetchData = async () => {
    try {
      const res = await fetch("/api/data");
      const json = await res.json();
      setData(json);
      setError(false);
    } catch (err) {
      console.error("❌ Error fetching data:", err);
      setError(true);
    }
  };

  useEffect(() => {
    fetchData();
    const interval = setInterval(fetchData, 1000);
    return () => clearInterval(interval);
  }, []);

  return (
    <div className="min-h-screen bg-gradient-to-br from-black via-indigo-900 to-pink-600 text-white flex flex-col items-center justify-center px-6">
      <nav className="w-full max-w-6xl flex justify-between items-center py-6">
        <h1 className="text-4xl font-bold text-white tracking-widest drop-shadow-md">
          Fuel Flow Monitor
        </h1>
        <button
          onClick={() => (window.location.href = "/")}
          className="bg-white text-indigo-700 font-semibold px-4 py-2 rounded-lg shadow hover:bg-indigo-200 transition"
        >
          ⬅ Back to Dashboard
        </button>
      </nav>

      <main className="flex-1 w-full max-w-4xl flex flex-col items-center justify-center">
        <h2 className="text-5xl font-extrabold text-blue-400 mb-12 animate-pulse">
          Real-Time Flow 💧
        </h2>

        <div className="grid grid-cols-1 sm:grid-cols-2 gap-10 w-full px-4">
          <div className="bg-white/10 backdrop-blur-md rounded-2xl shadow-lg p-8 text-center">
            <p className="text-lg text-gray-300 mb-2">Flow Rate</p>
            <p className="text-5xl font-bold text-blue-400">
              {error ? "Error" : `${data.flow.toFixed(2)} L/min`}
            </p>
          </div>

          <div className="bg-white/10 backdrop-blur-md rounded-2xl shadow-lg p-8 text-center">
            <p className="text-lg text-gray-300 mb-2">Total Volume</p>
            <p className="text-5xl font-bold text-blue-400">
              {error ? "Error" : `${data.total.toFixed(2)} L`}
            </p>
          </div>
        </div>
      </main>

      <footer className="text-xs text-white/40 mt-10">
        Built by Mahipal ✨
      </footer>
    </div>
  );
}
