"use client"

import { useState, useEffect } from "react"
import { motion } from "framer-motion"
import { Fuel } from "lucide-react"

const TotalVolumeCard = () => {
  const [totalVolume, setTotalVolume] = useState("0.00")
  const [startDate] = useState(new Date().toLocaleDateString())

  useEffect(() => {
    const fetchTotalVolume = async () => {
      try {
        const res = await fetch("/api/data") // expects { flow, total }
        const json = await res.json()
        const total = parseFloat(json.total)
        if (!isNaN(total)) {
          setTotalVolume(total.toFixed(2))
        } else {
          setTotalVolume("0.00")
        }
      } catch (err) {
        console.error("Error fetching total volume:", err)
        setTotalVolume("Err")
      }
    }

    fetchTotalVolume()
    const interval = setInterval(fetchTotalVolume, 1000)
    return () => clearInterval(interval)
  }, [])

  return (
    <div className="bg-gray-900 rounded-xl shadow-lg border border-blue-900/50 p-6 transition-all duration-300 hover:shadow-blue-500/10 hover:shadow-xl hover:-translate-y-2 hover:border-blue-800/70 h-full">
      <div className="flex flex-col h-full">
        <div className="flex items-center mb-4">
          <Fuel className="w-6 h-6 text-blue-400 mr-2" />
          <h3 className="text-xl font-bold text-white">Total Volume</h3>
        </div>

        <div className="flex-1 flex flex-col items-center justify-center">
          <motion.div
            className="text-5xl font-bold bg-clip-text text-transparent bg-gradient-to-r from-blue-400 to-indigo-300 mb-2"
            key={totalVolume}
            initial={{ y: -20, opacity: 0 }}
            animate={{ y: 0, opacity: 1 }}
            transition={{ type: "spring", stiffness: 300 }}
          >
            {totalVolume}
          </motion.div>
          <p className="text-gray-400 text-lg">Litres</p>
        </div>

        <div className="mt-4 pt-4 border-t border-blue-900/30">
          <p className="text-sm text-gray-500">Session started: {startDate}</p>
        </div>
      </div>
    </div>
  )
}

export default TotalVolumeCard
