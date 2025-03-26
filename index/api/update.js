// index/api/update.js

let latestData = { flow: 0, total: 0 };

export default function handler(req, res) {
  if (req.method === 'POST') {
    const { flow, total } = req.body;

    if (!isNaN(flow) && !isNaN(total)) {
      latestData = { flow, total };  // Store the latest data here
      console.log("✅ Received:", latestData);  // Log the received data
      return res.status(200).json({ message: "Stored successfully" });
    }

    return res.status(400).json({ message: "Invalid data" });
  }

  return res.status(405).json({ message: "Only POST allowed" });
  // index/api/update.js
  console.log('Received data:', { flow, total });  // Log received data

}

export { latestData };
