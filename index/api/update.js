// index/api/update.js

import latestData from './dataStore.js';

export default function handler(req, res) {
  if (req.method === 'POST') {
    const { flow, total } = req.body;

    if (!isNaN(flow) && !isNaN(total)) {
      latestData.flow = flow;
      latestData.total = total;
      console.log("✅ Received and updated data:", latestData);
      return res.status(200).json({ message: "Data updated successfully" });
    }

    return res.status(400).json({ message: "Invalid data" });
  }

  return res.status(405).json({ message: "Only POST allowed" });
}
