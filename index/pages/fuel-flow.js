import { useEffect, useState } from "react";
import { Card, CardContent } from "../components/ui/card";
import { Button } from "../components/ui/button";

export default function FuelDashboard() {
  const [data, setData] = useState({ flow: 0, total: 0 });
  const [error, setError] = useState(false);

  const fetchData = async () => {
    try {
      const res = await fetch("/api/data");
      const json = await res.json();
      setData({
        flow: json.flow ?? 0,
        total: json.total ?? 0,
      });
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
    <div className="min-h-screen bg-gradient-to-br from-black via-indigo-900 to-pink-600 text-white flex flex-col">
      <nav className="p-4 flex justify-between items-center max-w-6xl mx-auto w-full">
        <h1 className="text-3xl font-bold tracking-wide text-white">Fuel Flow Monitor</h1>
        <Button variant="outline" onClick={() => (window.location.href = "/home.html")}>
          Back to Dashboard
        </Button>
      </nav>

      <main className="flex-1 flex flex-col justify-center items-center text-center">
        <h2 className="text-5xl font-extrabold text-blue-400 mb-10">REAL-TIME FLOW</h2>
        <div className="grid grid-cols-1 sm:grid-cols-2 gap-8">
          <Card className="bg-white/10 backdrop-blur-md shadow-lg rounded-2xl p-6 w-72">
            <CardContent>
              <p className="text-gray-300 text-lg mb-2">Flow Rate</p>
              <p className="text-4xl font-bold text-blue-400">
                {error || data.flow == null ? "Error" : `${data.flow.toFixed(2)} L/min`}
              </p>
            </CardContent>
          </Card>

          <Card className="bg-white/10 backdrop-blur-md shadow-lg rounded-2xl p-6 w-72">
            <CardContent>
              <p className="text-gray-300 text-lg mb-2">Total Volume</p>
              <p className="text-4xl font-bold text-blue-400">
                {error || data.total == null ? "Error" : `${data.total.toFixed(2)} L`}
              </p>
            </CardContent>
          </Card>
        </div>
      </main>
    </div>
  );
}
