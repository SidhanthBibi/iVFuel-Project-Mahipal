// index/api/data.js
import { latestData } from './update.js';

export default function handler(req, res) {
  res.setHeader('Content-Type', 'application/json');
  res.status(200).json(latestData);  // Serve the latest data here
  // index/api/data.js
console.log('Serving data:', latestData);  // Log when serving data

}
// In this snippet, we import the latestData variable from the update.js file and serve it as a JSON response when a GET request is made to the /api/data endpoint. This allows us to retrieve the latest data stored in the update.js file from a different API route.