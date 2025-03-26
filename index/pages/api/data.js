import { redis } from "@/lib/redis";

export default async function handler(req, res) {
  try {
    const [flow, total] = await Promise.all([
      redis.get("flow"),
      redis.get("total"),
    ]);

    const latestData = {
      flow: parseFloat(flow) || 0,
      total: parseFloat(total) || 0,
    };

    console.log("📤 Serving the latest data:", latestData);
    res.status(200).json(latestData);
  } catch (err) {
    console.error("❌ Error in GET:", err);
    res.status(500).json({ message: "Internal server error" });
  }
}
