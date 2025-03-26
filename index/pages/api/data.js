import fs from 'fs';
import path from 'path';

const dataFile = path.resolve('./data.json');

export default function handler(req, res) {
  try {
    let latestData = { flow: 0, total: 0 };

    if (fs.existsSync(dataFile)) {
      const fileContent = fs.readFileSync(dataFile, 'utf8');
      latestData = JSON.parse(fileContent);
    }

    console.log('📤 Serving the latest data:', latestData);
    res.status(200).json(latestData);
  } catch (err) {
    console.error('❌ Error in GET:', err);
    res.status(500).json({ message: 'Internal server error' });
  }
}
