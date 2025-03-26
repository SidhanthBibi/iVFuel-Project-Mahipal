// index/api/data.js
import { latestData } from './update.js';  // Import the latestData from update.js

export default function handler(req, res) {
  res.setHeader('Content-Type', 'application/json');
  res.status(200).json(latestData);  // Serve the latest stored data
}
