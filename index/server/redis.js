import { createClient } from "@upstash/redis";

const redis = createClient({
  url: process.env.KV_REST_API_URL,
  token: process.env.KV_REST_API_TOKEN,
});

export default redis;
