import { Redis } from '@upstash/redis';

const redis = new Redis({
  url: import.meta.env.VITE_KV_REST_API_URL,
  token: import.meta.env.VITE_KV_REST_API_TOKEN,
});

export default redis;
