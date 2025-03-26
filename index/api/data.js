// index/api/data.js
import { latestData } from './update.js';  // Import the latest data from update.js

export default function handler(req, res) {
  console.log("Serving the latest data:", latestData);  // Log the latest data being served
  res.setHeader('Content-Type', 'application/json');
  res.status(200).json(latestData);  // Serve the latest stored data
}
