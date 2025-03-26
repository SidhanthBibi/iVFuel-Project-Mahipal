// index/api/data.js
import { latestData } from './update.js';  // Import the latest data from update.js

export default function handler(req, res) {
  // Log the data that's being served
  console.log("Serving the latest data:", latestData);

  res.setHeader('Content-Type', 'application/json'); // Set the correct content type
  res.status(200).json(latestData);  // Serve the latest data
}
