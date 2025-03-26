import fs from 'fs';
const filePath = '/tmp/latestData.json';

export default async function handler(req, res) {
  res.setHeader('Content-Type', 'application/json');
  res.setHeader('Access-Control-Allow-Origin', '*');

  let latestData = { flow: 0, total: 0 };

  try {
    if (fs.existsSync(filePath)) {
      const data = fs.readFileSync(filePath, 'utf-8');
      latestData = JSON.parse(data);
    }
  } catch (error) {
    console.error("❌ Error reading data:", error);
  }

  console.log("📤 Serving latest data:", latestData);
  res.status(200).json(latestData);
}
