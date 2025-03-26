import fs from 'fs';
import path from 'path';

const dataFile = path.resolve('./data.json');

export default function handler(req, res) {
  if (req.method === 'POST') {
    try {
      const { flow, total } = req.body;

      if (!isNaN(flow) && !isNaN(total)) {
        const latestData = { flow, total };
        fs.writeFileSync(dataFile, JSON.stringify(latestData));
        console.log('✅ Received and saved data:', latestData);
        return res.status(200).json({ message: 'Stored successfully' });
      }

      return res.status(400).json({ message: 'Invalid data' });
    } catch (err) {
      console.error('❌ Error in POST:', err);
      return res.status(500).json({ message: 'Internal server error' });
    }
  } else {
    res.status(405).json({ message: 'Only POST allowed' });
  }
}
