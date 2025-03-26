// index/api/data.js

import { latestData } from './update.js';

export default function handler(req, res) {
  res.setHeader('Content-Type', 'application/json');
  res.setHeader('Access-Control-Allow-Origin', '*'); // Optional if accessed from other domains
  res.status(200).json(latestData);
}
