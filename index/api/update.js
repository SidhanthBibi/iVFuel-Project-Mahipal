import fs from 'fs';
const filePath = '/tmp/latestData.json';

export default async function handler(req, res) {
  if (req.method === 'POST') {
    const { flow, total } = req.body;

    if (!isNaN(flow) && !isNaN(total)) {
      const latestData = { flow, total };
      fs.writeFileSync(filePath, JSON.stringify(latestData));
      console.log("✅ Received and saved:", latestData);
      return res.status(200).json({ message: "Stored successfully" });
    }

    return res.status(400).json({ message: "Invalid data" });
  }

  return res.status(405).json({ message: "Only POST allowed" });
}
