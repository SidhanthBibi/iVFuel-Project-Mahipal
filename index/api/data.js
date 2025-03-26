// index/api/data.js

import latestData from './dataStore.js';

export default function handler(req, res) {
  console.log("📦 Serving the latest data:", latestData);
  res.setHeader('Content-Type', 'application/json');
  res.status(200).json(latestData);
}
