"use client"

import { useState, useEffect } from "react"
import { motion } from "framer-motion"
import { Droplet } from "lucide-react"

const FlowRateCard = () => {
  const [flowRate, setFlowRate] = useState("0.00")
  const [lastUpdated, setLastUpdated] = useState("")

  useEffect(() => {
    const fetchFlowRate = async () => {
      try {
        const res = await fetch("/api/data")
        const json = await res.json()
        const flow = parseFloat(json.flow)
        if (!isNaN(flow)) {
          setFlowRate(flow.toFixed(2))
        } else {
          setFlowRate("0.00")
        }
        setLastUpdated(new Date().toLocaleTimeString())
      } catch (err) {
        console.error("Error fetching flow rate:", err)
        setFlowRate("Err")
      }
    }

    fetchFlowRate()
    const interval = setInterval(fetchFlowRate, 1000)
    return () => clearInterval(interval)
  }, [])

  return (
    <div className="bg-gray-900 rounded-xl shadow-lg border border-blue-900/50 p-6 transition-all duration-300 hover:shadow-blue-500/10 hover:shadow-xl hover:-translate-y-2 hover:border-blue-800/70 h-full">
      <div className="flex flex-col h-full">
        <div className="flex items-center mb-4">
          <Droplet className="w-6 h-6 text-blue-400 mr-2" />
          <h3 className="text-xl font-bold text-white">Flow Rate</h3>
        </div>

        <div className="flex-1 flex flex-col items-center justify-center">
          <motion.div
            className="text-5xl font-bold bg-clip-text text-transparent bg-gradient-to-r from-blue-400 to-indigo-300 mb-2"
            key={flowRate}
            initial={{ scale: 0.8, opacity: 0 }}
            animate={{ scale: 1, opacity: 1 }}
            transition={{ type: "spring", stiffness: 300 }}
          >
            {flowRate}
          </motion.div>
          <p className="text-gray-400 text-lg">Litres/minute</p>
        </div>

        <div className="mt-4 pt-4 border-t border-blue-900/30">
          <p className="text-sm text-gray-500">Last updated: {lastUpdated}</p>
        </div>
      </div>
    </div>
  )
}

export default FlowRateCard
