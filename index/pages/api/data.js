import { redis } from '../../lib/redis';

export default async function handler(req, res) {
  try {
    const data = await redis.get('latestData');
    console.log('📤 Serving from Redis:', data);
    res.status(200).json(data || { flow: 0, total: 0 });
  } catch (err) {
    console.error('❌ Redis fetch error:', err);
    res.status(500).json({ message: 'Internal Server Error' });
  }
}
