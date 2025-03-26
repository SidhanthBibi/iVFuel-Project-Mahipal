import { redis } from "@/lib/redis";

export default async function handler(req, res) {
  try {
    const flow = await redis.get("flow") || 0;
    const total = await redis.get("total") || 0;
    console.log("📤 Serving from Redis:", { flow, total });
    res.status(200).json({ flow: parseFloat(flow), total: parseFloat(total) });
  } catch (err) {
    console.error("❌ GET Error:", err);
    res.status(500).json({ message: "Internal server error" });
  }
}
