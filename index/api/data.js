// index/api/data.js
import { latestData } from './update.js';  // Import the latest data from update.js

export default function handler(req, res) {
  console.log("Serving latest data:", latestData);  // Log to confirm the data being served
  res.setHeader('Content-Type', 'application/json');
  res.status(200).json(latestData);  // Serve the latest stored data
}
// In this snippet, the latestData object is imported from the update.js file, which is where the data is updated when a POST request is received. The handler function in data.js simply serves the latest data when a GET request is made to the API endpoint. This separation of concerns allows for a clear distinction between updating and serving data, making the code more modular and maintainable.