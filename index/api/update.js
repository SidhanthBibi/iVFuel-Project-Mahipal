// index/api/update.js

let latestData = { flow: 0, total: 0 }; // initial state

export default function handler(req, res) {
  if (req.method === 'POST') {
    const { flow, total } = req.body;

    if (!isNaN(flow) && !isNaN(total)) {
      // Update the latestData object instead of reinitializing it
      latestData = { flow, total };
      console.log("✅ Received:", latestData); // Log to ensure correct data is received
      return res.status(200).json({ message: "Stored successfully" });
    }

    return res.status(400).json({ message: "Invalid data" });
  }

  return res.status(405).json({ message: "Only POST allowed" });
}

export { latestData };
