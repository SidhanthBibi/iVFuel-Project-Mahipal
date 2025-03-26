// index/api/update.js

let latestData = { flow: 0, total: 0 };

export default function handler(req, res) {
  if (req.method === 'POST') {
    const { flow, total } = req.body;

    if (!isNaN(flow) && !isNaN(total)) {
      latestData = { flow, total };
      console.log("✅ Received:", latestData);
      return res.status(200).json({ message: "Stored successfully" });
    }

    return res.status(400).json({ message: "Invalid data" });
  }

  return res.status(405).json({ message: "Only POST allowed" });
}

export { latestData };
