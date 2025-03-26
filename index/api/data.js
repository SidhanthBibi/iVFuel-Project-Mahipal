// index/api/data.js

import { latestData } from './update';

export default function handler(req, res) {
  res.status(200).json(latestData);
}
