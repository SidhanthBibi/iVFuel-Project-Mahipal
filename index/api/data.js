import { redis } from '../lib/redis';

export default async function handler(req, res) {
  const cached = await redis.get('fuelData');
  const latestData = cached ? JSON.parse(cached) : { flow: 0, total: 0 };

  console.log('📤 Serving latest data:', latestData);

  res.setHeader('Content-Type', 'application/json');
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.status(200).json(latestData);
}
