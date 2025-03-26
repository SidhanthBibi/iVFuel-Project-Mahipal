// index/api/data.js
import { latestData } from './update.js'; // Import the latest data from update.js

export default function handler(req, res) {
  console.log("Serving data:", latestData); // Log the data being served to ensure it's the latest data
  res.setHeader('Content-Type', 'application/json');
  res.status(200).json(latestData);  // Serve the latest stored data
}
// In this snippet, the latestData object is imported from the update.js file and served as a response to the client. This ensures that the latest data is always served to the client without reinitializing the object. The data is logged to ensure that the correct data is being served. This approach helps maintain the state of the data across different API routes.